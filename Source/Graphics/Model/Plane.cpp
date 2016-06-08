#include "Plane.h"

Plane::Plane(int width, int height) : width(width), height(height),
        vertexShader(GL_VERTEX_SHADER),
        fragmentShader(GL_FRAGMENT_SHADER),
        buffer(GL_ARRAY_BUFFER) {
    vertexShader.load("Base.vs");
    fragmentShader.load("Base.fs");

    programShader.addShader(vertexShader);
    programShader.addShader(fragmentShader);
    programShader.link();
    programShader.use();

    const GLfloat data[] = { -1.0f, -1.0f, 0.0f,
                            1.0f, -1.0f, 0.0f,
                            1.0f,  1.0f, 0.0f,

                            -1.0f,  1.0f, 0.0f,
                            -1.0f,  -1.0f, 0.0f,
                            1.0f,  1.0f, 0.0f,
                           };
    buffer.setData(data, sizeof(data));

    matrix = glGetUniformLocation(programShader.getId(), "mvp");
    glm::mat4 projection = glm::perspective(glm::radians(70.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 view = glm::lookAt(
                                glm::vec3(0, 0, 2), // Camera is at (4,3,3), in World Space
                                glm::vec3(0, 0, 0), // and looks at the origin
                                glm::vec3(0, 1, 0));  // Head is up (set to 0,-1,0 to look upside-down)

    glm::mat4 model = glm::mat4(1.0f);
    mvp = projection * view * model;
}

void Plane::draw() {
//    print("draw plane");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.getId());
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
}
