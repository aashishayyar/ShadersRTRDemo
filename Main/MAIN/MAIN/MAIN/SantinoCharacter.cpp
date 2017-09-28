#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"Util.h"
#include "SantinoCharacter.h"

void DrawSantinoFace()
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

	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;

	glPushMatrix();
	glTranslatef(-topX / 3, height / 3, 0.0f);
	DrawSector(0.15f, 0.15f, -topZ - 0.01f, color, 0.0f, 2 * 3.145);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX / 3, height / 3, 0.0f);
	DrawSector(0.15f, 0.15, -topZ - 0.01f, color, 0.0f, 2 * 3.145);
	glPopMatrix();

	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;

	glPushMatrix();
	glTranslatef(-topX / 3, height / 3 + 0.05, 0.0f);
	DrawSector(0.05f, 0.05f, -topZ - 0.03f, color, 0.0f, 2 * 3.145);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX / 3, height / 3 + 0.05, 0.0f);
	DrawSector(0.05f, 0.05, -topZ - 0.03f, color, 0.0f, 2 * 3.145);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, height / 1.35f, 0.0f);
	//DrawSectorLine(0.25f, 0.25, -topZ - 0.01f, color, 3.145f/5, 3* 3.145f/4);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.3f, 0.0f, -topZ - 0.01f);
	glVertex3f(-0.36f, 0.1f, -topZ - 0.01f);
	glVertex3f(-0.4f, 0.2f, -topZ - 0.01f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-topX / 3, height / 3.2f, 0.0f);
	DrawSectorLine(0.25f, 0.25, -topZ - 0.01f, color, 3.145f / 6, 3 * 3.145f / 4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX / 3, height / 3.2f, 0.0f);
	DrawSectorLine(0.25f, 0.25, -topZ - 0.01f, color, 3.145f / 4, 3 * 3.145f / 3.7);
	glPopMatrix();

}

void DrawSantinoChest()
{
	float chestBottomHeight = 0.3f;
	float height = -(gfChestHeight - chestBottomHeight);
	float topX = gfChestUpperWidth;
	float topZ = gfChestWidth;
	float bottomX = gfChestLowerWidth;
	float color[3] = { 1.0f, 1.0f, 1.0f };

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

	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	DrawCubiod(pointsChestBottom, color);

	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;

	DrawSquare(points[3], points[2], points[6], points[7], color);

	color[0] = 1.0f;
	color[1] = 0.5f;
	color[2] = 0.25f;
	DrawSector(gfChestUpperWidth / 2.5, gfChestUpperWidth / 2.5, -topZ - 0.01f, color, 3.145, 2 * 3.145);


	color[0] = 1.0f;
	color[1] = 0.5f;
	color[2] = 0.25f;
	glPushMatrix();
	glTranslatef(-gfChestUpperWidth, 0.0f, 0.0f);
	DrawSector(gfChestUpperWidth / 3.5, gfChestUpperWidth, -topZ - 0.01f, color, 1.3*3.145f, 2 * 3.145f);
	glPopMatrix();

	color[0] = 1.0f;
	color[1] = 0.5f;
	color[2] = 0.25f;
	glPushMatrix();
	glTranslatef(gfChestUpperWidth, 0.0f, 0.0f);
	DrawSector(gfChestUpperWidth / 3.5, gfChestUpperWidth, -topZ - 0.01f, color, 3.145f, 1.7f * 3.145f);
	glPopMatrix();

	color[0] = 1.0f;
	color[1] = 0.5f;
	color[2] = 0.25f;
	glPushMatrix();
	glTranslatef(-gfChestUpperWidth, 0.0f, 0.0f);
	DrawSector(gfChestUpperWidth / 3.5, gfChestUpperWidth, -topZ - 0.01f, color, 1.3*3.145, 2 * 3.145);
	glPopMatrix();



	float leftStrapPoints[4][3] = {
		{ gfChestUpperWidth / 2, 0, -topZ - 0.02f },
		{ gfChestUpperWidth / 2 + 0.15f, 0, -topZ - 0.02f },
		{ gfChestUpperWidth / 2 + 0.15f, height, -topZ - 0.02f },
		{ gfChestUpperWidth / 2, height, -topZ - 0.02f },
	};
	color[0] = 0.5f;
	color[1] = 0.25f;
	color[2] = 0.0f;
	DrawSquare(leftStrapPoints[0], leftStrapPoints[1], leftStrapPoints[2], leftStrapPoints[3], color);

	float leftButtonPoints[4][3] = {
		{ gfChestUpperWidth / 2 - 0.05f, height / 2, -topZ - 0.025f },
		{ gfChestUpperWidth / 2 + 0.2f, height / 2 , -topZ - 0.025f },
		{ gfChestUpperWidth / 2 + 0.2f, height / 2 - 0.17f, -topZ - 0.025f },
		{ gfChestUpperWidth / 2 - 0.05f, height / 2 - 0.17f, -topZ - 0.025f },
	};
	color[0] = 0.2f;
	color[1] = 0.2f;
	color[2] = 0.2f;
	DrawSquare(leftButtonPoints[0], leftButtonPoints[1], leftButtonPoints[2], leftButtonPoints[3], color);

	float rightStrapPoints[4][3] = {
		{ -gfChestUpperWidth / 2, 0, -topZ },
		{ -gfChestUpperWidth / 2 - 0.15f, 0, -topZ },
		{ -gfChestUpperWidth / 2 - 0.15f, height, -topZ },
		{ -gfChestUpperWidth / 2 , height, -topZ },
	};
	color[0] = 0.5f;
	color[1] = 0.25f;
	color[2] = 0.0f;
	DrawSquare(rightStrapPoints[0], rightStrapPoints[1], rightStrapPoints[2], rightStrapPoints[3], color);

	float rightButtonPoints[4][3] = {
		{ -gfChestUpperWidth / 2 + 0.05f, height / 2, -topZ - 0.025f },
		{ -gfChestUpperWidth / 2 - 0.2f, height / 2 , -topZ - 0.025f },
		{ -gfChestUpperWidth / 2 - 0.2f, height / 2 - 0.15f, -topZ - 0.025f },
		{ -gfChestUpperWidth / 2 + 0.05f, height / 2 - 0.15f, -topZ - 0.025f },
	};

	color[0] = 0.2f;
	color[1] = 0.2f;
	color[2] = 0.2f;
	DrawSquare(rightButtonPoints[0], rightButtonPoints[1], rightButtonPoints[2], rightButtonPoints[3], color);
}