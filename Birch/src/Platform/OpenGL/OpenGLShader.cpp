#include "bcpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Birch {

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// ����һ���յĶ�����ɫ�����
		GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);

		// ��������ɫ��Դ�봫��GL��
		// ע�⣺string.c_str()�Կ��ַ���β
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(VertexShader, 1, &source, 0);

		// ���붥����ɫ��
		glCompileShader(VertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &isCompiled);

		// ��ɫ������ʧ�ܣ���ӡ������Ϣ
		if (GL_FALSE == isCompiled)
		{
			GLint maxLength = 0;
			glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength����NULL
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(VertexShader, maxLength, &maxLength, &infoLog[0]);

			// ɾ����ɫ��
			glDeleteShader(VertexShader);

			BC_CORE_ERROR("{0}", infoLog.data());
			BC_CORE_ASSERT(false, "Vertex Shader Compilation failure!");
			return;
		}

		// ����һ���յ�Ƭ����ɫ�����
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// ��Ƭ����ɫ��Դ�봫��GL��
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// ����Ƭ����ɫ��
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

		// ��ɫ������ʧ�ܣ���ӡ������Ϣ
		if (GL_FALSE == isCompiled)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength����NULL
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// ɾ����ɫ��
			glDeleteShader(fragmentShader);

			BC_CORE_ERROR("{0}", infoLog.data());
			BC_CORE_ASSERT(false, "Fragment Shader Compilation failure!");
			return;
		}

		// ������ɫ����Ƭ����ɫ��������ɹ�ʱ
		// ��ȡ�������
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// ����ɫ�����ӵ�������
		glAttachShader(program, VertexShader);
		glAttachShader(program, fragmentShader);

		// ���ӳ���
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

		// ����ʧ�ܣ���ӡ������Ϣ
		if (GL_FALSE == isLinked)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength����NULL
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// ɾ������
			glDeleteProgram(program);

			// ɾ����ɫ��
			glDeleteShader(VertexShader);
			glDeleteShader(fragmentShader);

			BC_CORE_ERROR("{0}", infoLog.data());
			BC_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// �ɹ�����֮����Ҫ����ɫ���ӳ����з���
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