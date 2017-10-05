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

typedef struct colorShades {
	rgbValues topColor;
	rgbValues sideColor;
	rgbValues frontColor;
};

// color scheme for pistol body
rgbValues grayTopColors = { 0.7,0.7,0.7 };
rgbValues graySideColors = { 0.4,0.4,0.4 };
rgbValues grayFrontColors = { 0.3,0.3,0.3 };

colorShades grayShades = { grayTopColors, graySideColors, grayFrontColors };

// color scheme for pistol handle
rgbValues brownTopColors = { 107.0 / 255.0, 69.0 / 255.0, 32.0 / 255.0 };
rgbValues brownSideColors = { 204.0 / 255.0, 130.0 / 255.0, 57.0 / 255.0 };
rgbValues brownFrontColors = { 127.0 / 255.0, 67.0 / 255.0, 36.0 / 255.0 };

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

	float colors[3] = { 0.3,0.3,0.3 };
	float quardsDepth = 0.0;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glTranslatef( 0.0f, 0.6f, 1.8f);
	glScalef(0.35f, 0.35f, 0.35f);
	glPushMatrix();

	glColor3f(0.6, 0.6, 0.6);

	//main outer cylinder
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.2*pistolScale, 0.2*pistolScale, 2.0*pistolScale, 20, 20);
	glColor3f(0.3, 0.3, 0.3);

	// main inner cylinder
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.13*pistolScale, 0.13*pistolScale, 2.0*pistolScale, 20, 20);
	glColor3f(0.2, 0.2, 0.2);

	// upper cubiod on main cylinder
	float points[8][3] = {
		{ (xOriginalCord + 0.1)*pistolScale, (yOriginalCord + 0.29)*pistolScale, (zOriginalCord)*pistolScale },// counter clockwise backside)*pistolScale, upper cube
		{ (xOriginalCord - 0.1)*pistolScale, (yOriginalCord + 0.29)*pistolScale, (zOriginalCord)*pistolScale },
		{ (xOriginalCord - 0.1)*pistolScale, (yOriginalCord + 0.17)*pistolScale, (zOriginalCord)*pistolScale },
		{ (xOriginalCord + 0.1)*pistolScale, (yOriginalCord + 0.17)*pistolScale, (zOriginalCord)*pistolScale },
		{ (xOriginalCord + 0.1)*pistolScale, (yOriginalCord + 0.29)*pistolScale, (zOriginalCord + 1.98)*pistolScale },
		{ (xOriginalCord - 0.1)*pistolScale, (yOriginalCord + 0.29)*pistolScale, (zOriginalCord + 1.98)*pistolScale },
		{ (xOriginalCord - 0.1)*pistolScale, (yOriginalCord + 0.17)*pistolScale, (zOriginalCord + 1.98)*pistolScale },
		{ (xOriginalCord + 0.1)*pistolScale, (yOriginalCord + 0.17)*pistolScale, (zOriginalCord + 1.98)*pistolScale }
	};
	DrawPistolCuboid(points, grayShades);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2.0*pistolScale);
	glColor3f(0.2, 0.2, 0.2);

	// disc on the tip of
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.13*pistolScale, 0.2*pistolScale, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.98*pistolScale);

	// upper cuboid on the main cylinder
	float pointsTopTip[8][3] = {
		{ (xOriginalCord + 0.03)*pistolScale, (yOriginalCord + 0.38)*pistolScale, (zOriginalCord - 0.3)*pistolScale }, // back
		{ xOriginalCord - 0.03, yOriginalCord + 0.38, zOriginalCord - 0.3 },
		{ xOriginalCord - 0.04, yOriginalCord + 0.29, zOriginalCord - 0.5 },
		{ xOriginalCord + 0.04, yOriginalCord + 0.29, zOriginalCord - 0.5 },
		{ xOriginalCord + 0.03, yOriginalCord + 0.38, zOriginalCord },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.03, yOriginalCord + 0.38, zOriginalCord }, // front
		{ xOriginalCord - 0.04, yOriginalCord + 0.29, zOriginalCord },
		{ xOriginalCord + 0.04, yOriginalCord + 0.29, zOriginalCord }

	};
	DrawPistolCuboid(pointsTopTip, grayShades);
	glPopMatrix();
	glPushMatrix();
	// covering disc for back cylinder
	glColor3f(0.2, 0.2, 0.2);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.05, 0.23, 20, 20);
	//translate to draw back cylinder
	glTranslatef(0.0, 0.0, -0.4);
	glColor3f(0.4, 0.4, 0.4);

	// back cylinder
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.23*pistolScale, 0.23*pistolScale, 0.4*pistolScale, 20, 20);
	
	glPopMatrix();
	glPushMatrix();
	// upper cuboid on back cylinder
	float pointsTopBackLower[8][3] = {
		{ xOriginalCord + 0.14, yOriginalCord + 0.32, zOriginalCord - 1.1 }, //back
		{ xOriginalCord - 0.14, yOriginalCord + 0.32, zOriginalCord - 1.1 },
		{ xOriginalCord - 0.14, yOriginalCord + 0.17, zOriginalCord - 1.1 },
		{ xOriginalCord + 0.14, yOriginalCord + 0.17, zOriginalCord - 1.1 },
		{ xOriginalCord + 0.14, yOriginalCord + 0.32, zOriginalCord },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.14, yOriginalCord + 0.32, zOriginalCord },
		{ xOriginalCord - 0.14, yOriginalCord + 0.17, zOriginalCord },
		{ xOriginalCord + 0.14, yOriginalCord + 0.17, zOriginalCord }


	};
	DrawPistolCuboid(pointsTopBackLower, grayShades);

	glPopMatrix();
	glPushMatrix();	
	// front disc for bullets holder
	glTranslatef(0.0, -0.2, -0.3);
	glColor3f(0.3, 0.3, 0.3);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.005*pistolScale, 0.45*pistolScale, 20, 20);
	glPopMatrix();
	glPushMatrix();
	// rear disc for bullets holder 
	glTranslatef(0.0, -0.2, -1.0);
	glColor3f(0.2, 0.2, 0.2);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.005*pistolScale, 0.45*pistolScale, 20, 20);

	// bullets holder
	glColor3f(0.45, 0.45, 0.45);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.45*pistolScale, 0.45*pistolScale, 0.7*pistolScale, 20, 20);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles left
	glTranslatef(-0.22, -0.04, -0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles left
	glTranslatef(-0.27, -0.295, -0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles left
	glTranslatef(-0.1, -0.49, -0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles right
	glTranslatef(0.22, -0.04, -0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles right
	glTranslatef(0.27, -0.295, -0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	// bullets holder circles right
	glTranslatef(0.1, -0.49, -0.49);
	DrawBulletHolderDisc(pistolScale);
	glPopMatrix();
	glPushMatrix();
	//frame around bullet holder
	float pointsFrame[8][3] = {
		{ xOriginalCord + 0.14, yOriginalCord + 0.17, zOriginalCord - 1.18 }, //back
		{ xOriginalCord - 0.14, yOriginalCord + 0.17, zOriginalCord - 1.18 },
		{ xOriginalCord - 0.14, yOriginalCord - 0.8, zOriginalCord - 1.18 },
		{ xOriginalCord + 0.14, yOriginalCord - 0.8, zOriginalCord - 1.18 },
		{ xOriginalCord + 0.14, yOriginalCord + 0.17, zOriginalCord - 0.2 },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.14, yOriginalCord + 0.17, zOriginalCord - 0.2 },
		{ xOriginalCord - 0.14, yOriginalCord - 0.8, zOriginalCord - 0.2 },
		{ xOriginalCord + 0.14, yOriginalCord - 0.8, zOriginalCord - 0.2 }


	};
	DrawPistolCuboid(pointsFrame, grayShades);

	// the cuboid just above and behind the trigger
	float pointsFrame2[8][3] = {
		{ xOriginalCord + 0.14, yOriginalCord - 0.3, zOriginalCord - 1.7 },//back
		{ xOriginalCord - 0.14, yOriginalCord - 0.3, zOriginalCord - 1.7 },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.14, yOriginalCord - 0.8, zOriginalCord - 1.4 },
		{ xOriginalCord + 0.14, yOriginalCord - 0.8, zOriginalCord - 1.4 },
		{ xOriginalCord + 0.14, yOriginalCord - 0.3, zOriginalCord - 1.0 }, 
		{ xOriginalCord - 0.14, yOriginalCord - 0.3, zOriginalCord - 1.0 },
		{ xOriginalCord - 0.14, yOriginalCord - 0.8, zOriginalCord - 1.0 },
		{ xOriginalCord + 0.14, yOriginalCord - 0.8, zOriginalCord - 1.0 },

	};
	DrawPistolCuboid(pointsFrame2, grayShades);

	glPopMatrix();
	glPushMatrix();
	
	// the cuboid for handle
	float pointsHandle[8][3] = {

		{ xOriginalCord + 0.18, yOriginalCord - 1.8, zOriginalCord - 2.3 },//back
		{ xOriginalCord - 0.18, yOriginalCord - 1.8, zOriginalCord - 2.3 },
		{ xOriginalCord - 0.18, yOriginalCord - 2.6, zOriginalCord - 1.8 },
		{ xOriginalCord + 0.18, yOriginalCord - 2.6, zOriginalCord - 1.8 },
		{ xOriginalCord + 0.18, yOriginalCord - 0.3, zOriginalCord - 1.7 },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.18, yOriginalCord - 0.3, zOriginalCord - 1.7 },
		{ xOriginalCord - 0.18, yOriginalCord - 0.8, zOriginalCord - 1.3 },
		{ xOriginalCord + 0.18, yOriginalCord - 0.8, zOriginalCord - 1.3 },

	};
	DrawPistolCuboid(pointsHandle, brownShades);

	float pointsHandle2[8][3] = {

		{ xOriginalCord + 0.18, yOriginalCord - 2.7, zOriginalCord - 1.8 },//back
		{ xOriginalCord - 0.18, yOriginalCord - 2.7, zOriginalCord - 1.8 },
		{ xOriginalCord - 0.18, yOriginalCord - 2.6, zOriginalCord - 1.2 },
		{ xOriginalCord + 0.18, yOriginalCord - 2.6, zOriginalCord - 1.2 },
		{ xOriginalCord + 0.18, yOriginalCord - 1.7, zOriginalCord - 2.2 },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.18, yOriginalCord - 1.7, zOriginalCord - 2.2 },
		{ xOriginalCord - 0.18, yOriginalCord - 1.5, zOriginalCord - 1.7 },
		{ xOriginalCord + 0.18, yOriginalCord - 1.5, zOriginalCord - 1.7 },

	};
	DrawPistolCuboid(pointsHandle2, brownShades);

	// draw embedded outer bullets around bullet holder --> it's just a design
	//right side
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.25, 0.15, -0.32);
	DrawBelletSlots(0.2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.44, -0.15, -0.32);
	DrawBelletSlots(0.2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.32, -0.49, -0.32);
	DrawBelletSlots(0.2);
	glPopMatrix();

	// left
	glPushMatrix();
	glTranslatef(0.25, 0.15, -0.32);
	DrawBelletSlots(0.2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.44, -0.15, -0.32);
	DrawBelletSlots(0.2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.32, -0.49, -0.32);
	DrawBelletSlots(0.2);
	
	// handle and design
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -1.8, -2.4);
	glRotatef(-14.0, 1.0, 0.0, 0.0);
	glColor3f(204.0 / 255.0, 130.0 / 255.0, 57.0 / 255.0);
	DrawHandleDesign();
	glPopMatrix();

	// trigger circle
	glPushMatrix();
	glTranslatef(0.0, -1.3, -0.9);
	DrawTrigger();
	glPopMatrix();

	glPushMatrix();
	// cubiod below main cylinder
	float pointsLowerCuboid[8][3] = {
		{ xOriginalCord + 0.12, yOriginalCord - 0.33, zOriginalCord - 0.3 },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.12, yOriginalCord - 0.33, zOriginalCord - 0.3 },
		{ xOriginalCord - 0.12, yOriginalCord - 0.19, zOriginalCord - 0.3 },
		{ xOriginalCord + 0.12, yOriginalCord - 0.19, zOriginalCord - 0.3 },
		{ xOriginalCord + 0.12, yOriginalCord - 0.33, zOriginalCord + 1.0},
		{ xOriginalCord - 0.12, yOriginalCord - 0.33, zOriginalCord + 1.0 },
		{ xOriginalCord - 0.12, yOriginalCord - 0.19, zOriginalCord + 1.0 },
		{ xOriginalCord + 0.12, yOriginalCord - 0.19, zOriginalCord + 1.0 }
	};
	DrawPistolCuboid(pointsLowerCuboid, grayShades);
	glPopMatrix();
	glPushMatrix();
	// cubiod below trigger
	float pointsBelowTrigger[8][3] = {
		{ xOriginalCord + 0.12, yOriginalCord - 1.0, zOriginalCord - 0.5 },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.12, yOriginalCord - 1.0, zOriginalCord - 0.5 },
		{ xOriginalCord - 0.12, yOriginalCord - 0.5, zOriginalCord - 0.5 },
		{ xOriginalCord + 0.12, yOriginalCord - 0.5, zOriginalCord - 0.5 },
		{ xOriginalCord + 0.12, yOriginalCord - 1.0, zOriginalCord - 1.3 },
		{ xOriginalCord - 0.12, yOriginalCord - 1.0, zOriginalCord - 1.3 },
		{ xOriginalCord - 0.12, yOriginalCord - 0.5, zOriginalCord - 1.3 },
		{ xOriginalCord + 0.12, yOriginalCord - 0.5, zOriginalCord - 1.3 }
	};
	DrawPistolCuboid(pointsBelowTrigger, grayShades);
	glPopMatrix();
	glPushMatrix();

	// fillings around trigger ring
	glColor3f(0.4, 0.4, 0.4);
	//back
	for (int i = 0; i < 50; i++) {
		glBegin(GL_QUADS);
		glVertex3f(xOriginalCord + 0.12, yOriginalCord - 1.0, zOriginalCord - 1.3 + quardsDepth);
		glVertex3f(xOriginalCord - 0.12, yOriginalCord - 1.0, zOriginalCord - 1.3 + quardsDepth);
		glVertex3f(xOriginalCord - 0.12, yOriginalCord - 1.3, zOriginalCord - 1.3 + quardsDepth);
		glVertex3f(xOriginalCord + 0.12, yOriginalCord - 1.3, zOriginalCord - 1.3 + quardsDepth);
		glEnd();
		quardsDepth += 0.002;
	}
	quardsDepth = 0.0;
	// back ++
	for (int i = 0; i < 50; i++) {
		glBegin(GL_QUADS);
		glVertex3f(xOriginalCord + 0.12, yOriginalCord - 0.9, zOriginalCord - 1.2 + quardsDepth);
		glVertex3f(xOriginalCord - 0.12, yOriginalCord - 0.9, zOriginalCord - 1.2 + quardsDepth);
		glVertex3f(xOriginalCord - 0.12, yOriginalCord - 1.05, zOriginalCord - 1.2 + quardsDepth);
		glVertex3f(xOriginalCord + 0.12, yOriginalCord - 1.05, zOriginalCord - 1.2 + quardsDepth);
		glEnd();
		quardsDepth += 0.002;
	}


	// front
	for (int i = 0; i < 140; i++) {
		glBegin(GL_QUADS);
		glVertex3f(xOriginalCord + 0.12, yOriginalCord - 1.0, zOriginalCord - 0.75 + quardsDepth);
		glVertex3f(xOriginalCord - 0.12, yOriginalCord - 1.0, zOriginalCord - 0.75+ quardsDepth);
		glVertex3f(xOriginalCord - 0.12, yOriginalCord - 1.3, zOriginalCord - 0.75+ quardsDepth);
		glVertex3f(xOriginalCord + 0.12, yOriginalCord - 1.3, zOriginalCord - 0.75+ quardsDepth);
		glEnd();
		quardsDepth += 0.001;
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
		glVertex3f(xOriginalCord + 0.12, yOriginalCord - 0.8, zOriginalCord - 0.72 + quardsDepth);
		glVertex3f(xOriginalCord - 0.12, yOriginalCord - 0.8, zOriginalCord - 0.72 + quardsDepth);
		glVertex3f(xOriginalCord - 0.12, yOriginalCord - 1.0, zOriginalCord - 0.72 + quardsDepth);
		glVertex3f(xOriginalCord + 0.12, yOriginalCord - 1.0, zOriginalCord - 0.72 + quardsDepth);
		glEnd();
		quardsDepth += 0.002;
	}

	
	glPopMatrix();

	glPushMatrix();
	// upper trigger notch 

	float pointsUpperNotch[8][3] = {
		{ xOriginalCord + 0.06, yOriginalCord + 0.2, zOriginalCord - 1.7 },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.06, yOriginalCord + 0.2, zOriginalCord - 1.7 },
		{ xOriginalCord - 0.06, yOriginalCord + 0.1, zOriginalCord - 1.5 },
		{ xOriginalCord + 0.06, yOriginalCord + 0.1, zOriginalCord - 1.5 },
		{ xOriginalCord + 0.06, yOriginalCord + 0.2, zOriginalCord - 1.45 },
		{ xOriginalCord - 0.06, yOriginalCord + 0.2, zOriginalCord - 1.45 },
		{ xOriginalCord - 0.06, yOriginalCord + 0.1, zOriginalCord - 1.35 },
		{ xOriginalCord + 0.06, yOriginalCord + 0.1, zOriginalCord - 1.35}
	};
	DrawPistolCuboid(pointsUpperNotch, grayShades);
	glPopMatrix();

	glPushMatrix();
	// cubiod below main cylinder

	float pointsNotch1[8][3] = {
		{ xOriginalCord + 0.08, yOriginalCord + 0.45, zOriginalCord - 1.0 },// counter clockwise backside, upper cube
		{ xOriginalCord + 0.04, yOriginalCord + 0.45, zOriginalCord - 1.0 },
		{ xOriginalCord + 0.00, yOriginalCord + 0.3, zOriginalCord - 1.0 },
		{ xOriginalCord + 0.02, yOriginalCord + 0.3, zOriginalCord - 1.0 },
		{ xOriginalCord + 0.08, yOriginalCord + 0.45, zOriginalCord - 1.1 },
		{ xOriginalCord + 0.04, yOriginalCord + 0.45, zOriginalCord - 1.1 },
		{ xOriginalCord + 0.00, yOriginalCord + 0.3, zOriginalCord - 1.1 },
		{ xOriginalCord + 0.02, yOriginalCord + 0.3, zOriginalCord - 1.1 }
	};
	DrawPistolCuboid(pointsNotch1, grayShades);
	glPopMatrix();

	glPushMatrix();
	// cubiod below main cylinder

	float pointsNotch2[8][3] = {
		{ xOriginalCord - 0.08, yOriginalCord + 0.45, zOriginalCord - 1.0 },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.04, yOriginalCord + 0.45, zOriginalCord - 1.0 },
		{ xOriginalCord - 0.00, yOriginalCord + 0.3, zOriginalCord - 1.0 },
		{ xOriginalCord - 0.02, yOriginalCord + 0.3, zOriginalCord - 1.0 },
		{ xOriginalCord - 0.08, yOriginalCord + 0.45, zOriginalCord - 1.1 },
		{ xOriginalCord - 0.04, yOriginalCord + 0.45, zOriginalCord - 1.1 },
		{ xOriginalCord - 0.00, yOriginalCord + 0.3, zOriginalCord - 1.1 },
		{ xOriginalCord - 0.02, yOriginalCord + 0.3, zOriginalCord - 1.1 }
	};
	DrawPistolCuboid(pointsNotch2, grayShades);
	glPopMatrix();

	glPushMatrix();
	// cubiod below main cylinder

	float pointsHandleCover[8][3] = {
		{ xOriginalCord + 0.22, yOriginalCord - 0.2, zOriginalCord - 1.7 },// counter clockwise backside, upper cube
		{ xOriginalCord - 0.20, yOriginalCord - 0.2, zOriginalCord - 1.7 },
		{ xOriginalCord - 0.20, yOriginalCord - 0.4, zOriginalCord - 1.7 },
		{ xOriginalCord + 0.22, yOriginalCord - 0.4, zOriginalCord - 1.7 },
		{ xOriginalCord + 0.12, yOriginalCord - 0.2, zOriginalCord - 1.0 },
		{ xOriginalCord - 0.12, yOriginalCord - 0.2, zOriginalCord - 1.0 },
		{ xOriginalCord - 0.12, yOriginalCord - 0.4, zOriginalCord - 1.0 },
		{ xOriginalCord + 0.12, yOriginalCord - 0.4, zOriginalCord - 1.0 }
	};
	DrawPistolCuboid(pointsHandleCover, grayShades);
	glPopMatrix();
	glPopMatrix();

}

void DrawTrigger(void) {

	float triggerWidth = -0.08;
	glPointSize(5.0f);
	glColor3f(0.4, 0.4, 0.4);
	for (int j = 0; j <= 15; j++) {
		glBegin(GL_POINTS);
		
		for (int i = 0; i <= 1000; i++) {
			glVertex3f(triggerWidth, cos(2 * PI*(i / 1000.0))*0.35 , sin(2 * PI*(i / 1000.0))*0.35);
		}
		glEnd();
		triggerWidth += 0.01;
	}

	triggerWidth = -0.08;
	glColor3f(0.3, 0.3, 0.3);
	glTranslatef(0.0, 0.2, 0.15);
	glRotatef(180, 1.0, 0.0, 0.0);
	for (int j = 0; j <= 15; j++) {
		glBegin(GL_POINTS);

		for (int i = 0; i <= 300; i++) {
			glVertex3f(triggerWidth, cos(2 * PI*(i / 1000.0))*0.35, sin(2 * PI*(i / 1000.0))*0.35);
		}
		glEnd();
		triggerWidth += 0.01;
	}

	triggerWidth = -0.04;
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0.0, -1.3, 0.3);
	glRotatef(-40, 1.0, 0.0, 0.0);
	for (int j = 0; j <= 10; j++) {
		glBegin(GL_POINTS);

		for (int i = 0; i <= 300; i++) {
			glVertex3f(triggerWidth, cos(2 * PI*(i / 1000.0))*0.35, sin(2 * PI*(i / 1000.0))*0.35);
		}
		glEnd();
		triggerWidth += 0.01;
	}

}


void DrawHandleDesign(void) {

	float y = -1.0;
	float handleWidth = -0.2;
	float handleBreadth = 0.0;
	// back
	glColor3f(114.0 / 255.0, 48.0 / 255.0, 4.0 / 255.0);
	for (int j = 0; j <= 40; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 450; i++) {
			glVertex3f(handleWidth, y, ((y + 0.15)*(y + 0.15)*0.5));
			y += 0.005;
		}
		glEnd();
		y = -1.0;
		handleWidth += 0.01;
	}

	glColor3f(96.0 / 255.0, 41.0 / 255.0, 3.0 / 255.0);
	//glColor3f(127.0 / 255.0, 67.0 / 255.0, 36.0 / 255.0);
	for (int j = 0; j <= 28; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 450; i++) {
			glVertex3f(-0.2, y, ((y + 0.15)*(y + 0.15)*0.5) + handleBreadth);
			y += 0.005;
		}
		glEnd();
		y = -1.0;
		handleBreadth += 0.01;
	}

	handleBreadth = 0.0;
	for (int j = 0; j <= 28; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 450; i++) {
			glVertex3f(0.22, y, ((y + 0.15)*(y + 0.15)*0.5) + handleBreadth);
			y += 0.005;
		}
		glEnd();
		y = -1.0;
		handleBreadth += 0.01;
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
	glTranslatef(0.0, 0.0, 0.7);
	glRotatef(10, 1.0, 0.0, 0.0);
	
	handleWidth = -0.2;
	for (int j = 0; j <= 40; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 350; i++) {
			glVertex3f(handleWidth, y, ((y + 0.15)*(y + 0.15)*0.4) +0.21 );
			y += 0.005;
		}
		glEnd();
		y = -1.0;
		handleWidth += 0.01;
	}

	glColor3f(96.0 / 255.0, 41.0 / 255.0, 3.0 / 255.0);
	//glColor3f(127.0 / 255.0, 67.0 / 255.0, 36.0 / 255.0);
	for (int j = 0; j <= 20; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 350; i++) {
			glVertex3f(-0.2, y, ((y + 0.15)*(y + 0.15)*0.4) + handleBreadth);
			y += 0.005;
		}
		glEnd();
		y = -1.0;
		handleBreadth += 0.01;
	}
	//glTranslatef(0.0, -0.2, 0.3);
	handleBreadth = 0.0;
	for (int j = 0; j <= 20; j++) {
		glBegin(GL_POINTS);
		for (int i = 0; i <= 350; i++) {
			glVertex3f(0.22, y, ((y + 0.15)*(y + 0.15)*0.4) + handleBreadth);
			y += 0.005;
		}
		glEnd();
		y = -1.0;
		handleBreadth += 0.01;
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
	glColor3f(91.0 / 255.0, 88.0 / 255.0, 87.0 / 255.0);
	quadric = gluNewQuadric();

	// inner disk back of the bullet
	gluDisk(quadric, 0.001, 0.35*bulletScale, 20, 20);

	//yellowinsh shade
	glColor3f(153.0 / 255.0, 151.0 / 255.0, 146.0 / 255.0);
	quadric = gluNewQuadric();

	// outer disk back of the bullet
	gluDisk(quadric, 0.35*bulletScale, 0.5*bulletScale, 20, 20);

	// now we will draw second object which is related to the first one
	// back cylinder
	glPopMatrix(); // actually not needed since we didn't change the position

	glPushMatrix(); // save the previous position
	glColor3f(153.0 / 255.0, 151.0 / 255.0, 146.0 / 255.0);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5*bulletScale, 0.5*bulletScale, 0.08*bulletScale, 20, 20);
	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.08*bulletScale); // since we have rotated the whole matrix by hard
											  // coded 90 degrees first, so every axis got shifted and +z takes place of +x
											  //glRotatef((GLfloat)extra1, 0.0, 0.0, 1.0);
											  //glTranslatef(0.0, -0.5, 0.0);

	glPushMatrix();
	glColor3f(99.0 / 255.0, 98.0 / 255.0, 96.0 / 255.0);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix(); // translated position by 0.05

	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix(); // save the previous position second cylinder
	glColor3f(153.0 / 255.0, 151.0 / 255.0, 146.0 / 255.0);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.4*bulletScale, 0.4*bulletScale, 0.15*bulletScale, 20, 20);

	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.15*bulletScale);
	glPushMatrix();
	glColor3f(99.0 / 255.0, 98.0 / 255.0, 96.0 / 255.0);
	//glColor3f(0.6, 0.2, 0.0);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.5);
	glPushMatrix();
	glColor3f(160.0 / 255.0, 157.0 / 255.0, 155.0 / 255.0);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5*bulletScale, 0.5*bulletScale, 1.8*bulletScale, 20, 20);

	glPopMatrix();

	//glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 1.8*bulletScale);
	glPushMatrix(); // save the previous position second cylinder
	glScalef(1.0, 1.0, 2.0);
	glColor3f(160.0 / 255.0, 157.0 / 255.0, 155.0 / 255.0);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.5*bulletScale, 20, 20);

	glPopMatrix();
	//glPopMatrix();
}

void DrawBulletHolderDisc(float pistolScale) {
	float angle = 0.0;
	glPointSize(3.0f);
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(0.15, 0.15, 0.15);
	for (int i = 0; i <= 100; i++) {

		if (i < 35) {
			glColor3f(0.1, 0.1, 0.1);
		}
		else if (i < 50) {
			glColor3f(0.2, 0.2, 0.2);
		}
		else if (i<70)
		{
			glColor3f(0.4, 0.4, 0.4);
		}
		else {
			glColor3f(0.6, 0.6, 0.6);
		}

		angle = 2 * PI*i / 100.0f;
		glVertex3f(cos(angle) *0.1*pistolScale, sin(angle)*0.1*pistolScale, 0.2);
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
