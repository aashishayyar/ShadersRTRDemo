/**********************************************************************************
Description -> v1.0 :		Vintage Pistol

Priyanka Bhasme
************************************************************************************/

// Header files
#include"Pistol.h"

#define PI 3.1415926535898

float anglePyramid, angleRect, angleDetla;
int rotationsCount = 10000;

// for changing position of whole 'Shaders'
float xOriginalCord = 0.0;
float yOriginalCord = 0.0;
float zOriginalCord = 0.0;   // this is the distance between camera and the characters

// structure for color schemes
struct rgbValues {
	float rColor;
	float gColor;
	float bColor;
};

struct colorShades {
	rgbValues topColor;
	rgbValues sideColor;
	rgbValues frontColor;
};

// color scheme for pistol body
rgbValues grayTopColors = { (GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7 };
rgbValues graySideColors = { (GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4 };
rgbValues grayFrontColors = { (GLfloat)0.3,(GLfloat)0.3,(GLfloat)0.3 };

colorShades grayShades = { grayTopColors, graySideColors, grayFrontColors };

// color scheme for pistol handle
rgbValues brownTopColors = { (GLfloat)(107.0 / 255.0), (GLfloat)(69.0 / 255.0), (GLfloat)(32.0 / 255.0) };
rgbValues brownSideColors = { (GLfloat)(204.0 / 255.0), (GLfloat)(130.0 / 255.0), (GLfloat)(57.0 / 255.0) };
rgbValues brownFrontColors = { (GLfloat)(127.0 / 255.0), (GLfloat)(67.0 / 255.0), (GLfloat)(36.0 / 255.0) };

colorShades brownShades = { brownTopColors, brownSideColors, brownFrontColors };

float gwSideofTriangle = 2.0f;
float testAngle = 0.0;

extern GLUquadric *quadric;

void DrawPistolSquare(float vertice1[3], float vertice2[3], float vertice3[3], float vertice4[3], rgbValues color)
{
	glBegin(GL_QUADS);
	glColor3f(color.rColor, color.gColor, color.bColor);
	glVertex3f(vertice1[0], vertice1[1], vertice1[2]);
	glVertex3f(vertice2[0], vertice2[1], vertice2[2]);
	glVertex3f(vertice3[0], vertice3[1], vertice3[2]);
	glVertex3f(vertice4[0], vertice4[1], vertice4[2]);
	glEnd();

	//glBegin(GL_LINE_LOOP);
	//glColor3f(color[0] + 0.1f, color[1] + 0.1f, color[2] + 0.1f);
	//glVertex3f(vertice1[0], vertice1[1], vertice1[2]);
	//glVertex3f(vertice2[0], vertice2[1], vertice2[2]);
	//glVertex3f(vertice3[0], vertice3[1], vertice3[2]);
	//glVertex3f(vertice4[0], vertice4[1], vertice4[2]);
	//glEnd();

}

void DrawPistolCuboid(float points[10][3], colorShades colorScheme)
{

	
	DrawPistolSquare(points[0], points[1], points[2], points[3], colorScheme.frontColor);//front and rear
	DrawPistolSquare(points[4], points[5], points[6], points[7], colorScheme.frontColor);//
	DrawPistolSquare(points[1], points[5], points[6], points[2], colorScheme.sideColor);//left
	DrawPistolSquare(points[0], points[4], points[7], points[3], colorScheme.sideColor);//right
	DrawPistolSquare(points[0], points[1], points[5], points[4], colorScheme.topColor);//top and bottom
	DrawPistolSquare(points[3], points[2], points[6], points[7], colorScheme.topColor);//
}

void DrawPistol(float xPos, float yPos, float zPos, float pistolScale) {
	
	void DrawBulletHolderDisc(float pistolScale);
	void DrawBelletSlots(float bulletScale);
	void DrawHandleDesign(void);
	void DrawTrigger(void);

	float colors[3] = { (GLfloat)0.3,(GLfloat)0.3,(GLfloat)0.3 };
	float quardsDepth = 0.0;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glTranslatef( 0.0f, 0.6f, 1.8f);
	glScalef(0.35f, 0.35f, 0.35f);
	glPushMatrix();

	glColor3f((GLfloat)0.6, (GLfloat)0.6, (GLfloat)0.6);

	//main outer cylinder
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.2*pistolScale, 0.2*pistolScale, 2.0*pistolScale, 20, 20);
	glColor3f((GLfloat)0.3, (GLfloat)0.3, (GLfloat)0.3);

	// main inner cylinder
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.13*pistolScale, 0.13*pistolScale, 2.0*pistolScale, 20, 20);
	glColor3f((GLfloat)0.2, (GLfloat)0.2, (GLfloat)0.2);

	// upper cubiod on main cylinder
	float points[8][3] = {
		{ (xOriginalCord + 0.1f)*pistolScale, (yOriginalCord + 0.29f)*pistolScale, (zOriginalCord)*pistolScale },// counter clockwise backside)*pistolScale, upper cube
		{ (xOriginalCord - 0.1f)*pistolScale, (yOriginalCord + 0.29f)*pistolScale, (zOriginalCord)*pistolScale },
		{ (xOriginalCord - 0.1f)*pistolScale, (yOriginalCord + 0.17f)*pistolScale, (zOriginalCord)*pistolScale },
		{ (xOriginalCord + 0.1f)*pistolScale, (yOriginalCord + 0.17f)*pistolScale, (zOriginalCord)*pistolScale },
		{ (xOriginalCord + 0.1f)*pistolScale, (yOriginalCord + 0.29f)*pistolScale, (zOriginalCord + 1.98f)*pistolScale },
		{ (xOriginalCord - 0.1f)*pistolScale, (yOriginalCord + 0.29f)*pistolScale, (zOriginalCord + 1.98f)*pistolScale },
		{ (xOriginalCord - 0.1f)*pistolScale, (yOriginalCord + 0.17f)*pistolScale, (zOriginalCord + 1.98f)*pistolScale },
		{ (xOriginalCord + 0.1f)*pistolScale, (yOriginalCord + 0.17f)*pistolScale, (zOriginalCord + 1.98f)*pistolScale }
	};
	DrawPistolCuboid(points, grayShades);
	glPopMatrix();
	glPushMatrix();
	glTranslatef((GLfloat)0.0, (GLfloat)0.0, (GLfloat)2.0*pistolScale);
	glColor3f((GLfloat)0.2, (GLfloat)0.2, (GLfloat)0.2);

	// disc on the tip of
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.13*pistolScale, 0.2*pistolScale, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef((GLfloat)0.0, (GLfloat)0.0, (GLfloat)1.98*pistolScale);

	// upper cuboid on the main cylinder
	float pointsTopTip[8][3] = {
		{ (xOriginalCord + 0.03f)*pistolScale, (yOriginalCord + 0.38f)*pistolScale, (zOriginalCord - 0.3f)*pistolScale }, // back
		{ xOriginalCord - 0.03f, yOriginalCord + 0.38f, zOriginalCord - 0.3f },
		{ xOriginalCord - 0.04f, yOriginalCord + 0.29f, zOriginalCord - 0.5f },
		{ xOriginalCord + 0.04f, yOriginalCord + 0.29f, zOriginalCord - 0.5f },
		{ xOriginalCord + 0.03f, yOriginalCord + 0.38f, zOriginalCord },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.03f, yOriginalCord + 0.38f, zOriginalCord }, // front
		{ xOriginalCord - 0.04f, yOriginalCord + 0.29f, zOriginalCord },
		{ xOriginalCord + 0.04f, yOriginalCord + 0.29f, zOriginalCord }

	};
	DrawPistolCuboid(pointsTopTip, grayShades);
	glPopMatrix();
	glPushMatrix();
	// covering disc for back cylinder
	glColor3f((GLfloat)0.2, (GLfloat)0.2, (GLfloat)0.2);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.05, 0.23, 20, 20);
	//translate to draw back cylinder
	glTranslatef((GLfloat)0.0, (GLfloat)0.0, (GLfloat)-0.4);
	glColor3f(0.4f, 0.4f, 0.4f);

	// back cylinder
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.23*pistolScale, 0.23*pistolScale, 0.4*pistolScale, 20, 20);
	
	glPopMatrix();
	glPushMatrix();
	// upper cuboid on back cylinder
	float pointsTopBackLower[8][3] = {
		{ xOriginalCord + 0.14f, yOriginalCord + 0.32f, zOriginalCord - 1.1f }, //back
		{ xOriginalCord - 0.14f, yOriginalCord + 0.32f, zOriginalCord - 1.1f },
		{ xOriginalCord - 0.14f, yOriginalCord + 0.17f, zOriginalCord - 1.1f },
		{ xOriginalCord + 0.14f, yOriginalCord + 0.17f, zOriginalCord - 1.1f },
		{ xOriginalCord + 0.14f, yOriginalCord + 0.32f, zOriginalCord },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.14f, yOriginalCord + 0.32f, zOriginalCord },
		{ xOriginalCord - 0.14f, yOriginalCord + 0.17f, zOriginalCord },
		{ xOriginalCord + 0.14f, yOriginalCord + 0.17f, zOriginalCord }


	};
	DrawPistolCuboid(pointsTopBackLower, grayShades);

	glPopMatrix();
	glPushMatrix();	
	// front disc for bullets holder
	glTranslatef((GLfloat)0.0, (GLfloat)-0.2, (GLfloat)-0.3);
	glColor3f((GLfloat)0.3, (GLfloat)0.3, (GLfloat)0.3);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.005*pistolScale, 0.45*pistolScale, 20, 20);
	glPopMatrix();
	glPushMatrix();
	// rear disc for bullets holder 
	glTranslatef((GLfloat)0.0, (GLfloat)-0.2, (GLfloat)-1.0);
	glColor3f((GLfloat)0.2, (GLfloat)0.2, (GLfloat)0.2);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.005*pistolScale, 0.45*pistolScale, 20, 20);

	// bullets holder
	glColor3f((GLfloat)0.45, (GLfloat)0.45, (GLfloat)0.45);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.45*pistolScale, 0.45*pistolScale, 0.7*pistolScale, 20, 20);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles left
	glTranslatef((GLfloat)-0.22, (GLfloat)-0.04, (GLfloat)-0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles left
	glTranslatef((GLfloat)-0.27, (GLfloat)-0.295, (GLfloat)-0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles left
	glTranslatef((GLfloat)-0.1, (GLfloat)-0.49, (GLfloat)-0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles right
	glTranslatef((GLfloat)0.22, (GLfloat)-0.04, (GLfloat)-0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles right
	glTranslatef((GLfloat)0.27, (GLfloat)-0.295, (GLfloat)-0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles right
	glTranslatef((GLfloat)0.1, (GLfloat)-0.49, (GLfloat)-0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	//frame around bullet holder
	float pointsFrame[8][3] = {
		{ xOriginalCord + 0.14f, yOriginalCord + 0.17f, zOriginalCord - 1.18f }, //back
		{ xOriginalCord - 0.14f, yOriginalCord + 0.17f, zOriginalCord - 1.18f },
		{ xOriginalCord - 0.14f, yOriginalCord - 0.8f, zOriginalCord - 1.18f },
		{ xOriginalCord + 0.14f, yOriginalCord - 0.8f, zOriginalCord - 1.18f },
		{ xOriginalCord + 0.14f, yOriginalCord + 0.17f, zOriginalCord - 0.2f },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.14f, yOriginalCord + 0.17f, zOriginalCord - 0.2f },
		{ xOriginalCord - 0.14f, yOriginalCord - 0.8f, zOriginalCord - 0.2f },
		{ xOriginalCord + 0.14f, yOriginalCord - 0.8f, zOriginalCord - 0.2f }


	};
	DrawPistolCuboid(pointsFrame, grayShades);

	// the cuboid just above and behind the trigger
	float pointsFrame2[8][3] = {
		{ xOriginalCord + 0.14f, yOriginalCord - 0.3f, zOriginalCord - 1.7f },//back
		{ xOriginalCord - 0.14f, yOriginalCord - 0.3f, zOriginalCord - 1.7f },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.14f, yOriginalCord - 0.8f, zOriginalCord - 1.4f },
		{ xOriginalCord + 0.14f, yOriginalCord - 0.8f, zOriginalCord - 1.4f },
		{ xOriginalCord + 0.14f, yOriginalCord - 0.3f, zOriginalCord - 1.0f }, 
		{ xOriginalCord - 0.14f, yOriginalCord - 0.3f, zOriginalCord - 1.0f },
		{ xOriginalCord - 0.14f, yOriginalCord - 0.8f, zOriginalCord - 1.0f },
		{ xOriginalCord + 0.14f, yOriginalCord - 0.8f, zOriginalCord - 1.0f },

	};
	DrawPistolCuboid(pointsFrame2, grayShades);

	glPopMatrix();
	glPushMatrix();
	
	// the cuboid for handle
	float pointsHandle[8][3] = {

		{ xOriginalCord + 0.18f, yOriginalCord - 1.8f, zOriginalCord - 2.3f },//back
		{ xOriginalCord - 0.18f, yOriginalCord - 1.8f, zOriginalCord - 2.3f },
		{ xOriginalCord - 0.18f, yOriginalCord - 2.6f, zOriginalCord - 1.8f },
		{ xOriginalCord + 0.18f, yOriginalCord - 2.6f, zOriginalCord - 1.8f },
		{ xOriginalCord + 0.18f, yOriginalCord - 0.3f, zOriginalCord - 1.7f },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.18f, yOriginalCord - 0.3f, zOriginalCord - 1.7f },
		{ xOriginalCord - 0.18f, yOriginalCord - 0.8f, zOriginalCord - 1.3f },
		{ xOriginalCord + 0.18f, yOriginalCord - 0.8f, zOriginalCord - 1.3f },

	};
	DrawPistolCuboid(pointsHandle, brownShades);

	float pointsHandle2[8][3] = {

		{ xOriginalCord + 0.18f, yOriginalCord - 2.7f, zOriginalCord - 1.8f },//back
		{ xOriginalCord - 0.18f, yOriginalCord - 2.7f, zOriginalCord - 1.8f },
		{ xOriginalCord - 0.18f, yOriginalCord - 2.6f, zOriginalCord - 1.2f },
		{ xOriginalCord + 0.18f, yOriginalCord - 2.6f, zOriginalCord - 1.2f },
		{ xOriginalCord + 0.18f, yOriginalCord - 1.7f, zOriginalCord - 2.2f },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.18f, yOriginalCord - 1.7f, zOriginalCord - 2.2f },
		{ xOriginalCord - 0.18f, yOriginalCord - 1.5f, zOriginalCord - 1.7f },
		{ xOriginalCord + 0.18f, yOriginalCord - 1.5f, zOriginalCord - 1.7f },

	};
	DrawPistolCuboid(pointsHandle2, brownShades);

	// draw embedded outer bullets around bullet holder --> it's just a design
	//right side
	glPopMatrix();
	glPushMatrix();
	glTranslatef((GLfloat)-0.25, (GLfloat)0.15, (GLfloat)-0.32);
	DrawBelletSlots((GLfloat)0.2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.44f, -0.15f, -0.32f);
	DrawBelletSlots(0.2f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.32f, -0.49f, -0.32f);
	DrawBelletSlots(0.2f);
	glPopMatrix();

	// left
	glPushMatrix();
	glTranslatef(0.25f, 0.15f, -0.32f);
	DrawBelletSlots(0.2f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.44f, -0.15f, -0.32f);
	DrawBelletSlots(0.2f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.32f, -0.49f, -0.32f);
	DrawBelletSlots(0.2f);
	
	// handle and design
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -1.8f, -2.4f);
	glRotatef(-14.0, 1.0, 0.0, 0.0);
	glColor3f(204.0f / 255.0f, 130.0f / 255.0f, 57.0f / 255.0f);
	DrawHandleDesign();
	glPopMatrix();

	// trigger circle
	glPushMatrix();
	glTranslatef(0.0f, -1.3f, -0.9f);
	DrawTrigger();
	glPopMatrix();

	glPushMatrix();
	// cubiod below main cylinder
	float pointsLowerCuboid[8][3] = {
		{ xOriginalCord + 0.12f, yOriginalCord - 0.33f, zOriginalCord - 0.3f },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.12f, yOriginalCord - 0.33f, zOriginalCord - 0.3f },
		{ xOriginalCord - 0.12f, yOriginalCord - 0.19f, zOriginalCord - 0.3f },
		{ xOriginalCord + 0.12f, yOriginalCord - 0.19f, zOriginalCord - 0.3f },
		{ xOriginalCord + 0.12f, yOriginalCord - 0.33f, zOriginalCord + 1.0f },
		{ xOriginalCord - 0.12f, yOriginalCord - 0.33f, zOriginalCord + 1.0f },
		{ xOriginalCord - 0.12f, yOriginalCord - 0.19f, zOriginalCord + 1.0f },
		{ xOriginalCord + 0.12f, yOriginalCord - 0.19f, zOriginalCord + 1.0f }
	};
	DrawPistolCuboid(pointsLowerCuboid, grayShades);
	glPopMatrix();
	glPushMatrix();
	// cubiod below trigger
	float pointsBelowTrigger[8][3] = {
		{ xOriginalCord + 0.12f, yOriginalCord - 1.0f, zOriginalCord - 0.5f },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.12f, yOriginalCord - 1.0f, zOriginalCord - 0.5f },
		{ xOriginalCord - 0.12f, yOriginalCord - 0.5f, zOriginalCord - 0.5f },
		{ xOriginalCord + 0.12f, yOriginalCord - 0.5f, zOriginalCord - 0.5f },
		{ xOriginalCord + 0.12f, yOriginalCord - 1.0f, zOriginalCord - 1.3f },
		{ xOriginalCord - 0.12f, yOriginalCord - 1.0f, zOriginalCord - 1.3f },
		{ xOriginalCord - 0.12f, yOriginalCord - 0.5f, zOriginalCord - 1.3f },
		{ xOriginalCord + 0.12f, yOriginalCord - 0.5f, zOriginalCord - 1.3f }
	};
	DrawPistolCuboid(pointsBelowTrigger, grayShades);
	glPopMatrix();
	glPushMatrix();

	// fillings around trigger ring
	glColor3f(0.4f, 0.4f, 0.4f);
	//back
	for (int i = 0; i < 50; i++) {
		glBegin(GL_QUADS);
		glVertex3f(xOriginalCord + 0.12f, yOriginalCord - 1.0f, zOriginalCord - 1.3f + quardsDepth);
		glVertex3f(xOriginalCord - 0.12f, yOriginalCord - 1.0f, zOriginalCord - 1.3f + quardsDepth);
		glVertex3f(xOriginalCord - 0.12f, yOriginalCord - 1.3f, zOriginalCord - 1.3f + quardsDepth);
		glVertex3f(xOriginalCord + 0.12f, yOriginalCord - 1.3f, zOriginalCord - 1.3f + quardsDepth);
		glEnd();
		quardsDepth += 0.002f;
	}
	quardsDepth = 0.0;
	// back ++
	for (int i = 0; i < 50; i++) {
		glBegin(GL_QUADS);
		glVertex3f(xOriginalCord + 0.12f, yOriginalCord - 0.9f, zOriginalCord - 1.2f + quardsDepth);
		glVertex3f(xOriginalCord - 0.12f, yOriginalCord - 0.9f, zOriginalCord - 1.2f + quardsDepth);
		glVertex3f(xOriginalCord - 0.12f, yOriginalCord - 1.05f, zOriginalCord - 1.2f + quardsDepth);
		glVertex3f(xOriginalCord + 0.12f, yOriginalCord - 1.05f, zOriginalCord - 1.2f + quardsDepth);
		glEnd();
		quardsDepth += 0.002f;
	}


	// front
	for (int i = 0; i < 140; i++) {
		glBegin(GL_QUADS);
		glVertex3f(xOriginalCord + 0.12f, yOriginalCord - 1.0f, zOriginalCord - 0.75f + quardsDepth);
		glVertex3f(xOriginalCord - 0.12f, yOriginalCord - 1.0f, zOriginalCord - 0.75f + quardsDepth);
		glVertex3f(xOriginalCord - 0.12f, yOriginalCord - 1.3f, zOriginalCord - 0.75f + quardsDepth);
		glVertex3f(xOriginalCord + 0.12f, yOriginalCord - 1.3f, zOriginalCord - 0.75f + quardsDepth);
		glEnd();
		quardsDepth += 0.001f;
	}
	quardsDepth = 0.0;

	//glColor3f(1.0, 0.0, 1.0);	
	//glLineWidth(10.0);
	//for (int i = 0; i < 70; i++) {
	//	glBegin(GL_LINES);
	//	glVertex3f(xOriginalCord + 0.18, yOriginalCord - 1.0, zOriginalCord - 0.7 + quardsDepth);
	//	glVertex3f(xOriginalCord - 0.18, yOriginalCord - 1.0, zOriginalCord - 0.7 + quardsDepth);
	//	glEnd();
	//	quardsDepth += 0.002;
	//}

	// front
	for (int i = 0; i < 50; i++) {
		glBegin(GL_QUADS);
		glVertex3f(xOriginalCord + 0.12f, yOriginalCord - 0.8f, zOriginalCord - 0.72f + quardsDepth);
		glVertex3f(xOriginalCord - 0.12f, yOriginalCord - 0.8f, zOriginalCord - 0.72f + quardsDepth);
		glVertex3f(xOriginalCord - 0.12f, yOriginalCord - 1.0f, zOriginalCord - 0.72f + quardsDepth);
		glVertex3f(xOriginalCord + 0.12f, yOriginalCord - 1.0f, zOriginalCord - 0.72f + quardsDepth);
		glEnd();
		quardsDepth += 0.002f;
	}

	
	glPopMatrix();

	glPushMatrix();
	// upper trigger notch 

	float pointsUpperNotch[8][3] = {
		{ xOriginalCord + 0.06f, yOriginalCord + 0.2f, zOriginalCord - 1.7f },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.06f, yOriginalCord + 0.2f, zOriginalCord - 1.7f },
		{ xOriginalCord - 0.06f, yOriginalCord + 0.1f, zOriginalCord - 1.5f },
		{ xOriginalCord + 0.06f, yOriginalCord + 0.1f, zOriginalCord - 1.5f },
		{ xOriginalCord + 0.06f, yOriginalCord + 0.2f, zOriginalCord - 1.45f },
		{ xOriginalCord - 0.06f, yOriginalCord + 0.2f, zOriginalCord - 1.45f },
		{ xOriginalCord - 0.06f, yOriginalCord + 0.1f, zOriginalCord - 1.35f },
		{ xOriginalCord + 0.06f, yOriginalCord + 0.1f, zOriginalCord - 1.35f}
	};
	DrawPistolCuboid(pointsUpperNotch, grayShades);
	glPopMatrix();

	glPushMatrix();
	// cubiod below main cylinder

	float pointsNotch1[8][3] = {
		{ xOriginalCord + 0.08f, yOriginalCord + 0.45f, zOriginalCord - 1.0f },// counter clockwise backside, upper cube
		{ xOriginalCord + 0.04f, yOriginalCord + 0.45f, zOriginalCord - 1.0f },
		{ xOriginalCord + 0.00f, yOriginalCord + 0.3f, zOriginalCord - 1.0f },
		{ xOriginalCord + 0.02f, yOriginalCord + 0.3f, zOriginalCord - 1.0f },
		{ xOriginalCord + 0.08f, yOriginalCord + 0.45f, zOriginalCord - 1.1f },
		{ xOriginalCord + 0.04f, yOriginalCord + 0.45f, zOriginalCord - 1.1f },
		{ xOriginalCord + 0.00f, yOriginalCord + 0.3f, zOriginalCord - 1.1f },
		{ xOriginalCord + 0.02f, yOriginalCord + 0.3f, zOriginalCord - 1.1f }
	};
	DrawPistolCuboid(pointsNotch1, grayShades);
	glPopMatrix();

	glPushMatrix();
	// cubiod below main cylinder

	float pointsNotch2[8][3] = {
		{ xOriginalCord - 0.08f, yOriginalCord + 0.45f, zOriginalCord - 1.0f },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.04f, yOriginalCord + 0.45f, zOriginalCord - 1.0f },
		{ xOriginalCord - 0.00f, yOriginalCord + 0.3f, zOriginalCord - 1.0f },
		{ xOriginalCord - 0.02f, yOriginalCord + 0.3f, zOriginalCord - 1.0f },
		{ xOriginalCord - 0.08f, yOriginalCord + 0.45f, zOriginalCord - 1.1f },
		{ xOriginalCord - 0.04f, yOriginalCord + 0.45f, zOriginalCord - 1.1f },
		{ xOriginalCord - 0.00f, yOriginalCord + 0.3f, zOriginalCord - 1.1f },
		{ xOriginalCord - 0.02f, yOriginalCord + 0.3f, zOriginalCord - 1.1f }
	};
	DrawPistolCuboid(pointsNotch2, grayShades);
	glPopMatrix();

	glPushMatrix();
	// cubiod below main cylinder

	float pointsHandleCover[8][3] = {
		{ xOriginalCord + 0.22f, yOriginalCord - 0.2f, zOriginalCord - 1.7f },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.20f, yOriginalCord - 0.2f, zOriginalCord - 1.7f },
		{ xOriginalCord - 0.20f, yOriginalCord - 0.4f, zOriginalCord - 1.7f },
		{ xOriginalCord + 0.22f, yOriginalCord - 0.4f, zOriginalCord - 1.7f },
		{ xOriginalCord + 0.12f, yOriginalCord - 0.2f, zOriginalCord - 1.0f },
		{ xOriginalCord - 0.12f, yOriginalCord - 0.2f, zOriginalCord - 1.0f },
		{ xOriginalCord - 0.12f, yOriginalCord - 0.4f, zOriginalCord - 1.0f },
		{ xOriginalCord + 0.12f, yOriginalCord - 0.4f, zOriginalCord - 1.0f }
	};
	DrawPistolCuboid(pointsHandleCover, grayShades);
	glPopMatrix();
	glPopMatrix();

}

void DrawTrigger(void) {

	float triggerWidth = -0.08f;
	glPointSize(5.0f);
	glColor3f(0.4f, 0.4f, 0.4f);
	for (int j = 0; j <= 15; j++) {
		glBegin(GL_POINTS);
		
		for (int i = 0; i <= 1000; i++) {
			glVertex3f(triggerWidth, (GLfloat)cos(2 * PI*(i / 1000.0f))*0.35f , (GLfloat)sin(2 * PI*(i/ 1000.0f))*0.35f);
		}
		glEnd();
		triggerWidth += 0.01f;
	}

	triggerWidth = -0.08f;
	glColor3f(0.3f, 0.3f, 0.3f);
	glTranslatef(0.0f, 0.2f, 0.15f);
	glRotatef(180, 1.0, 0.0, 0.0);
	for (int j = 0; j <= 15; j++) {
		glBegin(GL_POINTS);

		for (int i = 0; i <= 300; i++) {
			glVertex3f(triggerWidth, (GLfloat)cos(2 * PI*(i / 1000.0f))*0.35f, (GLfloat)sin(2 * PI*(i / 1000.0f))*0.35f);
		}
		glEnd();
		triggerWidth += 0.01f;
	}

	triggerWidth = -0.04f;
	glColor3f(0.4f, 0.4f, 0.4f);
	glTranslatef(0.0f, -1.3f, 0.3f);
	glRotatef(-40, 1.0, 0.0, 0.0);
	for (int j = 0; j <= 10; j++) {
		glBegin(GL_POINTS);

		for (int i = 0; i <= 300; i++) {
			glVertex3f(triggerWidth, (GLfloat)cos(2 * PI*(i / 1000.0f))*0.35f, (GLfloat)sin(2 * PI*(i / 1000.0f))*0.35f);
		}
		glEnd();
		triggerWidth += 0.01f;
	}

}


void DrawHandleDesign(void) {

	float y = -1.0;
	float handleWidth = -0.2f;
	float handleBreadth = 0.0;
	// back
	glColor3f(114.0f / 255.0f, 48.0f / 255.0f, 4.0f / 255.0f);
	for (int j = 0; j <= 40; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 450; i++) {
			glVertex3f(handleWidth, y, ((y + 0.15f)*(y + 0.15f)*0.5f));
			y += 0.005f;
		}
		glEnd();
		y = -1.0;
		handleWidth += 0.01f;
	}

	glColor3f(96.0f / 255.0f, 41.0f / 255.0f, 3.0f / 255.0f);
	//glColor3f(127.0 / 255.0, 67.0 / 255.0, 36.0 / 255.0);
	for (int j = 0; j <= 28; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 450; i++) {
			glVertex3f(-0.2f, y, ((y + 0.15f)*(y + 0.15f)*0.5f) + handleBreadth);
			y += 0.005f;
		}
		glEnd();
		y = -1.0;
		handleBreadth += 0.01f;
	}

	handleBreadth = 0.0;
	for (int j = 0; j <= 28; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 450; i++) {
			glVertex3f(0.22f, y, ((y + 0.15f)*(y + 0.15f)*0.5f) + handleBreadth);
			y += 0.005f;
		}
		glEnd();
		y = -1.0;
		handleBreadth += 0.01f;
	}

	//front
	
	//glColor3f(1.0, 0.0, 0.0);
	//for (int j = 0; j <= 40; j++) {
	//	glBegin(GL_POINTS);
	//	for (int i = 0; i <= 450; i++) {
	//		glVertex3f(handleWidth, y, ((y + 0.15)*(y + 0.15)*0.5));
	//		y += 0.005;
	//	}
	//	glEnd();
	//	y = -1.0;
	//	handleWidth += 0.01;
	//}
	//middle
	////glColor3f(127.0 / 255.0, 67.0 / 255.0, 36.0 / 255.0);
	////for (int j = 0; j <= 28; j++) {
	////	glBegin(GL_POINTS);
	////	for (int i = 0; i <= 350; i++) {
	////		glVertex3f(-0.2, y, ((y + 0.15)*(y + 0.15)) + handleBreadth);
	////		y += 0.005;
	////	}
	////	glEnd();
	////	y = -1.0;
	////	handleBreadth += 0.01;
	////}

	////handleBreadth = 0.0;
	////for (int j = 0; j <= 28; j++) {
	////	glBegin(GL_POINTS);
	////	for (int i = 0; i <= 350; i++) {
	////		glVertex3f(0.22, y, ((y + 0.15)*(y + 0.15)) + handleBreadth);
	////		y += 0.005;
	////	}
	////	glEnd();
	////	y = -1.0;
	////	handleBreadth += 0.01;
	////}
	//front
	handleBreadth = 0.0;
	glTranslatef(0.0f, 0.0f, 0.7f);
	glRotatef(10, 1.0, 0.0, 0.0);
	
	handleWidth = -0.2f;
	for (int j = 0; j <= 40; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 350; i++) {
			glVertex3f(handleWidth, y, ((y + 0.15f)*(y + 0.15f)*0.4f) +0.21f );
			y += 0.005f;
		}
		glEnd();
		y = -1.0;
		handleWidth += 0.01f;
	}

	glColor3f(96.0f / 255.0f, 41.0f / 255.0f, 3.0f / 255.0f);
	//glColor3f(127.0 / 255.0, 67.0 / 255.0, 36.0 / 255.0);
	for (int j = 0; j <= 20; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 350; i++) {
			glVertex3f(-0.2f, y, ((y + 0.15f)*(y + 0.15f)*0.4f) + handleBreadth);
			y += 0.005f;
		}
		glEnd();
		y = -1.0;
		handleBreadth += 0.01f;
	}
	//glTranslatef(0.0, -0.2, 0.3);
	handleBreadth = 0.0;
	for (int j = 0; j <= 20; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 350; i++) {
			glVertex3f(0.22f, y, ((y + 0.15f)*(y + 0.15f)*0.4f) + handleBreadth);
			y += 0.005f;
		}
		glEnd();
		y = -1.0;
		handleBreadth += 0.01f;
	}
}

void DrawBelletSlots(float bulletScale) {
	//glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//depth prev now after rotate, it's position on current x means actual z-axis
	//keep initial depth fixed as -3.0, and adjust with zCord param
	//glTranslatef(xOriginalCord + xCord, yOriginalCord + yCord, zOriginalCord + zCord);

	//glPushMatrix(); // save initial position
					//glRotatef(90, 0.0, 1.0, 0.0);
					//gluLookAt(xTest, 0.0, 15.0 , 0.0, 0.0, -5.0, 0.0f, 1.0f, 0.0f);
	glRotatef(180, 0.0, 1.0, 0.0); // temporary
								   //gluLookAt(0.0, 0.0f, -xTest, 0.0, 0.0, xTest-5.0, 0.0f, 1.0f, 0.0f); //zoomout effect

	//glRotatef((GLfloat)rotateSingleBullet, 0.0, 1.0, 0.0);
	//glTranslatef(0.0, 0.0, zShift);

	//glTranslatef(xCord, yCord, zCord);
	//here xCord --> depth and zCord --> position on x screen / x-axis -- >IMP

	//glTranslatef(0.0, -0.5, 0.0); 

	glPushMatrix(); // save position of first object which will rotate around the initial point
	glColor3f(91.0f / 255.0f, 88.0f / 255.0f, 87.0f / 255.0f);
	quadric = gluNewQuadric();

	// inner disk back of the bullet
	gluDisk(quadric, 0.001, 0.35*bulletScale, 20, 20);

	//yellowinsh shade
	glColor3f(153.0f / 255.0f, 151.0f / 255.0f, 146.0f / 255.0f);
	quadric = gluNewQuadric();

	// outer disk back of the bullet
	gluDisk(quadric, 0.35*bulletScale, 0.5*bulletScale, 20, 20);

	// now we will draw second object which is related to the first one
	// back cylinder
	glPopMatrix(); // actually not needed since we didn't change the position

	glPushMatrix(); // save the previous position
	glColor3f(153.0f / 255.0f, 151.0f / 255.0f, 146.0f / 255.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5f*bulletScale, 0.5f*bulletScale, 0.08f*bulletScale, 20, 20);
	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.08f*bulletScale); // since we have rotated the whole matrix by hard
											  // coded 90 degrees first, so every axis got shifted and +z takes place of +x
											  //glRotatef((GLfloat)extra1, 0.0, 0.0, 1.0);
											  //glTranslatef(0.0, -0.5, 0.0);

	glPushMatrix();
	glColor3f(99.0f / 255.0f, 98.0f / 255.0f, 96.0f / 255.0f);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix(); // translated position by 0.05

	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix(); // save the previous position second cylinder
	glColor3f(153.0f / 255.0f, 151.0f / 255.0f, 146.0f / 255.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.4f*bulletScale, 0.4f*bulletScale, 0.15f*bulletScale, 20, 20);

	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.15f*bulletScale);
	glPushMatrix();
	glColor3f(99.0f / 255.0f, 98.0f / 255.0f, 96.0f / 255.0f);
	//glColor3f(0.6, 0.2, 0.0);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01f, 0.5f*bulletScale, 20, 20);

	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.5);
	glPushMatrix();
	glColor3f(160.0f / 255.0f, 157.0f / 255.0f, 155.0f / 255.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5f*bulletScale, 0.5f*bulletScale, 1.8f*bulletScale, 20, 20);

	glPopMatrix();

	//glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 1.8f*bulletScale);
	glPushMatrix(); // save the previous position second cylinder
	glScalef(1.0f, 1.0f, 2.0f);
	glColor3f(160.0f / 255.0f, 157.0f / 255.0f, 155.0f / 255.0f);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.5*bulletScale, 20, 20);

	glPopMatrix();
	//glPopMatrix();
}

void DrawBulletHolderDisc(float pistolScale) {
	float angle = 0.0;
	glPointSize(3.0f);
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(0.15f, 0.15f, 0.15f);
	for (int i = 0; i <= 100; i++) {

		if (i < 35) {
			glColor3f(0.1f, 0.1f, 0.1f);
		}
		else if (i < 50) {
			glColor3f(0.2f, 0.2f, 0.2f);
		}
		else if (i<70)
		{
			glColor3f(0.4f, 0.4f, 0.4f);
		}
		else {
			glColor3f(0.6f, 0.6f, 0.6f);
		}

		angle = (GLfloat)(2 * PI*i / 100.0f);
		glVertex3f((GLfloat)cos(angle) *0.1f*pistolScale, (GLfloat)sin(angle)*0.1f*pistolScale, 0.2f);
	}
	glEnd();
}

// draw graph paper
void drawGraphPaper(void) {

	float xIndex = 0.0f;
	float yIndex = 0.0f;
	glLineWidth(1.5f);
	//start drawing graph
	glBegin(GL_LINES);
	//glColor3f(0.4f, 0.4f, 0.4f);
	//glVertex3f(-1.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, -1.0f, 0.0f);
	//glEnd();

	//glLineWidth(1.0f);
	//glBegin(GL_LINES);
	glColor3f(0.4f, 0.4f, 0.4f);
	for (xIndex = -5.0f; xIndex < 5.0f; (xIndex += 1.0f))
	{
		glVertex3f(xIndex, 5.0f, 0.0f);
		glVertex3f(xIndex, -5.0f, 0.0f);
	}


	for (yIndex = -5.0f; yIndex < 5.0f; (yIndex += 1.0f))
	{
		glVertex3f(5.0f, yIndex, 0.0f);
		glVertex3f(-5.0f, yIndex, 0.0f);
	}
	glEnd();
	// end of graph
}

// update rotation angles
//
//void update(void) {
//
//	
//	anglePyramid += 0.007f;
//	if (anglePyramid >= 360) {
//		anglePyramid = 0.0;
//	}
//
//}
