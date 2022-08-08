#include<Birch.h>

#include "imgui/imgui.h"

class ExampleLayer : public Birch::Layer
{
public:
	ExampleLayer(std::string layerName)
		:Layer(layerName)	
	{
	}

	void OnUpdate() override
	{
		if (Birch::Input::IsKeyPressed(BC_KEY_TAB))
			BC_TRACE("Tab key is pressed(poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World");
		ImGui::End();
	}

	void OnEvent(Birch::Event& event) override
	{
		if (event.GetEventType() == Birch::EventType::KeyPressed)
		{
			Birch::KeyPressedEvent& e = (Birch::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BC_KEY_TAB)
				BC_TRACE("Tab key is pressed(event)!");
			BC_TRACE("{0}", (char)e.GetKeyCode()); 
		}
	}

};

class Sandbox : public Birch::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer("ExampleLayer"));
	}
	~Sandbox() {}
};

Birch::Application* Birch::CreateApplication()
{
	return new Sandbox();
}