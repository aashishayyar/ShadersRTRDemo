#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"Util.h"
#include"LucaBracy.h"

/*****************Here Onwards the variables dedicated to LucaBracy(Yellow) character*****************/
// Eyebrow
GLfloat eyebrowRadius = 0.5f;
GLfloat eyebrowThickness = 3.0f;
GLfloat eyebrowStartAngle = 1.17f;
GLfloat eyebrowEndAngle = 1.75f;

// Mustache
GLfloat mustacheRadius = 0.8f;
GLfloat mustacheThickness = 2.0f;
GLfloat mustacheStartAngle = 1.3f;
GLfloat mustacheEndAngle = 1.8f;

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

void DrawChestDesign_LucaBracy(GLfloat topX, GLfloat topZ)
{

	topX = topX / 2;
	topZ = -topZ - 0.1f;

	glPushMatrix();
	// zig-zag line of left side
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX + 0.2f, 0, topZ);
	glVertex3f(topX + 0.4f, -0.5f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX + 0.4f, -0.5f, topZ);
	glVertex3f(topX + 0.1f, -0.4f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX + 0.1f, -0.4f, topZ);
	glVertex3f(topX + 0.4f, -0.8f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX + 0.4f, -0.8f, topZ);
	glVertex3f(topX + 0.2f, -1.9f, topZ);
	glEnd();

	// zig-zag line of right side
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 1.2f, 0, topZ);
	glVertex3f(topX - 1.4f, -0.5f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 1.4f, -0.5f, topZ);
	glVertex3f(topX - 1.1f, -0.4f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 1.1f, -0.4f, topZ);
	glVertex3f(topX - 1.4f, -0.8f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 1.4f, -0.8f, topZ);
	glVertex3f(topX - 1.2f, -1.9f, topZ);
	glEnd();

	// two black lines above tie
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex3f(topX - 0.5f, 0, topZ);
	glVertex3f(topX - 0.2f, -0.3f, topZ);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 0.5f, 0, topZ);
	glVertex3f(topX - 0.8f, -0.3f, topZ);
	glEnd();

	// two black lines below tie
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 0.2f, -0.5f, topZ);
	glVertex3f(topX - 0.5f, -0.8f, topZ);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 0.45f, -0.85f, topZ);
	glVertex3f(topX - 0.8f, -0.5f, topZ);
	glEnd();

	// edge of shirt below tie
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 0.45f, -0.85f, topZ);
	glVertex3f(topX - 0.45f, -1.9f, topZ);
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
	glVertex3f(topX - 0.5f, 0, topZ);
	glVertex3f(topX - 0.3f, -0.18f, topZ);
	glVertex3f(topX - 0.45f, -0.3f, topZ);
	glVertex3f(topX - 0.55f, -0.3f, topZ);
	glVertex3f(topX - 0.7f, -0.18f, topZ);
	glEnd();

	// border around first half part of tie with black color
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 0.5f, 0, topZ);
	glVertex3f(topX - 0.3f, -0.18f, topZ);
	glVertex3f(topX - 0.45f, -0.3f, topZ);
	glVertex3f(topX - 0.55f, -0.3f, topZ);
	glVertex3f(topX - 0.7f, -0.18f, topZ);
	glEnd();

	// second half part of tie with red color
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(topX - 0.3f, -0.6f, topZ);
	glVertex3f(topX - 0.4f, -0.3f, topZ);
	glVertex3f(topX - 0.6f, -0.3f, topZ);
	glVertex3f(topX - 0.7f, -0.6f, topZ);
	glVertex3f(topX - 0.5f, -0.8f, topZ);
	glEnd();

	// border around second half part of tie with black color
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 0.3f, -0.6f, topZ);
	glVertex3f(topX - 0.4f, -0.3f, topZ);
	glVertex3f(topX - 0.6f, -0.3f, topZ);
	glVertex3f(topX - 0.7f, -0.6f, topZ);
	glVertex3f(topX - 0.5f, -0.8f, topZ);
	glEnd();

	GLfloat curvyRadius = 1.8f;
	// left side curvy lines
	//DrawArcUsingGL_POINTS_LucaBracy(topX + 1.3f, topZ, (-0.73f), curvyRadius, 2.65f, 3.55f, 2.0f);
	DrawArcUsingGL_POINTS_LucaBracy(topX + 1.5f, -1.0f, topZ, curvyRadius, 2.59f, 3.65f, 2.0f);
	// right side curvy lines
	DrawArcUsingGL_POINTS_LucaBracy(topX - 2.6f, -1.0f, topZ, curvyRadius, 0.0f, 0.57f, 2.0f);
	//DrawArcUsingGL_POINTS_LucaBracy(topX - 2.3f, -1.0f, topZ, curvyRadius, 2.9f, 3.6f, 2.0f);
	DrawArcUsingGL_POINTS_LucaBracy(topX - 2.6f, -1.0f, topZ, curvyRadius, 5.8f, 6.28f, 2.0f);
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

	DrawChestDesign_LucaBracy(topX, topZ);
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

void DrawFaceDesign_LucaBracy(GLfloat topX, GLfloat topZ)
{

	topX = topX / 2;
	topZ = (-topZ - 0.1f);

	float color[3] = { 0.0f, 0.0f, 0.0f };

	//glColor3f(0.0f, 0.0f, 0.0f);

	// eye brows
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawArcUsingGL_POINTS_LucaBracy(topX - 0.2f, -0.8f, topZ, eyebrowRadius, eyebrowStartAngle, eyebrowEndAngle, eyebrowThickness);
	DrawArcUsingGL_POINTS_LucaBracy(topX - 0.7f, -0.8f, topZ, eyebrowRadius, eyebrowStartAngle, eyebrowEndAngle, eyebrowThickness);

	// RED LINES
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(1.5f);
	glBegin(GL_LINES);
	glVertex3f(topX - 0.1f, -0.5f, topZ);
	glVertex3f(topX + 0.05f, -0.48f, topZ);
	glEnd();
	glLineWidth(1.5f);
	glBegin(GL_LINES);
	glVertex3f(topX - 0.1f, -0.55f, topZ);
	glVertex3f(topX + 0.05f, -0.60f, topZ);
	glEnd();

	// RIGHT RED LINES
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(1.5f);
	glBegin(GL_LINES);
	glVertex3f(topX - 0.8f, -0.5f, topZ);
	glVertex3f(topX - 0.95f, -0.48f, topZ);
	glEnd();
	glLineWidth(1.5f);
	glBegin(GL_LINES);
	glVertex3f(topX - 0.8f, -0.55f, topZ);
	glVertex3f(topX - 0.95f, -0.60f, topZ);
	glEnd();

	// LEFT EYE
	glPushMatrix();		// push matrix for left eye
	glTranslatef((topX - 0.2f), -0.5f, 0.0f);		// translation for left eye
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	DrawSector(0.1f, 0.1f, topZ, color, 0.0f, 2 * 3.145);

	// LEFT PUPIL
	glPushMatrix();
	glTranslatef(-0.04f, 0.07f, 0.0f);		// translation for pupil
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	DrawSector(0.05f, 0.05f, topZ, color, 0.0f, 2 * 3.145);
	glPopMatrix();
	glPopMatrix();		// pop matrix for left eye

						// RIGHT EYE
	glPushMatrix();		// push matrix for right eye
	glTranslatef((topX - 0.7f), -0.5f, 0.0f);		// translation for right eye
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	DrawSector(0.1f, 0.1f, topZ, color, 0.0f, 2 * 3.145);

	// RIGHT PUPIL
	glPushMatrix();
	glTranslatef(-0.04f, 0.07f, 0.0f);		// translation for pupil
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	DrawSector(0.05f, 0.05f, topZ, color, 0.0f, 2 * 3.145);
	glPopMatrix();

	glPopMatrix();		// pop matrix for right eye

						// Mustache
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(2.0f);
	DrawArcUsingGL_POINTS_LucaBracy(topX - 0.45f, -1.7f, topZ, mustacheRadius, mustacheStartAngle, mustacheEndAngle, mustacheThickness);

	// Lips
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(topX - 0.35f, -1.05f, topZ);
	glVertex3f(topX - 0.5f, -1.05f, topZ);
	glEnd();

	// DRAW CIGAR
	glPushMatrix();
	glTranslatef(-0.1f, -1.1f, -topZ - 1.7f);
	glRotatef(190.0f, 1.0f, 0.0f, 0.0f);
	color[0] = 0.5f;
	color[1] = 0.0f;
	color[2] = 0.1f;
	DrawCylinder(1.0f, 0.1f, color);

	glTranslatef(0.0f, 0.0f, 1.0f);
	color[0] = 0.8f;
	color[1] = 0.8f;
	color[2] = 0.8f;
	DrawCylinder(0.1f, 0.1f, color);
	glPopMatrix();

	// HAT
	glPushMatrix();
	glColor3f(0.5f, 0.25f, 0.0f);
	glTranslatef(topX - 0.39f, 0.2f, topZ + 1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 1.5f, 1.7f, 0.2f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.8f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5f, 1.3f, 0.7f, 30, 30);
	glPopMatrix();
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

	DrawFaceDesign_LucaBracy(topX, topZ);
}


/*****************Here Onwards the function dedicated to GodFather(Red Rose) character*****************/
