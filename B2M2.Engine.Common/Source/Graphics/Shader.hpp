/*
    @author Barney Wilks
*/

#pragma once

#include "../Platform/OpenGL.hpp"
#include "../Common.hpp"

#include <vector>

namespace b2m2 {
    class cShader {
    private:
        GLuint m_id;
        const char *m_vertexPath, *m_fragmentPath;
    private:
        std::string GetText(const char *filename);
        GLuint GenShader(const std::string& text, GLenum type);

    public:
        void SetFiles(const char *vertexPath, const char *fragmentPath);
        void Compile();
        void Link();

        void Bind()   { glUseProgram(m_id); }
        void Unbind() { glUseProgram(0); }

        void SubmitUniformMat4(const char *uniformName, const mat4& matrix) {
            glUniformMatrix4fv(glGetUniformLocation(m_id, uniformName), 1, GL_FALSE, &matrix[0][0]);
        }
    };

    struct cShaderManager {
    private:
        static std::vector<cShader*> m_shaders;

    public:
        static cShader *CreateShader(const char* vertexPath, const char *fragmentPath);
    };
}