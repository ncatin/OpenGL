

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"



static float xDimension, yDimension;
static int numSumdivide;


int main(void)
{
    

    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 960, "Hello World", NULL, NULL);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSwapInterval(0);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        //test::TestTexture2D* TerrainTest;
        test::Test* currentTest = nullptr;
        //test::TestMenu* testmenu = new test::TestMenu(currentTest);
        //currentTest = testmenu;

       // testmenu->RegisterTest<test::TestClearColor>("Clear Color");
        //testmenu->RegisterTest<test::TestTexture2D>("2D Texture");
    
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f)); 
            
            /* Render here */
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
            
            ImGui::Begin("Pre-Test");
            ImGui::InputFloat("input Width", &xDimension, 5.0f, 1000.0f);
            ImGui::InputFloat("input Height", &yDimension, 5.0f, 1000.0f);
            ImGui::InputInt("Number of Subdivisions ", &numSumdivide);
            if (ImGui::Button("Render Terrain")) {
                currentTest = new test::TestTexture2D(window);
                
                std::cout << "Test Created" << std::endl;
            }
            ImGui::End();

            
            
            if (currentTest) {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender(window);
                currentTest->SetWindow(window);
                ImGui::Begin("Test");
                if (ImGui::Button("<-")) {
                    delete currentTest;
                    //currentTest = testmenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
        delete currentTest;
        /*if (currentTest != testmenu)
            delete testmenu;*/
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

