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
        std::string m_vertexShader, m_fragmentShader;

    private:
        std::string GetText(const char *filename);
        GLuint GenShader(const std::string& text, GLenum type);

    public:
        void SetFiles(const char *vertexPath, const char *fragmentPath);
        void SetText(const char *vertexShader, const char *fragmentShader);

        void Compile();
        void Link();

        void Bind()   { glUseProgram(m_id); }
        void Unbind() { glUseProgram(0); }

        void SubmitUniformMat4(const char *uniformName, const mat4& matrix) {
            glUniformMatrix4fv(glGetUniformLocation(m_id, uniformName), 1, GL_TRUE, matrix.Elements);
        }

        void SubmitUniform1iv(const char *uniformname, int num, int *data) {
            glUniform1iv(glGetUniformLocation(m_id, uniformname), num, data);
        }
    };

    struct cShaderManager {
    private:
        static std::vector<cShader*> m_shaders;

    public:
        static cShader *CreateShaderFromFile(const char* vertexPath, const char *fragmentPath);
        static cShader *CreateShaderFromText(const char *vertex, const char *fragment);
    };
}