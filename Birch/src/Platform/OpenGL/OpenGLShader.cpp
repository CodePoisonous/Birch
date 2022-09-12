#include "bcpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Birch {

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// 创建一个空的顶点着色器句柄
		GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);

		// 将顶点着色器源码传到GL中
		// 注意：string.c_str()以空字符结尾
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(VertexShader, 1, &source, 0);

		// 编译顶点着色器
		glCompileShader(VertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &isCompiled);

		// 着色器编译失败，打印错误信息
		if (GL_FALSE == isCompiled)
		{
			GLint maxLength = 0;
			glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength包括NULL
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(VertexShader, maxLength, &maxLength, &infoLog[0]);

			// 删除着色器
			glDeleteShader(VertexShader);

			BC_CORE_ERROR("{0}", infoLog.data());
			BC_CORE_ASSERT(false, "Vertex Shader Compilation failure!");
			return;
		}

		// 创建一个空的片段着色器句柄
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// 将片段着色器源码传到GL中
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// 编译片段着色器
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

		// 着色器编译失败，打印错误信息
		if (GL_FALSE == isCompiled)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength包括NULL
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// 删除着色器
			glDeleteShader(fragmentShader);

			BC_CORE_ERROR("{0}", infoLog.data());
			BC_CORE_ASSERT(false, "Fragment Shader Compilation failure!");
			return;
		}

		// 顶点着色器和片段着色器都编译成功时
		// 获取程序对象
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// 将着色器附加到程序中
		glAttachShader(program, VertexShader);
		glAttachShader(program, fragmentShader);

		// 链接程序
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

		// 链接失败，打印错误信息
		if (GL_FALSE == isLinked)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength包括NULL
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// 删除程序
			glDeleteProgram(program);

			// 删除着色器
			glDeleteShader(VertexShader);
			glDeleteShader(fragmentShader);

			BC_CORE_ERROR("{0}", infoLog.data());
			BC_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// 成功链接之后，需要将着色器从程序中分离
		glDetachShader(program, VertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}