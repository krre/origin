#version 330 core

in vec2 vertTexCoord;
out vec4 fragColor;
uniform sampler2DRect surfaceTexture;

void main() {
    fragColor = texture(surfaceTexture, vertTexCoord);
}
