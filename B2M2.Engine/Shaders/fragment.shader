#version 330 core

in vec4 passColor;
in vec2 passUv;
in float passTexId;

out vec4 outColor;

uniform sampler2D sys_Textures[32];

void main() {
    if (passTexId < 0) {
        outColor = passColor;
    }
    else {
        int index = int(passTexId);
        outColor = texture(sys_Textures[index], passUv);
    }
}