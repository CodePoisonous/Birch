#pragma once

#ifdef BC_PLATFORM_WINDOWS

extern Birch::Application* Birch::CreateApplication();

int main(int argc, char** argv)
{
	Birch::Log::Init();
	BC_CORE_WARN("Initialized Log!");
	int a = 5;
	BC_CORE_INFO("Hello! Var={0}", a);

	auto app = Birch::CreateApplication();
	app->Run();
	delete app;
}

#endif