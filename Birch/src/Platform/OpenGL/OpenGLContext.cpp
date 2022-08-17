#include "bcpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Birch {


	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_windowHandle(windowHandle)
	{
		BC_CORE_ASSERTS(m_windowHandle, "Window handle is null");
	}

	OpenGLContext::~OpenGLContext()
	{

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BC_CORE_ASSERTS(status, "Failed to initialize Glad!");

		BC_CORE_INFO("OpenGL Info: ");
		BC_CORE_INFO(" Vendor:{0}", glGetString(GL_VENDOR));
		BC_CORE_INFO(" Renderer:{0}", glGetString(GL_RENDERER));
		BC_CORE_INFO(" Version:{0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}