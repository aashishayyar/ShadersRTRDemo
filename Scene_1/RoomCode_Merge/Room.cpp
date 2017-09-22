#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include "Header_Manishar.h"

#pragma Room
void drawRoom() {
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	int size = 27;
	int count = 1;
	glLineWidth(0.5f);
	glBegin(GL_LINES);
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	for (float i = count; i <= size; i += count) { //Floor
		glVertex3f(-size, 0, i);
		glVertex3f(size, 0, i);
		glVertex3f(-size, 0, -i);
		glVertex3f(size, 0, -i);
		glVertex3f(i, 0, -size);
		glVertex3f(i, 0, size);
		glVertex3f(-i, 0, -size);
		glVertex3f(-i, 0, size);
	}

	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex3f(roomDepth.xCor, roomDepth.yCor, -roomDepth.zCor); //Back
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, -roomDepth.zCor);
	glVertex3f(-roomDepth.xCor, 0.0f, -roomDepth.zCor);
	glVertex3f(roomDepth.xCor, 0.0f, -roomDepth.zCor);

	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-roomDepth.xCor, 0.0f, -roomSize.zCor); //Right
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, -roomSize.zCor);
	glVertex3f(-roomSize.xCor, roomDepth.yCor, roomSize.zCor);
	glVertex3f(-roomSize.xCor, 0.0f, roomSize.zCor);

	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(roomDepth.xCor, 0.0f, -roomSize.zCor); //Left
	glVertex3f(roomDepth.xCor, roomDepth.yCor, -roomSize.zCor);
	glVertex3f(roomSize.xCor, roomDepth.yCor, roomSize.zCor);
	glVertex3f(roomSize.xCor, 0.0f, roomSize.zCor);

	glEnd();
	glPopMatrix();
}