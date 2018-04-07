#include "Shader.h"
#include "File.h"

Shader::Shader(std::string vertexFilePath, std::string fragmentFilePath)
{
	m_ProgramHandle = glCreateProgram();
	if (m_ProgramHandle == 0)
	{
		std::cout << "Shader::Shader: Error creating shader! Could not generate program buffer.\n";
		exit(1);
	}

	this->AddShader(vertexFilePath, GL_VERTEX_SHADER);
	this->AddShader(fragmentFilePath, GL_FRAGMENT_SHADER);
	this->LinkShaders();
	this->DeleteShaders();
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramHandle);
}

void Shader::AddShader(std::string filePath, GLenum shaderType)
{
	std::string shaderFile = File::Read(filePath);
	int shader = glCreateShader(shaderType);
	if (shader == GL_FALSE)
	{
		std::cout << "Shader::AddShader: Error creating shader! Could not generate shader buffer.\n";
		exit(1);
	}

	const char* file = shaderFile.c_str();
	glShaderSource(shader, 1, &file, NULL);
	glCompileShader(shader);

	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		GLchar shaderInfoLog[1024];
		glGetShaderInfoLog(shader, 1024, NULL, shaderInfoLog);

		std::cout << "Shader::AddShader: Error compiling shader!\n";
		std::cout << shaderInfoLog << "\n";
		exit(1);
	}

	glAttachShader(m_ProgramHandle, shader);
	this->m_Shaders.push_back(shader);
}

void Shader::LinkShaders()
{
	glLinkProgram(m_ProgramHandle);

	GLint linkStatus;
	glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &linkStatus);
	if (linkStatus = GL_FALSE)
	{
		GLchar programInfoLog[1024];
		glGetProgramInfoLog(m_ProgramHandle, 1024, NULL, programInfoLog);

		std::cout << "Shader::LinkShaders: Error linking shader program!\n";
		std::cout << programInfoLog << "\n";
		exit(1);
	}

	glValidateProgram(m_ProgramHandle);

	GLint validationStatus;
	glGetProgramiv(m_ProgramHandle, GL_VALIDATE_STATUS, &validationStatus);
	if (validationStatus == GL_FALSE)
	{
		GLchar validationInfoLog[1024];
		glGetProgramInfoLog(m_ProgramHandle, 1024, NULL, validationInfoLog);

		std::cout << "Shader::LinkShaders: Error validating shader program!\n";
		std::cout << validationInfoLog << "\n";
		exit(1);
	}
}

void Shader::DeleteShaders()
{
	for (GLuint shader : this->m_Shaders)
	{
		glDetachShader(m_ProgramHandle, shader);
		glDeleteShader(shader);
	}
}

void Shader::AddUniform(const std::string& uniformName)
{
	GLuint uniform = glGetUniformLocation(m_ProgramHandle, uniformName.c_str());
	if (uniform == -1)
	{
		std::cout << "Shader::AddUniform: Could not find uniform: " << uniformName << "!\n";
		exit(1);
	}

	this->m_Uniforms.insert(std::pair<std::string, GLuint>(uniformName, uniform));
}