#version 330 core
//layout (location = 0) in vec2 position;
//layout (location = 1) in vec2 vertexUV;
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

//out vec2 UV;

//void main() {
//    gl_Position = vec4(position, 0.0f, 1.0f);
//    UV = vertexUV;
//}

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0f);
    ourColor = color;
    TexCoord = texCoord;
}
