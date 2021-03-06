#version 330 core

layout(location = 0) in vec3  position;
layout(location = 1) in vec4  color;
layout(location = 2) in vec2  uv;
layout(location = 3) in float textureId;

out vec4 passColor;
out vec2 passUv;
out float passTexId;

uniform mat4 sys_Projection;

void main() {
    gl_Position = sys_Projection * vec4(position, 1.0);
    
    passColor = color;
    passUv = uv;
    passTexId = textureId;
}