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
#include <algorithm>

using std::cout;
using std::endl;

#define woda_width 50.0f

const unsigned int const_width = 1920;
const unsigned int const_height = 1080;


//Done
GLfloat wyspa_vertices[] = {
	//X   Y     Z		||  R     G     B     ||         Text-X, Text-Y

	// Plaża
	//0,1,2,3
	-5.0f,0.0f, 0.0f,							      1.0f, 0.0f, 1.0f,      1.0f, 0.0f,
	-3.5355339059327f,-3.5355339059327f, 0.0f,         1.0f, 0.0f, 1.0f,     0.0f, 0.0f,
	0.0f,-5.0f, 0.0f,								  1.0f, 0.0f, 1.0f,      1.0f, 0.0f,
	3.5355339059327f,-3.5355339059327f, 0.0f,         1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
	//4,5,6,7
	5.0f, 0.0f, 0.0f,							      1.0f, 0.0f, 1.0f,      1.0f, 0.0f,
	3.5355339059327f,3.5355339059327f, 0.0f,          1.0f, 0.0f, 1.0f,      0.0f, 0.0f,
	0.0f, 5.0f, 0.0f,								  1.0f, 0.0f, 1.0f,      1.0f, 0.0f,
   -3.5355339059327f,3.5355339059327f, 0.0f,          1.0f, 0.0f, 1.0f,      0.0f, 0.0f,

   //Trawa
   //8,9,10,11
	-3.0f,0.0f, 0.5f  ,								  1.0f, 0.0f, 1.0f,      0.53f, 1.0f,
	-2.1213203435596f,-2.1213203435596f, 0.5f,        1.0f, 0.0f, 1.0f,      0.62f, 1.0f,
	0.0f,-3.0f, 0.5f     ,							  1.0f, 0.0f, 1.0f,      0.41f, 1.0f,
	2.1213203435596f,-2.1213203435596f, 0.5f,         1.0f, 0.0f, 1.0f,      0.18f, 1.0f,

	//12,13,14,15
	 3.0f,0.0f, 0.5f  ,								  1.0f, 0.0f, 1.0f,      0.62f, 1.0f,
	 2.1213203435596f, 2.1213203435596f, 0.5f,        1.0f, 0.0f, 1.0f,      0.53f, 0.78f,
	0.0f, 3.0f, 0.5f,	     						  1.0f, 0.0f, 1.0f,      0.55f, 0.87f,
	-2.1213203435596f, 2.1213203435596f, 0.5f,         1.0f, 0.0f, 1.0f,      0.6f, 0.92,
	//16
	0.0f, 0.0f, 0.75f,								  1.0f, 0.0f, 1.0f,		 1.0f, 2.0f,

};
GLuint wyspa_indices[] = {
	//Bottom
	0,1,9,
	0,8,9,

	1,9,10,
	1,2,10,

	2,3,10,
	3,10,11,

	3,11,12,
	3,4,12,

	12,4,5,
	5,12,13,

	13,14,5,
	5,6,14,

	6,7,14,
	7,14,15,

	7,8,15,
	0,7,8,
	//Hill
	8,9,16,
	9,10,16,
	10,11,16,
	11,12,16,
	12,13,16,
	13,14,16,
	14,15,16,
	15,8,16,

};

GLfloat woda_vert[] = {
-woda_width, -woda_width, 0.0f,			1.0f, 0.0f, 1.0f,		0.0f, 0.0f,
-woda_width, woda_width, 0.0f,			1.0f, 0.0f, 1.0f,		50.0f, 0.0f,
woda_width, -woda_width, 0.0f,			1.0f, 0.0f, 1.0f,		0.0f, 50.0f,
woda_width, woda_width, 0.0f,			1.0f, 0.0f, 1.0f,		50.0f, 50.0f,
};
GLuint woda_indices[] = {
	0,1,2,
	1,2,3,
};

GLfloat log_vert[] = {
	//X   Y     Z				||  R     G     B     ||         Text-X, Text-Y
	//BOTTOM
	//0
	0.5f, 0.0f, 0.0f,				1.0f, 0.0f, 1.0f,				0.0f, 0.0f,
	//1
	0.25f, 0.433012f, 0.0f,			 1.0f, 0.0f, 1.0f,				 1.0f, 0.0f,
	//2
	-0.25f, 0.433012f, 0.0f,		1.0f, 0.0f, 1.0f,				0.0f, 0.0f,
	//3
	-0.5f, 0.0f, 0.0f,				1.0f, 0.0f, 1.0f,				1.0f, 0.0f,
	//4
	-0.25f, -0.433012f, 0.0f,		 1.0f, 0.0f, 1.0f,				 0.0f, 0.0f,
	//5
	0.25f, -0.433012f, 0.0f,		1.0f, 0.0f, 1.0f,				1.0f, 0.0f,

	//TOP
	//6
	0.5f, 0.0f, 1.0f,				1.0f, 0.0f, 1.0f,				0.0f, 1.0f,
	//7
	0.25f, 0.433012f, 1.0f,			 1.0f, 0.0f, 1.0f,				 1.0f, 1.0f,
	//8
	-0.25f, 0.433012f, 1.0f,		1.0f, 0.0f, 1.0f,				0.0f, 1.0f,
	//9
	-0.5f, 0.0f, 1.0f,				1.0f, 0.0f, 1.0f,				1.0f, 1.0f,
	//10
	-0.25f, -0.433012f, 1.0f,		 1.0f, 0.0f, 1.0f,				 0.0f, 1.0f,
	//11
	0.25f, -0.433012f, 1.0f,		1.0f, 0.0f, 1.0f,				1.0f, 1.0f,


};
GLuint log_indices[] = {

	//Side A
	0,1,6,
	1,6,7,
	//Side B
	1,2,7,
	2,7,8,
	//Side C
	2,3,8,
	3,8,9,
	//Side D
	3,4,10,
	3,9,10,
	//Side E
	4,5,11,
	4,10,11,
	//Side F
	0,5,6,
	5,6,11,

};

GLuint liscie_indices[] = {
	//Botto,
	0,1,2,
	0,2,3,
	//Rising
	0,3,4,
	3,4,7,

	2,3,7,
	2,6,7,

	1,2,5,
	2,5,6,

	0,1,5,
	0,4,5,
	//Sides
	4,7,8,
	7,8,11,

	6,7,10,
	7,10,11,

	4,5,8,
	5,8,9,

	5,6,10,
	5,9,10,
	//Top
	11,8,9,
	11,9,10,
};
GLfloat liscie_vert[] = {
	//Bottom - 0,1,2,3 
-1.0f, -1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
 1.0f, -1.0f, 0.0f,			1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
 1.0f,  1.0f, 0.0f,			1.0f, 0.0f, 1.0f,			1.0f, 1.0f,
-1.0f,  1.0f, 0.0f,			1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

//Rising Side - 4,5,6,7
-1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			2.0f, 1.5f,
 1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.5f, 2.0f,
 1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			2.0f, 1.5f,
-1.2f, 1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,				1.5f, 2.0f,

//Topside 8,9,10,11 
 -1.2f, -1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
 1.2f, -1.2f, 2.0f,			1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
 1.2f,  1.2f, 2.0f,			1.0f, 0.0f, 1.0f,			1.0f, 1.0f,
-1.2f,  1.2f, 2.0f,			1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
};

GLfloat skala_vert[] = {
	//0 1 2 3
-0.5f, -0.5f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
 0.5f, -0.5f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
-0.5f,  0.5f, 0.0f,		    1.0f, 0.0f, 1.0f,			2.0f, 0.0f,
 0.5f,  0.5f, 0.0f,		    1.0f, 0.0f, 1.0f,			3.0f, 0.0f,
 // 4 5 6 7
 0.28f,   0.135f, 0.7f,		    1.0f, 0.0f, 1.0f,			1.64f, 1.0f,     //4
-0.14f,   0.375f, 0.7f,		    1.0f, 0.0f, 1.0f,			1.94f, 1.13f,     //5
-0.325f, -0.11f, 0.7f,		    1.0f, 0.0f, 1.0f,			1.1f, 1.8f,     //6
 0.04f,  -0.3f, 0.7f,		    1.0f, 0.0f, 1.0f,			1.3f, 1.7f,     //7
 //8
-0.02f, 0.21f, 1.0f,			1.0f, 0.0f, 1.0f,			2.5f, 2.9f,

};
GLuint skala_indices[] = {
	//Base
	0, 2, 6,
	0, 7, 1,
	1, 3, 4,
	2, 3, 5,
	//Base Filling
	0,6,7,
	2,5,6,
	3,4,5,
	1,4,7,
	//Top
	6,7,8,
	4,7,8,
	4,5,8,
	5,6,8,
};


void drawWyspa(GLfloat x_location, GLfloat y_location, GLfloat z_location, Shader shadProg);
void drawOcean(int frameState, Shader shaderProgram);
void drawOceanFrame(const char* image, Shader shadProg);
void drawLiscie(GLfloat x_location, GLfloat y_location, GLfloat z_location, Shader shadProg);
void drawDrzewko(GLfloat x_location, GLfloat y_location, GLfloat z_location, int height, Shader shadProg);
void drawSkala(GLfloat x_location, GLfloat y_location, GLfloat z_location, Shader shadProg);
void drawOceanFloor(Shader shadProg) {
	GLfloat localVertics[sizeof(woda_vert) / 4];
	std::copy(std::begin(woda_vert), std::end(woda_vert), localVertics);

	for (int i = 0; i < sizeof(localVertics) / 4; i++) {
		int id = i % 8;
		if(id==2)
			localVertics[i] -=0.5f;
	}

	VAO obVAO;
	obVAO.Bind();
	VBO obVBO(localVertics, sizeof(localVertics));
	EBO obEBO(woda_indices, sizeof(woda_indices));

	//Linkowanie atrybutów
	obVAO.LinkAttrib(obVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	obVAO.LinkAttrib(obVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	obVAO.LinkAttrib(obVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	Texture OceanFloor("drench.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	OceanFloor.texUnit(shadProg, "tex0", 0);
	OceanFloor.Bind();
	//Draw
	glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);
	//Delete this usless stuff
	glDisable(GL_BLEND);

	obEBO.Delete();
	obVBO.Delete();
	obVAO.Delete();
	OceanFloor.Delete();

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
		//Liczenie czy podmieniamy klatke animacji
		currTime = glfwGetTime();
		if (currTime - prevTime > 0.2) {
			frame_state++;
			prevTime = currTime;
		}
		if (frame_state >= 8)
			frame_state = 0;

		//Buffer Głębokości, Zapasowe tło, Szader
		glClearColor(0.19f, 0.64f, 0.89f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		//Kamera
		kamera.Inputs(window);
		kamera.Matrix(30.0f, 1.0f, 80.0f, shaderProgram, "camMatrix");

		drawOceanFloor(shaderProgram);
		//RYSOWANIE OBIEKTÓW	
		drawOcean(frame_state, shaderProgram);


		drawWyspa(0, 0, 0, shaderProgram);
		drawWyspa(15, -3, -0.15, shaderProgram);
		drawWyspa(-7.3, 1.2, -0.6, shaderProgram);
		drawWyspa(18, 20, 0.1, shaderProgram);

		drawDrzewko(2, -1, 0, 3, shaderProgram);
		drawDrzewko(-3, 3, 0, 6, shaderProgram);
		drawDrzewko(17, -2.4, 0, 1, shaderProgram);
		drawDrzewko(19.1, 20.6, 0, 5, shaderProgram);

		drawSkala(-5, 5, 0, shaderProgram);
		drawSkala(12, -7.6, -0.3, shaderProgram);
		drawSkala(-4.1, -5.8, -0.2, shaderProgram);
		drawSkala(-5, 5, 0, shaderProgram);
		drawSkala(6, -4.6, 0, shaderProgram);
		drawSkala(-5.1, 3, -0.2, shaderProgram);
		drawSkala(0, 0, 0.2, shaderProgram);
		drawSkala(9, 23.5, -0.3, shaderProgram);
		drawSkala(15, 13.7, -0.3, shaderProgram);
		drawSkala(8.7, 11.3, 0, shaderProgram);


		glfwSwapBuffers(window);									//Update Window
		glfwPollEvents();

		cout << "\n\nX:" << kamera.Position.x << "\tY:" << kamera.Position.y << "\tZ:" << kamera.Position.z << endl;
		//	cout << "Looking at:\t" "X:" << kamera.Orientation.x << "\tY:" << kamera.Orientation.y << "\tZ:" << kamera.Orientation.z << endl;
	}


	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}



void drawWyspa(GLfloat x_location, GLfloat y_location, GLfloat z_location, Shader shadProg) {

	//Skopiuj do lokalnej wersji (ważne, potem musi offset)
	GLfloat localVertics[sizeof(wyspa_vertices) / 4];
	std::copy(std::begin(wyspa_vertices), std::end(wyspa_vertices), localVertics);

	//Aplikuj offset
	for (int i = 0; i < sizeof(localVertics) / 4; i++) {
		int id = i % 8;
		switch (id) {
		case 0:									//X
			localVertics[i] += x_location;
			break;
		case 1:									//Y
			localVertics[i] += y_location;
			break;
		case 2:									//Z
			localVertics[i] += z_location;
			break;
		default:
			break;
		}
	}

	VAO obVAO;
	obVAO.Bind();
	VBO obVBO(localVertics, sizeof(localVertics));
	EBO obEBO(wyspa_indices, sizeof(wyspa_indices));

	//Linkowanie atrybutów
	obVAO.LinkAttrib(obVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	obVAO.LinkAttrib(obVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	obVAO.LinkAttrib(obVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	Texture wyspa_texture("Sand.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	wyspa_texture.texUnit(shadProg, "tex0", 0);
	wyspa_texture.Bind();


	//Draw
	glDrawElements(GL_TRIANGLES, 140, GL_UNSIGNED_INT, 0);



	obEBO.Delete();
	obVBO.Delete();
	obVAO.Delete();
	wyspa_texture.Delete();

}
void drawOcean(int frameState, Shader shaderProgram) {

	switch (frameState) {
	case 0:
		drawOceanFrame("water_frame0.png", shaderProgram);
		break;
	case 1:
		drawOceanFrame("water_frame1.png", shaderProgram);
		break;
	case 2:
		drawOceanFrame("water_frame2.png", shaderProgram);
		break;
	case 3:
		drawOceanFrame("water_frame3.png", shaderProgram);
		break;
	case 4:
		drawOceanFrame("water_frame4.png", shaderProgram);
		break;
	case 5:
		drawOceanFrame("water_frame5.png", shaderProgram);
		break;
	case 6:
		drawOceanFrame("water_frame6.png", shaderProgram);
		break;
	case 7:
		drawOceanFrame("water_frame7.png", shaderProgram);
		break;
	default:
		drawOceanFrame("water_frame8.png", shaderProgram);
		break;
	}
}
void drawOceanFrame(const char* image, Shader shadProg) {
	VAO obVAO;
	obVAO.Bind();
	VBO obVBO(woda_vert, sizeof(woda_vert));
	EBO obEBO(woda_indices, sizeof(woda_indices));

	//Linkowanie atrybutów
	obVAO.LinkAttrib(obVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	obVAO.LinkAttrib(obVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	obVAO.LinkAttrib(obVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	Texture waterTexture(image, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	waterTexture.texUnit(shadProg, "tex0", 0);
	waterTexture.Bind();

	//Draw
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//Delete this usless stuff
	glDisable(GL_BLEND);
	

	obEBO.Delete();
	obVBO.Delete();
	obVAO.Delete();
	waterTexture.Delete();
}
void drawLiscie(GLfloat x_location, GLfloat y_location, GLfloat z_location, Shader shadProg) {
	//Skopiuj do lokalnej wersji (ważne, potem musi offset)
	GLfloat localVertics[sizeof(liscie_vert) / 4];
	std::copy(std::begin(liscie_vert), std::end(liscie_vert), localVertics);

	//Aplikuj offset
	for (int i = 0; i < sizeof(localVertics) / 4; i++) {
		int id = i % 8;
		switch (id) {
		case 0:									//X
			localVertics[i] += x_location;
			break;
		case 1:									//Y
			localVertics[i] += y_location;
			break;
		case 2:									//Z
			localVertics[i] += z_location;
			break;
		default:
			break;
		}
	}

	VAO obVAO;
	obVAO.Bind();
	VBO obVBO(localVertics, sizeof(localVertics));
	EBO obEBO(liscie_indices, sizeof(liscie_indices));

	//Linkowanie atrybutów
	obVAO.LinkAttrib(obVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	obVAO.LinkAttrib(obVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	obVAO.LinkAttrib(obVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	Texture leavesTexture("leaves.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	leavesTexture.texUnit(shadProg, "tex0", 0);
	leavesTexture.Bind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Draw
	glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);
	//Delete this usless stuff
	glDisable(GL_BLEND);


	obEBO.Delete();
	obVBO.Delete();
	obVAO.Delete();
	leavesTexture.Delete();

}
void drawDrzewko(GLfloat x_location, GLfloat y_location, GLfloat z_location, int height, Shader shadProg) {
	//Skopiuj indices pnia, tak żeby dało się je przemieścić w odpowiednie miejsce
	//Dzielone przez 4, bo OpenGL-float lubi zwracać x4 więcej niż powinnien
	GLfloat currentLog[sizeof(log_vert) / 4];
	std::copy(std::begin(log_vert), std::end(log_vert), currentLog);

	//Zmien koodynaty PNIA do cord'ów miejsca w których chcemy je wygenerować - Loop po lokalnej kopii indices (currentLog)
	for (int i = 0; i < sizeof(currentLog) / 4; i++) {
		int id = i % 8;
		switch (id) {
		case 0:									//X
			currentLog[i] += x_location;
			break;
		case 1:									//Y
			currentLog[i] += y_location;
			break;
		case 2:									//Z
			currentLog[i] += z_location;
			break;
		default:
			break;
		}
	}
	//Pętla rysująca CAŁY pień, blok po bloku - narysuj blok i zmień położenie następnego (currentLog - indices)
	for (int i = 0; i < height; i++) {
		//RYSOWANIE
		//Tworzy,y obiekty VAO, EBO, VBO
		//VBO działa na lokalnej kopii indices (zachowuje offset), EBO na globalnych po kształt ten sam zostaje
		VAO obVAO;
		obVAO.Bind();
		VBO obVBO(currentLog, sizeof(currentLog));
		EBO obEBO(log_indices, sizeof(log_indices));

		//Linkowanie atrybutów
		obVAO.LinkAttrib(obVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		obVAO.LinkAttrib(obVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		obVAO.LinkAttrib(obVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		Texture woodTexture("wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		woodTexture.texUnit(shadProg, "tex0", 0);
		woodTexture.Bind();

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		obEBO.Delete();
		obVBO.Delete();
		obVAO.Delete();
		woodTexture.Delete();
		//ZMIANA NASTĘPNEGO
		for (int i = 0; i < sizeof(currentLog) / 4; i++) {
			int id = i % 8;
			if (id == 2)
				currentLog[i] += 1.0;
		}
	}

	//Rysowanie Lisci
	drawLiscie(x_location, y_location, z_location + height, shadProg);

}
void drawSkala(GLfloat x_location, GLfloat y_location, GLfloat z_location, Shader shadProg) {
	//Skopiuj do lokalnej wersji (ważne, potem musi offset)
	GLfloat localVertics[sizeof(skala_vert) / 4];
	std::copy(std::begin(skala_vert), std::end(skala_vert), localVertics);

	//Aplikuj offset
	for (int i = 0; i < sizeof(localVertics) / 4; i++) {
		int id = i % 8;
		switch (id) {
		case 0:									//X
			localVertics[i] += x_location;
			break;
		case 1:									//Y
			localVertics[i] += y_location;
			break;
		case 2:									//Z
			localVertics[i] += z_location;
			break;
		default:
			break;
		}
	}

	VAO obVAO;
	obVAO.Bind();
	VBO obVBO(localVertics, sizeof(localVertics));
	EBO obEBO(skala_indices, sizeof(skala_indices));

	//Linkowanie atrybutów
	obVAO.LinkAttrib(obVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	obVAO.LinkAttrib(obVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	obVAO.LinkAttrib(obVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	Texture stoneTexture("rock.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	stoneTexture.texUnit(shadProg, "tex0", 0);
	stoneTexture.Bind();

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	obEBO.Delete();
	obVBO.Delete();
	obVAO.Delete();
	stoneTexture.Delete();

}