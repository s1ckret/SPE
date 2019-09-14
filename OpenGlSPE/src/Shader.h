#pragma once
#include <string>
#include "GL\glew.h"
#include <unordered_map>

struct ShaderProgram {
	std::string VertexShader;
	std::string FragmentShader;
};


class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	unsigned int GetUniformLocation(const std::string& name);

	ShaderProgram ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string & vertexShader, const std::string& fragmentShader);

private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_LocationCache;

};