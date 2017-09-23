#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"Util.h"

/*****************Here Onwards the function dedicated to LucaBracy(Yellow) character*****************/
void DrawSphere_LucaBracy(GLfloat radius, GLint slices, GLint stacks);

void DrawArcUsingGL_POINTS_LucaBracy(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat r, GLfloat startAngle, GLfloat endAngle, GLfloat pointSize);

/*****************Here Onwards the function dedicated to GodFather(Red Rose) character*****************/


/*****************Here Onwards the function dedicated to LucaBracy(Yellow) character*****************/

void DrawSphere_LucaBracy(GLfloat radius, GLint slices, GLint stacks)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
	GLUquadric *quadric = NULL;
	quadric = gluNewQuadric();
	gluSphere(quadric, radius, slices, stacks);
}

void DrawChestDesign_LucaBracy()
{
	glPushMatrix();
	// zig-zag line of left side
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( 0.2f, 0, -0.73f);
	glVertex3f( 0.4f, -0.3f, -0.73f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( 0.4f, -0.3f, -0.73f);
	glVertex3f( 0.1f, -0.3f, -0.73f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1f, -0.3f, -0.73f);
	glVertex3f( 0.4f, -0.5f, -0.73f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4f, -0.5f, -0.73f);
	glVertex3f( 0.2f, -1.3f, -0.73f);
	glEnd();

	// zig-zag line of right side
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( - 1.2f, 0, -0.73f);
	glVertex3f( - 1.4f, -0.3f, -0.73f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( - 1.4f, -0.3f, -0.73f);
	glVertex3f(- 1.1f, -0.3f, -0.73f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( - 1.1f, -0.3f, -0.73f);
	glVertex3f( - 1.4f, -0.5f, -0.73f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( - 1.4f, -0.5f, -0.73f);
	glVertex3f( - 1.2f, -1.3f, -0.73f);
	glEnd();

	// two black lines above tie
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex3f( - 0.5f, 0, -0.73f);
	glVertex3f( - 0.2f, -0.3f, -0.73f);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( - 0.5f, 0, -0.73f);
	glVertex3f( - 0.8f, -0.3f, -0.73f);
	glEnd();

	// two black lines below tie
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( - 0.2f, -0.5f, -0.73f);
	glVertex3f( - 0.5f, -0.8f, -0.73f);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(- 0.45f, -0.85f, -0.73f);
	glVertex3f(- 0.8f, -0.5f, -0.73f);
	glEnd();

	// edge of shirt below tie
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( - 0.45f, -0.85f, -0.73f);
	glVertex3f( - 0.45f, -1.4f, -0.73f);
	glEnd();

	// buttons
	GLfloat buttonY = 0.9f;
	GLfloat radius = 0.05;
	GLint butttonCount = 3.0f;
	for (GLfloat i = 1.0f; i <= butttonCount; i = i + 1.0f)
	{
		glLineWidth(3);
		glBegin(GL_POINTS);
		for (GLfloat angle = 0.0f; angle < 2.0f*3.14f; angle = angle + 0.001f)
		{
			glVertex3f((cos(angle)*radius) - 0.1f, (sin(angle)*radius) - buttonY, (-0.73f));
		}
		buttonY = buttonY + 0.2f;
		glEnd();
	}

	// first half part of tie with red color
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f( - 0.5f, 0, -0.73f);
	glVertex3f(- 0.3f, -0.18f, -0.73f);
	glVertex3f(- 0.45f, -0.3f, -0.73f);
	glVertex3f(- 0.55f, -0.3f, -0.73f);
	glVertex3f(- 0.7f, -0.18f, -0.73f);
	glEnd();

	// border around first half part of tie with black color
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( - 0.5f, 0, -0.73f);
	glVertex3f( - 0.3f, -0.18f, -0.73f);
	glVertex3f( - 0.45f, -0.3f, -0.73f);
	glVertex3f( - 0.55f, -0.3f, -0.73f);
	glVertex3f( - 0.7f, -0.18f, -0.73f);
	glEnd();

	// second half part of tie with red color
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f( - 0.3f, -0.6f, -0.73f);
	glVertex3f( - 0.4f, -0.3f, -0.73f);
	glVertex3f( - 0.6f, -0.3f, -0.73f);
	glVertex3f( - 0.7f, -0.6f, -0.73f);
	glVertex3f( - 0.5f, -0.8f, -0.73f);
	glEnd();

	// border around second half part of tie with black color
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(- 0.3f, -0.6f, -0.73f);
	glVertex3f( - 0.4f, -0.3f, -0.73f);
	glVertex3f( - 0.6f, -0.3f, -0.73f);
	glVertex3f( - 0.7f, -0.6f, -0.73f);
	glVertex3f( - 0.5f, -0.8f, -0.73f);
	glEnd();

	GLfloat curvyRadius = 1.5f;
	// left side curvy lines
	DrawArcUsingGL_POINTS_LucaBracy(+ 1.3f, -0.7f, (-0.73f), curvyRadius, 2.65f, 3.55f, 2.0f);
	// right side curvy lines
	DrawArcUsingGL_POINTS_LucaBracy( - 2.3f, -0.7f, (-0.73f), curvyRadius, 0.0f, 0.50f, 2.0f);
	DrawArcUsingGL_POINTS_LucaBracy( - 2.3f, -0.7f, (-0.73f), curvyRadius, 5.875f, 6.28f, 2.0f);
	glPopMatrix();
}


void DrawLucaBracyChest()
{
	float chestBottomHeight = 0.3f;
	float height = -(gfChestHeight - chestBottomHeight);
	float topX = gfChestUpperWidth;
	float topZ = gfChestWidth;
	float bottomX = gfChestLowerWidth;
	float color[3] = { 0.5f, 0.25f, 0.0f };


	float points[10][3] = {
		{ topX, 0, topZ },
		{ -topX, 0, topZ },
		{ -topX, 0, -topZ },
		{ topX, 0, -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(points, color);

	height = -gfChestHeight;
	topX = gfChestLowerWidth;
	topZ = gfChestWidth;
	bottomX = gfChestLowerWidth;

	float pointsChestBottom[10][3] = {
		{ topX, -(gfChestHeight - chestBottomHeight), topZ },
		{ -topX, -(gfChestHeight - chestBottomHeight), topZ },
		{ -topX, -(gfChestHeight - chestBottomHeight), -topZ },
		{ topX, -(gfChestHeight - chestBottomHeight), -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(pointsChestBottom, color);

	DrawChestDesign_LucaBracy();
}


// Draw arc
// x1 - x axis value for center point of circle
// y1 - y axis value for center point of circle
// r - radius of circle
// startAngle - angle from where to start render arc
// endAngle - angle where to end the arc render
void DrawArcUsingGL_POINTS_LucaBracy(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat r, GLfloat startAngle, GLfloat endAngle, GLfloat pointSize)
{
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	for (GLfloat angle = 0.0f; angle < 3.14f*2.0f; angle = angle + 0.01f)
	{
		if (angle >= startAngle && angle <= endAngle)
		{
			glVertex3f(((cos(angle)*r) + x1), ((sin(angle)*r) + y1), z1);
		}
	}
	glEnd();
}

void DrawFaceDesign_LucaBracy()
{
	float color[3] = { 0.0f, 0.0f, 0.0f };
	// eye brows
	glColor3f(0.0f, 0.0f, 0.0f);
	//DrawArcUsingGL_POINTS_LucaBracy(topX - 0.2f, -0.8f, topZ, lb_eyebrowRadius, lb_eyebrowStartAngle, lb_eyebrowEndAngle, lb_eyebrowThickness);
	//	DrawArcUsingGL_POINTS_LucaBracy(topX - 0.7f, -0.8f, topZ, lb_eyebrowRadius, lb_eyebrowStartAngle, lb_eyebrowEndAngle, lb_eyebrowThickness);

	//// RED LINES
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glLineWidth(1.5f);

	//glPushMatrix();
	//glBegin(GL_LINES);
	//glVertex3f( 0.1f, -0.5f, -0.9f);
	//glVertex3f(0.05f, -0.48f, -0.9f);
	//glEnd();
	//glPopMatrix();

	//glPushMatrix();
	//glLineWidth(1.5f);
	//glBegin(GL_LINES);
	//glVertex3f(- 0.1f, -0.55f, -0.9f);
	//glVertex3f( 0.05f, -0.60f, -0.9f);
	//glEnd();
	//glPopMatrix();

	////// RIGHT RED LINES
	////glPushMatrix();
	////glColor3f(1.0f, 0.0f, 0.0f);
	////glLineWidth(1.5f);
	////glBegin(GL_LINES);
	////glVertex3f(0.8f, -0.5f, -0.9f);
	////glVertex3f(- 0.95f, -0.48f, -0.9f);
	////glEnd();
	////glLineWidth(1.5f);
	////glBegin(GL_LINES);
	////glVertex3f( - 0.8f, -0.55f, -0.9f);
	////glVertex3f( - 0.95f, -0.60f, -0.9f);
	////glEnd();
	////glPopMatrix();

	// LEFT EYE //fixed by  praveen
	glPushMatrix();		// push matrix for left eye
	glTranslatef(-0.2f, -0.5f, -0.8f);		// translation for left eye
	glColor3f(0.0f, 0.0f, 0.0f);	// black color
	DrawSector(0.15f, 0.15f, - 0.01f, color, 0.0f, 2 * 3.145);
	//DrawSphere_LucaBracy(0.14f, 10, 10);
	glPopMatrix();
	
	
	// LEFT PUPIL //fixed by  praveen
	glPushMatrix();
	glTranslatef(-0.2f, -0.5f, -0.81f);		// translation for pupil
	//DrawSphere_LucaBracy(0.05f, 10, 10);		// draw sphere
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;

	DrawSector(0.08f, 0.08f, -0.01f, color, 0.0f, 2 * 3.145);
	glPopMatrix();

	
	// RIGHT EYE //fixed by praveen
	glPushMatrix();		// push matrix for right eye
	glTranslatef(0.3f, -0.5f, -0.8f);		// translation for right eye
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	DrawSector(0.15f, 0.15f, -0.01f, color, 0.0f, 2 * 3.145);
	glPopMatrix();

	// RIGHT PUPIL
	glPushMatrix();
	glTranslatef(0.3f, -0.5f, -0.81f);		// translation for pupil
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	DrawSector(0.08f, 0.08f, -0.01f, color, 0.0f, 2 * 3.145);
	glPopMatrix();
	// pop matrix for right eye
	/*
	*/
					
	// Mustache
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(2.0f);
	
	// Lips //fixed now by praveen
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -1.05f, -0.9f);
	glVertex3f(-0.3f, -1.05f, -0.9f);
	glEnd();
	glPopMatrix();
	//

	// HAT //fixed now by praveen
	glPushMatrix();
	glColor3f(0.5f, 0.25f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -0.1f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 1.3f, 1.5f, 0.2f, 30, 30);

	glTranslatef(0.0f, 0.0f, -0.6f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5f, 1.0f, 0.6f, 30, 30);
	glPopMatrix();
	//
}
void DrawLucaBracyFace()
{
	float height = -gfFaceHeight;
	float topX = gfFaceWidth;
	float topZ = gfFaceWidth;
	float bottomX = gfFaceWidth;
	float color[3] = { 1.0f, 0.5f, 0.25f };

	float points[10][3] = {
		{ topX, 0, topZ },
		{ -topX, 0, topZ },
		{ -topX, 0, -topZ },
		{ topX, 0, -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(points, color);

	DrawFaceDesign_LucaBracy();
}


/*****************Here Onwards the function dedicated to GodFather(Red Rose) character*****************/
