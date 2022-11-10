#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Birch::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Birch::Timestep ts)
{
	// update
	m_CameraController.OnUpdate(ts);

	// Render
	Birch::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });		// 设置背景颜色
	Birch::RenderCommand::clear();

	Birch::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Birch::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });		// 两个矩形的绘制
	Birch::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });

	Birch::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);	// 绘制棋盘格

	Birch::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Setting");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));	// 调色板颜色
	ImGui::End();
}

void Sandbox2D::OnEvent(Birch::Event& e)
{
	m_CameraController.OnEvent(e);
}

