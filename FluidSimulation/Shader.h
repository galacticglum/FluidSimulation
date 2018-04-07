#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class Shader
{
public:
	Shader(std::string vertexFilePath, std::string fragmentFilePath);
	~Shader();

	inline void Start() { glUseProgram(m_ProgramHandle); }
	inline void Stop() { glUseProgram(0); }

	void AddUniform(const std::string& uniformName);
	inline void SetUniform(const std::string& uniformName, int value) { glUniform1i(m_Uniforms.at(uniformName), value); }
	inline void SetUniform(const std::string& uniformName, float value) { glUniform1f(m_Uniforms.at(uniformName), value); }
	inline void SetUniform(const std::string& uniformName, bool value) { glUniform1i(m_Uniforms.at(uniformName), value ? 1 : 0); }
	inline void SetUniform(const std::string& uniformName, const Vector2f& value) { glUniform2f(m_Uniforms.at(uniformName), value.X, value.Y); }
	inline void SetUniform(const std::string& uniformName, const Vector3f& value) { glUniform3f(m_Uniforms.at(uniformName), value.X, value.Y, value.Z); }
	inline void SetUniform(const std::string& uniformName, const Vector4f& value) { glUniform4f(m_Uniforms.at(uniformName), value.X, value.Y, value.Z, value.W); }

	inline void SetAttributeLocation(const std::string& attributeName, GLuint attributeLocation) { glBindAttribLocation(m_ProgramHandle, attributeLocation, attributeName.c_str()); }
private:
	int m_ProgramHandle;

	std::vector<GLuint> m_Shaders;
	std::map<std::string, GLuint> m_Uniforms;

	void AddShader(std::string filePath, GLenum shaderType);
	void LinkShaders();
	void DeleteShaders();
};

