#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"Util.h"
#include"SantinoCharacter.h"
#include "MichaelCorleone.h"
#include "GodFather.h"
#include"LucaBracy.h"
#include "LegoWalk.h"
#include "MachineGun.h"
#include "Pistol.h"
#include "Rifle.h"

float gfFaceHeight = 1.5f;
float gfFaceWidth = 0.8f;
float gfNeckHeight = 1.7f;
float gfNeckWidth = 0.5f;
float gfArmHeight = 1.0f;
float gfArmWidth = 0.25f;
float gfChestUpperWidth = 1.0f;
float gfChestLowerWidth = 1.3f;
float gfChestWidth = 0.7f;
float gfChestHeight = 2.2f;

float gfLegWidth = 0.5f;
float gfLegHeight = 1.2f;
float gfLegCylHeight = 1.0f;
float gfLegCylRadius = 0.75f;

float gfFootHeight = 0.35f;
float gfFootWidth = 0.5f;
float gfFootLength = 0.65f;

float gfSpeed = 1.0f;
float gfTranslateX = -15.0f;
float gfTranslateY = 0.0f;
float gfTranslateZ[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

bool gbStopLegoCharacters = false;
float gbAngle = 0.0f;

float lArm[4] = { 30, 70, 30, 70 };
int giLArmDirection[4] = { 1,1,1,1 };

float rArm[4] = { 70, 30, 70, 30 };
int giRArmDirection[4] = { 1,1,1,1 };

float lLeg[4] = { 20, -20, 20, -20 };
int giLLegDirection[4] = { 1,1,1,1 };

float rLeg[4] = { -20 , 20, -20, 20 };
int giRLegDirection[4] = { 1,1,1,1 };

void DrawCircle(float radius)
{
	float angle;
	glLineWidth(2);
	glBegin(GL_POLYGON);
	for (angle = 0.0f; angle < 2 * 3.145; angle = angle + 0.001f)
		glVertex3f(radius*cos(angle), radius*sin(angle), 0.0f);
	glEnd();
}

void DrawSector(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle)
{
	float angle;
	glLineWidth(2);
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

}

void DrawSectorLine(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle)
{
	float angle;
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*cos(angle), bRadius*sin(angle), z);
	glEnd();
}

void DrawSquare(float vertice1[3], float vertice2[3], float vertice3[3], float vertice4[3], float color[3])
{
	float border = 0.1f;
	glBegin(GL_QUADS);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(vertice1[0], vertice1[1], vertice1[2]);
	glVertex3f(vertice2[0], vertice2[1], vertice2[2]);
	glVertex3f(vertice3[0], vertice3[1], vertice3[2]);
	glVertex3f(vertice4[0], vertice4[1], vertice4[2]);
	glEnd();
	if (color[0] == 1.0f)
		border = -0.1f;
	glBegin(GL_LINE_LOOP);
	glColor3f(color[0] + border, color[1] + border, color[2] + border);
	glVertex3f(vertice1[0], vertice1[1], vertice1[2]);
	glVertex3f(vertice2[0], vertice2[1], vertice2[2]);
	glVertex3f(vertice3[0], vertice3[1], vertice3[2]);
	glVertex3f(vertice4[0], vertice4[1], vertice4[2]);
	glEnd();

}

void DrawCubiod(float points[10][3], float color[3])
{
	DrawSquare(points[0], points[1], points[2], points[3], color);//top
	DrawSquare(points[4], points[5], points[6], points[7], color);//bottom
	DrawSquare(points[1], points[5], points[6], points[2], color);//left
	DrawSquare(points[0], points[4], points[7], points[3], color);//right
	DrawSquare(points[0], points[1], points[5], points[4], color);//front
	DrawSquare(points[3], points[2], points[6], points[7], color);//rear
}

void DrawNeck()
{
	float height = -gfNeckHeight;
	float topX = gfNeckWidth;
	float topZ = gfNeckWidth;
	float bottomX = gfNeckWidth;
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
}

void DrawCylinder(float height, float radius, float color[3])
{
	quadric = gluNewQuadric();
	glColor3f(color[0], color[1], color[2]);
	gluCylinder(quadric, radius, radius, height, 30, 30);

	glColor3f(color[0], color[1], color[2]);
	DrawCircle(radius);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, height);

	glColor3f(color[0], color[1], color[2]);
	DrawCircle(radius);
	glPopMatrix();
}

void DrawJoints(float height, float radius, float color[3])
{
	quadric = gluNewQuadric();
	glColor3f(color[0], color[1], color[2]);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, height);

	quadric = gluNewQuadric();
	glColor3f(color[0], color[1], color[2]);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, -height);
}

void DrawWrist(float height, float radius, float color[3])
{
	quadric = gluNewQuadric();
	glColor3f(color[0], color[1], color[2]);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, height);

	quadric = gluNewQuadric();
	glColor3f(1.0f, 0.5f, 0.25f);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, -height);
}

void DrawBiceps(float height, float radius, float color[3])
{
	DrawCylinder(height, radius, color);
	DrawJoints(height, radius, color);
}

void DrawForeArm(float height, float radius, float color[3])
{
	DrawCylinder(height, radius, color);
}

void DrawHead(int currentStickMan)
{
	switch (currentStickMan)
	{
	case 0:
		DrawLucaBracyFace();
		DrawNeck();
		break;
	case 1:
		DrawSantinoFace();
		DrawNeck();
		break;
	case 2:
		DrawMichaelCorleoneFace();
		DrawNeck();
		break;
	case 3:
		DrawGodFatherFace();
		DrawNeck();
		break;
	}
}


void DrawHand(int direction, int currentStickMan)
{
	float armAngle = direction == 1 ? lArm[currentStickMan] : rArm[currentStickMan];
	float color[3] = { 1.0f, 0.5f, 0.25f };

	glPushMatrix();
	glRotatef(armAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(direction * 25, 0.0f, 1.0f, 0.0f);


	switch (currentStickMan)//currentLegoCharacter
	{
	case 0: //Lucca Brassi
		color[0] = 0.5f;
		color[1] = 0.25f;
		color[2] = 0.0f;
		break;

	case 1: //Santino
		color[0] = 1.0f;
		color[1] = 0.5f;
		color[2] = 0.25f;
		break;
	
	case 2:	//Michael Corleone
		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 1.0f;
		break;

	case 3:	//Vito Corleone
		color[0] = 0.0f;
		color[1] = 0.0f;
		color[2] = 0.0f;
		break;
	
	}

	DrawBiceps(gfArmHeight, gfArmWidth, color);
	glTranslatef(0.0f, 0.0f, gfArmHeight);
	glRotatef(armAngle, 1.0f, 0.0f, 0.0f);

	DrawForeArm(gfArmHeight, gfArmWidth,color);
	DrawWrist(gfArmHeight, gfArmWidth, color);
	
	if (direction == 1)

	{
		switch (currentStickMan)//currentLegoCharacter
		{
		case 0: //Lucca Brassi
			break;

		case 1: //Santino
			DrawMachineGun();
			break;

		case 2:	//Michael Corleone
			DrawRifle();
			break;

		case 3:	//Vito Corleone
			DrawPistol(0.0, 0.0, 0.0, 1.0);
			
			break;

		}
	}
	glPopMatrix();
}

void DrawThigh(float color[3])
{
	float height = -gfLegHeight;
	float topX = gfLegWidth;
	float topZ = gfLegWidth;
	float bottomX = gfLegWidth;

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
}

void DrawFoot()
{
	float height = -gfFootHeight;
	float topX = gfFootWidth;
	float topZ = gfFootLength;
	float bottomX = gfFootWidth;
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
}

void DrawLeg(int direction, int currentStickMan)
{
	float legAngle = direction == 1 ? lLeg[currentStickMan] : rLeg[currentStickMan];
	float color[3] = { 0.0f, 0.0f, 0.0f };
	if (currentStickMan == 0)
	{
		color[0] = 0.5f;
		color[1] = 0.25f;
		color[2] = 0.0f;
	}
	glRotatef(legAngle, 1.0f, 0.0f, 0.0f);

	glPushMatrix();
	glRotatef(direction * 90, 0.0f, 1.0f, 0.0f);
	DrawCylinder(gfLegCylHeight, gfLegCylRadius, color);//1,1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(direction* gfLegCylHeight / 2, -gfLegCylRadius + 0.25f, 0.0f);
	DrawThigh(color);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(direction * gfLegCylHeight / 2, -(gfLegCylRadius + gfLegHeight) + 0.25f, -(gfFootLength - gfLegWidth));
	DrawFoot();
	glPopMatrix();
}

void DrawLegSeparation(float color[3])
{
	glPushMatrix();
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	DrawCylinder(0.4f, gfLegCylRadius, color);
	glPopMatrix();
}

void DrawLegoCharacters()
{
	int i = 0;
	float translateX = gfTranslateX;
	float color[3] = { 0.0f, 0.0f, 0.0f };

	for (i = 0; i < 4; i++)
	{
		updateNormalWalk(i);

		glPushMatrix();
		glTranslatef(translateX, 0.0f, gfTranslateZ[i]);
		glRotatef(240.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		DrawHead(i);
		glPopMatrix();

		glTranslatef(0.0f, -gfNeckHeight, 0.0f);
		switch (i)//currentLegoCharacter
		{
		case 0:
			DrawLucaBracyChest();
			break;
		case 1:
			DrawSantinoChest();
			break;
		case 2:
			DrawMichaelChest();
			break;
		case 3:
			DrawGodFatherChest();
			break;
		}

		glPushMatrix();
		glTranslatef(gfChestUpperWidth, -0.25f, 0.0f);
		DrawHand(1, i);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-gfChestUpperWidth, -0.25f, 0.0f);
		DrawHand(-1, i);
		glPopMatrix();

		glTranslatef(0.0f, -gfChestHeight, 0.0f);

		glPushMatrix();
		glTranslatef(0.2f, 0.0f, 0.0f);
		DrawLeg(1, i);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.2f, 0.0f, 0.0f);
		if (i == 0)
		{
			color[0] = 0.5f;
			color[1] = 0.25f;
			color[2] = 0.0f;		
		}
		else
		{
			color[0] = 0.0f;
			color[1] = 0.0f;
			color[2] = 0.0f;
		}
		DrawLegSeparation(color);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.2f, 0.0f, 0.0f);
		DrawLeg(-1, i);
		glPopMatrix();

		glPopMatrix();
		translateX += 4.0f;
	}
}
