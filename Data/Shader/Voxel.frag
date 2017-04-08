#version 450 core
// Rendering algorithm is based on article:
// Samuli Laine and Tero Karras.
// Efficient Sparse Voxel Octrees – Analysis, Extensions, and Implementation.
// NVIDIA Technical Report NVR-2010-001, 2010.
// https://mediatech.aalto.fi/~samuli/publications/laine2010tr1_paper.pdf
// http://code.google.com/p/efficient-sparse-voxel-octrees

layout(std140, binding = 0) uniform UBO {
    int shadeless;
    int pageBytes;
    int blockInfoEnd;
    int frameWidth;
    int frameHeight;
    int transformCount;

    float ambientStrength;
    float lod;

    vec4 backgroundColor;
    vec4 lightColor;
    vec4 lightPos;

    vec4 pickPixel;
} ubo;


layout (std430, binding = 1) buffer Octree {
    uint data[];
} octree;

layout (std430, binding = 2) buffer RenderList {
    int count;
    uint offsets[];
} renderList;


layout (std430, binding = 3) buffer PickResult {
    vec3 pos;
    uint parent;
    uint scale;
    int childIdx;
} pickResult;


layout (std430, binding = 4) buffer DebugOut {
    vec4 debugVec;
    int debugInt;
    float debugFloat;
} debugOut;

struct Ray {
    vec3 origin;
    vec3 direction;
    float ray_size_coef;
    float ray_size_bias;
};

struct CastResult {
    float t;
    vec3 pos;
    vec4 normal;
    uint node;
    int childIdx;
    uint scale;
};

const uint s_max = 23u;  // Maximum scale (number of float mantissa bits)
const float epsilon = exp2(-s_max);

uvec2 stack[s_max + 1u]; // Stack of parent voxels

layout (location = 0) out vec4 fragColor;

Ray constructRay(in int index) {
    int offset = int(renderList.offsets[index] + ubo.pageBytes) / 4 - ubo.transformCount * 4;
    offset += 16; // skip octreeToWorld matrix
    Ray ray;

    float v[4];
    for (int i = 0; i < 4; i++) {
        v[i] = uintBitsToFloat(octree.data[offset++]);
    }
    ray.origin = vec3(v[0], v[1], v[2]);

    for (int i = 0; i < 4; i++) {
        v[i] = uintBitsToFloat(octree.data[offset++]);
    }
    vec3 startCornerPos = vec3(v[0], v[1], v[2]);

    for (int i = 0; i < 4; i++) {
        v[i] = uintBitsToFloat(octree.data[offset++]);
    }
    vec3 stepW = vec3(v[0], v[1], v[2]);

    for (int i = 0; i < 4; i++) {
        v[i] = uintBitsToFloat(octree.data[offset++]);
    }
    vec3 stepH = vec3(v[0], v[1], v[2]);

    ray.direction = normalize(startCornerPos + stepW * gl_FragCoord.x + stepH * gl_FragCoord.y);
    return ray;
}

bool castRay(in int index, in Ray ray, out CastResult castRes) {
    float ray_size_coef = 0;
    float ray_size_bias = 0;
     // Shift origin at (1.5, 1.5, 1.5) to follow reside octree at [1, 2]
    vec3 origin = ray.origin + vec3(1.5);

    // Precompute the coefficients of tx(x), ty(y), and tz(z).
    // The octree is assumed to reside at coordinates [1, 2].
    vec3 t_coef = 1.0 / -abs(ray.direction);
    vec3 t_bias = t_coef * origin;


    // Select octant mask to mirror the coordinate system so
    // that ray direction is negative along each axis.
    int octant_mask = 7;
    if (ray.direction.x > 0.0) octant_mask ^= 1, t_bias.x = 3.0 * t_coef.x - t_bias.x;
    if (ray.direction.y > 0.0) octant_mask ^= 2, t_bias.y = 3.0 * t_coef.y - t_bias.y;
    if (ray.direction.z > 0.0) octant_mask ^= 4, t_bias.z = 3.0 * t_coef.z - t_bias.z;

    // Initialize the active span of t-values
    float t_min = max(max(2.0 * t_coef.x - t_bias.x, 2.0 * t_coef.y - t_bias.y), 2.0 * t_coef.z - t_bias.z);
    float t_max = min(min(t_coef.x - t_bias.x, t_coef.y - t_bias.y), t_coef.z - t_bias.z);

    if (t_min > t_max || t_max < 0) {
        return false;
    }

    float h = t_max;
    t_min = max(t_min, 0.0);
//    t_max = min(t_max, 1.0);

    // Initialize the current voxel to the first child of the root.
    uint parent = uint(renderList.offsets[index] / 4 + 1);
    uint child_descriptor = 0u; // invalid until fetched
    int idx = 0;
    vec3 pos = vec3(1.0);
    uint scale = s_max - 1u;
    float scale_exp2 = 0.5; // exp2f(scale - s_max)

    if (1.5 * t_coef.x - t_bias.x > t_min) idx ^= 1, pos.x = 1.5;
    if (1.5 * t_coef.y - t_bias.y > t_min) idx ^= 2, pos.y = 1.5;
    if (1.5 * t_coef.z - t_bias.z > t_min) idx ^= 4, pos.z = 1.5;

    // Traverse voxels along the ray as long as the current voxel
    // stays within the octree.
    while (scale < s_max) {
        // Fetch child descriptor unless it is already valid.
        if (child_descriptor == 0u) {
            child_descriptor = octree.data[int(parent)];
        }

        // Determine maximum t-value of the cube by evaluating
        // tx(), ty(), and tz() at its corner.
        vec3 t_corner = pos * t_coef - t_bias;
        float tc_max = min(min(t_corner.x, t_corner.y), t_corner.z);

//        if (gl_FragCoord.x == ubo.frameWidth / 2 + 0.5 && gl_FragCoord.y == ubo.frameHeight / 2 + 0.5) {
//            debugOut.debugVec = vec4(pos, 1.0);
//        }

        // Process voxel if the corresponding bit in valid mask is set
        // and the active t-span is non-empty.
        int child_shift = idx ^ octant_mask; // permute child slots based on the mirroring
        uint child_masks = child_descriptor << child_shift;

        if ((child_masks & 0x8000u) != 0u && t_min <= t_max) {
            // Terminate if the voxel is small enough.
//            if (tc_max * ray_size_coef + ray_size_bias >= scale_exp2) {
//            if (gl_FragCoord.x == ubo.frameWidth / 2 + 0.5 && gl_FragCoord.y == ubo.frameHeight / 2 + 0.5) {
//                debugFloat = ubo.lod * tc_max;
//            }
            if (ubo.lod * tc_max  >= scale_exp2) {
                break; // at t_min
            }

            // INTERSECT
            // Intersect active t-span with the cube and evaluate
            // tx(), ty(), and tz() at the center of the voxel.
            float tv_max = min(t_max, tc_max);
            float half_scale_exp2 = scale_exp2 * 0.5;
            vec3 t_center = half_scale_exp2 * t_coef + t_corner;

            // Descend to the first child if the resulting t-span is non-empty.
            if (t_min <= tv_max) {
                // Terminate if the corresponding bit in the non-leaf mask is not set.
                if ((child_masks & 0x0080u) == 0u) break; // at t_min (overridden with tv_min).

                // PUSH
                // Write current parent to the stack.
                if (tc_max < h) {
                    stack[scale] = uvec2(parent, floatBitsToUint(t_max));
                }

                h = tc_max;

                // Find child descriptor corresponding to the current voxel.
                uint ofs = child_descriptor >> 17; // child pointer
                if ((child_descriptor & 0x10000u) != 0u) { // far
                    ofs += parent; // far pointer
                }

                ofs += bitCount(child_masks & 0x7F);
                parent += ofs;

                // Select child voxel that the ray enters first.
                idx = 0;
                scale--;
                scale_exp2 = half_scale_exp2;
                if (t_center.x > t_min) idx ^= 1, pos.x += scale_exp2;
                if (t_center.y > t_min) idx ^= 2, pos.y += scale_exp2;
                if (t_center.z > t_min) idx ^= 4, pos.z += scale_exp2;

                // Update active t-span and invalidate cached child descriptor.
                t_max = tv_max;
                child_descriptor = 0u;
                continue;
            }
        }

        // ADVANCE
        // Step along the ray.
        int step_mask = 0;
        if (t_corner.x <= tc_max) step_mask ^= 1, pos.x -= scale_exp2;
        if (t_corner.y <= tc_max) step_mask ^= 2, pos.y -= scale_exp2;
        if (t_corner.z <= tc_max) step_mask ^= 4, pos.z -= scale_exp2;

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
            parent = stackEntry.x;
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
            h = 0.0;
            child_descriptor = 0u;
        }
    }

    // Indicate miss if we are outside the octree.
    if (scale >= s_max) {
        return false;
    }

    // Undo mirroring of the coordinate system.
    if ((octant_mask & 1) == 0) pos.x = 3.0 - scale_exp2 - pos.x;
    if ((octant_mask & 2) == 0) pos.y = 3.0 - scale_exp2 - pos.y;
    if ((octant_mask & 4) == 0) pos.z = 3.0 - scale_exp2 - pos.z;

    // Take vector from center of voxel to hit point, convert to prevailing axis direction and use as voxel normal
    vec3 hitPoint = origin + ray.direction * t_min;
    vec3 centerToHit = hitPoint - (pos + scale_exp2 * 0.5); // vector
    float maxDir = max(abs(centerToHit.x), max(abs(centerToHit.y), abs(centerToHit.z)));
    vec3 axisDir = vec3(int(centerToHit.x / maxDir), int(centerToHit.y / maxDir), int(centerToHit.z / maxDir));

    castRes.normal = vec4(axisDir, 0.0);
    castRes.node = parent;
    castRes.childIdx = idx ^ octant_mask ^ 7;
    castRes.scale = scale;
    castRes.pos = pos;
    castRes.t = t_min;

    return true;
}

vec4 lookupColor(in int index, in CastResult castRes) {
    int px = floatBitsToInt(castRes.pos.x);
    int py = floatBitsToInt(castRes.pos.y);
    int pz = floatBitsToInt(castRes.pos.z);

    // Current position in tree
    uint node  = castRes.node;
    int cidx  = castRes.childIdx;
    uint level = castRes.scale;

    // Clear lower 11 bits.
    // Same as uint(-ubo.pageBytes) / 4, however this formula gives different result on Windows and Linux,
    // so simple do hardcode.
    uint pageHeader = node & 0xFFFFF800;

    uint blockInfo = pageHeader + octree.data[pageHeader];
    int attachData = int(blockInfo) + ubo.blockInfoEnd;
    uint paletteNode = octree.data[attachData + int(node) - renderList.offsets[index] / 4 - 1];

    // While node has no color, loop
    while ((int(paletteNode >> cidx) & 1) != 1) {
        level++;
        if (level >= s_max) {
            return vec4(0.0, 0.0, 0.0, 1.0);
        }

        node = stack[level].x;
        cidx = 0;
        if ((px & (1 << level)) != 0) cidx |= 1;
        if ((py & (1 << level)) != 0) cidx |= 2;
        if ((pz & (1 << level)) != 0) cidx |= 4;

        pageHeader = node & 0xFFFFF800; // Clear lower 11 bits.
        blockInfo = pageHeader + int(octree.data[pageHeader]);
        attachData = int(blockInfo) + ubo.blockInfoEnd;
        paletteNode = octree.data[attachData + int(node) - renderList.offsets[index] / 4 - 1];
    }

    // Found, return it
    int attachOffset = attachData + int(paletteNode >> 8) + bitCount(paletteNode & (1 << cidx) - 1);
    int c = int(octree.data[attachOffset]);
    int r = (c >> 16) & 0xFF;
    int g = (c >> 8) & 0xFF;
    int b = c & 0xFF;
    float d = 255.0; // On Windows division like v.b / 255.0 rises runtime error
    vec3 octreeColor = vec3(r / d, g / d, b / d);

    if (ubo.shadeless == 1) {
        return vec4(octreeColor, 1.0);
    }

    int offset = int(renderList.offsets[index] + ubo.pageBytes) / 4 - ubo.transformCount * 4;
    float v[16];
    for (int i = 0; i < 16; i++) {
        v[i] = uintBitsToFloat(octree.data[offset++]);
    }
    vec4 col0 = vec4(v[0], v[1], v[2], v[3]);
    vec4 col1 = vec4(v[4], v[5], v[6], v[7]);
    vec4 col2 = vec4(v[8], v[9], v[10], v[11]);
    vec4 col3 = vec4(v[12], v[13], v[14], v[15]);
    mat4 octreeToWorld = mat4(col0, col1, col2, col3);

    vec3 ambient = ubo.ambientStrength * vec3(ubo.lightColor);
    vec4 hitNormalWorld = normalize(octreeToWorld * castRes.normal);
    vec3 lightDir = vec3(normalize(ubo.lightPos));
    vec3 diffuse = max(dot(vec3(hitNormalWorld), lightDir), 0.0) * vec3(ubo.lightColor);
    vec3 color = (ambient + diffuse) * octreeColor;

    return vec4(color, 1.0);
}

void main() {
    CastResult outCastRes;
    outCastRes.node = 0u;
    float t = 10000;
    int index = -1;
    for (int i = 0; i < renderList.count; i++) {
        Ray ray = constructRay(i);
        // Take near to camera t
        CastResult castRes;
        if (castRay(i, ray, castRes)) {
            int offset = int(renderList.offsets[i] + ubo.pageBytes) / 4 - ubo.transformCount * 4;
            float octreeScale = uintBitsToFloat(octree.data[offset]);
            float real_t = castRes.t * octreeScale;
            if (real_t < t) {
                t = real_t;
                index = i;
                outCastRes = castRes;
            }
        }
    }

    if (gl_FragCoord.y == (ubo.pickPixel.y + 0.5) && gl_FragCoord.x == (ubo.pickPixel.x + 0.5)) { // For OctreeFarm pick node
        pickResult.parent = outCastRes.node;
        if (pickResult.parent != 0u) {
            pickResult.pos = outCastRes.pos;
            pickResult.scale = outCastRes.scale;
            pickResult.childIdx = outCastRes.childIdx;
        }
    }

    if (index != -1) {
        fragColor = lookupColor(index, outCastRes);
    } else {
        fragColor = ubo.backgroundColor;
    }

//    if (gl_FragCoord.x == ubo.frameWidth / 2 + 0.5 && gl_FragCoord.y == ubo.frameHeight / 2 + 0.5) {
//        color = vec4(1.0, 0.0, 0.0, 1.0);
//    }
}
