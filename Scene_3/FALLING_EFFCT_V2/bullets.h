#include<gl/GL.h>
#include<GL/glu.h>

void drawBullet1()
{
	glColor3f((GLfloat)218 / 255, (GLfloat)165 / 255, (GLfloat)32 / 255);

	glTranslatef(0.0f, 0.0f, -7.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();

	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

	glColor3f(0.4f, 0.9f, 1.0f);

	glColor3f((GLfloat)218 / 255, (GLfloat)165 / 255, (GLfloat)32 / 255);

	gluCylinder(quadric, 0.70, 0.70, 2.0, 30, 30);

	glTranslatef(0.0, 0.0, 2.0);
	gluCylinder(quadric, 0.70, 0.5, 1.0, 30, 30);

	glTranslatef(0.0, 0.0, -2.1);
	gluCylinder(quadric, 0.60, 0.60, 1.0, 30, 30);
	glTranslatef(0.0, 0.0, -0.1);
	gluCylinder(quadric, 0.70, 0.70, 0.1, 30, 30);
}