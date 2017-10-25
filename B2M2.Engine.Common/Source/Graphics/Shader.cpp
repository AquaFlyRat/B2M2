/*
    @author Barney Wilks
*/

#include "Shader.hpp"

#include <fstream>
#include <sstream>


using namespace b2m2;

std::vector<cShader*> cShaderManager::m_shaders = std::vector<cShader*>();

cShader *cShaderManager::CreateShaderFromFile(const char* vertexPath, const char *fragmentPath) {
    cShader *shader = new cShader;
    
    shader->SetFiles(vertexPath, fragmentPath);
    shader->Compile();
    shader->Link();

    m_shaders.push_back(shader);

    return shader;
}

cShader * cShaderManager::CreateShaderFromText(const char * vertex, const char * fragment)
{
    cShader *shader = new cShader;

    shader->SetText(vertex, fragment);
    shader->Compile();
    shader->Link();

    m_shaders.push_back(shader);

    return shader;
}

std::string cShader::GetText(const char * filename)
{
    std::ifstream fileStream(filename);
    std::ostringstream buffer;
    buffer << fileStream.rdbuf();
    std::string str = buffer.str();
    return str;
}

GLuint cShader::GenShader(const std::string & text, GLenum type)
{
    const char *src = text.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, log);
        printf("Shader Error: [%s] -> %s\n", type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader", log);
        abort();
    }

    return shader;
}

void cShader::SetFiles(const char * vertexPath, const char * fragmentPath)
{
    m_vertexShader = GetText(vertexPath);
    m_fragmentShader = GetText(fragmentPath);
}

void cShader::SetText(const char * vertexShader, const char * fragmentShader)
{
    m_vertexShader = vertexShader;
    m_fragmentShader = fragmentShader;
}

void cShader::Compile()
{
    GLuint vertexShader   = GenShader(m_vertexShader, GL_VERTEX_SHADER);
    GLuint fragmentShader = GenShader(m_fragmentShader, GL_FRAGMENT_SHADER);
    m_id = glCreateProgram();
    
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void cShader::Link()
{
    glLinkProgram(m_id);
}
