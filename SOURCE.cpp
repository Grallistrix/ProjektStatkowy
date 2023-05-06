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
GLfloat beach_and_grass[] =
{ //     COORDINATES					/        COLORS      /				 TexCoord  //
	//x      y     z								RBG						x   y
	// 
	//Pierwsze 16 to Plaża, kolejne 8 to trawa
//1
-3.5355339059327f,3.5355339059327f, 0.0f,         1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
0.0f,5.0f, 0.0f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
0.0f,3.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//2
-3.5355339059327f,3.5355339059327f, 0.0f,         1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
-2.1213203435596f,2.1213203435596f, 0.5f,         1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
0.0f,3.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//3
0.0f,5.0f, 0.0f,								 1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
0.0f,3.0f, 0.5f,								 1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
3.5355339059327f,3.5355339059327f, 0.0f,		 1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//4
0.0f,3.0f, 0.5f,								 1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
3.5355339059327f, 3.5355339059327f, 0.0f,		 1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
2.1213203435596f, 2.1213203435596f, 0.5f,		 1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//5
2.1213203435596f,2.1213203435596f, 0.5f,		 1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
3.5355339059327f,3.5355339059327f, 0.0f,	     1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
3.0f,0.0f, 0.5f,								 1.0f, 0.0f, 1.0f,		0.5f, 1.0f,
//6
3.0f,0.0f, 0.5f,							 	 1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
3.5355339059327f,3.5355339059327f, 0.0f,		 1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
5.0f,0.0f, 0.0f,								 1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//7
-3.5355339059327f,3.5355339059327F, 0.0f,		 1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
-2.1213203435596f,2.1213203435596f, 0.5f,        1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
-3.0f,0.0f, 0.5f,								 1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//8
-3.5355339059327f,3.5355339059327f, 0.0f   ,	 1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
-3.0f,0.0f, 0.5f     ,							 1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
-5.0f,0.0f, 0.0f    ,						     1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//9
-5.0f,0.0f, 0.0f    ,							 1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
-3.0f,0.0f, 0.5f    ,							 1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
-3.5355339059327f,-3.5355339059327f, 0.0f  ,     1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//10
-3.0f,0.0f, 0.5f  ,								 1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
-3.5355339059327f,-3.5355339059327f, 0.0f,       1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
-2.1213203435596f,-2.1213203435596f, 0.5f,       1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//11
-3.5355339059327f,-3.5355339059327f, 0.0f ,      1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
0.0f,-3.0f, 0.5f     ,							 1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
-2.1213203435596f,-2.1213203435596f, 0.5f  ,     1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//12
0.0f,-3.0f, 0.5f   ,						     1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
-3.5355339059327f,-3.5355339059327f, 0.0f  ,     1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
0.0f,-5.0f, 0.0f    ,							 1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//13
0.0f,-3.0f, 0.5f   ,							 1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
0.0f,-5.0f, 0.0f,							     1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
3.5355339059327f,-3.5355339059327f, 0.0f ,       1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//14
2.1213203435596f,-2.1213203435596f, 0.5f    ,    1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
0.0f,-3.0f, 0.5f  ,								 1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
3.5355339059327f,-3.5355339059327f, 0.0f    ,    1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//15
3.5355339059327f,-3.5355339059327f, 0.0f ,        1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
2.1213203435596f,-2.1213203435596f, 0.5f,         1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
3.0f,0.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.5f, 1.0f,
//16
3.0f,0.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.0f, 0.5f,
5.0f,0.0f, 0.0f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
3.5355339059327f,-3.5355339059327f, 0.0f,         1.0f, 0.0f, 1.0f,      0.5f, 1.0f,

//START TRAWY
//1
-3.0f,0.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
-2.1213203435596f,2.1213203435596f, 0.5f,		  1.0f, 0.0f, 1.0f,      0.5f, 0.0f,
0.0f, 0.0f, 0.75f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
//2
-2.1213203435596f,2.1213203435596f, 0.5f,		  1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
0.0f, 3.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.0f,
0.0f, 0.0f, 0.75f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
//3
0.0f, 3.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
2.1213203435596f, 2.1213203435596f, 0.5f,		  1.0f, 0.0f, 1.0f,      0.5f, 0.0f,
0.0f, 0.0f, 0.75f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
//4
3.0f, 0.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
2.1213203435596f, 2.1213203435596f, 0.5f,		  1.0f, 0.0f, 1.0f,      0.5f, 0.0f,
0.0f, 0.0f, 0.75f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
//5
3.0f,0.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
2.1213203435596f,-2.1213203435596f, 0.5f,		  1.0f, 0.0f, 1.0f,      0.5f, 0.0f,
0.0f, 0.0f, 0.75f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
//6
0.0f,-3.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
2.1213203435596f,-2.1213203435596f, 0.5f,		  1.0f, 0.0f, 1.0f,      0.5f, 0.0f,
0.0f, 0.0f, 0.75f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
//7
0.0f, -3.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
-2.1213203435596f,-2.1213203435596f, 0.5f,		  1.0f, 0.0f, 1.0f,      0.5f, 0.0f,
0.0f, 0.0f, 0.75f,								  1.0f, 0.0f, 1.0f,      0.5f, 0.5f,
//8
-3.0f, 0.0f, 0.5f,								  1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
-2.1213203435596f,-2.1213203435596f, 0.5f,		  1.0f, 0.0f, 1.0f,      0.5f, 0.0f,
0.0f, 0.0f, 0.75f,								  1.0f, 0.0f, 1.0f,		 0.5f, 0.5f,

//Woda [WIP, jakoś trzeba poprawić, dunno, może napisać funkcję żeby zrobiła 100 kwadratów w to miejsce]
-20.0f, -20.0f, 0.0f,				1.0f, 0.0f, 1.0f,	0.5f, 0.0f,
-20.0f, 20.0f, 0.0f,				1.0f, 0.0f, 1.0f,	1.0f, 0.0f,
20.0f, 20.0f, 0.0f,					1.0f, 0.0f, 1.0f,	1.0f, 0.5f,

-20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
20.0f, 20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,


};

GLfloat vert2[] = {
	-3.0f, -3.0f,  0.0f,       1.0f, 0.0f, 0.0f,	     0.0f,  0.0f,	//A
	 3.0f, -3.0f,  0.0f,       1.0f, 0.0f, 0.0f,     	 3.0f,  0.0f,	//B
	 3.0f,  3.0f,  0.0f,       1.0f, 0.0f, 0.0f,         3.0f,  3.0f,	//C

	 3.0f,  3.0f,  0.0f,       1.0f, 0.0f, 0.0f,    	 3.0f,  3.0f,	//-A
	-3.0f,  3.0f,  0.0f,       1.0f, 0.0f, 0.0f,	     0.0f,  3.0f,	//-B
	-3.0f, -3.0f,  0.0f,       1.0f, 0.0f, 0.0f,		 0.0f,  0.0f	//-C
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
	VBO VBO1(beach_and_grass, sizeof(beach_and_grass));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();






	// Oteksturuj kostke
	Texture texture_frame_1("everything_texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture_frame_1.texUnit(shaderProgram, "tex0", 0);

	//Kamera, Test Glebokosci i enable przezroczyste tekstury
	Camera kamera(const_width, const_height, glm::vec3(-2.0f, 3.0f, 1.0f));

	glEnable(GL_DEPTH_TEST);



	GLfloat currTime = glfwGetTime();
	GLfloat prevTime = currTime;
	int jkl = 0;


	while (!glfwWindowShouldClose(window))
	{
		currTime = glfwGetTime();

		//if (currTime - prevTime < 0.1)
		//	continue;

		prevTime = currTime;
		
		
		glClearColor(0.19f, 0.64f, 0.89f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();
		//shaderProgram2.Activate();

		kamera.Inputs(window);
		kamera.Matrix(45.0f, 1.0f, 40.0f, shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering
		texture_frame_1.Bind();

		VAO1.Bind();
		//VAO2.Bind();
		// Narysuj array na podstawie indicies
		glDrawArrays(GL_TRIANGLES, 0, 50*3);
		glfwSwapBuffers(window);




		glfwPollEvents();

		std::cout << "\n\nX:" << kamera.Position.x << "\tY:" << kamera.Position.y << "\tZ:" << kamera.Position.z << std::endl;
		std::cout << "Looking at:\t" "X:" << kamera.Orientation.x << "\tY:" << kamera.Orientation.y << "\tZ:" << kamera.Orientation.z << std::endl;
	}

	VAO1.Delete();
	VBO1.Delete();
	texture_frame_1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
