#pragma once

#include "Core.h"

#include "Window.h"
#include "Birch/LayerStack.h"
#include "Events/Event.h"
#include "Birch/Events/ApplicationEvent.h"

#include "Birch/ImGui/ImGuiLayer.h"
#include "Birch/Renderer/Shader.h"
#include "Birch/Renderer/Buffer.h"
#include "Birch/Renderer/VertexArray.h"

#include "Birch/Renderer/OrthographicCamera.h"

namespace Birch
{
	class BIRCH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		 
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		
		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		orthographicCamera m_Camera;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}