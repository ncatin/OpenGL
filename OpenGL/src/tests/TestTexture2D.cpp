#include "TestTexture2D.h"
#include "imgui/imgui.h"
#include "Renderer.h"
#include "Vertex.h"



#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct MyCallBack {
	static Camera* cam;

	static void mouse_callback(GLFWwindow* window, double a, double b) {
		cam->mouse_callback(window, a, b);
	}

	static void scroll_callback(GLFWwindow* window, double a, double b) {
		cam->scroll_callback(window, a, b);
	}
};

Camera* MyCallBack::cam = nullptr;


namespace test {

	TestTexture2D::TestTexture2D(GLFWwindow* window, int xLength=5, int zLength=5, int sub=4)
		:context(window), width(xLength), height(zLength), numDivide(sub)
	{

		
		MyCallBack::cam = &camera;
		glfwSetCursorPosCallback(context, &MyCallBack::mouse_callback);
		glfwSetScrollCallback(context, &MyCallBack::scroll_callback);

		m_View = camera.getView();
		m_Proj = camera.getProjection();
		glMatrixMode(GL_MODELVIEW);
		std::vector<Vertex::Vertex> positions = Vertex::GenerateRectVertex(width, height, numDivide);
		std::vector<unsigned int> indices = Vertex::CalculateIndices(positions, numDivide);
		Vertex::CalculateNormals(positions, indices);

		std::cout << "Math done " << std::endl;

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions.data(), positions.size()*sizeof(float)*6);
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		//IndexBuffer ib(indices, 6);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices.data(), indices.size());
		
		m_Shader->Bind();
		m_Shader->SetUniformVec3("u_Color", 1.0f, 1.0f, 1.0f);
		m_Shader->SetUniformVec3("lightPos", 2.5f, 2.5f, 5.0f);
		m_Shader->SetUniformVec3("viewPos", camera.getPosition());
		
		
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
			m_Proj = camera.getProjection();
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Shader->SetUniformMat4f("u_Model", model);
			m_Shader->SetUniformVec3("lightPos", camera.getPosition());
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}


	}

	void TestTexture2D::SetWindow(GLFWwindow* window)
	{
		context = window;
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	

}