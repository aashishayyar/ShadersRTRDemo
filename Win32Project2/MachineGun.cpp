#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"MachineGun.h"
#include"Util.h"

#define PI 3.1415926535898

//for translating half circle
float ZAxis = 0.0f;
GLfloat angleMG;
GLfloat baseMG, topMG, radiusMG, heightMG;
float GunRotateMG = 0.0f;

//float GunRotate = 0.0f;

void updateMachineGun(void)
{
	GunRotateMG = GunRotateMG + 0.0f;

	if (GunRotateMG >= 360.0)
		GunRotateMG = 0.0f;
}

void DrawMachineGunCircle(float radiusMG)
{
	glBegin(GL_TRIANGLE_FAN);
	for (angleMG = 0.0f; angleMG <= 2.0*PI; angleMG = angleMG + 0.01f)
	{
		glVertex3f((float)cos(angleMG)*radiusMG, (float)sin(angleMG)*radiusMG, 0.0f);
	}
	glEnd();
}

void DrawMachineGunHalfCircle(float ZAxis)
{
	float angle;
	GLfloat red = 1.3f;
	GLint circle_points = 1000; //try using 1000 or 10000

	glTranslatef(0.0f, 0.5f, ZAxis);
	glScalef(0.60f, 1.0f, 1.0f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

	glLineWidth(7.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.52f,0.37f,0.26f);
	for (int i = 0; i < circle_points; i++)
	{
		angle = 1 * (float)PI *(float)i / (float)circle_points;
		glVertex2f((float)cos(angle)*red, (float)sin(angle)*red);
	}
	glEnd();
}

void DrawMachineGunCylinder(float baseMG ,float topMG,float heightMG)
{
	glColor3f(0.9f, 0.9f, 0.9f);//Gray final
	quadric = gluNewQuadric();
	gluCylinder(quadric, baseMG, topMG, heightMG, 10, 10);
}

void DrawMachineGunCube(void)
{
	glBegin(GL_QUADS);

	//topMG face
	glColor3f(0.70f, 0.70f, 0.70f);//Gray final
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	//Bottom face
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	//front face 
	glVertex3f(1.0f, 1.0f, 1.0f);//right-topMG
	glVertex3f(-1.0f, 1.0f, 1.0f);//left-topMG
	glVertex3f(-1.0f, -1.0f, 1.0f);//left-bottom
	glVertex3f(1.0f, -1.0f, 1.0f);//right-bottom

	//Back face
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//Right face
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//left face
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}

void DrawMachineGun(void)
{
	glPushMatrix();
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glScalef(0.7f, 0.7f, 0.7f);
		//main cylinder
		glPushMatrix();
			baseMG = topMG = radiusMG = 0.6f;
			heightMG = 2.0f;			
			DrawMachineGunCylinder(baseMG, topMG, heightMG);
			DrawMachineGunCircle(radiusMG);
			glTranslatef(0.0f, 0.0f, heightMG);
			DrawMachineGunCircle(radiusMG);
		glPopMatrix();
		
		//front pipes	
		//circle between the front pipes
		glPushMatrix();
			glRotatef(GunRotateMG,0.0f,0.0f,1.0f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, heightMG + 1.0F);
				glColor3f(0.65f, 0.50f, 0.39f);
				DrawMachineGunCircle(radiusMG);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0f, 0.0f, heightMG + 1.8F);
				glColor3f(0.65f, 0.50f, 0.39f);
				DrawMachineGunCircle(radiusMG);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0f, 0.0f, heightMG);
				baseMG = topMG = radiusMG = 0.12f;
				DrawMachineGunCylinder(baseMG, topMG, heightMG + 0.5F);
				glColor3f(0.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, heightMG + 0.5F);
				DrawMachineGunCircle(radiusMG);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.33f, 0.0f, heightMG);
				baseMG = topMG = radiusMG = 0.12f;
				DrawMachineGunCylinder(baseMG, topMG, heightMG + 0.5F);
				glColor3f(0.0f, 0.0f, 0.0f);
				glTranslatef(-0.01f, 0.0f, heightMG + 0.5F);
				DrawMachineGunCircle(radiusMG);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.33f, 0.0f, heightMG);
				baseMG = topMG = radiusMG = 0.12f;
				DrawMachineGunCylinder(baseMG, topMG, heightMG + 0.5F);
				glColor3f(0.0f, 0.0f, .0f);
				glTranslatef(0.01f, 0.0f, heightMG + 0.5F);
				DrawMachineGunCircle(radiusMG);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.2f, 0.35f, heightMG);
				baseMG = topMG = radiusMG = 0.12f;
				DrawMachineGunCylinder(baseMG, topMG, heightMG + 0.5F);
				glColor3f(0.0f, 0.0f, 0.0f);
				glTranslatef(0.01f, -0.01f, heightMG + 0.5F);
				DrawMachineGunCircle(radiusMG);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.2f, -0.35f, heightMG);
				baseMG = topMG = radiusMG = 0.12f;
				DrawMachineGunCylinder(baseMG, topMG, heightMG + 0.5F);
				glColor3f(0.0f, 0.0f, 0.0f);
				glTranslatef(-0.01f, 0.0f, heightMG + 0.5F);
				DrawMachineGunCircle(radiusMG);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.15f, 0.35f, heightMG);
				baseMG = topMG = radiusMG = 0.12f;
				DrawMachineGunCylinder(baseMG, topMG, heightMG + 0.5F);
				glColor3f(0.0f, 0.0f, 0.0f);
				glTranslatef(-0.01f, -0.01f, heightMG + 0.5F);
				DrawMachineGunCircle(radiusMG);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.15f, -0.35f, heightMG);
				baseMG = topMG = radiusMG = 0.12f;
				DrawMachineGunCylinder(baseMG, topMG, heightMG + 0.5F);
				glTranslatef(0.01f, 0.0f, heightMG + 0.5F);
				glColor3f(0.0f, 0.0f, 0.0f);
				DrawMachineGunCircle(radiusMG);
			glPopMatrix();
		glPopMatrix();

		//main cylinder left
		glPushMatrix();
			baseMG = topMG = radiusMG = 0.3f, heightMG = 1.5f;
			glTranslatef(-0.7f, -0.5f, 0.0f);
			DrawMachineGunCylinder(baseMG, topMG, heightMG);
			glColor3f(1.0f, 1.0f, 0.0f);
			DrawMachineGunCircle(radiusMG);
			glTranslatef(0.0f, 0.0f, heightMG);
			DrawMachineGunCircle(radiusMG);
		glPopMatrix();

		//main cylinder right
		glPushMatrix();
			baseMG = topMG = radiusMG = 0.3f, heightMG = 1.5f;
			glTranslatef(0.7f, -0.5f, 0.0f);
			DrawMachineGunCylinder(baseMG, topMG, heightMG);
			glColor3f(1.0f, 1.0f, 0.0f);
			DrawMachineGunCircle(radiusMG);
			glTranslatef(0.0f, 0.0f, heightMG);
			DrawMachineGunCircle(radiusMG);
		glPopMatrix();


		//Half circle center in GUN
		glPushMatrix();
			DrawMachineGunHalfCircle(2.0f);
		glPopMatrix();
				
		glPushMatrix();
			DrawMachineGunHalfCircle(1.9f);
		glPopMatrix();
		
		glPushMatrix();
			DrawMachineGunHalfCircle(1.8f);
		glPopMatrix();
		
		glPushMatrix();
			DrawMachineGunHalfCircle(1.7f);
		glPopMatrix();

		glPushMatrix();
			DrawMachineGunHalfCircle(1.6f);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, 0.9f, 1.0f);
			glScalef(0.30f, 0.10f, 1.1f);
			DrawMachineGunCube();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0F, 0.7F, 1.8f);
			glScalef(0.85f, 0.20f, 0.20f);
			DrawMachineGunCube();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.5F, 1.1F, 1.8f);
			glScalef(0.06f, 0.3f, 0.1f);
			DrawMachineGunCube();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.5F, 1.1F, 1.8f);
			glScalef(0.06f, 0.3f, 0.1f);
			DrawMachineGunCube();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.0F, 1.4F, 1.8f);
			glScalef(0.55f, 0.05f, 0.1f);
			DrawMachineGunCube();
		glPopMatrix();

	glPopMatrix();	
	updateMachineGun();
}
