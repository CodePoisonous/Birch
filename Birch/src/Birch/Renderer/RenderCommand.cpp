#include "bcpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Birch {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}