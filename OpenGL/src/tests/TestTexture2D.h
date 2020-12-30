#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <GLFW/glfw3.h>
#include "Camera.h"

#include <memory>


namespace test {
	class TestTexture2D : public Test{
	public:
		TestTexture2D(GLFWwindow* window);
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender(GLFWwindow* window) override;
		void SetWindow(GLFWwindow* window) override;
		void OnImGuiRender() override;
	private:
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		GLFWwindow* context;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA;
		Camera camera;
		
	};
}
