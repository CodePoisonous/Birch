#include "bcpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Birch {

	VertexArray* VertexArray::Creat()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		BC_CORE_ASSERTS(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		BC_CORE_ASSERTS(false, "Unknown RendererAPI!");
		return nullptr;
	}
}