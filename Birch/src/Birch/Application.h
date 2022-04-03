#pragma once

#include "Core.h"

namespace Birch
{
	class BIRCH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}