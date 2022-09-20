#pragma once

#include "Birch.h"

class Sandbox2D : public Birch::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Birch::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Birch::Event& e) override;

private:
	Birch::OrthographicCameraController m_CameraController;

	// Temp
	Birch::Ref<Birch::Shader> m_FlatColorShader;
	Birch::Ref<Birch::VertexArray> m_SquareVA;

	Birch::Ref<Birch::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};