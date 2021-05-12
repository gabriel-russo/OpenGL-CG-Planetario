/// **********************************************************************
///  Computer Graphics - Trabalho Final - Sistema solar em OpenGL
///
///  Autor: Gabriel M. Russo
///
///  DACC - Departamento Academico de ciência da computacao
///
///  UNIR - Fundação Universidade Federal de Rondônia
///
///     -------------- Compilador Usado ---------------
///  gcc (Debian 8.3.0-6) 8.3.0
///  Copyright (C) 2018 Free Software Foundation, Inc.
///  This is free software; see the source for copying conditions.
///
///      ------------- Sistema Operacional Usado --------------
///  Linux
/// OS: MX x86_64
/// Kernel: 5.8.0-3-amd64
/// **********************************************************************

//Bibliotecas

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <cstdio>
#include "tgaload.h"

//-----------------------------

//ID DAS TEXTURAS
#define MAX_NO_TEXTURES 12

#define TEX_ID_SOL 0
#define TEX_ID_MERCURIO 1
#define TEX_ID_VENUS 2
#define TEX_ID_TERRA 3
#define TEX_ID_LUA 4
#define TEX_ID_MARTE 5
#define TEX_ID_JUPITER 6
#define TEX_ID_EUROPA 7
#define TEX_ID_SATURNO 8
#define TEX_ID_ANEL_SAT 9
#define TEX_ID_URANO 10
#define TEX_ID_NETUNO 11
//#define TEX_ID_LACTEA 12

//vetor com o numero das texturas
GLuint texture_id[MAX_NO_TEXTURES];

GLfloat fAspect = 1;

// Variaveis matemáticas ---------------------
int xrot;
int yrot;
int zrot;
float ratio;
int bot, rotX_ini, rotY_ini, x_ini, y_ini;

/* angulos de rotacao para os corpos celestes */
float angleEarth = 0;
float angleMoon = 0;
float angleMars = 0;
//------------------------------------------------

/* para a camera, lembrem-se dos exercicios anteriores */
#define y_min 60
#define ro_min 120
float eyex = 0;
float eyey = y_min;
float eyez = ro_min;

void initTexture() {
    //Habilita o uso de textura
    glEnable(GL_TEXTURE_2D);

    // Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //Define quantas texturas sera usado no programa
    // texture_id eh o vetor que guarda o ID das texturas
    glGenTextures(12, texture_id);

    //definindo o id das texturas (em ordem)

    texture_id[TEX_ID_SOL] = 50;
    texture_id[TEX_ID_MERCURIO] = 100;
    texture_id[TEX_ID_VENUS] = 150;
    texture_id[TEX_ID_TERRA] = 200;
    texture_id[TEX_ID_LUA] = 250;
    texture_id[TEX_ID_MARTE] = 300;
    texture_id[TEX_ID_JUPITER] = 350;
    texture_id[TEX_ID_EUROPA] = 400;
    texture_id[TEX_ID_SATURNO] = 450;
    texture_id[TEX_ID_ANEL_SAT] = 500;
    texture_id[TEX_ID_URANO] = 550;
    texture_id[TEX_ID_NETUNO] = 600;

    // Define que tipo de textura sera usada
    // GL_TEXTURE_2D ==> define que sera usada uma textura 2D (bitmaps)
    // texture_id[<nome do planeta>]  ==> define o numero da textura
    image_t temp_image;
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_SOL]);
    tgaLoad("sun.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_MERCURIO]);
    tgaLoad("mercury.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_VENUS]);
    tgaLoad("venus.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_TERRA]);
    tgaLoad("terra.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_LUA]);
    tgaLoad("moon.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_MARTE]);
    tgaLoad("mars.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_JUPITER]);
    tgaLoad("jupiter.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_EUROPA]);
    tgaLoad("europa.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_SATURNO]);
    tgaLoad("saturn.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_ANEL_SAT]);
    tgaLoad("saturn_ring.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_URANO]);
    tgaLoad("uranus.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
    glBindTexture(GL_TEXTURE_2D,texture_id[TEX_ID_NETUNO]);
    tgaLoad("neptune.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

}

void init() {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.5f);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_CULL_FACE);

}

// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
// **********************************************************************

void reshape(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    ratio = 1.0f * w / h;
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the clipping volume
    gluPerspective(80, ratio, 1, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 30,
              0, 0, 10,
              0.0f, 1.0f, 0.0f);
}

/* Hierarquia de um planetário (Apenas o principal)

Sol
  ¦
  +- Mercurio
  ¦
  +-Venus
  ¦
  +- Terra
  ¦    ¦
  ¦    +- Lua
  ¦
  +- Marte
  ¦
  +- Jupiter
  ¦     ¦
  ¦     +-Europa
  ¦
  +- Saturno + Anel de saturno
  ¦
  +- Urano
  ¦
  +- Netuno

  Será criado e estabelecido essa relação e ordem planetária na funcao display()
 */

void display() {


}

int main(int argc, char **argv) {


}
