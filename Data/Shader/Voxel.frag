// Rendering algorithm is based on article:
// Samuli Laine and Tero Karras.
// Efficient Sparse Voxel Octrees – Analysis, Extensions, and Implementation.
// NVIDIA Technical Report NVR-2010-001, 2010.
// https://mediatech.aalto.fi/~samuli/publications/laine2010tr1_paper.pdf
// http://code.google.com/p/efficient-sparse-voxel-octrees
#version 330 core

#if 1
#extension GL_ARB_shader_storage_buffer_object : require
layout (std430, binding = 0) buffer OctreeBuffer {
    int count;
};
#endif

struct AABB {
    vec3 min;
    vec3 max;
};

struct Ray {
    vec3 origin;
    vec3 direction;
};

const AABB aabb = AABB(vec3(-1.0, -1.0, -1.0) , vec3(1.0, 1.0, 1.0));
const uint s_max = 23u;  // Maximum scale (number of float mantissa bits)
const float epsilon = exp2(-s_max);

uniform samplerBuffer objects;
uniform usamplerBuffer octrees;

uniform vec3 backgroundColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform float ambientStrength;
uniform int objectCount;
uniform int objectStride;

out vec4 color;

Ray constructRay(in int index) {
    int offset = index * objectStride + 4;
    Ray ray;
    ray.origin = vec3(texelFetch(objects, offset++));
    vec3 startCornerPos = vec3(texelFetch(objects, offset++));
    vec3 stepW = vec3(texelFetch(objects, offset++));
    vec3 stepH = vec3(texelFetch(objects, offset));
    ray.direction = normalize(startCornerPos + stepW * gl_FragCoord.x + stepH * gl_FragCoord.y);
    return ray;
}

bool rayAABBIntersect(in Ray ray, out float tmin, out float tmax) {
    float loX = (aabb.min.x - ray.origin.x) / ray.direction.x;
    float hiX = (aabb.max.x - ray.origin.x) / ray.direction.x;

    tmin = min(loX, hiX);
    tmax = max(loX, hiX);

    float loY = (aabb.min.y - ray.origin.y) / ray.direction.y;
    float hiY = (aabb.max.y - ray.origin.y) / ray.direction.y;

    tmin = max(tmin, min(loY, hiY));
    tmax = min(tmax, max(loY, hiY));

    float loZ = (aabb.min.z - ray.origin.z) / ray.direction.z;
    float hiZ = (aabb.max.z - ray.origin.z) / ray.direction.z;

    tmin = max(tmin, min(loZ, hiZ));
    tmax = min(tmax, max(loZ, hiZ));

    return (tmin <= tmax) && (tmax > 0.0f);
}

bool castRay(in Ray ray, in int index, out vec3 color, out float distance) {
    float ray_size_coef;
    float ray_size_bias;

    uvec2 stack[s_max + 1u]; // Stack of parent voxels

    // Get rid of small ray direction components to avoid division by zero.
    float dx = (abs(ray.direction.x) < epsilon ? epsilon * sign(ray.direction.x) : ray.direction.x);
    float dy = (abs(ray.direction.y) < epsilon ? epsilon * sign(ray.direction.y) : ray.direction.y);
    float dz = (abs(ray.direction.z) < epsilon ? epsilon * sign(ray.direction.z) : ray.direction.z);

    // Precompute the coefficients of tx(x), ty(y), and tz(z).
    // The octree is assumed to reside at coordinates [1, 2].
    float tx_coef = 1.0f / -abs(dx);
    float ty_coef = 1.0f / -abs(dy);
    float tz_coef = 1.0f / -abs(dz);

    float tx_bias = tx_coef * ray.origin.x;
    float ty_bias = ty_coef * ray.origin.y;
    float tz_bias = tz_coef * ray.origin.z;

    // Select octant mask to mirror the coordinate system so
    // that ray direction is negative along each axis.
    int octant_mask = 7;
    if (dx > 0.0f) octant_mask ^= 1, tx_bias = 3.0f * tx_coef - tx_bias;
    if (dy > 0.0f) octant_mask ^= 2, ty_bias = 3.0f * ty_coef - ty_bias;
    if (dz > 0.0f) octant_mask ^= 4, tz_bias = 3.0f * tz_coef - tz_bias;

    // Initialize the active span of t-values
    float t_min = max(max(2.0f * tx_coef - tx_bias, 2.0f * ty_coef - ty_bias), 2.0f * tz_coef - tz_bias);
    float t_max = min(min(tx_coef - tx_bias, ty_coef - ty_bias), tz_coef - tz_bias);

    if (t_min > t_max || t_max < 0) {
        return false;
    }

    float h = t_max;
    t_min = max(t_min, 0.0f);
    t_max = min(t_max, 1.0f);

    // Initialize the current voxel to the first child of the root.
    int parent = 0;
    uint child_descriptor = 0u; // invalid until fetched
    int idx = 0;
    vec3 pos = vec3(1.0f, 1.0f, 1.0f);
    uint scale = s_max - 1u;
    float scale_exp2 = 0.5f; // exp2f(scale - s_max)

    if (1.5f * tx_coef - tx_bias > t_min) idx ^= 1, pos.x = 1.5f;
    if (1.5f * ty_coef - ty_bias > t_min) idx ^= 2, pos.y = 1.5f;
    if (1.5f * tz_coef - tz_bias > t_min) idx ^= 4, pos.z = 1.5f;

    // Traverse voxels along the ray as long as the current voxel
    // stays within the octree.
    while (scale < s_max) {

        // Fetch child descriptor unless it is already valid.
        if (child_descriptor == 0u) {
            uvec4 v = texelFetch(octrees, parent);
            child_descriptor = v.a << 24 | v.b << 16 | v.g << 8 | v.r;
        }

        // Determine maximum t-value of the cube by evaluating
        // tx(), ty(), and tz() at its corner.
        float tx_corner = pos.x * tx_coef - tx_bias;
        float ty_corner = pos.y * ty_coef - ty_bias;
        float tz_corner = pos.z * tz_coef - tz_bias;
        float tc_max = min(min(tx_corner, ty_corner), tz_corner);

        // Process voxel if the corresponding bit in valid mask is set
        // and the active t-span is non-empty.
        int child_shift = idx ^ octant_mask; // permute child slots based on the mirroring
        uint child_masks = child_descriptor << child_shift;

        if ((child_masks & 0x8000u) != 0u && t_min <= t_max) {
//            color = vec3(1.0, 0.0, 0.0);
//            return true;
            // Terminate if the voxel is small enough.
            if (tc_max * ray_size_coef + ray_size_bias >= scale_exp2) {
                break; // at t_min
            }

            // INTERSECT
            // Intersect active t-span with the cube and evaluate
            // tx(), ty(), and tz() at the center of the voxel.
            float tv_max = min(t_max, tc_max);
            float half = scale_exp2 * 0.5f;
            float tx_center = half * tx_coef + tx_corner;
            float ty_center = half * ty_coef + ty_corner;
            float tz_center = half * tz_coef + tz_corner;

            // Descend to the first child if the resulting t-span is non-empty.
            if (t_min <= tv_max) {
                // Terminate if the corresponding bit in the non-leaf mask is not set.
                if ((child_masks & 0x0080u) == 0u) {
                    break; // at t_min (overridden with tv_min).
                }

                // PUSH
                // Write current parent to the stack.
                if (tc_max < h) {
                    stack[scale] = uvec2(parent, floatBitsToUint(t_max));
                }

                h = tc_max;

                // Find child descriptor corresponding to the current voxel.
                uint ofs = child_descriptor >> 17; // child pointer
                if ((child_descriptor & 0x10000u) != 0u) { // far
//                        ofs = parent[ofs * 2]; // far pointer
                }

//                    ofs += popc8(child_masks & 0x7Fu);
//                    parent += ofs * 2;

                // Select child voxel that the ray enters first.
                idx = 0;
                scale--;
                scale_exp2 = half;
                if (tx_center > t_min) idx ^= 1, pos.x += scale_exp2;
                if (ty_center > t_min) idx ^= 2, pos.y += scale_exp2;
                if (tz_center > t_min) idx ^= 4, pos.z += scale_exp2;

                // Update active t-span and invalidate cached child descriptor.
                t_max = tv_max;
                child_descriptor = 0u;
                continue;
            }
        }

        // ADVANCE
        // Step along the ray.
        int step_mask = 0;
        if (tx_corner <= tc_max) step_mask ^= 1, pos.x -= scale_exp2;
        if (ty_corner <= tc_max) step_mask ^= 2, pos.y -= scale_exp2;
        if (tz_corner <= tc_max) step_mask ^= 4, pos.z -= scale_exp2;

        // Update active t-span and flip bits of the child slot index.
        t_min = tc_max;
        idx ^= step_mask;

        // Proceed with pop if the bit flips disagree with the ray direction.
        if ((idx & step_mask) != 0) {
            // POP
            // Find the highest differing bit between the two positions.
            uint differing_bits = 0u;

            if ((step_mask & 1) != 0) differing_bits |= floatBitsToUint(pos.x) ^ floatBitsToUint(pos.x + scale_exp2);
            if ((step_mask & 2) != 0) differing_bits |= floatBitsToUint(pos.y) ^ floatBitsToUint(pos.y + scale_exp2);
            if ((step_mask & 4) != 0) differing_bits |= floatBitsToUint(pos.z) ^ floatBitsToUint(pos.z + scale_exp2);
            scale = (floatBitsToUint(float(differing_bits)) >> 23) - 127u; // position of the highest bit
            scale_exp2 = uintBitsToFloat((scale - s_max + 127u) << 23); // exp2f(scale - s_max)

            // Restore parent voxel from the stack.
            uvec2 stackEntry = stack[scale];
            parent = int(stackEntry.x);
            t_max = uintBitsToFloat(stackEntry.y);

            // Round cube position and extract child slot index.
            int shx = floatBitsToInt(pos.x) >> scale;
            int shy = floatBitsToInt(pos.y) >> scale;
            int shz = floatBitsToInt(pos.z) >> scale;
            pos.x = intBitsToFloat(shx << scale);
            pos.y = intBitsToFloat(shy << scale);
            pos.z = intBitsToFloat(shz << scale);
            idx = (shx & 1) | ((shy & 1) << 1) | ((shz & 1) << 2);

            // Prevent same parent from being stored again and invalidate cached child descriptor.
            h = 0.0f;
            child_descriptor = 0u;
        }
    }

    // Indicate miss if we are outside the octree.
    if (scale >= s_max) {
        t_min = 2.0f;
    }

    // Undo mirroring of the coordinate system.
    if ((octant_mask & 1) == 0) pos.x = 3.0f - scale_exp2 - pos.x;
    if ((octant_mask & 2) == 0) pos.y = 3.0f - scale_exp2 - pos.y;
    if ((octant_mask & 4) == 0) pos.z = 3.0f - scale_exp2 - pos.z;

    // Output results.
//        hit_t = t_min;
    vec3 hit_pos;
    hit_pos.x = min(max(ray.origin.x + t_min * dx, pos.x + epsilon), pos.x + scale_exp2 - epsilon);
    hit_pos.y = min(max(ray.origin.y + t_min * dy, pos.y + epsilon), pos.y + scale_exp2 - epsilon);
    hit_pos.z = min(max(ray.origin.z + t_min * dz, pos.z + epsilon), pos.z + scale_exp2 - epsilon);
//        hit_parent = parent;
//        hit_idx = idx ^ octant_mask ^ 7;
//        hit_scale = scale;


    int offset = index * objectStride;
    vec3 ambient = ambientStrength * lightColor;
//    vec3 hitPoint = ray.origin + ray.direction * t_min;
    vec3 hitPoint = hit_pos;

    float fixPrecision = 0.00001; // for fix numbers 0.9999999 to 1.0
    vec4 hitNormalObject = vec4(int(hitPoint.x + fixPrecision), int(hitPoint.y + fixPrecision), int(hitPoint.z + fixPrecision), 0.0);
    mat4 octreeToWorld = mat4(texelFetch(objects, offset++), texelFetch(objects, offset++), texelFetch(objects, offset++), texelFetch(objects, offset));
    vec4 hitNormalWorld = normalize(octreeToWorld * hitNormalObject);
    vec3 lightDir = normalize(lightPos);
    vec3 diffuse = max(dot(vec3(hitNormalWorld), lightDir), 0.0) * lightColor;
    vec3 octreeColor = vec3(texelFetch(objects, index * objectStride + 8));
    color = (ambient + diffuse) * octreeColor;
    distance = t_min * octreeToWorld[0][0]; // t_min * scale
    return true;
}

void main() {
    vec4 outColor = vec4(backgroundColor, 1.0);
    float distanceMin = 10000;
    for (int i = 0; i < objectCount; i++) {
        Ray ray = constructRay(i);
        vec3 castColor;
        float distance;
        if (castRay(ray, i, castColor, distance)) {
            if (distance < distanceMin) {
                distanceMin = distance;
                outColor = vec4(castColor, 1.0);
            }
        }
    }

    color = outColor;
}
