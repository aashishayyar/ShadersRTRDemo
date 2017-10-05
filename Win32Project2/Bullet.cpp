/********************************************************************************** 
Description -> v1.0 :		 Normal 3D bullet drawn

		       modified v2.0: Creates bullets of different sizes and at diferrent
							 location (with function) 

			   modified v3.0: bullets are placed in 3D space so as to draw shape of 
						     gsroupname "Shaders"

			   modified v4.0: Added x-axis shifting argument for characters

			   modified v5.0: Added more characters

			   modified v6.0: refined code with array of srtuctures for placing bullets

Key Controls -> s --> Rotate clockwise
				d --> Rotate anticlockwise
				r --> Rotate camera - actual video - uncomment gluLookAt() to make it work
				p --> translate

Priyanka Bhasme
************************************************************************************/
// Header files

#include<Windows.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include<math.h>
#include"Bullet.h"



#define PI 3.145
// Pragma
	
int giCurrentRingCount = 0;

float gfXranslateCounter = -3.2f;
GLfloat xPara;
GLfloat yPara;
GLint circle_points = 1000000;
//GLfloat angle;
static GLfloat incenter = 0.0f;
float gfBulletTranslateX = 0.0f;
float gfRingTranslateX[100] = { 0.0f };
float gfMaximumX = 1.0f;

float ringRadius[100] = {0.5f};

static float rotateSingleBullet = 0;
static int extra1 = 0;
static int extra2 = 0;
float zShift = 0.0;
float leftShift = -5.0;
float xLShift = 0.0;//6.0;
float xTest = -8.0;

// for changing position of whole 'Shaders'
float xBulletCord = 0.0;
float yBulletCord = 0.0;
float zBulletCord = -8.0;   // this is the distance between camera and the characters

							// structure to hold bullets co-ordinates
typedef struct bullCords {
	float xCord;
	float yCord;
	float zCord;
	float bulletScale;
} bulletData;

struct Point
{
	GLfloat xAxis;
	GLfloat yAxis;
};

struct Color
{
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};

// bullets spaced for character 'S'
bulletData positionS[18] = {

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
bulletData positionH[13] = {
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
bulletData positionA[15] = {

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
bulletData positionD[16] = {
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
bulletData positionE[12] = {
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
bulletData positionR[16] = {
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
bulletData positionLastS[11] = {
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


// structure for bullets shade
//typedef struct {
//	float rColor;
//	float gColor;
//	float bColor;
//};
//void display(void) {
//
//	void drawBullet(float xCord, float yCord, float zCord, float bulletScale);
//	//void drawCharacter(void);
//	void drawCharacter(byte bChar);
//	void drawGraphPaper(void);
//	//void drawCharacterTest(void);
//
//	
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // GL_DEPTH_BUFFER_BIT - For 3D
//	glMatrixMode(GL_MODELVIEW);
//	// comment out to remove graph
//	glLoadIdentity();
//	glTranslatef(0.0, 0.0, -6.0);
//	drawGraphPaper();
//
//
//	// Necessary code starts here
//	glLoadIdentity();	
//	
//	gluLookAt(0.0,0.0,zShift, 0.0f, 0.0f, -6.0f, 0.0f, 1.0f, 0.0f); // working properly
//	//gluLookAt(cos(anglePyramid)*8.0, 0.0f, sin(anglePyramid)*8.0 -8.0, 0.0f, 0.0f, -8.0f, 0.0f, 1.0f, 0.0f); // actual video effect
//
//
//	// draw SHADERS
//	drawCharacter('S');
//	drawCharacter('H');
//	drawCharacter('A');
//	drawCharacter('D');
//	drawCharacter('E');
//	drawCharacter('R');	
//	drawCharacter('s');
//	SwapBuffers(ghdc);
//
//}

void drawCharacter(byte bChar) {

	void drawBullet(float xCord, float yCord, float zCord, float bulletScale);
	
	switch (bChar) {

	case 'S':
		glPushMatrix();
		for (int i = 0; i < 18; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionS[i].xCord, positionS[i].yCord, positionS[i].zCord, positionS[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'H':
		
		glPushMatrix();
		for (int i = 0; i < 13; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionH[i].xCord, positionH[i].yCord, positionH[i].zCord, positionH[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'A':

		glPushMatrix();
		for (int i = 0; i < 15; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionA[i].xCord, positionA[i].yCord, positionA[i].zCord, positionA[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'D':

		glPushMatrix();
		for (int i = 0; i < 16; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionD[i].xCord, positionD[i].yCord, positionD[i].zCord, positionD[i].bulletScale);
		}
		glPopMatrix();
		break;

	case 'E':

		glPushMatrix();
		for (int i = 0; i < 12; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionE[i].xCord, positionE[i].yCord, positionE[i].zCord, positionE[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'R':

		glPushMatrix();
		for (int i = 0; i < 16; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionR[i].xCord, positionR[i].yCord, positionR[i].zCord, positionR[i].bulletScale);
		}
		glPopMatrix();
		break;

	case 's':

		glPushMatrix();
		for (int i = 0; i < 11; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionLastS[i].xCord, positionLastS[i].yCord, positionLastS[i].zCord, positionLastS[i].bulletScale);
		}
		glPopMatrix();
		break;
		
		
	}
}

void DrawBullet(float xCord)
{
	glPushMatrix(); // save initial position
		glTranslatef(xCord, 0.0f, 0.0f);
		glRotatef(-90, 0.0, 1.0, 0.0);
		glPushMatrix(); // save position of first object which will rotate around the initial point
			glColor3f(160.0f / 255.0f, 82.0f / 255.0f, 45.0f / 255.0f);
			quadric = gluNewQuadric();

			gluDisk(quadric, 0.001, 0.35, 20, 20);

			//yellowinsh shade
			glColor3f(218.0f / 255.0f, 168.0f / 255.0f, 32.0f / 255.0f);
			quadric = gluNewQuadric();

			// outer disk back of the bullet
			gluDisk(quadric, 0.35, 0.5, 20, 20);

			// now we will draw second object which is related to the first one
			// back cylinder
		glPopMatrix(); // actually not needed since we didn't change the position

		glPushMatrix(); // save the previous position
			glColor3f(218.0f/ 255.0f, 168.0f / 255.0f, 32.0f / 255.0f);
			quadric = gluNewQuadric();
			gluCylinder(quadric, 0.5, 0.5, 0.08, 20, 20);
		glPopMatrix();

		//glTranslatef(0.0, 0.0, 0.08*bulletScale); // since we have rotated the whole matrix by hard
		// coded 90 degrees first, so every axis got shifted and +z takes place of +x
		//glRotatef((GLfloat)extra1, 0.0, 0.0, 1.0);
		//glTranslatef(0.0, -0.5, 0.0);

		glPushMatrix();
			glColor3f(184.0f / 255.0f, 134.0f / 255.0f, 11.0f / 255.0f);
			quadric = gluNewQuadric();
			gluDisk(quadric, 0.01, 0.5, 20, 20);

		glPopMatrix(); // translated position by 0.05

		glPushMatrix(); // save the previous position second cylinder
			glColor3f(218.0f / 255.0f, 168.0f / 255.0f, 32.0f / 255.0f);
			quadric = gluNewQuadric();
			gluCylinder(quadric, 0.4f, 0.4f, 0.15f, 20, 20);

		glPopMatrix();

		glPushMatrix();
			glColor3f(184.0f / 255.0f, 134.0f / 255.0f, 11.0f / 255.0f);
			quadric = gluNewQuadric();
			gluDisk(quadric, 0.01f, 0.5f, 20, 20);

		glPopMatrix();

		glPushMatrix();
			glColor3f(0.9f, 0.7f, 0.2f);
			quadric = gluNewQuadric();
			gluCylinder(quadric, 0.5, 0.5, 1.3, 20, 20);

		glPopMatrix();

		glPushMatrix(); // save the previous position second cylinder
						//glScalef(1.0, 1.0, 2.0);
			glColor3f(210.0f / 255.0f, 105.0f / 255.0f, 30.0f / 255.0f);
			quadric = gluNewQuadric();
			gluSphere(quadric, 0.5, 20, 20);

		glPopMatrix();
	glPopMatrix();
}
/* x,y,z cords give position of bullet
 BulleteScale --> size of bullet*/
void drawBullet(float xCord, float yCord, float zCord, float bulletScale) {	

	//glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//depth prev now after rotate, it's position on current x means actual z-axis
	//keep initial depth fixed as -3.0, and adjust with zCord param

	glPushMatrix(); // save initial position
	glTranslatef(xCord, yCord, zCord);

	//glRotatef(-90, 0.0, 1.0, 0.0);
	//gluLookAt(xTest, 0.0, 15.0 , 0.0, 0.0, -5.0, 0.0f, 1.0f, 0.0f);
	//glRotatef(180, 0.0, 1.0, 0.0); // temporary
	//gluLookAt(0.0, 0.0f, -xTest, 0.0, 0.0, xTest-5.0, 0.0f, 1.0f, 0.0f); //zoomout effect

	//glRotatef((GLfloat)rotateSingleBullet, 0.0, 1.0, 0.0);
	//glTranslatef(0.0, 0.0, zShift);

	//glTranslatef(xCord, yCord, zCord);
	//here xCord --> depth and zCord --> position on x screen / x-axis -- >IMP

	//glTranslatef(0.0, -0.5, 0.0); 

	glPushMatrix(); // save position of first object which will rotate around the initial point
	glColor3f(160.0f / 255.0f, 82.0f / 255.0f, 45.0f / 255.0f);
	quadric = gluNewQuadric();

	// inner disk back of the bullet
	gluDisk(quadric, 0.001, 0.35*bulletScale, 20, 20);

	//yellowinsh shade
	glColor3f(218.0f / 255.0f, 168.0f / 255.0f, 32.0f / 255.0f);
	quadric = gluNewQuadric();

	// outer disk back of the bullet
	gluDisk(quadric, 0.35*bulletScale, 0.5*bulletScale, 20, 20);

	// now we will draw second object which is related to the first one
	// back cylinder
	glPopMatrix(); // actually not needed since we didn't change the position

	glPushMatrix(); // save the previous position
	glColor3f(218.0f / 255.0f, 168.0f / 255.0f, 32.0f / 255.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5*bulletScale, 0.5*bulletScale, 0.08*bulletScale, 20, 20);
	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.08*bulletScale); // since we have rotated the whole matrix by hard
	// coded 90 degrees first, so every axis got shifted and +z takes place of +x
	//glRotatef((GLfloat)extra1, 0.0, 0.0, 1.0);
	//glTranslatef(0.0, -0.5, 0.0);

	glPushMatrix();
	glColor3f(184.0f / 255.0f, 134.0f / 255.0f, 11.0f / 255.0f);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix(); // translated position by 0.05

	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix(); // save the previous position second cylinder
	glColor3f(218.0f / 255.0f, 168.0f / 255.0f, 32.0f / 255.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.4*bulletScale, 0.4*bulletScale, 0.15*bulletScale, 20, 20);

	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.15*bulletScale);
	glPushMatrix(); 
	glColor3f(184.0f / 255.0f, 134.0f / 255.0f, 11.0f / 255.0f);
	//glColor3f(0.6, 0.2, 0.0);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.5);
	glPushMatrix();
	glColor3f(0.9f, 0.7f, 0.2f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5f*bulletScale, 0.5f*bulletScale, 1.3f*bulletScale, 20, 20);

	glPopMatrix();

	//glRotatef(90, 1.0, 0.0, 0.0);
	//glTranslatef(0.0, 0.0, 1.3*bulletScale);
	glPushMatrix(); // save the previous position second cylinder
	//glScalef(1.0, 1.0, 2.0);
	glColor3f(210.0f / 255.0f, 105.0f / 255.0f, 30.0f / 255.0f);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.5f*bulletScale, 20, 20);

	glPopMatrix();
	glPopMatrix();
}


void DrawBulletCircle(GLfloat radius, Point incenter, float alpha)
{
	GLint circle_points = 100;
	GLfloat angle;
	glPushMatrix();
	glBegin(GL_POINTS);

	glColor4f(1.0f, 1.0f, 1.0f, alpha);

	for (int i = 0; i<circle_points; i++)
	{
		angle = 2 * (GLfloat)PI * i / circle_points;
		glVertex3f(0.0f, (GLfloat)cos(angle)*radius ,
			(GLfloat)sin(angle)*radius);
	}

	glEnd();
	glPopMatrix();
}

void drawRippledBullet()
{
	void DrawBulletCircle(GLfloat, Point, float);
	int i = 0;
	float color[3] = { 0.5f, 0.5f, 0.5f };
	float transparency = 1.0f;
	for (i = giCurrentRingCount - 1; i >= 0; i--)
	{
		glEnable(GL_BLEND);

		glPushMatrix();
			glTranslatef(gfRingTranslateX[i], 0.0, 0.0);
			DrawBulletCircle(ringRadius[i], Point{ gfRingTranslateX[i],0.0f }, transparency);
		glPopMatrix();

		glDisable(GL_BLEND);
		ringRadius[i] += 0.08f;
		gfRingTranslateX[i] += 0.05f;
		transparency -= 0.1f;
	}
}

void DrawSingleBullet()
{
	//if (gfBulletTranslateX >= 100.0f) {
	if (objectsIteration >= 16) {
		sceneIndex = 3;
	}
	glPushMatrix();
		if (gfBulletTranslateX > gfMaximumX)
		{
			gfRingTranslateX[giCurrentRingCount] = gfBulletTranslateX;
			ringRadius[giCurrentRingCount] = 0.5f;
			giCurrentRingCount++;
			gfMaximumX += 2.0f;
		}
		gfBulletTranslateX += 0.6f;
		
		DrawBullet(gfBulletTranslateX);
	glPopMatrix();
}

void DrawSingleBulletWithRipples()
{
	glPushMatrix();
		glTranslatef(21.0f, -1.7f, 5.0f);
		glScalef(0.3f, 0.3f, 1.0f);
		DrawSingleBullet();
		if (sceneIndex == 2)
			drawRippledBullet();
	glPopMatrix();
}