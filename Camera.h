#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "ShaderClass.h"

class Camera
{
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 Orientation = glm::vec3(-2.0f, -3.0f, 1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 0.0f, 1.0f);

	bool firstMove = true;
	int width;
	int height;
	float speed = 0.4f;
	float sensitivity = 100.0f;

	bool wPress = true;
	bool sPress = true;
	bool aPress = true;
	bool dPress = true;

	Camera(int width, int height, glm::vec3 position);
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
	glm::vec3 RetOrientNormV3();
	glm::vec2 RetOrientNormV2();
	float focusDistance();
};
#endif