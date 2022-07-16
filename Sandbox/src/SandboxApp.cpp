#include<Birch.h>

class ExampleLayer : public Birch::Layer
{
public:
	ExampleLayer(std::string layerName)
		:Layer(layerName)
	{
	}

	void OnUpdate() override
	{
		BC_INFO(m_DebugName + "::Update");
	}

	void OnEvent(Birch::Event& event) override
	{
		BC_TRACE("{0}", event);
	}

};

class Sandbox : public Birch::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer("ExampleLayer 1"));
		PushLayer(new ExampleLayer("ExampleLayer 2"));
		PushLayer(new ExampleLayer("ExampleLayer 3"));
	}
	~Sandbox() {}
};

Birch::Application* Birch::CreateApplication()
{
	return new Sandbox();
}