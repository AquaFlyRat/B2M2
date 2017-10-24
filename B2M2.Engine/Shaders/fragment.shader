#version 330 core

in vec4 passColor;
in vec2 passUv;
in float passTexId;

out vec4 outColor;

void main() {
    outColor = passColor;
}