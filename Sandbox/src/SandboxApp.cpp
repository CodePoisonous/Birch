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
		PushLayer(new ExampleLayer("ExampleLayer"));

		PushLayer(new Birch::ImGuiLayer());
	}
	~Sandbox() {}
};

Birch::Application* Birch::CreateApplication()
{
	return new Sandbox();
}