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
#define MAX_NO_TEXTURES 13

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
#define TEX_ID_LACTEA 12

//vetor com o numero das texturas
GLuint texture_id[MAX_NO_TEXTURES];
//-------------------------------

//propriedades das texturas
GLfloat mat_difusa[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_especular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_brilho[] = {50.0};
//--------------------------------

// Iluminacao --------------------
GLfloat fonte_luz_solar[] = {0.0, 0.0, 0.0, 1.0};
GLfloat posicao_luz0[] = {0.0, 10.0, 0.0, 1.0};  // posição luz
GLfloat cor_luz0[] = {1.0, 1.0, 1.0, 1.0};  // componentes de luz para reflexão difusa e especular
GLfloat cor_luz0_amb[] = {0.3, 0.3, 0.3, 1.0};  // componente de luz para reflexão ambiente
//-------------------------

// Variaveis matemáticas ---------------------
int xrot;
int yrot;
int zrot;
float ratio;
int bot, rotX_ini, rotY_ini, x_ini, y_ini;

/* angulos de rotacao para os corpos celestes */
float angleMercury = 0;
float angleVenus = 0;
float angleEarth = 0;
float angleMoon = 0;
float angleMars = 0;
float angleJupiter = 0;
float angleEuropa = 0;
float angleSaturn = 0;
float angleUranus = 0;
float angleNeptune = 0;
//------------------------------------------------

/* para a camera, lembrem-se dos exercicios anteriores */
#define y_min 60
#define ro_min 120
float eyex = 0;
float eyey = y_min;
float eyez = ro_min;

void initTexture() {
    // Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //Define quantas texturas sera usado no programa
    // texture_id eh o vetor que guarda o ID das texturas
    glGenTextures(13, texture_id);

    //definindo o id das texturas (em ordem)
    // texture_id[<nome do planeta>]  ==> define o numero da textura
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
    texture_id[TEX_ID_LACTEA] = 650;


    image_t temp_image;

    // TEXTURA DO SOL
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_SOL]);
    tgaLoad("sun.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA MERCURIO
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_MERCURIO]);
    tgaLoad("mercury.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA VENUS
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_VENUS]);
    tgaLoad("venus.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA TERRA
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_TERRA]);
    tgaLoad("terra.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA LUA
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_LUA]);
    tgaLoad("moon.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA MARTE
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_MARTE]);
    tgaLoad("mars.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA JUPITER
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_JUPITER]);
    tgaLoad("jupiter.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA EUROPA (LUA DE JUPITER)
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_EUROPA]);
    tgaLoad("europa.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA SATURNO
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_SATURNO]);
    tgaLoad("saturn.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA ANEL DE SATURNO
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_ANEL_SAT]);
    tgaLoad("saturn_ring.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA URANO
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_URANO]);
    tgaLoad("uranus.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA NETUNO
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_NETUNO]);
    tgaLoad("neptune.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //TEXTURA DO BACKGROUND
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_LACTEA]);
    tgaLoad("milky_way.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

    //Habilita/gera o uso de textura nas esferas
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    // GL_TEXTURE_2D ==> define que sera usada uma textura 2D (bitmaps)
    glEnable(GL_TEXTURE_2D);
}

void init() {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
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

    /* GLU PERSPECTIVE INSTRUÇÕES
     * gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
     * fovy : angulo de abertura da camera
     * aspect: area de visualizacao em x
     * zNear: Distancia do observador ao plano de corte frontal
     * zfar: distancia do observador ao plano de corte traseiro
     */
    gluPerspective(60, ratio, 0.5, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

void SkyBox() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id[TEX_ID_LACTEA]);
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    // Back Face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    // Top Face
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    // Bottom Face
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    // Right face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    // Left Face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();
}

void drawSun() {
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_SOL]);
    glutSolidSphere(12, 16, 16);
}

void drawMercury() {
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_MERCURIO]);
    glutSolidSphere(1, 16, 16);
}

void drawVenus(){
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_VENUS]);
    glutSolidSphere(3.3, 16, 16);
}

void drawEarth() {
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_TERRA]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glutSolidSphere(3, 16, 16);
}

void drawMoon() {
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_LUA]);
    glutSolidSphere(1, 16, 16);
}

void drawMars(){

    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_MARTE]);
    glutSolidSphere( 2, 16, 16 );

}

void drawJupiter(){
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_JUPITER]);
    glutSolidSphere( 7, 16, 16 );
}

void drawEuropa(){
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_EUROPA]);
    glutSolidSphere( 0.8, 16, 16 );

}

void drawSaturn(){
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_SATURNO]);
    glutSolidSphere( 6, 16, 16 );
}

void drawUranus(){
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_URANO]);
    glutSolidSphere( 4.5, 16, 16 );
}

void drawNeptune(){
    glBindTexture(GL_TEXTURE_2D, texture_id[TEX_ID_NETUNO]);
    glutSolidSphere( 4.1, 16, 16 );
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /*
     * GLUT LOOK AT INSTRUÇÕES:
     *  gluLookAt (GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ,
     *  GLdouble upX, GLdouble upY, GLdouble upZ);
     *
     * eye_: definir posicao da camera
     * center_:ponto para onde observador esta olhando
     * up_: coordenadas do vetor up (vetor que indica a "vertical" da camera)
    */
    gluLookAt(eyex,eyey,eyez,0,0,0,0,1,0);

    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(xrot, 1.0, 0.0, 0.0);
    glRotatef(yrot, 0.0, 1.0, 0.0);
    glRotatef(zrot, 0.0, 0.0, 1.0);

    glPushMatrix();
        drawSun();
        glPushMatrix();
            glRotatef( angleMercury, 0, 1, 0 );
            glTranslatef( 18, 0, 0 );
            drawMercury();
        glPopMatrix();
        glPushMatrix();
            glRotatef( angleVenus, 0, 1, 0 );
            glTranslatef( 30, 0, 0 );
            drawVenus();
        glPopMatrix();
        glPushMatrix();
            glRotatef( angleEarth, 0, 1, 0 );
            glTranslatef( 50, 0, 0 );
            drawEarth();
            glPushMatrix();
                glRotatef( angleMoon, 0, 1, 0 );
                glTranslatef( 7, 0, 0 );
                drawMoon();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glRotatef( angleMars, 0, 1, 0 );
            glTranslatef( 70, 0, 0 );
            drawMars();
        glPopMatrix();
        glPushMatrix();
            glRotatef(angleJupiter,0,1,0);
            glTranslatef(90,0,0);
            drawJupiter();
            glPushMatrix();
                glRotatef(angleEuropa,0,1,0);
                glTranslatef(14,0,0);
                drawEuropa();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glRotatef(angleSaturn,0,1,0);
            glTranslatef(110,0,0);
            drawSaturn();
        glPopMatrix();
        glPushMatrix();
            glRotatef(angleUranus,0,1,0);
            glTranslatef(130,0,0);
            drawUranus();
        glPopMatrix();
        glPushMatrix();
            glRotatef(angleNeptune,0,1,0);
            glTranslatef(150,0,0);
            drawNeptune();
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();

    //Propriedades
    glEnable(GL_DEPTH_TEST);   // teste de profundidade - habilita z-buffer
    //glEnable(GL_LIGHTING);
    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GerenciaMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        // Salva os par�metros atuais
        x_ini = x;
        y_ini = y;
        rotX_ini = xrot;
        rotY_ini = yrot;
        bot = button;
    } else bot = -1;
}

// Fun��o callback para eventos de movimento do mouse
#define SENS_ROT    5.0
#define SENS_OBS    15.0
#define SENS_TRANSL    30.0

void GerenciaMovim(int x, int y) {
    // Bot�o esquerdo ?
    if (bot == GLUT_LEFT_BUTTON) {
        // Calcula diferen�as
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica �ngulos
        yrot = rotY_ini - deltax / SENS_ROT;
        xrot = rotX_ini - deltay / SENS_ROT;
    }
    glutPostRedisplay();
}


void TimerFunction(int value) {
    /* Fonte : http://www.astronoo.com/pt/artigos/caracteristicas-dos-planetas.html

     Objetos | 	Período de revolução (dias)	| Período de revolução (anos)

    Mercúrio |	87.96934 | 0.241 anos
    Vênus |	224.701	| 0.615 anos
    Terra |	365.25696 |	1 anos
    Marte |	686.9601 |	1,881 anos
    Júpiter |	4 335.3545	| 11.862 anos
    Saturno |	10 757.7365	| 29.452 anos
    Urano |	30 799.095 |	84.323 anos
    Netuno |	60 224.9036 |	164.882 anos
     */


    angleEarth += 1;
    if (angleEarth >= 360) angleEarth = 0;

    angleMoon += 1.2;
    if (angleMoon >= 360) angleMoon = 0;

    angleMars += 0.9;
    if (angleMars >= 360) angleMars = 0;

    angleMercury += 2;
    if (angleMercury >= 360) angleMercury = 0;

    angleVenus += 1.7;
    if (angleVenus >=360) angleVenus = 0;

    angleJupiter += 0.3;
    if (angleJupiter >= 360) angleJupiter =0;

    angleEuropa += 1;
    if(angleEuropa >= 360) angleEuropa =0;

    angleSaturn +=0.1;
    if (angleSaturn>=360) angleSaturn = 0;

    angleUranus +=0.05;
    if (angleUranus>=360) angleSaturn = 0;

    angleNeptune +=0.025;
    if (angleNeptune>=360) angleNeptune = 0;

    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Sistema Planetario");

    init();
    initTexture();
    TimerFunction(0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Registra a fun��o callback para eventos de bot�es do mouse
    glutMouseFunc(GerenciaMouse);

    // Registra a fun��o callback para eventos de movimento do mouse
    glutMotionFunc(GerenciaMovim);

    // glutKeyboardFunc(keyboard);
    // glutSpecialFunc(arrow_keys);
    // 	glutIdleFunc ( display );
    glutMainLoop();

}
