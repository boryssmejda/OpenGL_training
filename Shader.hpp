#ifndef SHADER_HPP
#define SHADER_HPP

#include <fstream>
#include <sstream>
#include <utility>
#include <stdexcept>
#include <string>
#include <unordered_map>

using VertexShaderSource = std::string;
using FragmentShaderSource = std::string;

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	unsigned int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	std::pair<VertexShaderSource, FragmentShaderSource> ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind();
	void Unbind();

	// Set Uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	
};

#endif // !SHADER_HPP
