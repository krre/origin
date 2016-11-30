#version 450 core

//in vec2 UV;
//uniform sampler2D surface;

//void main() {
//    gl_FragColor = vec4(texture(surface, UV).rgb, 1.0);
//}

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    color = texture(ourTexture, TexCoord);
}
