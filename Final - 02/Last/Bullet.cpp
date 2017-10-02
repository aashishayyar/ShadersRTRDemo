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

float gfXranslateCounter = -3.2;
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
bulletData positionH[13] = {
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
bulletData positionA[15] = {
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
bulletData positionD[16] = {
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
bulletData positionE[12] = {
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
bulletData positionR[16] = {
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
bulletData positionLastS[11] = {
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
			glColor3f(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0);
			quadric = gluNewQuadric();

			gluDisk(quadric, 0.001, 0.35, 20, 20);

			//yellowinsh shade
			glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
			quadric = gluNewQuadric();

			// outer disk back of the bullet
			gluDisk(quadric, 0.35, 0.5, 20, 20);

			// now we will draw second object which is related to the first one
			// back cylinder
		glPopMatrix(); // actually not needed since we didn't change the position

		glPushMatrix(); // save the previous position
			glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
			quadric = gluNewQuadric();
			gluCylinder(quadric, 0.5, 0.5, 0.08, 20, 20);
		glPopMatrix();

		//glTranslatef(0.0, 0.0, 0.08*bulletScale); // since we have rotated the whole matrix by hard
		// coded 90 degrees first, so every axis got shifted and +z takes place of +x
		//glRotatef((GLfloat)extra1, 0.0, 0.0, 1.0);
		//glTranslatef(0.0, -0.5, 0.0);

		glPushMatrix();
			glColor3f(184.0 / 255.0, 134.0 / 255.0, 11.0 / 255.0);
			quadric = gluNewQuadric();
			gluDisk(quadric, 0.01, 0.5, 20, 20);

		glPopMatrix(); // translated position by 0.05

		glPushMatrix(); // save the previous position second cylinder
			glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
			quadric = gluNewQuadric();
			gluCylinder(quadric, 0.4, 0.4, 0.15, 20, 20);

		glPopMatrix();

		glPushMatrix();
			glColor3f(184.0 / 255.0, 134.0 / 255.0, 11.0 / 255.0);
			quadric = gluNewQuadric();
			gluDisk(quadric, 0.01, 0.5, 20, 20);

		glPopMatrix();

		glPushMatrix();
			glColor3f(0.9, 0.7, 0.2);
			quadric = gluNewQuadric();
			gluCylinder(quadric, 0.5, 0.5, 1.3, 20, 20);

		glPopMatrix();

		glPushMatrix(); // save the previous position second cylinder
						//glScalef(1.0, 1.0, 2.0);
			glColor3f(210.0 / 255.0, 105.0 / 255.0, 30.0 / 255.0);
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
	glColor3f(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0);
	quadric = gluNewQuadric();

	// inner disk back of the bullet
	gluDisk(quadric, 0.001, 0.35*bulletScale, 20, 20);

	//yellowinsh shade
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadric = gluNewQuadric();

	// outer disk back of the bullet
	gluDisk(quadric, 0.35*bulletScale, 0.5*bulletScale, 20, 20);

	// now we will draw second object which is related to the first one
	// back cylinder
	glPopMatrix(); // actually not needed since we didn't change the position

	glPushMatrix(); // save the previous position
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5*bulletScale, 0.5*bulletScale, 0.08*bulletScale, 20, 20);
	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.08*bulletScale); // since we have rotated the whole matrix by hard
	// coded 90 degrees first, so every axis got shifted and +z takes place of +x
	//glRotatef((GLfloat)extra1, 0.0, 0.0, 1.0);
	//glTranslatef(0.0, -0.5, 0.0);

	glPushMatrix();
	glColor3f(184.0 / 255.0, 134.0 / 255.0, 11.0 / 255.0);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix(); // translated position by 0.05

	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix(); // save the previous position second cylinder
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.4*bulletScale, 0.4*bulletScale, 0.15*bulletScale, 20, 20);

	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.15*bulletScale);
	glPushMatrix(); 
	glColor3f(184.0 / 255.0, 134.0 / 255.0, 11.0 / 255.0);
	//glColor3f(0.6, 0.2, 0.0);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.5);
	glPushMatrix();
	glColor3f(0.9, 0.7, 0.2);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5*bulletScale, 0.5*bulletScale, 1.3*bulletScale, 20, 20);

	glPopMatrix();

	//glRotatef(90, 1.0, 0.0, 0.0);
	//glTranslatef(0.0, 0.0, 1.3*bulletScale);
	glPushMatrix(); // save the previous position second cylinder
	//glScalef(1.0, 1.0, 2.0);
	glColor3f(210.0 / 255.0, 105.0 / 255.0, 30.0 / 255.0);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.5*bulletScale, 20, 20);

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

	for (int i = 0.0f; i<circle_points; i++)
	{
		angle = 2 * PI * i / circle_points;
		glVertex3f(0.0f, cos(angle)*radius ,
			sin(angle)*radius);
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