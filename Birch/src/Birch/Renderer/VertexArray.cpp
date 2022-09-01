#include "bcpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Birch {

	VertexArray* VertexArray::Creat()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	BC_CORE_ASSERTS(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		BC_CORE_ASSERTS(false, "Unknown RendererAPI!");
		return nullptr;
	}
}