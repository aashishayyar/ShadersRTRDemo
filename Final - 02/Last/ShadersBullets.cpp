// Header files
#include<Windows.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include<math.h>
#include"ShadersBullets.h"


GLUquadric *quadricBullet = NULL;
// additional vars
static float rotateSingleBullet = 0;

float yFreeFall = 0.0;


// for changing position of whole 'Shaders'
float xOriginalCordBullet = 0.0;
float yOriginalCordBullet = 0.0;
float zOriginalCordBullet = -8.0;   // this is the distance between camera and the characters

									// structure to hold bullets co-ordinates
typedef struct bullShaderCords {
	float xCord;
	float yCord;
	float zCord;
	float bulletScale;
} bulletShaderData;

// bullets spaced for character 'S'
bulletShaderData positionS[18] = {

	{ -4.60f, 1.50f, -3.00f, 0.20f },
	{ -4.50f, 1.70f, -1.00f, 0.30f },
	{ -4.80f, 2.00f, -1.00f, 0.25f },
	{ -4.80f, 1.70f, -2.50f, 0.30f },
	{ -4.80f, 1.60f, -0.50f, 0.40f },
	{ -4.70f, 1.20f,  0.00f, 0.30f },
	{ -5.20f, 1.00f, -0.40f, 0.35f },
	{ -5.80f, 0.70f, -1.00f, 0.40f },
	{ -4.90f, 0.35f,  0.00f, 0.30f },
	{ -5.00f, 0.10f, -0.50f, 0.40f },
	{ -4.30f, -0.10f, 0.20f, 0.40f },
	{ -4.60f, -0.40f, 0.00f, 0.45f },
	{ -5.15f, -0.75f, -0.70f, 0.35f },
	{ -5.50f, -1.00f, -1.00f, 0.40f },
	{ -6.40f, -1.50f, -2.00f, 0.40f },
	{ -6.50f, -1.75f, -1.70f, 0.25f },
	{ -6.80f, -2.00f, -1.80f, 0.20f },
	{ -6.45f, -2.05f, -1.00f, 0.15f }

};

// bullets spaced for character 'H'
bulletShaderData positionH[13] = {
	{ -3.00f, 0.65f,-1.00f, 0.40f },
	{ -2.50f, 0.25f, 0.50f, 0.30f },
	{ -2.85f, 0.00f,-0.50f, 0.40f },
	{ -2.35f,-0.30f, 1.00f, 0.30f },
	{ -2.80f,-0.70f,-0.40f, 0.35f },
	{ -2.35f,-0.90f, 1.00f, 0.35f },
	{ -4.00f, 0.65f,-1.00f, 0.40f },
	{ -3.40f, 0.25f, 0.30f, 0.30f },
	{ -3.80f,-0.05f,-0.50f, 0.35f },
	{ -3.35f,-0.30f, 0.50f, 0.30f },
	{ -3.75f,-0.65f,-0.40f, 0.35f },
	{ -3.35f,-0.90f, 0.50f, 0.40f },
	{ -2.60f,-0.20f, 1.50f, 0.30f }
};

// bullets spaced for character 'A'
bulletShaderData positionA[15] = {
	{ -1.00f,  0.50f, -0.00f, 0.35f },
	{ -1.10f,  0.20f, -1.50f, 0.50f },
	{ -0.90f, -0.20f,  0.50f, 0.35f },
	{ -0.90f, -0.10f, -2.00f, 0.20f },
	{ -0.85f, -0.55f,  0.50f, 0.35f },
	{ -1.00f, -1.00f, -1.00f, 0.50f },
	{ -0.70f, -0.90f,  1.00f, 0.20f },
	{ -2.50f,  0.10f, -2.50f, 0.50f },
	{ -1.80f, -0.25f,  0.50f, 0.30f },
	{ -2.15f, -0.65f, -1.00f, 0.40f },
	{ -1.65f, -0.80f,  1.00f, 0.30f },
	{ -2.20f,  0.50f, -1.50f, 0.40f },
	{ -2.00f,  0.80f, -3.00f, 0.65f },
	{ -1.50f, -0.30f,  0.50f, 0.30f },
	{ -1.60f, -0.40f, -2.50f, 0.50f }
};

// bullets spaced for character 'D'
bulletShaderData positionD[16] = {
	{ -0.30f, 0.70f,-1.20f, 0.50f },
	{ 0.12f, 0.60f,-0.50f, 0.35f },
	{ 0.45f, 0.40f, 1.00f, 0.40f },
	{ 0.75f, 0.30f, 0.00f, 0.30f },
	{ 1.10f, 0.00f,-2.50f, 0.55f },
	{ 0.80f,-0.30f, 0.20f, 0.30f },
	{ 0.60f,-0.50f, 1.80f, 0.30f },
	{ 0.45f,-0.85f, 0.00f, 0.30f },
	{ 0.20f,-1.00f,-0.80f, 0.45f },
	{ -0.20f,-1.00f, 0.00f, 0.35f },
	{ 0.20f,-1.00f,-0.80f, 0.45f },
	{ 0.20f,-1.00f,-0.80f, 0.45f },
	{ -0.20f,-0.80f,-0.00f, 0.20f },
	{ -0.20f,-0.40f, 2.00f, 0.30f },
	{ -0.25f,-0.20f,-1.00f, 0.40f },
	{ -0.20f, 0.20f, 1.00f, 0.40f }
};

// bullets spaced for character 'E'
bulletShaderData positionE[12] = {
	{ 2.00f,  0.70f, -2.20f, 0.50f },
	{ 2.00f,  0.60f, -0.20f, 0.30f },
	{ 2.50f,  0.60f, -1.00f, 0.40f },
	{ 1.90f,  0.30f, -2.00f, 0.40f },
	{ 1.35f, -0.10f,  1.00f, 0.35f },
	{ 1.35f, -0.10f,  2.50f, 0.20f },
	{ 2.00f, -0.10f,  1.00f, 0.30f },
	{ 2.10f, -0.75f, -3.00f, 0.55f },
	{ 1.40f, -0.90f,  0.30f, 0.35f },
	{ 1.60f, -0.80f,  0.60f, 0.28f },
	{ 2.00f, -0.90f,  0.00f, 0.30f },
	{ 3.00f, -1.20f, -2.80f, 0.50f }
};

// bullets spaced for character 'R'
bulletShaderData positionR[16] = {
	{ 3.30f,  0.60f, -0.80f, 0.40f },
	{ 3.80f,  0.60f, -1.00f, 0.30f },
	{ 3.80f,  0.35f, -0.20f, 0.30f },
	{ 4.20f,  0.03f, -1.00f, 0.30f },
	{ 3.80f, -0.20f, -0.50f, 0.30f },
	{ 3.90f, -0.40f, -1.50f, 0.30f },
	{ 4.40f, -0.70f, -2.00f, 0.35f },
	{ 3.70f, -0.85f,  0.00f, 0.30f },
	{ 4.50f, -1.30f, -1.30f, 0.25f },
	{ 2.40f,  0.15f,  1.50f, 0.25f },
	{ 3.50f, -0.10f, -1.50f, 0.40f },
	{ 2.00f, -0.25f,  2.50f, 0.20f },
	{ 3.70f, -0.80f, -2.00f, 0.40f },
	{ 2.95f, -0.95f,  0.00f, 0.35f },
	{ 3.50f, -1.18f,  1.00f, 0.18f },
	{ 5.10f, -1.90f, -2.00f, 0.20f }
};

// bullets spaced for character 's'
bulletShaderData positionLastS[11] = {
	{ 5.90f,  0.50f, -0.80f, 0.20f },
	{ 5.50f,  0.60f, -0.60f, 0.30f },
	{ 4.80f,  0.52f,  0.00f, 0.30f },
	{ 2.80f,  0.22f,  3.00f, 0.20f },
	{ 4.80f,  0.05f, -0.50f, 0.35f },
	{ 5.10f, -0.10f, -0.60f, 0.40f },
	{ 5.50f, -0.30f, -0.40f, 0.30f },
	{ 4.00f, -0.43f,  2.00f, 0.20f },
	{ 6.75f, -1.10f, -2.50f, 0.40f },
	{ 5.20f, -1.10f, -0.60f, 0.30f },
	{ 4.00f, -0.95f,  1.00f, 0.20f }
};



//// structure for bullets shade
//typedef struct {
//	float rColor;
//	float gColor;
//	float bColor;
//};



void drawShaderCharacter(byte bChar) {

	void drawShadersBullet(float xCord, float yCord, float zCord, float bulletScale);
	
	switch (bChar) {

	case 'S':
		glPushMatrix();
		for (int i = 0; i < 18; i++) {
			glPopMatrix();
			glPushMatrix();
			drawShadersBullet(positionS[i].xCord, positionS[i].yCord, positionS[i].zCord, positionS[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'H':
		
		glPushMatrix();
		for (int i = 0; i < 13; i++) {
			glPopMatrix();
			glPushMatrix();
			drawShadersBullet(positionH[i].xCord, positionH[i].yCord, positionH[i].zCord, positionH[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'A':

		glPushMatrix();
		for (int i = 0; i < 15; i++) {
			glPopMatrix();
			glPushMatrix();
			drawShadersBullet(positionA[i].xCord, positionA[i].yCord, positionA[i].zCord, positionA[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'D':

		glPushMatrix();
		for (int i = 0; i < 16; i++) {
			glPopMatrix();
			glPushMatrix();
			drawShadersBullet(positionD[i].xCord, positionD[i].yCord, positionD[i].zCord, positionD[i].bulletScale);
		}
		glPopMatrix();
		break;

	case 'E':

		glPushMatrix();
		for (int i = 0; i < 12; i++) {
			glPopMatrix();
			glPushMatrix();
			drawShadersBullet(positionE[i].xCord, positionE[i].yCord, positionE[i].zCord, positionE[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'R':

		glPushMatrix();
		for (int i = 0; i < 16; i++) {
			glPopMatrix();
			glPushMatrix();
			drawShadersBullet(positionR[i].xCord, positionR[i].yCord, positionR[i].zCord, positionR[i].bulletScale);
		}
		glPopMatrix();
		break;

	case 's':

		glPushMatrix();
		for (int i = 0; i < 11; i++) {
			glPopMatrix();
			glPushMatrix();
			drawShadersBullet(positionLastS[i].xCord, positionLastS[i].yCord, positionLastS[i].zCord, positionLastS[i].bulletScale);
		}
		glPopMatrix();
		break;
		
		
	}
}



/* x,y,z cords give position of bullet
 BulleteScale --> size of bullet*/
void drawShadersBullet(float xCord, float yCord, float zCord, float bulletScale) {

	//glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//depth prev now after rotate, it's position on current x means actual z-axis
	//keep initial depth fixed as -3.0, and adjust with zCord param
	glTranslatef(xOriginalCordBullet+xCord, yOriginalCordBullet+yCord - yFreeFall, zOriginalCordBullet+zCord);
	
	glPushMatrix(); // save initial position
	//glRotatef(90, 0.0, 1.0, 0.0);
	//gluLookAt(xTest, 0.0, 15.0 , 0.0, 0.0, -5.0, 0.0f, 1.0f, 0.0f);
	glRotatef(180, 0.0, 1.0, 0.0); // temporary
	//gluLookAt(0.0, 0.0f, -xTest, 0.0, 0.0, xTest-5.0, 0.0f, 1.0f, 0.0f); //zoomout effect

	glRotatef((GLfloat)rotateSingleBullet, 0.0, 1.0, 0.0);
	
	
	//glTranslatef(0.0, 0.0, zShift);

	//glTranslatef(xCord, yCord, zCord);
	//here xCord --> depth and zCord --> position on x screen / x-axis -- >IMP

	//glTranslatef(0.0, -0.5, 0.0); 

	glPushMatrix(); // save position of first object which will rotate around the initial point
	glColor3f(160.0f / 255.0f, 82.0f / 255.0f, 45.0f / 255.0f);
	quadricBullet = gluNewQuadric();

	// inner disk back of the bullet
	gluDisk(quadricBullet, 0.001f, 0.35f*bulletScale, 20, 20);

	//yellowinsh shade
	glColor3f(218.0f / 255.0f, 168.0f / 255.0f, 32.0f / 255.0f);
	quadricBullet = gluNewQuadric();

	// outer disk back of the bullet
	gluDisk(quadricBullet, 0.35f*bulletScale, 0.5f*bulletScale, 20, 20);

	// now we will draw second object which is related to the first one
	// back cylinder
	glPopMatrix(); // actually not needed since we didn't change the position

	glPushMatrix(); // save the previous position
	glColor3f(218.0f / 255.0f, 168.0f / 255.0f, 32.0f / 255.0f);
	quadricBullet = gluNewQuadric();
	gluCylinder(quadricBullet, 0.5f*bulletScale, 0.5f*bulletScale, 0.08f*bulletScale, 20, 20);
	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.08f*bulletScale); // since we have rotated the whole matrix by hard
	// coded 90 degrees first, so every axis got shifted and +z takes place of +x
	//glRotatef((GLfloat)extra1, 0.0, 0.0, 1.0);
	//glTranslatef(0.0, -0.5, 0.0);

	glPushMatrix();
	glColor3f(184.0f / 255.0f, 134.0f / 255.0f, 11.0f / 255.0f);
	quadricBullet = gluNewQuadric();
	gluDisk(quadricBullet, 0.01f, 0.5f*bulletScale, 20, 20);

	glPopMatrix(); // translated position by 0.05

	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix(); // save the previous position second cylinder
	glColor3f(218.0f / 255.0f, 168.0f / 255.0f, 32.0f / 255.0f);
	quadricBullet = gluNewQuadric();
	gluCylinder(quadricBullet, 0.4f*bulletScale, 0.4f*bulletScale, 0.15f*bulletScale, 20, 20);

	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.15f*bulletScale);
	glPushMatrix(); 
	glColor3f(184.0f / 255.0f, 134.0f / 255.0f, 11.0f / 255.0f);
	//glColor3f(0.6, 0.2, 0.0);
	quadricBullet = gluNewQuadric();
	gluDisk(quadricBullet, 0.01f, 0.5f*bulletScale, 20, 20);

	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.5);
	glPushMatrix();
	glColor3f(0.9f, 0.7f, 0.2f);
	quadricBullet = gluNewQuadric();
	gluCylinder(quadricBullet, 0.5f*bulletScale, 0.5f*bulletScale, 1.3f*bulletScale, 20, 20);

	glPopMatrix();

	//glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 1.3f*bulletScale);
	glPushMatrix(); // save the previous position second cylinder
	glScalef(1.0f, 1.0f, 2.0f);
	glColor3f(210.0f / 255.0f, 105.0f / 255.0f, 30.0f / 255.0f);
	quadricBullet = gluNewQuadric();
	gluSphere(quadricBullet, 0.5f*bulletScale, 20, 20);

	glPopMatrix();
	glPopMatrix();

}
