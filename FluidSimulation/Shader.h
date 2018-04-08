#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <GL/glew.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class Shader
{
public:
    Shader() = default;
	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	~Shader();

    Shader(Shader&& other) = default;
    Shader& operator=(Shader&& other) = default;

    Shader(const Shader& other) = default;
    Shader& operator=(const Shader& other) = default;

    void Bind() const { glUseProgram(m_ProgramHandle); }
    static void Unbind() { glUseProgram(0); }

	void AddUniform(const std::string& uniformName);
    void SetUniform(const std::string& uniformName, const int value) { glUniform1i(m_Uniforms.at(uniformName), value); }
    void SetUniform(const std::string& uniformName, const float value) { glUniform1f(m_Uniforms.at(uniformName), value); }
    void SetUniform(const std::string& uniformName, const bool value) { glUniform1i(m_Uniforms.at(uniformName), value ? 1 : 0); }
    void SetUniform(const std::string& uniformName, const Vector2f& value) { glUniform2f(m_Uniforms.at(uniformName), value.X, value.Y); }
    void SetUniform(const std::string& uniformName, const Vector3f& value) { glUniform3f(m_Uniforms.at(uniformName), value.X, value.Y, value.Z); }
    void SetUniform(const std::string& uniformName, const Vector4f& value) { glUniform4f(m_Uniforms.at(uniformName), value.X, value.Y, value.Z, value.W); }

    void SetAttributeLocation(const std::string& attributeName, GLuint attributeLocation) const;

    static void FreeCache();
private:
	int m_ProgramHandle{};

	std::map<std::string, GLuint> m_Uniforms;
    static std::map<std::string, GLuint> s_ShaderCache;

	void AddShader(const std::string& filePath, GLenum shaderType) const;
	void LinkShaders() const;
    void DetachShaders() const;
};

