#pragma once
#include<string>
#include<unordered_map>
#include "glm/glm.hpp"

struct MyStruct
{
	std::string vertexSource;
	std::string fragmentSource;

};


class Shader {
private:
	std::string m_filepath;
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_uniorm_location_cache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void Setuniform1i(const std::string& name, int value);
	void Setuniform1f(const std::string& name, float value);
	void Setuniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetuniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	MyStruct pass(const std::string& filepath);
	unsigned int CompileShaders(unsigned int type, const std::string& source);
	unsigned int CreateShaders(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};	