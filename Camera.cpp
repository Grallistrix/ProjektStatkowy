#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}
void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader,
	const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	view = glm::lookAt(Position, Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height,
		nearPlane, farPlane);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE,
		glm::value_ptr(projection * view));
}

glm::vec3 Camera::RetOrientNormV3() {
	glm::vec2 xyOrient(Orientation.x, Orientation.y);
	xyOrient = glm::normalize(xyOrient);

	return glm::vec3(xyOrient, 0);
}
glm::vec2 Camera::RetOrientNormV2() {
	glm::vec2 xyOrient(Orientation.x, Orientation.y);
	xyOrient = glm::normalize(xyOrient);

	return xyOrient;
}

float Camera::focusDistance() {
	float wynik = sqrt(pow(Position.x * Orientation.x, 2) + pow(Position.y * Orientation.y, 2));

	return wynik;
}


void Camera::Inputs(GLFWwindow* window)
{
	// Obsluga klawiszy
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && wPress) {

		glm::vec2 newPos = RetOrientNormV2();
		Orientation += glm::vec3(newPos, 0);
		Position += speed * glm::vec3(newPos, 0);

		std::cout << "w\n";
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && sPress)
	{

		glm::vec2 newPos = RetOrientNormV2();
		Orientation += glm::vec3(newPos, 0);
		Position += -speed * glm::vec3(newPos, 0);

		std::cout << "s\n";
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && aPress)
	{
		Orientation = glm::rotate(Orientation, glm::radians(1.0f), Up);

		std::cout << "a\n";
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && dPress)
	{
		Orientation = glm::rotate(Orientation, glm::radians(-1.0f), Up);
		std::cout << "d\n";
	}


	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position.z += 0.05;
		std::cout << "space\n";
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position.z += -0.05;
		std::cout << "l_ctrl\n";
	}

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		glm::vec3 RotateAround = glm::cross(Orientation, Up);
		Orientation = glm::rotate(Orientation, glm::radians(1.0f), RotateAround);
		std::cout << "k\n";
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		glm::vec3 RotateAround = glm::cross(Orientation, Up);
		Orientation = glm::rotate(Orientation, glm::radians(-1.0f), RotateAround);
		std::cout << "l\n";
	}
}