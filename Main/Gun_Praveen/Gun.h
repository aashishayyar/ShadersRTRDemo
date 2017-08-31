#include<GL/glu.h>
#pragma once


typedef struct Gun
{
	GLfloat X;
	GLfloat Y;
	GLfloat Z;

	GLfloat RED;
	GLfloat GREEN;
	GLfloat BLUE;

}GUN;



GLUquadric *_pGLUGunFilledPipe = gluNewQuadric();
GLUquadric *_pGLUGunWireddPipe = gluNewQuadric();
GLfloat _gGunAngle = 0.0f;


void GUN_DRAW_FILLED_PIPE()
{
	glColor3f((218.0f / 255.0f), (165.0f / 255.0f), (32.0f / 255.0f));
	gluCylinder(_pGLUGunFilledPipe, 0.06f, 0.06f, 1.0f, 100.0f, 100.0f);

}


void GUN_DRAW_WIRED_PIPE()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	gluQuadricDrawStyle(_pGLUGunWireddPipe, GLU_LINE);
	gluCylinder(_pGLUGunWireddPipe, 0.07f, 0.07f, 1.0f, 10.0f, 100.0f);

}


const int GUN_CLIPPER_LENGTH = 16;
GUN GUN_CLIPPER[GUN_CLIPPER_LENGTH] = {

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
	{ -0.1f, -0.1f,0.0f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f)},
	/**/

	/*LEFT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ 0.1f, -0.1f, 0.0f ,(96.0f / 255.0f), (96.0f / 255.0f), (96.0f / 255.0f) },
	{ 0.1f, -0.1f, -0.4f ,(160.0f / 255.0f), (160.0f / 255.0f), (160.0f / 255.0f) },
	{ 0.1f, 0.1f, -0.1f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f) }
	/**/

};
void GUN_DRAW_CLIPPER()
{
	glBegin(GL_QUADS);
	for (size_t i = 0; i < GUN_CLIPPER_LENGTH; i++)
	{
		glColor3f(GUN_CLIPPER[i].RED, GUN_CLIPPER[i].GREEN, GUN_CLIPPER[i].BLUE);
		glVertex3f(GUN_CLIPPER[i].X, GUN_CLIPPER[i].Y, GUN_CLIPPER[i].Z);
	}
	glEnd();
}


const int GUN_HANDLE_LENGTH = 20;
GUN GUN_HANDLE[GUN_HANDLE_LENGTH] = {
	
	
	/*FRONT*/
	{ 0.1f, 0.1f, 0.0f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ -0.1f, 0.1f, 0.0f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f},
	{ -0.1, -0.4f, -0.2f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ 0.0f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/


	/*BACK*/
	{ 0.1f, 0.1f, -0.3f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ 0.0, -0.1f, -0.6f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1, -0.1f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ -0.1f, 0.1f, -0.3f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/


	/*LEFT*/
	{ 0.1f, 0.1f, 0.0f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ 0.1f, 0.1f, -0.3f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ 0.0, -0.1f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ 0.0f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/

	/*RIGHT*/
	{ -0.1f, 0.1f, 0.0f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ -0.1f, 0.1f, -0.3f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1, -0.1f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ -0.1, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/


	/*BOTTOM*/
	{ 0.0f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ 0.0, -0.1f, -0.6f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1, -0.1f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ -0.1, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/

};
void GUN_DRAW_HANDLE()
{
	glBegin(GL_QUADS);
	for (size_t i = 0; i < GUN_HANDLE_LENGTH; i++)
	{
		glColor3f(GUN_HANDLE[i].RED, GUN_HANDLE[i].GREEN, GUN_HANDLE[i].BLUE);
		glVertex3f(GUN_HANDLE[i].X, GUN_HANDLE[i].Y, GUN_HANDLE[i].Z);
	}
	glEnd();
}



const int GUN_TRIGGER_LENGTH = 18;
GUN GUN_TRIGGER[] = {

	/*FRONT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, 0.0f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) },
	/**/

	/*BACK*/
	{ 0.1f, 0.1f, -0.1f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, -0.1f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) },
	/**/

	/*RIGHT*/
	{ -0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, -0.1f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) },
	/**/

	/*LEFT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ 0.1f, 0.1f, -0.1f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) }
	/**/
};
void GUN_DRAW_TRIGGER()
{
	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < GUN_TRIGGER_LENGTH; i++)
	{
		glColor3f(GUN_TRIGGER[i].RED, GUN_TRIGGER[i].GREEN, GUN_TRIGGER[i].BLUE);
		glVertex3f(GUN_TRIGGER[i].X, GUN_TRIGGER[i].Y, GUN_TRIGGER[i].Z);
	}
	glEnd();
}

void GUN_UPDATE()
{
	if (_gGunAngle >= 360.0f)
		_gGunAngle = 0.0f;
	else
		_gGunAngle += 0.5f;

}

void GUN_DRAW()
{
	/*================ Gun PIPE ==============*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*pipe  1*/
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotatef(_gGunAngle, 0.0f, 1.0f, 0.0f);

	GUN_DRAW_FILLED_PIPE();
	GUN_DRAW_WIRED_PIPE();
	/**/

	/*pipe 2*/
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0f, 0.099f, -3.0f);
	glRotatef(_gGunAngle, 0.0f, 1.0f, 0.0f);

	GUN_DRAW_FILLED_PIPE();
	GUN_DRAW_WIRED_PIPE();
	/**/

	/*==========================================*/


	/*=============== CLipper ================*/
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0f, 0.2f, -3.0f);

	glRotatef(_gGunAngle, 0.0f, 1.0f, 0.0f);

	GUN_DRAW_CLIPPER();
	/*=======================================*/




	/*============== Handle ==================*/
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -3.0f);

	glRotatef(_gGunAngle, 0.0f, 1.0f, 0.0f);

	GUN_DRAW_HANDLE();
	/*===================================*/




	/*============ TRIGGER =============*/
	glPopMatrix();

	glTranslatef(0.0f, 0.0f, -3.1f);

	glRotatef(_gGunAngle, 0.0f, 1.0f, 0.0f);

	GUN_DRAW_TRIGGER();
	/*===============================*/
}