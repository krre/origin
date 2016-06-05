#version 330 core

//layout(location = 0) in vec4 vPosition;

void main() {
    //gl_Position = vPosition;
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    gl_PointSize = 10.0;
}
