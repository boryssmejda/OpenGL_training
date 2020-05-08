#include "Shader.hpp"
#include "debugHelper.hpp"

#include <fstream>
#include <iostream>
#include <sstream>


std::string Shader::readShaderSourceFromFile(const char* filepath)
{
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	shaderFile.open(filepath);
	std::stringstream ss;

	ss << shaderFile.rdbuf();
	shaderFile.close();

	return ss.str();
}

GLuint Shader::compileShader(GLenum shaderType, const std::string& source)
{
	GLuint shaderID = glCreateShader(shaderType);
	const char* src = source.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);
	glCheckError();

	return shaderID;
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	int success;
	char infolog[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(infolog), nullptr, infolog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" 
			<< infolog << '\n';
	}

	glCheckError();
}

void Shader::checkLinkingErrors(GLuint shader)
{
	int success;
	char infolog[1024];
	glCheckError();

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	glCheckError();
	if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(infolog), nullptr, infolog);
		glCheckError();
		std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM\n"
			<< infolog << '\n';
	}

	glCheckError();
}

GLuint Shader::linkShadersIntoProgram(GLuint vertexID, GLuint fragmentID)
{
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);
	glCheckError();

	return programID;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	try
	{
		vertexCode   = readShaderSourceFromFile(vertexPath);
		fragmentCode = readShaderSourceFromFile(fragmentPath);
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::cout << e.what() << '\n';
	}

	GLuint vertexID	  = compileShader(GL_VERTEX_SHADER, vertexCode);
	checkCompileErrors(vertexID, "VERTEX");

	GLuint fragmentID = compileShader(GL_FRAGMENT_SHADER, fragmentCode);
	checkCompileErrors(fragmentID, "FRAGMENT");

	m_ID = linkShadersIntoProgram(vertexID, fragmentID);
	checkLinkingErrors(m_ID);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Shader::use()
{
	glUseProgram(m_ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), static_cast<int>(value));
	glCheckError();
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	glCheckError();
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	glCheckError();
}
