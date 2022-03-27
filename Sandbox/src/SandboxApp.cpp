#include<Birch.h>

class Sandbox : public Birch::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

Birch::Application* Birch::CreateApplication()
{
	return new Sandbox();
}