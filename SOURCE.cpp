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
#include <vector>

using std::cout;
using std::endl;

const unsigned int const_width = 1000;
const unsigned int const_height = 1000;
float cameraSpeed = 0.001f;
float cameraSensiticity = 100.0f;
bool firstClick = true;

// Vertices coordinates
GLfloat scene_indices[] =
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
-20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
-20.0f,	 20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
20.0f,   20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,

-20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
20.0f, 20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,
};

GLfloat vert2[] = {
	0.0f, 1.2f
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(const_width, const_height, "PROJECT: PARADISE || Andrzej Piotrowski, Jakub Rejek, Karol Przydzial", NULL, NULL);
	if (window == NULL) {
		cout << "Nie udało się stworzyć Okna\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, const_width, const_height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generuj VAO, binduj
	VAO VAO1;
	VAO1.Bind();

	// Generuj Vertex (i Element Buffer Object jak wam sie chce robic), zlinkuj
	VBO VBO1(scene_indices, sizeof(scene_indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();

	// Ładowanie tekstur wszystkiego
	Texture texture_frame_1("everything_texture_frame1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture_frame_1.texUnit(shaderProgram, "tex0", 0);

	Texture texture_frame_2("everything_texture_frame2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture_frame_1.texUnit(shaderProgram, "tex0", 0);

	Texture texture_frame_3("everything_texture_frame3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture_frame_1.texUnit(shaderProgram, "tex0", 0);

	Texture texture_frame_4("everything_texture_frame4.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture_frame_1.texUnit(shaderProgram, "tex0", 0);

	//Kamera, Test Glebokosci i enable przezroczyste tekstury
	Camera kamera(const_width, const_height, glm::vec3(-2.0f, 3.0f, 1.0f));

	glEnable(GL_DEPTH_TEST);

	GLfloat currTime = glfwGetTime();
	GLfloat prevTime = currTime;
	int frame_state = 0;

	while (!glfwWindowShouldClose(window))
	{
		//Porcja odpowiedzialna za klatkę animacji
		currTime = glfwGetTime();
		if (currTime - prevTime > 0.5) {
			frame_state++;
			prevTime = currTime;
		}
		if (frame_state >= 4)
			frame_state = 0;

		// Bindowanie odpowiedniej tekstury [na podstawieczasu
		switch (frame_state) {
		case 0:
			texture_frame_1.Bind();
			break;
		case 1:
			texture_frame_2.Bind();
			break;
		case 2:
			texture_frame_3.Bind();
			break;
		case 3:
			texture_frame_4.Bind();
			break;
		default:
			return -23;
		}

		//Buffer Głębokości, Zapasowe tło, Szader
		glClearColor(0.19f, 0.64f, 0.89f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		//Kamera
		kamera.Inputs(window);
		kamera.Matrix(30.0f, 1.0f, 80.0f, shaderProgram, "camMatrix");

		//VAO, można by zrobić z niego też animacje
		VAO1.Bind();

		// Rysowanie
		glDrawArrays(GL_TRIANGLES, 0, 500 * 3);
		glfwSwapBuffers(window);

		glfwPollEvents();

		cout << "\n\nX:" << kamera.Position.x << "\tY:" << kamera.Position.y << "\tZ:" << kamera.Position.z << endl;
		cout << "Looking at:\t" "X:" << kamera.Orientation.x << "\tY:" << kamera.Orientation.y << "\tZ:" << kamera.Orientation.z << endl;
	}

	VAO1.Delete();
	VBO1.Delete();
	texture_frame_1.Delete();
	texture_frame_2.Delete();
	texture_frame_3.Delete();
	texture_frame_4.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}