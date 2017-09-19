
#include "ShortGun.h"

void SHORTGUN_DRAW_FILLED_PIPE(GLdouble radius,GLdouble height ,COLOR color)
{
	glColor3f(color.PISTOL_COLOR_RED,color.PISTOL_COLOR_GREEN,color.PISTOL_COLOR_BLUE);
	gluCylinder(_pGLUShortGunFilledPipe,radius,radius,height, 100, 100);

}

void SHORTGUN_DRAW_WIRED_PIPE(GLdouble radius, GLdouble height, COLOR color)
{
	glColor3f(color.PISTOL_COLOR_RED,color.PISTOL_COLOR_GREEN,color.PISTOL_COLOR_BLUE);
	gluQuadricDrawStyle(_pGLUShortGunWireddPipe, GLU_LINE);
	gluCylinder(_pGLUShortGunWireddPipe,radius,radius, height, 10, 100);

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
	if (_gShortGunAngle >= 360.0f)
		_gShortGunAngle = 0.0f;
	else
		_gShortGunAngle += 0.5f;

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
	SHORTGUN_DRAW_FILLED_PIPE(0.03,1.2,c);
	c = { 33.0f / 255.0f, 33.0f / 255.0f, 33.0f / 255.0f };
	SHORTGUN_DRAW_WIRED_PIPE(0.04,1.2,c);
	/**/

	/*pipe 2*/
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0f, 0.099f, -3.0f);
	glRotatef(_gShortGunAngle, 0.0f, 1.0f, 0.0f);

	c = { 189.0f / 255.0f, 189.0f / 255.0f, 189.0f / 255.0f };
	SHORTGUN_DRAW_FILLED_PIPE(0.06,1.6,c);
	c = { 117.0f / 255.0f, 117.0f / 255.0f, 117.0f / 255.0f };
	SHORTGUN_DRAW_WIRED_PIPE(0.07,1.6,c);
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

	//_gShortGunAngle = 90.0f;
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