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
#include "indices.h"
#include <vector>


using std::cout;
using std::endl;

#define woda_width 20.0f

const unsigned int const_width = 1000;
const unsigned int const_height = 1000;

GLfloat wyspa1_indices[] =
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

};

GLfloat woda_indices[] = {
-woda_width, woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
0.0f, woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,
-woda_width, woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
-woda_width,	 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,

woda_width, -woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
0.0f, -woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,
woda_width, -woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
woda_width,	 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,

woda_width, woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
0.0f, woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,
woda_width, woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
woda_width,	 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,

-woda_width, -woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
0.0f, -woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,
-woda_width, -woda_width, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f,
-woda_width,	 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f,

};


void drawThing(int whichIndices, const char* image, Shader shadProg) {
	//Stwórz pusty VBO, za moment wypełnimy
	VBO obVBO;


	//Wybierz indices to wygenerowania, zwykł parsing jakoś nie chce działać
	switch (whichIndices)
	{
	case 0:
		obVBO.setData(wyspa1_indices, sizeof(wyspa1_indices));
		break;
	case 1:
		obVBO.setData(woda_indices, sizeof(woda_indices));
		break;

	default:
		break;
	}
		
	//Stwórz teksture, zbinduj
	Texture texture(image, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shadProg, "tex0", 0);
		texture.Bind();

	//Stwórz VAO, zbinduj i zlinkuj atrybuty
	VAO obVAO;
	obVAO.Bind();
	obVAO.LinkAttrib(obVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	obVAO.LinkAttrib(obVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	obVAO.LinkAttrib(obVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));



	glDrawArrays(GL_TRIANGLES, 0, 500 * 3);

	//Unbind i Delete, żeby zużycie pamięci nie rosło jak bloki nad Wisłą
	obVAO.Unbind();
	obVBO.Unbind();
	texture.Unbind();
	obVAO.Delete();
	obVBO.Delete();
	texture.Delete();

}
void drawOcean(int frameState, Shader shaderProgram) {

	switch (frameState) {
	case 0:
		drawThing(1, "everything_texture_frame1.png", shaderProgram);
		break;
	case 1:
		drawThing(1, "everything_texture_frame2.png", shaderProgram);
		break;
	case 2:
		drawThing(1, "everything_texture_frame3.png", shaderProgram);
		break;
	case 3:
		drawThing(1, "everything_texture_frame4.png", shaderProgram);
		break;
	default:
		break;
	}

}




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

	// Stwóz szader
	Shader shaderProgram("default.vert", "default.frag");

	//Kamera, Test Glebokosci i enable przezroczyste tekstury
	Camera kamera(const_width, const_height, glm::vec3(-2.0f, 3.0f, 1.0f));
	glEnable(GL_DEPTH_TEST);

	//Funkcje czasu do obsługi animacji
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

		//Buffer Głębokości, Zapasowe tło, Szader
		glClearColor(0.19f, 0.64f, 0.89f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		//Kamera
		kamera.Inputs(window);
		kamera.Matrix(30.0f, 1.0f, 80.0f, shaderProgram, "camMatrix");


		/// /RYSOWANIE 
		/// Najpierw zbinduj teksture
		/// potem zbinduj VAO
		/// na końcu draw		
		/// 
		///VAO_morze.Bind();
		///texture_morze.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 500 * 3);


		//RYSOWANIE OBIEKTÓW	
		drawThing(0,"everything_texture.png",shaderProgram);		//Wyspa
		drawOcean(frame_state, shaderProgram);						//Morze
																	//Wyspa 2
																	//Wyspa 3
		glfwSwapBuffers(window);
		glfwPollEvents();

	//	cout << "\n\nX:" << kamera.Position.x << "\tY:" << kamera.Position.y << "\tZ:" << kamera.Position.z << endl;
	//	cout << "Looking at:\t" "X:" << kamera.Orientation.x << "\tY:" << kamera.Orientation.y << "\tZ:" << kamera.Orientation.z << endl;
	}

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
