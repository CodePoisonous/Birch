#include "bcpch.h"
#include "Shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Birch {

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
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
			BC_CORE_ASSERTS(false, "Vertex Shader Compilation failure!");
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
			BC_CORE_ASSERTS(false, "Fragment Shader Compilation failure!");
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
			BC_CORE_ASSERTS(false, "Shader link failure!");
			return;
		}

		// �ɹ�����֮����Ҫ����ɫ���ӳ����з���
		glDetachShader(program, VertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}