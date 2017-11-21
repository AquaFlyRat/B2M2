#include "Renderer2DShader.h"

std::string arch::Renderer2DShaderText::Vertex =
"#version 330 core \n\
layout(location = 0) in vec3  position; \n\
layout(location = 1) in vec4  color; \n\
layout(location = 2) in vec2  uv;\n\
layout(location = 3) in float textureId;\n\
\n\
out vec4 passColor;\n\
out vec2 passUv;\n\
out float passTexId;\n\
\n\
uniform mat4 sys_Projection;\n\
uniform mat4 sys_View;\n\
\n\
void main() {\n\
    gl_Position = sys_Projection * sys_View * vec4(position, 1.0);\n\
\n\
    passColor = color;\n\
    passUv = uv;\n\
    passTexId = textureId;\n\
}";

std::string arch::Renderer2DShaderText::Fragment =
"#version 330 core \n\
\n\
in vec4 passColor;\n\
in vec2 passUv;\n\
in float passTexId;\n\
\n\
out vec4 outColor;\n\
\n\
uniform sampler2D sys_Textures[32];\n\
\n\
void main() {\n\
    if (passTexId < 0) {\n\
        outColor = passColor;\n\
    }\n\
    else {\n\
        int index = int(passTexId);\n\
        outColor = passColor * texture(sys_Textures[index], passUv);\n\
    }\n\
}";