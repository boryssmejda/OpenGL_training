#include "Shader.hpp"
#include "GL/glew.h"
#include "Renderer.hpp"
#include <iostream>

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int success;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

    if (GL_FALSE == success)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        std::string infolog(length, '\0');
        std::cout << "Compilation failed!\n";
        GLCall(glGetShaderInfoLog(id, length, &length, &infolog[0]));
        std::cout << infolog << '\n';
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

std::pair<VertexShaderSource, FragmentShaderSource> Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    if (!stream)
    {
        throw std::runtime_error("Could not open the file!");
    }
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[static_cast<int>(type)] << line << '\n';
        }

    }

    return {
            ss[static_cast<int>(ShaderType::VERTEX)].str(),
            ss[static_cast<int>(ShaderType::FRAGMENT)].str()
    };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program;
    GLCall(program = glCreateProgram());
    unsigned int vs, fs;
    GLCall(vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
    GLCall(fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

Shader::Shader(const std::string& filepath)
	: m_FilePath{ filepath }, m_RendererID{ 0 }
{
    auto [vertexShaderSource, fragmentShaderSource] = ParseShader(filepath);
    m_RendererID = CreateShader(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];


    int location;
    GLCall(location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (-1 == location)
    {
        std::cout << "Warning: uniform " << name << "doesn't exist!\n";
    }
    
    m_UniformLocationCache[name] = location;
    
    return location;
}