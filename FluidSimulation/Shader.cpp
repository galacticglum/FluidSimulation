#include "Shader.h"
#include "File.h"

std::map<std::string, GLuint> Shader::s_ShaderCache;

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	m_ProgramHandle = glCreateProgram();
	if (m_ProgramHandle == 0)
	{
		std::cout << "Shader::Shader: Error creating shader! Could not generate program buffer.\n";
		exit(1);
	}

	AddShader(vertexFilePath, GL_VERTEX_SHADER);
	AddShader(fragmentFilePath, GL_FRAGMENT_SHADER);
	LinkShaders();
    DetachShaders();

    GLint activeUniforms = 0;
    glGetProgramiv(m_ProgramHandle, GL_ACTIVE_UNIFORMS, &activeUniforms);

    const GLsizei bufferSize = 256;
    GLchar name[bufferSize];
    GLsizei length;

    for (int i = 0; i < activeUniforms; ++i)
    {
        glGetActiveUniformName(m_ProgramHandle, i, bufferSize, &length, name);
        AddUniform(name);
    }
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramHandle);
}

void Shader::SetAttributeLocation(const std::string& attributeName, const GLuint attributeLocation) const
{
    glBindAttribLocation(m_ProgramHandle, attributeLocation, attributeName.c_str());
}

void Shader::FreeCache()
{
    for(auto const& pair : s_ShaderCache)
    {
        glDeleteShader(pair.second);
    }
}

void Shader::AddShader(const std::string& filePath, const GLenum shaderType) const
{
    GLuint shader;
    if(s_ShaderCache.find(filePath) == s_ShaderCache.end())
    {
        std::string shaderFile = File::Read(filePath);
        shader = glCreateShader(shaderType);

        if (shader == GL_FALSE)
        {
            std::cout << "Shader::AddShader: Error creating shader! Could not generate shader buffer.\n";
            exit(1);
        }

        const char* file = shaderFile.c_str();
        glShaderSource(shader, 1, &file, nullptr);
        glCompileShader(shader);

        GLint compileStatus;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus == GL_FALSE)
        {
            GLchar shaderInfoLog[1024];
            glGetShaderInfoLog(shader, 1024, nullptr, shaderInfoLog);

            std::cout << "Shader::AddShader: Error compiling shader: \"" << filePath << "\"\n";
            std::cout << shaderInfoLog << "\n";
            exit(1);
        }

        s_ShaderCache.insert(std::pair<std::string, GLuint>(filePath, shader));
    }
    else
    {
        shader = s_ShaderCache.at(filePath);
    }
	
	glAttachShader(m_ProgramHandle, shader);
}

void Shader::LinkShaders() const
{
	glLinkProgram(m_ProgramHandle);

	GLint linkStatus;
	glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		GLchar programInfoLog[1024];
		glGetProgramInfoLog(m_ProgramHandle, 1024, nullptr, programInfoLog);

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
		glGetProgramInfoLog(m_ProgramHandle, 1024, nullptr, validationInfoLog);

		std::cout << "Shader::LinkShaders: Error validating shader program!\n";
		std::cout << validationInfoLog << "\n";
		exit(1);
	}
}

void Shader::DetachShaders() const
{ 
	for (auto const& pair : s_ShaderCache)
	{
		glDetachShader(m_ProgramHandle, pair.second);
	}
}

void Shader::AddUniform(const std::string& uniformName)
{
	GLint uniform = glGetUniformLocation(m_ProgramHandle, uniformName.c_str());
	if (uniform == -1)
	{
		std::cout << "Shader::AddUniform: Could not find uniform: " << uniformName << "!\n";
		exit(1);
	}

	m_Uniforms.insert(std::pair<std::string, GLuint>(uniformName, uniform));
}