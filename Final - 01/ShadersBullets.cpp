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
	{ -4.6, 1.5, -3.0, 0.2 },
	{ -4.5, 1.7, -1.0, 0.3 },
	{ -4.8, 2.0, -1.0, 0.25 },
	{ -4.8, 1.7, -2.5, 0.3 },
	{ -4.8, 1.6, -0.5, 0.4 },
	{ -4.7, 1.2, 0.0, 0.3 },
	{ -5.2, 1.0, -0.4, 0.35 },
	{ -5.8, 0.7, -1.0, 0.4 },
	{ -4.9, 0.35, 0.0, 0.3 },
	{ -5.0, 0.1, -0.5, 0.4 },
	{ -4.3, -0.1, 0.2, 0.4 },
	{ -4.6, -0.4, 0.0, 0.45 },
	{ -5.15, -0.75, -0.7, 0.35 },
	{ -5.5, -1.0, -1.0, 0.4 },
	{ -6.4, -1.5, -2.0, 0.4 },
	{ -6.5, -1.75, -1.7, 0.25 },
	{ -6.8, -2.0, -1.8, 0.2 },
	{ -6.45, -2.05, -1.0, 0.15 }
};

// bullets spaced for character 'H'
bulletShaderData positionH[13] = {
	{ -3.0, 0.65, -1.0, 0.4 },
	{ -2.5, 0.25, 0.5, 0.3 },
	{ -2.85, 0.0, -0.5, 0.4 },
	{ -2.35, -0.3, 1.0, 0.3 },
	{ -2.8, -0.7, -0.4, 0.35 },
	{ -2.35, -0.9, 1.0, 0.35 },
	{ -4.0, 0.65, -1.0, 0.4 },
	{ -3.4, 0.25, 0.3, 0.3 },
	{ -3.8, -0.05, -0.5, 0.35 },
	{ -3.35, -0.3, 0.5, 0.3 },
	{ -3.75, -0.65, -0.4, 0.35 },
	{ -3.35, -0.9, 0.5, 0.4 },
	{ -2.6, -0.2, 1.5, 0.3 }
};

// bullets spaced for character 'A'
bulletShaderData positionA[15] = {
	{ -1.0, 0.5, -0.0, 0.35 },
	{ -1.1, 0.2, -1.5, 0.5 },
	{ -0.9, -0.2, 0.5, 0.35 },
	{ -0.9, -0.1, -2.0, 0.2 },
	{ -0.85f, -0.55, 0.5, 0.35 },
	{ -1.0, -1.0, -1.0, 0.5 },
	{ -0.7, -0.9, 1.0, 0.2 },
	{ -2.5, 0.1, -2.5, 0.5 },
	{ -1.8, -0.25, 0.5, 0.3 },
	{ -2.15, -0.65, -1.0, 0.4 },
	{ -1.65, -0.8, 1.0, 0.3 },
	{ -2.2, 0.5, -1.5, 0.4 },
	{ -2.0, 0.8, -3.0, 0.65 },
	{ -1.5, -0.3, 0.5, 0.3 },
	{ -1.6, -0.4, -2.5, 0.5 }
};

// bullets spaced for character 'D'
bulletShaderData positionD[16] = {
	{ -0.3, 0.7, -1.2, 0.5 },
	{ 0.12, 0.6, -0.5, 0.35 },
	{ 0.45, 0.4, 1.0, 0.4 },
	{ 0.75, 0.3, 0.0, 0.3 },
	{ 1.1, 0.0, -2.5, 0.55 },
	{ 0.8, -0.3, 0.2, 0.3 },
	{ 0.6, -0.5, 1.8, 0.3 },
	{ 0.45, -0.85, 0.0, 0.3 },
	{ 0.2, -1.0, -0.8, 0.45 },
	{ -0.2, -1.0, 0.0, 0.35 },
	{ 0.2, -1.0, -0.8, 0.45 },
	{ 0.2, -1.0, -0.8, 0.45 },
	{ -0.2, -0.8, -0.0, 0.2 },
	{ -0.2, -0.4, 2.0, 0.3 },
	{ -0.25, -0.2, -1.0, 0.4 },
	{ -0.2, 0.2, 1.0, 0.4 }
};

// bullets spaced for character 'E'
bulletShaderData positionE[12] = {
	{ 2.0, 0.7, -2.2, 0.5 },
	{ 2.0, 0.6, -0.2, 0.3 },
	{ 2.5, 0.6, -1.0, 0.4 },
	{ 1.9, 0.3, -2.0, 0.4 },
	{ 1.35, -0.1, 1.0, 0.35 },
	{ 1.35, -0.1, 2.5, 0.2 },
	{ 2.0, -0.1, 1.0, 0.3 },
	{ 2.1, -0.75, -3.0, 0.55 },
	{ 1.4, -0.9, 0.3, 0.35 },
	{ 1.6, -0.8, 0.6, 0.28 },
	{ 2.0, -0.9, 0.0, 0.3 },
	{ 3.0, -1.2, -2.8, 0.5 }
};

// bullets spaced for character 'R'
bulletShaderData positionR[16] = {
	{ 3.3, 0.6, -0.8, 0.4 },
	{ 3.8, 0.6, -1.0, 0.3 },
	{ 3.8, 0.35, -0.2, 0.3 },
	{ 4.2f, 0.03, -1.0, 0.3 },
	{ 3.8f, -0.2, -0.5, 0.3 },
	{ 3.9, -0.4, -1.5, 0.3 },
	{ 4.4, -0.7, -2.0, 0.35 },
	{ 3.7, -0.85, 0.0, 0.3 },
	{ 4.5, -1.3, -1.3, 0.25 },
	{ 2.4, 0.15, 1.5, 0.25 },
	{ 3.5, -0.1, -1.5, 0.4 },
	{ 2.0, -0.25, 2.5, 0.2 },
	{ 3.7, -0.8, -2.0, 0.4 },
	{ 2.95, -0.95, 0.0, 0.35 },
	{ 3.5, -1.18, 1.0, 0.18 },
	{ 5.1, -1.9, -2.0, 0.2 }
};

// bullets spaced for character 's'
bulletShaderData positionLastS[11] = {
	{ 5.9, 0.5, -0.8, 0.2 },
	{ 5.5, 0.6, -0.6, 0.3 },
	{ 4.8, 0.52, 0.0, 0.3 },
	{ 2.8, 0.22, 3.0, 0.2 },
	{ 4.8, 0.05, -0.5, 0.35 },
	{ 5.1, -0.1, -0.6, 0.4 },
	{ 5.5, -0.3, -0.4, 0.3 },
	{ 4.0, -0.43, 2.0, 0.2 },
	{ 6.75, -1.1, -2.5, 0.4 },
	{ 5.2, -1.1, -0.6, 0.3 },
	{ 4.0, -0.95, 1.0, 0.2 }
};


// structure for bullets shade
typedef struct {
	float rColor;
	float gColor;
	float bColor;
};



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
	glColor3f(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0);
	quadricBullet = gluNewQuadric();

	// inner disk back of the bullet
	gluDisk(quadricBullet, 0.001, 0.35*bulletScale, 20, 20);

	//yellowinsh shade
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadricBullet = gluNewQuadric();

	// outer disk back of the bullet
	gluDisk(quadricBullet, 0.35*bulletScale, 0.5*bulletScale, 20, 20);

	// now we will draw second object which is related to the first one
	// back cylinder
	glPopMatrix(); // actually not needed since we didn't change the position

	glPushMatrix(); // save the previous position
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadricBullet = gluNewQuadric();
	gluCylinder(quadricBullet, 0.5*bulletScale, 0.5*bulletScale, 0.08*bulletScale, 20, 20);
	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.08*bulletScale); // since we have rotated the whole matrix by hard
	// coded 90 degrees first, so every axis got shifted and +z takes place of +x
	//glRotatef((GLfloat)extra1, 0.0, 0.0, 1.0);
	//glTranslatef(0.0, -0.5, 0.0);

	glPushMatrix();
	glColor3f(184.0 / 255.0, 134.0 / 255.0, 11.0 / 255.0);
	quadricBullet = gluNewQuadric();
	gluDisk(quadricBullet, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix(); // translated position by 0.05

	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix(); // save the previous position second cylinder
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadricBullet = gluNewQuadric();
	gluCylinder(quadricBullet, 0.4*bulletScale, 0.4*bulletScale, 0.15*bulletScale, 20, 20);

	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.15*bulletScale);
	glPushMatrix(); 
	glColor3f(184.0 / 255.0, 134.0 / 255.0, 11.0 / 255.0);
	//glColor3f(0.6, 0.2, 0.0);
	quadricBullet = gluNewQuadric();
	gluDisk(quadricBullet, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.5);
	glPushMatrix();
	glColor3f(0.9, 0.7, 0.2);
	quadricBullet = gluNewQuadric();
	gluCylinder(quadricBullet, 0.5*bulletScale, 0.5*bulletScale, 1.3*bulletScale, 20, 20);

	glPopMatrix();

	//glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 1.3*bulletScale);
	glPushMatrix(); // save the previous position second cylinder
	glScalef(1.0, 1.0, 2.0);
	glColor3f(210.0 / 255.0, 105.0 / 255.0, 30.0 / 255.0);
	quadricBullet = gluNewQuadric();
	gluSphere(quadricBullet, 0.5*bulletScale, 20, 20);

	glPopMatrix();
	glPopMatrix();

}
