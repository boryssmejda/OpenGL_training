#ifndef SHADER_HPP 
#define SHADER_HPP

#include <GL/glew.h>
#include <string>

#include "glm/glm.hpp"


class Shader
{
private:
	GLint m_ID;
	std::string readShaderSourceFromFile(const char* filepath);
	GLuint compileShader(GLenum shaderType, const std::string& source);
	void checkCompileErrors(GLuint shader, std::string type);
	void checkLinkingErrors(GLuint shader);
	GLuint linkShadersIntoProgram(GLuint vertexID, GLuint fragmentID);

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void use();

	// utility uniform function
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	inline unsigned int getShaderID() const { return m_ID; }
	void setMat4(const std::string& name, const glm::mat4& mat) const;
};

#endif