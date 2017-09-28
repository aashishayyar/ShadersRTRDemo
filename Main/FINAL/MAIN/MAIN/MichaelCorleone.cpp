#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"Util.h"

#define circle_points 1000
GLfloat angle = 0.0f, PI = 3.1415f, nextRadius = 1.0f;

void DrawExpression_MichaelCorleone() {

	/*right eye*/
	glPushMatrix();
	glTranslatef(0.3f, -0.4f, -0.9f);
	glScalef(0.8f, 1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (GLfloat angle = 0.0f; angle <= 2.0f*PI; angle = angle + 0.00001f)
	{
		glVertex3f(cos(angle)* 0.2f, sin(angle)* 0.2f, 0.0f);

	}
	glEnd();
	glPopMatrix();

	/*cortina*/
	glPushMatrix();
	glTranslatef(0.3f, -0.33f, -0.9f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (GLfloat angle = 0.0f; angle <= 2.0f*PI; angle = angle + 0.00001f)
	{
		glVertex3f(cos(angle)* 0.04f, sin(angle)* 0.04f, 0.0f);

	}
	glEnd();
	glPopMatrix();

	/*left eye*/
	glPushMatrix();
	glTranslatef(-0.3f, -0.4f, -0.9f);
	//glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glScalef(0.8f, 1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (GLfloat angle = 0.0f; angle <= 2.0f*PI; angle = angle + 0.00001f)
	{
		glVertex3f(cos(angle)* 0.2f, sin(angle)* 0.2f, 0.0f);

	}
	glEnd();
	glPopMatrix();

	/*cortina*/
	glPushMatrix();
	glTranslatef(-0.3f, -0.33f, -0.9f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (GLfloat angle = 0.0f; angle <= 2.0f*PI; angle = angle + 0.00001f)
	{
		glVertex3f(cos(angle)* 0.04f, sin(angle)* 0.04f, 0.0f);

	}
	glEnd();
	glPopMatrix();
	/**/


	/*right eyebrow*/
	glPushMatrix();
	glTranslatef(0.2f, -0.1f, -0.9f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex3f(0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glEnd();
	glPopMatrix();
	/**/

	/*left eyebrow*/
	glPushMatrix();
	glTranslatef(-0.3f, -0.1f,-0.9f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();
	glPopMatrix();
	/**/


	/*draw Mouth*/
	glPushMatrix();
	glTranslatef(0.0f, -1.0f, -0.9f);
	glRotatef(340.0f, 0.0f, 0.0f, 1.0f);
	glScalef(1.0f, 0.3f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < circle_points; i++)
	{
		angle = 1 * PI * i / circle_points;
		glVertex3f(cos(angle)* 0.3f, sin(angle)* 0.3f, 0.0f);
	}
	glEnd();
	glPopMatrix();
}

void DrawMichaelCorleoneFace()
{
	float height = -gfFaceHeight;
	float topX = gfFaceWidth;
	float topZ = gfFaceWidth;
	float bottomX = gfFaceWidth;
	float color[3] = { 1.0f, 0.5f, 0.25f };

	float points[10][3] = {
		{ topX, 0, topZ },
		{ -topX, 0, topZ },
		{ -topX, 0, -topZ },
		{ topX, 0, -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(points, color);

	DrawExpression_MichaelCorleone();
}


void DrawSuit_MichaelCorleone()
{
	/*White nect color*/
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.73f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glScalef(0.5f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < circle_points; i++)
	{
		angle = 1 * PI * i / circle_points;
		glVertex3f(cos(angle)*nextRadius, sin(angle)* nextRadius, 0.0f);
	}
	glEnd();
	glPopMatrix();

	/**/
	/*Draw BLue Tie*/
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, -0.75f);
	glScalef(0.5f, 0.8f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.4f, -0.8f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.4f, -0.8f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.4f, -0.8f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.4f, -0.8f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glPopMatrix();
	/**/

	/*Pocket Left blue*/
	glPushMatrix();
	glTranslatef(0.8f, -1.4f, -0.75f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < circle_points; i++)
	{
		angle = 1 * PI * i / circle_points;
		glVertex3f(cos(angle)* 0.3f, sin(angle)* 0.3f, 0.0f);
	}
	glEnd();
	glPopMatrix();
	/**/


	/*Pocket Right blue*/
	glPushMatrix();
	glTranslatef(-0.8f, -1.4f, -0.75f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < circle_points; i++)
	{
		angle = 1 * PI * i / circle_points;
		glVertex3f(cos(angle)* 0.3f, sin(angle)* 0.3f, 0.0f);
	}
	glEnd();
	glPopMatrix();
	/**/
}

void DrawMichaelChest()
{
	float chestBottomHeight = 0.3f;
	float height = -(gfChestHeight - chestBottomHeight);
	float topX = gfChestUpperWidth;
	float topZ = gfChestWidth;
	float bottomX = gfChestLowerWidth;
	float color[3] = { 0.0f, 0.0f, 0.0f };


	float points[10][3] = {
		{ topX, 0, topZ },
		{ -topX, 0, topZ },
		{ -topX, 0, -topZ },
		{ topX, 0, -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(points, color);

	height = -gfChestHeight;
	topX = gfChestLowerWidth;
	topZ = gfChestWidth;
	bottomX = gfChestLowerWidth;

	float pointsChestBottom[10][3] = {
		{ topX, -(gfChestHeight - chestBottomHeight), topZ },
		{ -topX, -(gfChestHeight - chestBottomHeight), topZ },
		{ -topX, -(gfChestHeight - chestBottomHeight), -topZ },
		{ topX, -(gfChestHeight - chestBottomHeight), -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(pointsChestBottom, color);

	DrawSuit_MichaelCorleone();
}