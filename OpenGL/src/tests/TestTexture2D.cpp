#include "TestTexture2D.h"
#include "imgui/imgui.h"
#include "Renderer.h"
#include "Vertex.h"



#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct MyCallBack {
	static Camera* cam;

	static void callback(GLFWwindow* window, double a, double b) {
		cam->mouse_callback(window, a, b);
	}
};

Camera* MyCallBack::cam = nullptr;

namespace test {

	TestTexture2D::TestTexture2D()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, 0.0f, 5.0f)),  
		m_TranslationA(0, 0, 0), m_TranslationB(400, 200, 0)
	{

		/*m_View = glm::lookAt(
			glm::vec3(10,10,10),
			glm::vec3(0,0,0),
			glm::vec3(0,0,1)
		);*/
		
		MyCallBack::cam = &camera;
		glfwSetCursorPosCallback(context, &MyCallBack::callback);
		
		m_View = camera.getView();

		std::vector<Vertex::Vertex> positions = Vertex::GenerateRectVertex();
		std::vector<unsigned int> indices = Vertex::CalculateIndices(positions);
		Vertex::CalculateNormals(positions, indices);

		std::cout << "Math done " << std::endl;

		/*float positions[] = {
			-50.f, -50.0f, 50.0f,// 0
			50.0f, -50.0f, 0.0f,// 1
			50.0f, 50.0f,  0.0f,//2
			-50.0f, 50.0f, 0.0f,// 3
		};*/
		/*unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};*/
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions.data(), sizeof(positions));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		//IndexBuffer ib(indices, 6);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices.data(), indices.size());
		
		m_Shader->Bind();
		m_Shader->SetUniformVec3("u_Color", 1.0f, 1.0f, 1.0f);
		m_Shader->SetUniformVec3("lightPos", 5.0f, 5.0f, 5.0f);
		m_Shader->SetUniformVec3("viewPos", camera.getPosition());
		m_Texture = std::make_unique<Texture>("res/textures/salem.jpg");
		//m_Shader->SetUniform1i("u_Texture", 0);
		
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender(GLFWwindow* window)
	{
		
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		//m_Texture->Bind();

		

		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			camera.processInput(window, deltaTime);
			m_View = camera.getView();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Shader->SetUniformMat4f("u_Model", model);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}


	}

	void TestTexture2D::SetWindow(GLFWwindow* window)
	{
		context = window;
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 5.0f);
		ImGui::SliderFloat3("View", &m_View[0].x, 0.0f, 5.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	

}