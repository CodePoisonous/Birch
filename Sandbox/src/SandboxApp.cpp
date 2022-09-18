#include <Birch.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Birch::Layer
{
public:
	ExampleLayer(std::string layerName)
		:Layer(layerName), m_CameraController(1280.0f / 720.0f, true)
	{
		// 矩形
		m_SquareVA.reset(Birch::VertexArray::Creat());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Birch::Ref<Birch::VertexBuffer> squareVB;
		squareVB.reset(Birch::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Birch::ShaderDataType::Float3, "a_Position"},
			{Birch::ShaderDataType::Float2, "a_TexCoord"}
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
		Birch::Ref<Birch::IndexBuffer> squareIB;
		squareIB.reset(Birch::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string flatColorShaderVertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				
				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;

				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}

		)";
		std::string flatColorShaderFragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;
				
				in vec3 v_Position;

				uniform vec3 u_Color;

				void main()
				{
					color = vec4(u_Color, 1.0);
				}

		)";
		m_FlatColorShader = Birch::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		
		auto TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Birch::Texture2D::Create("assets/textures/Checkerboard.png");
		m_BirchLogoTexture = Birch::Texture2D::Create("assets/textures/Logo.png");

		std::dynamic_pointer_cast<Birch::OpenGLShader>(TextureShader)->Bind();
		std::dynamic_pointer_cast<Birch::OpenGLShader>(TextureShader)->UploadUniformInt("u_Texture", 0);
		
		// 三角形
		m_VertexArray.reset(Birch::VertexArray::Creat());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Birch::Ref<Birch::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Birch::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{ Birch::ShaderDataType::Float3, "a_Position" },
			{ Birch::ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Birch::Ref<Birch::IndexBuffer> indexBuffer;
		indexBuffer.reset(Birch::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}

		)";
		std::string fragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;				
				
				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position * 0.5 + 0.5, 1.0);
					color = v_Color;
				}

		)";
		m_Shader = Birch::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
	}

	void OnUpdate(Birch::Timestep ts) override
	{
		// update
		m_CameraController.OnUpdate(ts);

		// Render
		Birch::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Birch::RenderCommand::clear();

		Birch::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Birch::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Birch::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Birch::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Birch::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_BirchLogoTexture->Bind();
		Birch::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// 三角形
		//Birch::Renderer::Submit(m_Shader, m_VertexArray);

		Birch::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Birch::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Birch::ShaderLibrary m_ShaderLibrary;
	Birch::Ref<Birch::Shader> m_Shader;
	Birch::Ref<Birch::VertexArray> m_VertexArray;

	Birch::Ref<Birch::Shader> m_FlatColorShader;
	Birch::Ref<Birch::VertexArray> m_SquareVA;

	Birch::Ref<Birch::Texture2D> m_Texture, m_BirchLogoTexture;
	
	Birch::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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