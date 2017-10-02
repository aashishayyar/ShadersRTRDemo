
#include "ShortGun.h"

typedef struct shortgun
{
	GLfloat PISTOL_X;
	GLfloat PISTOL_Y;
	GLfloat PISTOL_Z;

	GLfloat PISTOL_COLOR_RED;
	GLfloat PISTOL_COLOR_GREEN;
	GLfloat PISTOL_COLOR_BLUE;

}SHORTGUN;

typedef struct color
{
	GLfloat PISTOL_COLOR_RED;
	GLfloat PISTOL_COLOR_GREEN;
	GLfloat PISTOL_COLOR_BLUE;

}COLOR;


GLUquadric *_pGLUShortGunFilledPipe = gluNewQuadric();
GLUquadric *_pGLUShortGunWireddPipe = gluNewQuadric();
GLfloat _gShortGunAngle = 360.0f;


const int SHORTGUN_CLIPPER_LENGTH = 16;
SHORTGUN SHORTGUN_CLIPPER[SHORTGUN_CLIPPER_LENGTH] = {

	/*FRONT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, 0.0f ,(96.0f / 255.0f), (96.0f / 255.0f), (96.0f / 255.0f) },
	{ -0.1f, -0.1f, 0.0f ,(160.0f / 255.0f), (160.0f / 255.0f), (160.0f / 255.0f) },
	{ 0.1f, -0.1f, 0.0f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f) },
	/**/

	/*BACK*/
	{ 0.1f, 0.1f, -0.1f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, -0.1f ,(96.0f / 255.0f), (96.0f / 255.0f), (96.0f / 255.0f) },
	{ -0.1f, -0.1f, -0.4f ,(160.0f / 255.0f), (160.0f / 255.0f), (160.0f / 255.0f) },
	{ 0.1f, -0.1f, -0.4f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f) },
	/**/

	/*RIGHT*/
	{ -0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f,-0.1f ,(96.0f / 255.0f), (96.0f / 255.0f), (96.0f / 255.0f) },
	{ -0.1f, -0.1f, -0.4f ,(160.0f / 255.0f), (160.0f / 255.0f), (160.0f / 255.0f) },
	{ -0.1f, -0.1f,0.0f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f) },
	/**/

	/*LEFT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ 0.1f, -0.1f, 0.0f ,(96.0f / 255.0f), (96.0f / 255.0f), (96.0f / 255.0f) },
	{ 0.1f, -0.1f, -0.4f ,(160.0f / 255.0f), (160.0f / 255.0f), (160.0f / 255.0f) },
	{ 0.1f, 0.1f, -0.1f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f) }
	/**/

};

const int SHORTGUN_HANDLE_LENGTH = 20;
SHORTGUN SHORTGUN_HANDLE[SHORTGUN_HANDLE_LENGTH] = {


	/*FRONT*/
	{ 0.1f, 0.1f, 0.0f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ -0.1f, 0.1f, 0.0f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1f, -0.4f, -0.2f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ 0.0f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/


	/*BACK*/
	{ 0.1f, 0.1f, -0.3f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ 0.0f, -0.4f, -0.6f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1f, -0.4f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ -0.1f, 0.1f, -0.3f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/


	/*LEFT*/
	{ 0.1f, 0.1f, 0.0f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ 0.1f, 0.1f, -0.3f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ 0.0f, -0.4f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ 0.0f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/

	/*RIGHT*/
	{ -0.1f, 0.1f, 0.0f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ -0.1f, 0.1f, -0.3f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1f, -0.4f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ -0.1f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/


	/*BOTTOM*/
	{ 0.0f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ 0.0f, -0.4f, -0.4f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1f, -0.4f, -0.4f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ -0.1f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/

};


const int SHORTGUN_TRIGGER_LENGTH = 18;
SHORTGUN SHORTGUN_TRIGGER[] = {

	/*FRONT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, 0.0f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2f, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) },
	/**/

	/*BACK*/
	{ 0.1f, 0.1f, -0.1f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, -0.1f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2f, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) },
	/**/

	/*RIGHT*/
	{ -0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, -0.1f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2f, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) },
	/**/

	/*LEFT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ 0.1f, 0.1f, -0.1f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2f, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) }
	/**/
};



void SHORTGUN_DRAW_FILLED_PIPE(GLdouble radius, GLdouble height, COLOR color)
{
	glColor3f(color.PISTOL_COLOR_RED, color.PISTOL_COLOR_GREEN, color.PISTOL_COLOR_BLUE);
	gluCylinder(_pGLUShortGunFilledPipe, radius, radius, height, 100, 100);

}

void SHORTGUN_DRAW_WIRED_PIPE(GLdouble radius, GLdouble height, COLOR color)
{
	glColor3f(color.PISTOL_COLOR_RED, color.PISTOL_COLOR_GREEN, color.PISTOL_COLOR_BLUE);
	gluQuadricDrawStyle(_pGLUShortGunWireddPipe, GLU_LINE);
	gluCylinder(_pGLUShortGunWireddPipe, radius, radius, height, 10, 100);

}

void SHORTGUN_DRAW_CLIPPER()
{
	glBegin(GL_QUADS);
	for (size_t i = 0; i < SHORTGUN_CLIPPER_LENGTH; i++)
	{
		glColor3f(SHORTGUN_CLIPPER[i].PISTOL_COLOR_RED, SHORTGUN_CLIPPER[i].PISTOL_COLOR_GREEN, SHORTGUN_CLIPPER[i].PISTOL_COLOR_BLUE);
		glVertex3f(SHORTGUN_CLIPPER[i].PISTOL_X, SHORTGUN_CLIPPER[i].PISTOL_Y, SHORTGUN_CLIPPER[i].PISTOL_Z);
	}
	glEnd();
}

void SHORTGUN_DRAW_HANDLE()
{
	glBegin(GL_QUADS);
	for (size_t i = 0; i < SHORTGUN_HANDLE_LENGTH; i++)
	{
		glColor3f(SHORTGUN_HANDLE[i].PISTOL_COLOR_RED, SHORTGUN_HANDLE[i].PISTOL_COLOR_GREEN, SHORTGUN_HANDLE[i].PISTOL_COLOR_BLUE);
		glVertex3f(SHORTGUN_HANDLE[i].PISTOL_X, SHORTGUN_HANDLE[i].PISTOL_Y, SHORTGUN_HANDLE[i].PISTOL_Z);
	}
	glEnd();
}

void SHORTGUN_DRAW_TRIGGER()
{
	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < SHORTGUN_TRIGGER_LENGTH; i++)
	{
		glColor3f(SHORTGUN_TRIGGER[i].PISTOL_COLOR_RED, SHORTGUN_TRIGGER[i].PISTOL_COLOR_GREEN, SHORTGUN_TRIGGER[i].PISTOL_COLOR_BLUE);
		glVertex3f(SHORTGUN_TRIGGER[i].PISTOL_X, SHORTGUN_TRIGGER[i].PISTOL_Y, SHORTGUN_TRIGGER[i].PISTOL_Z);
	}
	glEnd();
}

void SHORTGUN_UPDATE()
{
	/*	if (_gShortGunAngle >= 360.0f)
	_gShortGunAngle = 0.0f;
	else
	_gShortGunAngle += 0.5f;
	*/
}

void SHORTGUN_DRAW()
{
	/*================ Gun PIPE ==============*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*pipe  1*/
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotatef(_gShortGunAngle, 0.0f, 1.0f, 0.0f);

	COLOR c = { 97.0f / 255.0f, 97.0f / 255.0f, 97.0f / 255.0f };
	SHORTGUN_DRAW_FILLED_PIPE(0.03, 1.2, c);
	c = { 33.0f / 255.0f, 33.0f / 255.0f, 33.0f / 255.0f };
	SHORTGUN_DRAW_WIRED_PIPE(0.04, 1.2, c);
	/**/

	/*pipe 2*/
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0f, 0.099f, -3.0f);
	glRotatef(_gShortGunAngle, 0.0f, 1.0f, 0.0f);

	c = { 189.0f / 255.0f, 189.0f / 255.0f, 189.0f / 255.0f };
	SHORTGUN_DRAW_FILLED_PIPE(0.06, 1.6, c);
	c = { 117.0f / 255.0f, 117.0f / 255.0f, 117.0f / 255.0f };
	SHORTGUN_DRAW_WIRED_PIPE(0.07, 1.6, c);
	/**/

	/*==========================================*/


	/*=============== CLipper ================*/
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0f, 0.2f, -3.0f);

	glRotatef(_gShortGunAngle, 0.0f, 1.0f, 0.0f);

	SHORTGUN_DRAW_CLIPPER();
	/*=======================================*/




	/*============== Handle ==================*/
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -3.0f);

	glRotatef(_gShortGunAngle, 0.0f, 1.0f, 0.0f);

	SHORTGUN_DRAW_HANDLE();
	/*===================================*/




	/*============ TRIGGER =============*/
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -3.1f);

	glRotatef(_gShortGunAngle, 0.0f, 1.0f, 0.0f);

	SHORTGUN_DRAW_TRIGGER();

	glPopMatrix();
	/*===============================*/

}

void drawShortGun()
{
	glPushMatrix();

	glRotatef(180.0f, 0.0f, 0.0f, 0.1f);
	glTranslatef(0.0f, 0.4f, 4.3f);
	SHORTGUN_DRAW();

	glPopMatrix();
}
