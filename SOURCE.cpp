#include<iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "Camera.h"

const unsigned int const_width = 1000;
const unsigned int const_height = 1000;
float cameraSpeed = 0.001f;
float cameraSensiticity = 100.0f;
bool firstClick = true;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /				 TexCoord  //
	//x      y     z				RBG						x   y

	//Podloga
	-3.0f, -3.0f,  0.0f,       1.0f, 0.0f, 0.0f,	     0.0f,  0.0f,	//A
	 3.0f, -3.0f,  0.0f,       1.0f, 0.0f, 0.0f,     	 3.0f,  0.0f,	//B
	 3.0f,  3.0f,  0.0f,       1.0f, 0.0f, 0.0f,         3.0f,  3.0f,	//C

	 3.0f,  3.0f,  0.0f,       1.0f, 0.0f, 0.0f,    	 3.0f,  3.0f,	//-A
	-3.0f,  3.0f,  0.0f,       1.0f, 0.0f, 0.0f,	     0.0f,  3.0f,	//-B
	-3.0f, -3.0f,  0.0f,       1.0f, 0.0f, 0.0f,		 0.0f,  0.0f,	//-C

	//Boczna Sciana 1
	 3.0f,  3.0f,  0.0f,	   1.0f, 0.0f, 0.0f,	     0.0f,  0.0f,
	-1.0f,  3.0f,  0.0f,	   1.0, 0.0f, 0.0f,			 4.0f,  0.0f,
	-1.0f,  3.0f,  3.0f,	   1.0f, 0.0f, 0.0f,	     4.0f,  4.0f,


};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(const_width, const_height, "Labirynt - 3D", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, const_width, const_height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generuj Vertex i Element Buffer Object, zlinkuj
	VBO VBO1(vertices, sizeof(vertices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();






	// Oteksturuj kostke
	Texture kostka("bruk_granica.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	kostka.texUnit(shaderProgram, "tex0", 0);

	//Kamera, Test Glebokosci i enable przezroczyste tekstury
	Camera kamera(const_width, const_height, glm::vec3(-2.0f, 3.0f, 1.0f));

	glEnable(GL_DEPTH_TEST);



	GLfloat currTime = glfwGetTime();
	GLfloat prevTime = currTime;
	int jkl = 0;


	while (!glfwWindowShouldClose(window))
	{
		currTime = glfwGetTime();

		if (currTime - prevTime < 0.1)
			continue;

		prevTime = currTime;
	
		
		glClearColor(0.21f, 0.33f, 0.21f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate

		kamera.Inputs(window);
		kamera.Matrix(45.0f, 1.0f, 40.0f, shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering

		kostka.Bind();
	

		VAO1.Bind();
		// Narysuj array na podstawie indicies
		glDrawArrays(GL_TRIANGLES, 0, 42);
		glfwSwapBuffers(window);




		glfwPollEvents();

		std::cout << "\n\nX:" << kamera.Position.x << "\tY:" << kamera.Position.y << "\tZ:" << kamera.Position.z << std::endl;
		std::cout << "Looking at:\t" "X:" << kamera.Orientation.x << "\tY:" << kamera.Orientation.y << "\tZ:" << kamera.Orientation.z << std::endl;
	}

	VAO1.Delete();
	VBO1.Delete();
	kostka.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
