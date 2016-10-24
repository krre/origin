#include "RenderSurface.h"
#include "../../Resource/ResourceManager.h"
#include "Octree.h"
#include "../../Core/App.h"
#include "../../ECS/Components/Components.h"
#include "../../ECS/Systems/Systems.h"
#include "../../ECS/Systems/CameraSystem.h"
#include "../../ECS/Engine.h"
#include "../../Core/Common.h"
#include "../../Core/Utils.h"

RenderSurface::RenderSurface() {
    raycastShaderGroup = ResourceManager::getInstance()->getShaderGroup("RaycastShaderGroup");
    surfaceShaderGroup = ResourceManager::getInstance()->getShaderGroup("SurfaceShaderGroup");
    program = raycastShaderGroup->getProgram();
    raycastShaderGroup->bind();

    glm::vec4 bgColor = App::getInstance()->getViewport()->getBackgroundColor();
    glm::vec2 pickPixel(-1, -1);

    glUniform1i(glGetUniformLocation(program, "pageBytes"), pageBytes);
    glUniform1i(glGetUniformLocation(program, "blockInfoEnd"), blockInfoEnd);
    glUniform3fv(glGetUniformLocation(program, "backgroundColor"), 1, &bgColor[0]);
    glUniform2fv(glGetUniformLocation(program, "pickPixel"), 1, &pickPixel[0]);

//    GLfloat vertices[] = {
//        -1.0f,  1.0f,
//        -1.0f, -1.0f,
//         1.0f,  1.0f,
//         1.0f, -1.0f,
//    };

    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left
    };

    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
//    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0); // Unbind VAO

    glGenTextures(1, &surfaceTex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, surfaceTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 800, 480, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindImageTexture(0, surfaceTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    int work_grp_cnt[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);

    printf("max global (total) work group size x: %i y: %i z: %i\n",
        work_grp_cnt[0], work_grp_cnt[1], work_grp_cnt[2]);

    int work_grp_size[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

    printf("max local (in one shader) work group sizes x: %i y: %i z: %i\n",
        work_grp_size[0], work_grp_size[1], work_grp_size[2]);

    int work_grp_inv;
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
    printf("max local work group invocations: %i\n", work_grp_inv);
}

void RenderSurface::draw(float dt) {
    int width = App::getInstance()->getWidth();
    int height = App::getInstance()->getHeight();

    OctreeSystem* octreeSystem = static_cast<OctreeSystem*>(Engine::getInstance()->getSystem(SystemType::Octree).get());
    Entity* currentCamera = App::getInstance()->getViewport()->getCurrentCamera().get();
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[ComponentType::Camera].get());
    TransformComponent* cameraTransform = static_cast<TransformComponent*>(currentCamera->components[ComponentType::Transform].get());

    TransformComponent* octreeTransform;

    TransformComponent* lightTransform;
    glm::vec3 lightColor = glm::vec3(0.0);
    glm::vec3 lightPos = glm::vec3(0.0);

    // TODO: Replace by family
    for (auto entity : Engine::getInstance()->getEntities()) {
        OctreeComponent* octreeComp = static_cast<OctreeComponent*>(entity.second->components[ComponentType::Octree].get());
        if (octreeComp) {
            octreeTransform = static_cast<TransformComponent*>(entity.second->components[ComponentType::Transform].get());
        }

        LightComponent* lightComp = static_cast<LightComponent*>(entity.second->components[ComponentType::Light].get());
        if (lightComp) {
            lightTransform = static_cast<TransformComponent*>(entity.second->components[ComponentType::Transform].get());
            lightColor = lightComp->color;
            lightPos = glm::vec3(lightTransform->objectToWorld[3]);
        }
    }

    octreeSystem->getGpuMemoryManager()->beginBatch();
    int transformCount = 0;

    for (auto imap: octreeSystem->getGpuMemoryManager()->getOctreeOffsets()) {
        std::vector<glm::vec4> transform;
        Entity* entity = Engine::getInstance()->getEntity(imap.first).get();
        TransformComponent* octreeTransform = static_cast<TransformComponent*>(entity->components[ComponentType::Transform].get());
        transform.push_back(octreeTransform->objectToWorld[0]);
        transform.push_back(octreeTransform->objectToWorld[1]);
        transform.push_back(octreeTransform->objectToWorld[2]);
        transform.push_back(octreeTransform->objectToWorld[3]);

        glm::mat4 cameraToOctree = octreeTransform->worldToObject * cameraTransform->objectToWorld;
        transform.push_back(cameraToOctree[3]);

        glm::vec4 up = cameraToOctree * cameraComp->up;
        glm::vec4 look = cameraToOctree * cameraComp->look;
        glm::vec4 right = cameraToOctree * cameraComp->right;

        // Ray calculation is based on Johns Hopkins presentation:
        // http://www.cs.jhu.edu/~cohen/RendTech99/Lectures/Ray_Casting.bw.pdf
        glm::vec4 h0 = look - up * glm::tan(cameraComp->fov); // min height vector
        glm::vec4 h1 = look + up * glm::tan(cameraComp->fov); // max height vector
        glm::vec4 stepH = (h1 - h0) / height;
        h0 += stepH / 2;

        glm::vec4 w0 = look - right * glm::tan(cameraComp->fov) * width / height; // min width vector
        glm::vec4 w1 = look + right * glm::tan(cameraComp->fov) * width / height; // max width vector
        glm::vec4 stepW = (w1 - w0) / width;
        w0 += stepW / 2;

        glm::vec4 startCornerPos = w0 + h0;

        transform.push_back(startCornerPos);
        transform.push_back(stepW);
        transform.push_back(stepH);

        octreeSystem->getGpuMemoryManager()->updateEntityTransform(entity, transform);

        if (!transformCount) {
            transformCount = transform.size();
        }
    }

    octreeSystem->getGpuMemoryManager()->endBatch();

    raycastShaderGroup->bind();

    glUniform3fv(glGetUniformLocation(program, "lightColor"), 1, &lightColor[0]);
    glUniform3fv(glGetUniformLocation(program, "lightPos"), 1, &lightPos[0]);
    glUniform1f(glGetUniformLocation(program, "ambientStrength"), 0.1f);
    glUniform1i(glGetUniformLocation(program, "octreeCount"), octreeSystem->getGpuMemoryManager()->getOctreeOffsets().size());
    glUniform1i(glGetUniformLocation(program, "transformCount"), transformCount);

    glDispatchCompute(800, 480, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    surfaceShaderGroup->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, surfaceTex);

    glBindVertexArray(vao);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

