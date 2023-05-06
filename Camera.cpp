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

float Camera::focusDistance(){
	float wynik = sqrt(pow(Position.x * Orientation.x, 2) + pow(Position.y * Orientation.y, 2));

	return wynik;

}

void Camera::sanitizeDistance() {
	if (focusDistance() > 1000) {
		Orientation.x /= 10;
		Orientation.y /= 10;
	}
}


void Camera::Inputs(GLFWwindow* window)
{

	// Obsluga klawiszy
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && wPress){
		wPress = false;

		
     	glm::vec2 newPos = RetOrientNormV2();
		Orientation += glm::vec3(newPos, 0);
		Position += speed * glm::vec3(newPos, 0);
		sanitizeDistance();
	
		std::cout << "w\n";
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && sPress)
	{
		sPress = false;
		if (firstMove) {
			Orientation.x *= 2;
			Orientation.y *= 2;
			firstMove = false;
		}
		glm::vec2 newPos = RetOrientNormV2();
		Orientation += glm::vec3(newPos, 0);
		Position += -speed * glm::vec3(newPos, 0);
		sanitizeDistance();
		

		std::cout << "s\n";
	}	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && aPress)
	{
		aPress = false;
		Orientation = glm::rotate(Orientation, glm::radians(36.0f), Up);
	
		std::cout << "a\n";
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && dPress)
	{
		dPress = false;
		Orientation = glm::rotate(Orientation, glm::radians(-36.0f), Up);
		std::cout << "d\n";
	}

	//Obs³uga release w celu pojedyñczych akcji
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
		wPress = true;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
		sPress = true;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
		aPress = true;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
		dPress = true;


	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position.z += 0.01;
		//Orientation.z += 0.01;
		std::cout << "space\n";
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position.z += -0.01;
		//Orientation.z += -0.01;
		std::cout << "l_ctrl\n";
	}
	
}