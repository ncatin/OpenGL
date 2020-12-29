#pragma once
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"


class Camera {
private:
	glm::vec3 cameraPos, cameraFront, cameraUp;
	bool firstMouse;
	float yaw, pitch, lastX, lastY, fov;
public:
	Camera();
	~Camera();

	glm::mat4 getView();
	glm::vec3 getPosition();
	void processInput(GLFWwindow* window, float deltaTime);

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	
};


