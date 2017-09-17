#include "Character.h"

void updateNormalWalk(int currentStickMan)
{
	if (lLeg[currentStickMan] < -20)
	{
		giLLegDirection[currentStickMan] = 1;
	}
	else if (lLeg[currentStickMan] > 20)
	{
		giLLegDirection[currentStickMan] = -1;
	}
	lLeg[currentStickMan] = lLeg[currentStickMan] + giLLegDirection[currentStickMan] * gfSpeed;

	if (rLeg[currentStickMan] < -20)
	{
		giRLegDirection[currentStickMan] = 1;
	}
	else if (rLeg[currentStickMan] > 20)
	{
		giRLegDirection[currentStickMan] = -1;
	}
	rLeg[currentStickMan] = rLeg[currentStickMan] + giRLegDirection[currentStickMan] * gfSpeed;

	if (lArm[currentStickMan] < 30)
	{
		giLArmDirection[currentStickMan] = 1;
	}
	else if (lArm[currentStickMan] > 70)
	{
		giLArmDirection[currentStickMan] = -1;
	}
	lArm[currentStickMan] = lArm[currentStickMan] + giLArmDirection[currentStickMan] * gfSpeed;

	if (rArm[currentStickMan] < 30)
	{
		giRArmDirection[currentStickMan] = 1;
	}
	else if (rArm[currentStickMan] > 70)
	{
		giRArmDirection[currentStickMan] = -1;
	}
	rArm[currentStickMan] = rArm[currentStickMan] + giRArmDirection[currentStickMan] * gfSpeed;

}

void update()
{
	int i = 0;
	gfTranslateX += gfSpeed / 15;

	for (i = 0; i < 4; i++)
	{
		updateNormalWalk(i);
	}
}

void DrawCircle(float radius)
{
	float angle;
	glLineWidth(2);
	glBegin(GL_POLYGON);
	for (angle = 0.0f; angle < 2 * 3.145; angle = angle + 0.001f)
		glVertex3f(radius*cos(angle), radius*sin(angle), 0.0f);
	glEnd();
}

void DrawSquare(float vertice1[3], float vertice2[3], float vertice3[3], float vertice4[3], float color[3])
{
	glBegin(GL_QUADS);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(vertice1[0], vertice1[1], vertice1[2]);
	glVertex3f(vertice2[0], vertice2[1], vertice2[2]);
	glVertex3f(vertice3[0], vertice3[1], vertice3[2]);
	glVertex3f(vertice4[0], vertice4[1], vertice4[2]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(color[0] + 0.1f, color[1] + 0.1f, color[2] + 0.1f);
	glVertex3f(vertice1[0], vertice1[1], vertice1[2]);
	glVertex3f(vertice2[0], vertice2[1], vertice2[2]);
	glVertex3f(vertice3[0], vertice3[1], vertice3[2]);
	glVertex3f(vertice4[0], vertice4[1], vertice4[2]);
	glEnd();

}

void DrawCubiod(float points[10][3], float color[3])
{
	DrawSquare(points[0], points[1], points[2], points[3], color);//top
	DrawSquare(points[4], points[5], points[6], points[7], color);//bottom
	DrawSquare(points[1], points[5], points[6], points[2], color);//left
	DrawSquare(points[0], points[4], points[7], points[3], color);//right
	DrawSquare(points[0], points[1], points[5], points[4], color);//front
	DrawSquare(points[3], points[2], points[6], points[7], color);//rear
}

void DrawFace(int currentStickMan)
{

	float height = -gfFaceHeight;
	float topX = gfFaceWidth;
	float topZ = gfFaceWidth;
	float bottomX = gfFaceWidth;
	float color[3] = { 255.0f, 255.0f, 0.0f };

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

	if (currentStickMan == 0)
	{
		DrawFaceDesign_LucaBracy(topX, topZ);
	}
}

void DrawNeck()
{
	float height = -gfNeckHeight;
	float topX = gfNeckWidth;
	float topZ = gfNeckWidth;
	float bottomX = gfNeckWidth;
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
}

void DrawCylinder(float height, float radius)
{
	quadric = gluNewQuadric();
	glColor3f(255.0f, 255.0f, 0.0f);
	gluCylinder(quadric, radius, radius, height, 30, 30);

	glColor3f(255.0f, 255.0f, 0.0f);
	DrawCircle(radius);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, height);

	glColor3f(255.0f, 255.0f, 0.0f);
	DrawCircle(radius);
	glPopMatrix();
}

void DrawJoints(float height, float radius)
{
	quadric = gluNewQuadric();
	glColor3f(255.0f, 255.0f, 0.0f);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, height);

	quadric = gluNewQuadric();
	glColor3f(255.0f, 255.0f, 0.0f);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, -height);
}

void DrawWrist(float height, float radius)
{
	quadric = gluNewQuadric();
	glColor3f(0.1f, 0.1f, 0.1f);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, height);

	quadric = gluNewQuadric();
	glColor3f(1.0f, 0.5f, 0.25f);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, -height);
}

void DrawBiceps(float height, float radius)
{
	DrawCylinder(height, radius);
	DrawJoints(height, radius);
}

void DrawForeArm(float height, float radius)
{
	DrawCylinder(height, radius);
	DrawWrist(height, radius);
}

void DrawHead(int currentStickMan)
{
	DrawFace(currentStickMan);
	DrawNeck();

	//switch (currentStickMan)
	//{
	//case 0://Vito Corleone - Bow and red flower
	//	DrawFace(currentStickMan);
	//	DrawNeck();
	//	break;
	//case 1://Michael Corleone - Tie and Hat
	//	DrawFace();
	//	DrawNeck();
	//	break;
	//case 2://Sonny Corleone - Bow
	//	DrawFace();
	//	DrawNeck();
	//	break;
	//case 3://Lucca Brassi - Tie and Cigar
	//	DrawFace();
	//	DrawNeck();
	//	break;
	//}
}


void DrawChest(int currentStickMan)
{

	float chestBottomHeight = 0.3f;
	float height = -(gfChestHeight - chestBottomHeight);
	float topX = gfChestUpperWidth;
	float topZ = gfChestWidth;
	float bottomX = gfChestLowerWidth;
	float color[3] = { 255.0f, 255.0f, 0.0f };

	if (currentStickMan == 0)
	{
		DrawChestDesign_LucaBracy(topX, topZ);
	}

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
}

void DrawHand(int direction, int currentStickMan)
{
	float armAngle = direction == 1 ? lArm[currentStickMan] : rArm[currentStickMan];

	glPushMatrix();
	glRotatef(armAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(direction * 25, 0.0f, 1.0f, 0.0f);
	DrawBiceps(gfArmHeight, gfArmWidth);
	glTranslatef(0.0f, 0.0f, gfArmHeight);
	glRotatef(armAngle, 1.0f, 0.0f, 0.0f);
	DrawForeArm(gfArmHeight, gfArmWidth);
	glPopMatrix();
}

void DrawThigh()
{
	float height = -gfLegHeight;
	float topX = gfLegWidth;
	float topZ = gfLegWidth;
	float bottomX = gfLegWidth;
	float color[3] = { 0.0f, 0.0f, 0.0f };

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
}

void DrawFoot()
{
	float height = -gfFootHeight;
	float topX = gfFootWidth;
	float topZ = gfFootLength;
	float bottomX = gfFootWidth;
	float color[3] = { 205.0f, 205.0f, 0.0f };

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
}

void DrawLeg(int direction, int currentStickMan)
{
	float legAngle = direction == 1 ? lLeg[currentStickMan] : rLeg[currentStickMan];

	glRotatef(legAngle, 1.0f, 0.0f, 0.0f);

	glPushMatrix();
	glRotatef(direction * 90, 0.0f, 1.0f, 0.0f);
	DrawCylinder(gfLegCylHeight, gfLegCylRadius);//1,1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(direction* gfLegCylHeight / 2, -gfLegCylRadius + 0.25f, 0.0f);
	DrawThigh();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(direction * gfLegCylHeight / 2, -(gfLegCylRadius + gfLegHeight) + 0.25f, -(gfFootLength - gfLegWidth));
	DrawFoot();
	glPopMatrix();
}

void DrawLegSeparation()
{
	glPushMatrix();
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	DrawCylinder(0.4f, gfLegCylRadius);
	glPopMatrix();
}

void debug()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0, 0);
	glVertex3f(-15.0f, 0.0f, 0.0f);
	glVertex3f(15.0f, 0.0f, 0.0f);

	glVertex3f(0.0f, -15.0f, 0.0f);
	glVertex3f(0.0f, 15.0f, 0.0f);

	glVertex3f(-15.0f, -1.0f, 0.0f);
	glVertex3f(15.0f, -1.0f, 0.0f);

	glVertex3f(-15.0f, -1.5, 0.0f);
	glVertex3f(15.0f, -1.5, 0.0f);

	glEnd();
}

// Draw sphere
void DrawSphere_LucaBracy(GLfloat radius, GLint slices, GLint stacks)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
	GLUquadric *quadric = NULL;
	quadric = gluNewQuadric();
	gluSphere(quadric, radius, slices, stacks);
}

// Render all lego character
void LegoCharacter_Render()
{
	float translateX = gfTranslateX;

	for (i = 0; i < 1; i++)
	{
		glPushMatrix();
		glTranslatef(translateX, 0.0f, -18.0f);

		glRotatef(180, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		DrawHead(i);
		glPopMatrix();

		glTranslatef(0.0f, -gfNeckHeight, 0.0f);
		DrawChest(i);

		glPushMatrix();
		glTranslatef(gfChestUpperWidth, -0.25f, 0.0f);
		DrawHand(1, i);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-gfChestUpperWidth, -0.25f, 0.0f);
		DrawHand(-1, i);
		glPopMatrix();

		glTranslatef(0.0f, -gfChestHeight, 0.0f);

		glPushMatrix();
		glTranslatef(0.2f, 0.0f, 0.0f);
		DrawLeg(1, i);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.2f, 0.0f, 0.0f);
		DrawLegSeparation();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.2f, 0.0f, 0.0f);
		DrawLeg(-1, i);
		glPopMatrix();

		glPopMatrix();
		translateX += 4.0f;
	}
}

void DrawChestDesign_LucaBracy(GLfloat topX, GLfloat topZ)
{
	topX = topX / 2;
	topZ = -topZ - 2.0f;

	// zig-zag line of left side
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX + 0.2f, 0, topZ);
	glVertex3f(topX + 0.4f, -0.3f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX + 0.4f, -0.3f, topZ);
	glVertex3f(topX + 0.1f, -0.3f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX + 0.1f, -0.3f, topZ);
	glVertex3f(topX + 0.4f, -0.5f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX + 0.4f, -0.5f, topZ);
	glVertex3f(topX + 0.2f, -1.3f, topZ);
	glEnd();

	// zig-zag line of right side
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 1.2f, 0, topZ);
	glVertex3f(topX - 1.4f, -0.3f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 1.4f, -0.3f, topZ);
	glVertex3f(topX - 1.1f, -0.3f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 1.1f, -0.3f, topZ);
	glVertex3f(topX - 1.4f, -0.5f, topZ);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(topX - 1.4f, -0.5f, topZ);
	glVertex3f(topX - 1.2f, -1.3f, topZ);
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
	glVertex3f(topX - 0.45f, -1.4f, topZ);
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
			glVertex3f((cos(angle)*radius) - 0.1f, (sin(angle)*radius) - buttonY, (topZ));
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

	GLfloat curvyRadius = 1.5f;
	// left side curvy lines
	DrawArcUsingGL_POINTS_LucaBracy(topX + 1.3f, -0.7f, (topZ), curvyRadius, 2.65f, 3.55f, 2.0f);
	// right side curvy lines
	DrawArcUsingGL_POINTS_LucaBracy(topX - 2.3f, -0.7f, (topZ), curvyRadius, 0.0f, 0.50f, 2.0f);
	DrawArcUsingGL_POINTS_LucaBracy(topX - 2.3f, -0.7f, (topZ), curvyRadius, 5.875f, 6.28f, 2.0f);
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
	topZ = (-topZ - 2.0f);

	// eye brows
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawArcUsingGL_POINTS_LucaBracy(topX - 0.2f, -0.8f, topZ, lb_eyebrowRadius, lb_eyebrowStartAngle, lb_eyebrowEndAngle, lb_eyebrowThickness);
	DrawArcUsingGL_POINTS_LucaBracy(topX - 0.7f, -0.8f, topZ, lb_eyebrowRadius, lb_eyebrowStartAngle, lb_eyebrowEndAngle, lb_eyebrowThickness);

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
	glTranslatef((topX - 0.2f), -0.5f, topZ);		// translation for left eye
	glColor3f(0.0f, 0.0f, 0.0f);	// black color
	DrawSphere_LucaBracy(0.1f, 10, 10);		// draw sphere

		// LEFT PUPIL
		glPushMatrix();
		glTranslatef(-0.05f, 0.13f, topZ);		// translation for pupil
		glColor3f(1.0f, 1.0f, 1.0f);	// black color
		DrawSphere_LucaBracy(0.03f, 10, 10);		// draw sphere
		glPopMatrix();
	glPopMatrix();		// pop matrix for left eye

	// RIGHT EYE
	glPushMatrix();		// push matrix for right eye
	glTranslatef((topX - 0.7f), -0.5f, topZ);		// translation for right eye
	glColor3f(0.0f, 0.0f, 0.0f);	// black color
	DrawSphere_LucaBracy(0.1f, 10, 10);		// draw sphere

		// RIGHT PUPIL
		glPushMatrix();
		glTranslatef(0.05f, 0.13f, topZ);		// translation for pupil
		glColor3f(1.0f, 1.0f, 1.0f);	// black color
		DrawSphere_LucaBracy(0.03f, 10, 10);		// draw sphere
		glPopMatrix();
	glPopMatrix();		// pop matrix for right eye

	// Mustache
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(2.0f);
	DrawArcUsingGL_POINTS_LucaBracy(topX - 0.45f, -1.7f, topZ, lb_mustacheRadius, lb_mustacheStartAngle, lb_mustacheEndAngle, lb_mustacheThickness);

	// Lips
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(topX - 0.35f, -1.05f, topZ);
	glVertex3f(topX - 0.5f, -1.05f, topZ);
	glEnd();

	// HAT
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(topX - 0.39f, 0.1f, topZ);
	glRotatef(85.0f, 1.0f, 0.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.0f, 1.3f, 30, 30);

	glTranslatef(0.0f, 0.0f, -0.6f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5f, 0.8f, 0.6f, 30, 30);
	glPopMatrix();
}