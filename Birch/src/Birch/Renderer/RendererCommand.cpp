#include "bcpch.h"
#include "RendererCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Birch {

	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}