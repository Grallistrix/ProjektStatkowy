#include<iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"

#include "Camera.h"
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

#define woda_width 50.0f

const unsigned int const_width = 1920;
const unsigned int const_height = 1080;

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

GLfloat woda_indices[] = 
{
-woda_width, -woda_width, 0.0f,			1.0f, 0.0f, 1.0f,		0.0f, 0.0f,
-woda_width, woda_width, 0.0f,			1.0f, 0.0f, 1.0f,			25.0f, 0.0f,
woda_width, -woda_width, 0.0f,			1.0f, 0.0f, 1.0f,					0.0f, 25.0f,

woda_width, woda_width, 0.0f,		1.0f, 0.0f, 1.0f,		 25.0f, 25.0f,
-woda_width,woda_width, 0.0f,		1.0f, 0.0f, 1.0f,			25.0f, 0.0f,
woda_width, -woda_width, 0.0f,		 1.0f, 0.0f, 1.0f,					0.0f, 25.0f,
};

GLfloat log_indices[] =
{
-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
-0.25f, 0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.25f, 0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
-0.25f, 0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,

-0.25f, 0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
0.25f, 0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
-0.25f, 0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.25f, 0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
0.25f, 0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.25f, 0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,

0.25f, 0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.25f, 0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
0.25f, 0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,

0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
0.25f, -0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
0.25f, -0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.25f, -0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,

0.25f, -0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
-0.25f, -0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.25f, -0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
0.25f, -0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.25f, -0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
-0.25f, -0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,

-0.25f, -0.433012f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
-0.25f, -0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.25f, -0.433012f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,


};

GLfloat liscie_indices[] =
{
	//Bottom
	-1.0f, -1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,			1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,			1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

	 1.0f,  1.0f, 0.0f,			1.0f, 0.0f, 1.0f,			1.0f, 1.0f,
	 1.0f, -1.0f, 0.0f,			1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,			1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

	//Rising East
	-1.0f, -1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	-1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

	-1.0f,  1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	-1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,
	-1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

	//Rising North
	-1.0f,  1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
	-1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
	 1.0f,  1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,

	-1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
	 1.0f,  1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	 1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

	 //Rising West
	  1.0f,  1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
	  1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
	  1.0f, -1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,

	  1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
	  1.0f, -1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	  1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

	  //Rising South
	   1.0f, -1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
	   1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
	  -1.0f, -1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,

	   1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
	  -1.0f, -1.0f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	  -1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

	  //Side East
	  -1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
	  -1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	  -1.2f, -1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

	  -1.2f, -1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
	  -1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	  -1.2f,  1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

	  //Side North
	  -1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
	   1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	  -1.2f,  1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

	  -1.2f,  1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
	   1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
	   1.2f,  1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

	   //Side West
		1.2f,  1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
		1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
		1.2f,  1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

		1.2f,  1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
		1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
		1.2f, -1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

		//Side South
		 1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
		-1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
		 1.2f, -1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

		 1.2f, -1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
		-1.2f, -1.2f, 0.5f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
		-1.2f, -1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

		//Topside
		-1.2f, -1.2f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
		 1.2f, -1.2f, 2.0f,			1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
		-1.2f,  1.2f, 2.0f,			1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

		 1.2f,  1.2f, 2.0f,			1.0f, 0.0f, 1.0f,			1.0f, 1.0f,
		 1.2f, -1.2f, 2.0f,			1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
		-1.2f,  1.2f, 2.0f,			1.0f, 0.0f, 1.0f,			0.0f, 1.0f,



};

GLfloat skala_indices[] =
{
-0.8f, -0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
-0.8f,  0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
-0.8f, -0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

-0.8f, -0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
-0.8f,  0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
-0.8f,  0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

//Side North
-0.8f,  0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
 0.8f,  0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
-0.8f,  0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

-0.8f,  0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
 0.8f,  0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
 0.8f,  0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

 //Side West
  0.8f,  0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
  0.8f, -0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
  0.8f,  0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

  0.8f,  0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
  0.8f, -0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
  0.8f, -0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,

  //Side South
   0.8f, -0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 0.0f,
  -0.8f, -0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
   0.8f, -0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,

   0.8f, -0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			0.0f, 1.0f,
  -0.8f, -0.8f, 0.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 0.0f,
  -0.8f, -0.8f, 2.0f,		    1.0f, 0.0f, 1.0f,			1.0f, 1.0f,



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
	case 2:
		obVBO.setData(skala_indices, sizeof(skala_indices));
		break;

	default:
		 obVBO.setData(log_indices, sizeof(log_indices));
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

	glDrawArrays(GL_TRIANGLES, 0, 100 * 3);

	//Delete, żeby zużycie pamięci nie rosło jak bloki nad Wisłą
	obVAO.Delete();
	obVBO.Delete();
	texture.Delete();

}
void drawOcean(int frameState, Shader shaderProgram) {

	switch (frameState) {
	case 0:
		drawThing(1, "water_frame0.png", shaderProgram);
		break;
	case 1:
		drawThing(1, "water_frame1.png", shaderProgram);
		break;
	case 2:
		drawThing(1, "water_frame2.png", shaderProgram);
		break;
	case 3:
		drawThing(1, "water_frame3.png", shaderProgram);
		break;
	case 4:
		drawThing(1, "water_frame4.png", shaderProgram);
		break;
	case 5:
		drawThing(1, "water_frame5.png", shaderProgram);
		break;
	case 6:
		drawThing(1, "water_frame6.png", shaderProgram);
		break;
	case 7:
		drawThing(1, "water_frame7.png", shaderProgram);
		break;
	default:
		drawThing(1, "water_frame8.png", shaderProgram);
		break;
	}

}
void drawDrzewo(GLfloat x_location, GLfloat y_location, GLfloat z_location, int height,Shader shadProg) {
	//Skopiuj dane z tablicy drzewa [ma tylko 1 pień]
	GLfloat currentLog[sizeof(log_indices)];
	std::copy(std::begin(log_indices), std::end(log_indices), currentLog);

	//Zmien koodynaty do cord'ów drzewa w których chcemy je wygenerować
	//Loop po całej pętli, dodajemy offset koordynatów XYZ
	for (int i = 0; i < 288; i++) {
		int id = i % 8;
		switch (id) {
		case 0:
			currentLog[i] += x_location;
			break;
		case 1:
			currentLog[i] += y_location;
			break;
		case 2:
			currentLog[i] += z_location;
			break;
		default:
			break;
		}
	}

	
	//Rysowanie Pnia drzewa
	for (int i = 0; i < height; i++) {

		//Rysowanie - prepare
		VBO obVBO(currentLog, sizeof(currentLog));
		VAO obVAO;
		obVAO.Bind();
		obVAO.LinkAttrib(obVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		obVAO.LinkAttrib(obVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		obVAO.LinkAttrib(obVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		Texture texture("wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		texture.texUnit(shadProg, "tex0", 0);
		texture.Bind();
		//DrawArray
		glDrawArrays(GL_TRIANGLES, 0, 100 * 3);
		obVAO.Delete();
		obVBO.Delete();
		texture.Delete();
		//Zmien wysokosc, zeby kolejny pien byl wyzej
		for (int i = 0; i < 288; i++) {
			int id = i % 8;
			if (id == 2)
				currentLog[i] += 1;
		}
	}



	//Rysowanie Korony drzewa
	//Offset coodrynatów
	GLfloat currentLeaves[sizeof(liscie_indices)];
	std::copy(std::begin(liscie_indices), std::end(liscie_indices), currentLeaves);
	for (int i = 0; i < 480; i++) {
		int id = i % 8;
		switch (id) {
		case 0:
			currentLeaves[i] += x_location;
			break;
		case 1:
			currentLeaves[i] += y_location;
			break;
		case 2:
			currentLeaves[i] += z_location;
			currentLeaves[i] += height;
			break;
		default:
			break;
		}
	}

	//Prepare the sauce
	VBO obVBO(currentLeaves, sizeof(currentLeaves));
	VAO obVAO;
	obVAO.Bind();
	obVAO.LinkAttrib(obVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	obVAO.LinkAttrib(obVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	obVAO.LinkAttrib(obVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	Texture texture("leaves.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shadProg, "tex0", 0);
	texture.Bind();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Draw
	glDrawArrays(GL_TRIANGLES, 0, 100 * 3);
	//Delete this usless stuff
	obVAO.Delete();
	obVBO.Delete();
	texture.Delete();
	glDisable(GL_BLEND);

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
		if (currTime - prevTime > 0.5) {
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
		drawDrzewo(0, 2, 0, 2, shaderProgram);						//Wyspa1-Drzewo1
		drawDrzewo(-1, -2, 0, 5, shaderProgram);					//Wyspa2-Drzewo2
		//drawThing(2, "stone.png", shaderProgram);
		drawThing(3, "wood.png", shaderProgram);
																	//Wyspa 2
																	//Wyspa 3
		glfwSwapBuffers(window);									//Update Window
		glfwPollEvents();

	//	cout << "\n\nX:" << kamera.Position.x << "\tY:" << kamera.Position.y << "\tZ:" << kamera.Position.z << endl;
	//	cout << "Looking at:\t" "X:" << kamera.Orientation.x << "\tY:" << kamera.Orientation.y << "\tZ:" << kamera.Orientation.z << endl;
	}

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
