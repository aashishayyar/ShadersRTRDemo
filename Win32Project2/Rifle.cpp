#include"Rifle.h"

#define PI 3.1415926535898

float baseRifle; //for baseRifle of the cylinder
float topRifle; //for topRifle of the cylinder
float heightRifle; //for heightRifle of the cylinder

float angleRifle; //used in circle

int RotateGun=90;

//rotate the each part of the Gun
float RotateAngle=90.0f;

void DrawRifleCylinder(float baseRifle, float topRifle, float heightRifle )
{
	quadric = gluNewQuadric();
	gluCylinder(quadric, baseRifle, topRifle, heightRifle, 20, 20);
}

void DrawRifleCircle(float redius)
{
	glBegin(GL_TRIANGLE_FAN);
	for (angleRifle = 0.0f; angleRifle <= 2.0*PI; angleRifle = angleRifle + 0.01f)
	{
		glVertex3f((float)cos(angleRifle)*redius, (float)sin(angleRifle)*redius, 0.0f);
	}
	glEnd();
}

void CUBE(void)
{
	glBegin(GL_QUADS);
	
	//topRifle face
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
	glVertex3f(1.0f, 1.0f, 1.0f);//right-topRifle
	glVertex3f(-1.0f, 1.0f, 1.0f);//left-topRifle
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

void FireStickDecoration(void)
{
	float angleRifle;
	float red = 0.4f;

	glPushMatrix();
		GLint circle_points = 1000;
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glLineWidth(7.0f);
		glBegin(GL_LINE_LOOP);
		glColor3f(0.80f, 0.80f, 0.80f);//
		for (int i = 0; i < circle_points; i++)
		{
			angleRifle = (float)1 * (float)PI *(float)i / (float)circle_points;
			glVertex2f((float)cos(angleRifle)*red, (float)sin(angleRifle)*red);
		}
		glEnd();
	glPopMatrix();

	glTranslatef(0.15f, 0.1f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.0f, -0.1f, 0.0f);
	glVertex3f(-0.2f, -0.4f, 0.0f);
	glEnd();
}

void DrawRifle()
{
	glPushMatrix();
	glScalef(0.50f, 0.50f, 0.50f);
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 1.0f, 3.0f);
		glRotatef((GLfloat)RotateGun, 0.0f, 1.0f, 0.0f);
		//Middle Gray Cylinder part
		glPushMatrix();
			baseRifle = topRifle = 0.3f, heightRifle = 3.0f;
			glTranslatef(-heightRifle+1.2f, 0.1f, 0.0f);
			glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
			glColor3f(0.60f, 0.60f, 0.60f);//Gray final
			DrawRifleCylinder(baseRifle, topRifle, heightRifle);
			DrawRifleCircle(baseRifle);
		glPopMatrix();

		//first Pipe part 
		glPushMatrix();
			baseRifle = topRifle = 0.1f, heightRifle = 1.3f;
			glTranslatef(-heightRifle-1.5f , 0.05f, 0.0f);
			glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
			glColor3f(0.81f, 0.71f, 0.23f);
			DrawRifleCylinder(baseRifle, topRifle, heightRifle);
			DrawRifleCircle(baseRifle);
			baseRifle = topRifle = 0.12f, heightRifle = 0.3f;
			glTranslatef(0.0f, 0.0f, -0.3f);
			glColor3f(1.0f, 1.0f, 0.0f);
			DrawRifleCylinder(baseRifle, topRifle, heightRifle);
			glColor3f(0.0f, 0.0f, 0.0f);
			DrawRifleCircle(baseRifle);
		glPopMatrix();

		//Upper small pipe stick
		glPushMatrix();
			baseRifle = topRifle = 0.08f, heightRifle = 0.3f;
			glTranslatef(-heightRifle-1.8f, 0.2f, 0.0f);
			glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
			glColor3f(0.80f, 0.80f, 0.80f);//Light Gray final
			DrawRifleCylinder(baseRifle, topRifle, heightRifle);
			glColor3f(0.0f, 0.0f, 0.0f);
			DrawRifleCircle(baseRifle);
		glPopMatrix();

		//topRifle Camera (cylinder)
		glPushMatrix();
			baseRifle = topRifle = 0.1f, heightRifle = 0.9f;
			glTranslatef(0.2f, 0.5f, 0.0f);
			glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
			glColor3f(0.75f, 0.75f, 0.75f);//Light Gray final
			DrawRifleCylinder(baseRifle, topRifle, heightRifle);
			DrawRifleCircle(baseRifle);
		glPopMatrix();

		//topRifle cube
		glPushMatrix();
			glTranslatef(0.5f, -0.3f, 0.0f);
			glScalef(0.40f, 0.10f, 0.15f);
			CUBE();
		glPopMatrix();

		//down left cube
		glPushMatrix();
			glTranslatef(0.2f, -0.6f, 0.0f);
			glScalef(0.10f, 0.30f, 0.15f);
			CUBE();
		glPopMatrix();

		//down right cube
		glPushMatrix();
			glTranslatef(1.0f, -0.45f, 0.0f);
			glScalef(0.10f, 0.30f, 0.15f);
			glColor3f(0.35f, 0.16f, 0.14f);//Brown final
			CUBE();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.6f, -0.4f, 0.0f);
			FireStickDecoration();
			//back side of gun
			glPushMatrix();
				baseRifle = 0.2f, topRifle = 0.3f, heightRifle = 1.5f;
				glTranslatef(0.4f, 0.5f, 0.0f);
				glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
				glRotatef(RotateAngle - 70.0f, 1.0f, 0.0f, 1.0f);
				glColor3f(1.0f,168/255.0f,81.0f/255.0f);//Brown final
				DrawRifleCylinder(baseRifle, topRifle, heightRifle);
				glTranslatef(0.0f, 0.0f, 1.5f);
				DrawRifleCircle(topRifle);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();//OUTER stack

}