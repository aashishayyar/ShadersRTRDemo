#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"Util.h"


/*****************Here Onwards the function dedicated to GodFather(Red Rose) character*****************/


void DrawSector_GodFather(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle);

void DrawSectorLine_GodFather(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle);

void DrawFaceDesign_Godfather(void);

void DrawSuit_Godfather(void);

void DrawButtons_GodFather(GLfloat redius);

void DrawLinesOnDress_GodFather(void);


void DrawSector_GodFather(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle)
{
	float angle;
	glLineWidth(2);
	glPushMatrix();
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, z);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*cos(angle), bRadius*sin(angle), z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*cos(angle), bRadius*sin(angle), z);
	glEnd();
	glPopMatrix();

}

void DrawSectorLine_GodFather(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle)
{
	float angle;
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*cos(angle), bRadius*sin(angle), z);
	glEnd();
}

void DrawFaceDesign_Godfather(void)
{

	GLfloat PI = 3.1415f, angle = 0.0f; //added by praveen

	float height = -gfFaceHeight;
	float topX = gfFaceWidth;
	float topZ = gfFaceWidth;
	float bottomX = gfFaceWidth;
	float color[3] = { 1.0f, 0.5f, 0.25f };

	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;

	glPushMatrix();
	glTranslatef(-topX / 3, height / 3, 0.0f);
	DrawSector_GodFather(0.15f, 0.15f, -topZ - 0.01f, color, 0.0f, 2 * PI);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX / 3, height / 3, 0.0f);
	DrawSector_GodFather(0.15f, 0.15, -topZ - 0.01f, color, 0.0f, 2 * PI);
	glPopMatrix();

	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;

	glPushMatrix();
	glTranslatef(-topX / 3, height / 3 + 0.05, 0.0f);
	DrawSector_GodFather(0.1f, 0.1f, -topZ - 0.03f, color, 0.0f, 2 * PI);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX / 3, height / 3 + 0.05, 0.0f);
	DrawSector_GodFather(0.1f, 0.1f, -topZ - 0.03f, color, 0.0f, 2 * PI);
	glPopMatrix();

	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;

	glPushMatrix();
	glTranslatef(-topX / 3, height / 3.2f, 0.0f);
	DrawSectorLine_GodFather(0.25f, 0.25, -topZ - 0.01f, color, 3.145f / 6, 3 * PI / 4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX / 3, height / 3.2f, 0.0f);
	DrawSectorLine_GodFather(0.25f, 0.25, -topZ - 0.01f, color, 3.145f / 4, 3 * PI / 3.7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4f, -1.0f, -1.81f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 1.0f);
	glVertex3f(-0.36f, 0.1f, 1.0f);
	glVertex3f(-0.4f, 0.2f, 1.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4f, -1.0f, -0.81f);
	glRotatef(180.0, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glVertex3f(-0.36f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.2f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX - 0.76, height + 0.2, 0.0f);
	DrawSectorLine_GodFather(0.25f, 0.25, -topZ - 0.01f, color, 3.145f / 4, 3 * PI / 3.7);
	glPopMatrix();
}
void DrawGodFatherFace()
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

	DrawFaceDesign_Godfather();
}
void DrawSuit_Godfather(void)
{
	GLfloat redius = 1.0f;

	int circle_points = 1000; //added by praveen 
	GLfloat PI = 3.1415f, angle = 0.0f; //added by praveen

	//white dressed
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.71f);
	glScalef(0.4f, 1.3f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < circle_points; i++)
	{
		angle = -1 * PI * i / circle_points;
		glVertex3f(cos(angle)*redius, sin(angle)*redius, 0.0f);
	}
	glEnd();

	//drawing Dress Line
	glLineWidth(2.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glPushMatrix();
	glTranslatef(0.0f, -0.1f, -0.15f);
	DrawLinesOnDress_GodFather();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.12f, -0.0f);
	glRotatef(180.0, 0.0f, 1.0f, 0.0f);
	DrawLinesOnDress_GodFather();
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	//code for buttons
	//1st
	redius = 0.08f;
	glTranslatef(-0.2f, -0.5f, -0.72f);
	glRotatef(180.0, 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawButtons_GodFather(redius);

	//2nd
	glTranslatef(0.0f, -0.3f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawButtons_GodFather(redius);

	//3rd
	glTranslatef(0.0f, -0.7f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawButtons_GodFather(redius);

	//4th
	glTranslatef(0.0f, -0.3f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawButtons_GodFather(redius);
	glPopMatrix();

	//toy
	glPushMatrix();
	glScalef(0.25f, 0.25f, 1.0f);
	glTranslatef(-0.4f, -0.3f, -0.7f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glEnd();

	redius = 0.5f;
	glLineWidth(2);
	glTranslatef(0.5f, -0.2f, 0.0f);
	glBegin(GL_POLYGON);
	for (angle = 0.0f; angle < 2 * 3.145; angle = angle + 0.001f)
		glVertex3f(redius*cos(angle), redius*sin(angle), 0.0f);
	glEnd();

	glTranslatef(0.4f, 0.2f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	redius = 0.2f;
	glLineWidth(2);
	glTranslatef(-0.7f, -0.7f, -0.77f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (angle = 0.0f; angle < 2 * 3.145; angle = angle + 0.001f)
		glVertex3f(redius*cos(angle), redius*sin(angle), 0.0f);
	glEnd();

	redius = 0.1f;
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (angle = 0.0f; angle < 2 * 3.145; angle = angle + 0.001f)
		glVertex3f(redius*cos(angle), redius*sin(angle), 0.0f);
	glEnd();
	glPopMatrix();
}
void DrawGodFatherChest()
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

	DrawSuit_Godfather();
}

void DrawButtons_GodFather(GLfloat redius)
{

	int circle_points = 1000; //added by praveen
	GLfloat PI = 3.1415f, angle = 0.0f; //added by praveen

	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0.0f; angle <= 2.0*PI; angle = angle + 0.01f)
	{
		glVertex3f(cos(angle)*redius, sin(angle)*redius, 0.0f);
	}
	glEnd();
}

void DrawLinesOnDress_GodFather(void)
{
	glBegin(GL_LINES);

	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, -1.7, 0.1f);

	glVertex3f(-1.3f, 0.2f, 0.1f);
	glVertex3f(-2.0f, -0.1f, 0.1f);

	glVertex3f(-2.0f, -0.1f, 0.1f);
	glVertex3f(-1.7f, -0.4f, 0.1f);

	glVertex3f(-1.0f, -0.1f, 0.1f);
	glVertex3f(-2.0f, -0.5f, 0.1f);

	glVertex3f(-2.0f, -0.5f, 0.1f);
	glVertex3f(-1.4f, -1.7, 0.1f);

	glVertex3f(-1.4f, -1.7, 0.1f);
	glVertex3f(1.4f, -1.7, 0.1f);

	glEnd();
}
/*****************Godfather Functions Over**********************/