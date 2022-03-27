#pragma once

#ifdef BC_PLATFORM_WINDOWS

extern Birch::Application* Birch::CreateApplication();

int main(int argc, char** argv)
{
	printf("Birch Engine!\n");
	auto app = Birch::CreateApplication();
	app->Run();
	delete app;
}

#endif