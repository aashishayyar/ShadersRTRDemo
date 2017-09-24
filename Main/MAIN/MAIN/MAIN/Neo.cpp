#include "Main.h"
#include "Neo.h"

void moveNeo(void)
{
	if (objectsIteration >= 5)
	{
		if ((gfTranslateNeoX >= -30.0f) && (gfNeoRotate_Y < 300.0f))
		{
			gfTranslateNeoX -= gfNeoSpeed / 30;
		}
		else if (gfNeoRotate_Y <= 300.0f)
			gfNeoRotate_Y += 20 * gfNeoSpeed / 30;
		else if (gfTranslateNeoX <= INITIAL_NEO_TRANSLATE_X)
		{
			gfTranslateNeoX += gfNeoSpeed / 30;
			gfTranslateNeoZ +=2* gfNeoSpeed / 30;
		}
	}
	
//	gfTranslateNeoX = 18.0f;
//	gfTranslateNeoZ = -10.0f;
	updateNormalWalk();
}

void DrawNeo(void)
{
	if (objectsIteration >= 5)
	{
		//fprintf(fp, "HERE\n");
		glPushMatrix();
		glTranslatef(INITIAL_NEO_TRANSLATE_X + gfTranslateNeoX, INITIAL_NEO_TRANSLATE_Y, INITIAL_NEO_TRANSLATE_Z + gfTranslateNeoZ);
		//	glTranslatef(gfTranslateNeoX, INITIAL_NEO_TRANSLATE_Y, gfTranslateNeoZ);
		glRotatef(gfNeoRotate_Y, 0.0f, 1.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		DrawStickMan();
		glPopMatrix();

	}
}

void updateNormalWalk()
{

	if (gbIsLeftArm)
	{
		lNeck -= gfNeoSpeed;
		rNeck += gfNeoSpeed;
		if (rNeck > 10)
		{
			gbIsLeftArm = false;
		}
	}
	else
	{
		lNeck += gfNeoSpeed;
		rNeck -= gfNeoSpeed;
		if (lNeck > 10)
		{
			gbIsLeftArm = true;
		}
	}

	if (gbOneLeg == 1)
	{
		if (gbIsLeftLeg)
		{
			lKnee = lKnee + 4 * gfNeoSpeed;
			if (lKnee > -10.0f)
			{
				gbOneLeg = false;
			}
		}
		else
		{
			rKnee = rKnee + 4 * gfNeoSpeed;
			if (rKnee > -10.0f)
			{
				gbOneLeg = false;
			}
		}
	}
	else
	{
		if (gbIsLeftLeg)
		{
			lHip -= gfNeoSpeed;

			rHip += gfNeoSpeed;
			rKnee = rKnee - 2 * gfNeoSpeed;

			if (rHip > 20.0f)
			{
				gbOneLeg = true;
				gbIsLeftLeg = false;
			}
		}
		else
		{
			rHip -= gfNeoSpeed;

			lHip += gfNeoSpeed;
			lKnee = lKnee - 2 * gfNeoSpeed;

			if (lHip > 20.0f)
			{
				gbOneLeg = true;
				gbIsLeftLeg = true;
			}

		}
	}
}

void DrawCylinder(float height)
{
	quadric = gluNewQuadric();
	glColor3f(NEO_COLOR_RED, NEO_COLOR_GREEN, NEO_COLOR_BLUE);
	gluCylinder(quadric, 0.2f*gbStickWidth, 0.2f*gbStickWidth, 2 * height, 30, 30);
}

void DrawJoints(float height)
{
	quadric = gluNewQuadric();
	glColor3f(NEO_COLOR_RED, NEO_COLOR_GREEN, NEO_COLOR_BLUE);
	gluSphere(quadric, 0.2f*gbStickWidth, 30, 30);

	glTranslatef(0.0f, 0.0f, 2 * height);

	quadric = gluNewQuadric();
	glColor3f(NEO_COLOR_RED, NEO_COLOR_GREEN, NEO_COLOR_BLUE);
	gluSphere(quadric, 0.2f*gbStickWidth, 30, 30);

	glTranslatef(0.0f, 0.0f, -2 * height);
}

void DrawCylinderAndJoints(float height)
{
	void DrawCylinder(float);
	void DrawJoints(float);

	DrawCylinder(height);
	DrawJoints(height);
}

void DrawHead(float radius)
{
	GLdouble equation[4] = { 0.0f, 0.0f, 1.0f, 0.25f };


	//Sonny Corleone - Bow
	gbStickWidth = 0.7f;
	gbStickHeight = 0.72f;

	quadric = gluNewQuadric();
	glColor3f(NEO_COLOR_RED, NEO_COLOR_GREEN, NEO_COLOR_BLUE);
	gluSphere(quadric, radius, 30, 30);


}

void DrawStickMan()
{
	float length = gbStickHeight;

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -length);
	DrawHead(length);
	glPopMatrix();

	glPushMatrix();
	//Draw Left Neck to Elbow part
	glRotatef((GLfloat)lNeck, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length);
	glPopMatrix();

	//Draw Left Elbow
	glTranslatef(0.0f, 0.0f, length * 2);
	glRotatef((GLfloat)lElbow, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	//Draw Right Neck to Elbow part
	glRotatef((GLfloat)rNeck, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length);
	glPopMatrix();

	//Draw Right Elbow
	glTranslatef(0.0f, 0.0f, length * 2);
	glRotatef((GLfloat)rElbow, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glRotatef((GLfloat)body, 0.0f, 1.0f, 0.0f);
	DrawCylinderAndJoints(length + 0.5f);
	glPopMatrix();

	glTranslatef(2 * (length + 0.5f)*sin(body / 180.0f*3.145), 0.0f, 2 * (length + 0.5f)*cos(body / 180.0f*3.145));

	glPushMatrix();

	glPushMatrix();

	//Draw Right Leg to Knee part
	glRotatef((GLfloat)rHip, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length);
	glPopMatrix();

	//Draw Right Knee
	glTranslatef(0.0f, 0.0f, length * 2);
	glRotatef((GLfloat)rKnee, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length);
	glPopMatrix();

	//Draw Right Ankle
	glTranslatef(0.0f, 0.0f, length * 2);
	glRotatef((GLfloat)rAnkle, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length / 4);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();

	//Draw Left Leg to Knee part
	glRotatef((GLfloat)lHip, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length);
	glPopMatrix();

	//Draw Left Knee
	glTranslatef(0.0f, 0.0f, length * 2);
	glRotatef((GLfloat)lKnee, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length);
	glPopMatrix();

	//Draw Left Ankle
	glTranslatef(0.0f, 0.0f, length * 2);
	glRotatef((GLfloat)lAnkle, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCylinderAndJoints(length / 4);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

