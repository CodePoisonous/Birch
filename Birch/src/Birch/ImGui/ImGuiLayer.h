#pragma once

#include "Birch/Core/Layer.h"
#include "Birch/Events/ApplicationEvent.h"
#include "Birch/Events/KeyEvent.h"
#include "Birch/Events/MouseEvent.h"

namespace Birch {

	class BIRCH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}