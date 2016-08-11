#version 330 core

uniform sampler2DRect surfaceTexture;

void main() {
    gl_FragColor = texture(surfaceTexture, gl_FragCoord.xy);
}
