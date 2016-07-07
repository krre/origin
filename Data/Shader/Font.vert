#version 330 core

attribute vec4 coord;
varying vec2 texcoord;

void main() {
    gl_Position = vec4(coord.xy, 0, 1);
    texcoord = coord.zw;
}
