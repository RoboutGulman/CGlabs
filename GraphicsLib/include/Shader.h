#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_filePath;
	unsigned int m_id;
	std::unordered_map<std::string, int> m_uniformLocationCache;

	int GetUniformLocation(const std::string& name);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);

public:
	Shader(const std::string& filepath);
	~Shader();

	// DONE: запретить копирование объекта
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform2f(const std::string& name, float v1, float v2);
	void SetUniform1iv(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform4f(const std::string& name, glm::vec4 value);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);
};
