#version 330 core

in vec2 vertTexCoord;
out vec4 fragColor;
uniform sampler2D surfaceTexture;

void main() {
    fragColor = texture(surfaceTexture, vertTexCoord);
}
