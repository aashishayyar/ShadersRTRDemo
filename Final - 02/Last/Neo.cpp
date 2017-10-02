#include "Main.h"
#include "Neo.h"

void moveNeo(void)
{
	if (objectsIteration == 9) 
	{
		gfTranslateNeoX = -19.0f;
		gfTranslateNeoZ =  19.0f;
	}

	if (objectsIteration >= 6)
	{
		if (NeoStage1)
		{
			if ((gfTranslateNeoX >= -50.0f) && (gfNeoRotate_Y < 300.0f))
			{
				gfTranslateNeoX -= 0.7f * gfNeoSpeed / 60;
				updateNormalWalk();
			}
			else
			{
				NeoStage1 = false;
				NeoStage2 = true;
			}
		}
		else if (NeoStage2)
		{
			if (gfNeoRotate_Y <= 300.0f)
			{
				gfNeoRotate_Y += 40 * gfNeoSpeed / 30;
				updateNormalWalk();
			}
			else
			{
				NeoStage2 = false;
				NeoStage3 = true;
			}

		}
		else if (NeoStage3)
		{
			gfTranslateNeoX += 0.4f * gfNeoSpeed / 30;
			gfTranslateNeoZ += 0.6f * gfNeoSpeed / 30;
			updateNormalWalk();
			if (objectsIteration == 9)
			{
				NeoStage3 = false;
				NeoStage5 = true;
			}
		}

/*		else if (NeoStage4)
		{
			NeoStage5 = true;
			if (gfNeoRotate_Y >= 270.0f)
			{
				
				gfNeoRotate_Y -= 40 * gfNeoSpeed / 30;
				updateNormalWalk();
			}
			else 
			{
				NeoStage4 = false;
				NeoStage5 = true;
			}
		}
*/		else if(objectsIteration == 9 || objectsIteration == 10)
		{
			if (cameraPosition.z >= 27.0f)
			{
				if (gfTranslateNeoZ <= 50.0f)
				{
					gfNeoSpeed = 4.0f;
					gfTranslateNeoX -= 1.5f * gfNeoSpeed / 30;
					gfTranslateNeoZ += 15.0f / 30;
					updateNormalWalk();
					if (gfNeoRotate_Y >= 270.0f)
						gfNeoRotate_Y -= 1.0f;
				}

				else
				{
					NeoStage5 = false;
					NeoStage6 = true;
				}
			}
		}
		else if(NeoStage6)
		{
			if (gfNeoRotate_Y >= 180.0f)
			{
				gfNeoRotate_Y -= 40 * gfNeoSpeed / 30;
				updateNormalWalk();
			}
			else 
			{
				NeoStage6 = false;
			}
		}
		else 
		{
			if (objectsIteration == 12) {
				Scene2 = true;
				sceneIndex = 2;
			}
		}
	}
}

void DrawNeo(void)
{
	if (objectsIteration >= 5  || Scene2)
	{	
		glPushMatrix();
		glTranslatef(INITIAL_NEO_TRANSLATE_X + gfTranslateNeoX, INITIAL_NEO_TRANSLATE_Y + gfTranslateNeoY, INITIAL_NEO_TRANSLATE_Z + gfTranslateNeoZ);
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

void updateNeoHandUp()
{
	if (rNeck < 60)
		rNeck += gfNeoSpeed;
}

void updateNeoHandDown()
{
	if (rNeck > 20)
		rNeck -= gfNeoSpeed;
}

void dodgeBullet()
{
	int i = 0;

	if (body < 80 && giNeoDirection == 1 ) //&& gfBulletTranslateX <= 58.0f)
	{
		gfNeoSpeed = 1.6f;
		gfNeoTheta += gfNeoSpeed / 4;
	}
	else
	{
		if(gfNeoTheta >= 18.0f)
			gfNeoSpeed = 0.3f;
		else 
			gfNeoSpeed = 1.0f;
		giNeoDirection = -1;
		gfNeoTheta -= gfNeoSpeed / 4;
	}
	if (body < 0 && giNeoDirection == -1)
	{
		;
	}
	else
	{
		gfTranslateNeoX = -(2 * (1.25f + 0.75f)*(GLfloat)sin(3.14f*body / 180)) + 2 * 0.75f* (GLfloat)sin(3.14f * gfNeoTheta / 180) + 2 * 0.75f* (GLfloat)sin(3.14f * gfNeoTheta / 180); //- 35.0f;
		gfTranslateNeoX = -gfTranslateNeoX - 34.0f;
		gfTranslateNeoY = -(2 * (1.25f + 0.75f) - 2 * (1.25f + 0.75f)*(GLfloat)cos(3.14f*body / 180) - (2 * (0.75f) - 2 * 0.75f*(GLfloat)cos(gfNeoTheta * 3.14f / 180)) - (2 * (0.75f) - 2 * 0.75f*(GLfloat)cos(gfNeoTheta * 3.14f / 180)));

		body = body + giNeoDirection * gfNeoSpeed;
		lHip = 10 + body - gfNeoTheta;
		rHip = -10 + body - gfNeoTheta;
		lKnee = -body - gfNeoTheta;
		rKnee = -body - gfNeoTheta;
		lAnkle = lAnkle + giNeoDirection *gfNeoSpeed / 2;
		rAnkle = rAnkle + giNeoDirection *gfNeoSpeed / 2;
		lNeck = lNeck + giNeoDirection *1.7f*gfNeoSpeed;
		rNeck = rNeck - giNeoDirection *gfNeoSpeed / 5;
	}
}

void DrawCylinder(GLfloat height)
{
	quadric = gluNewQuadric();
	glColor3f(NEO_COLOR_RED, NEO_COLOR_GREEN, NEO_COLOR_BLUE);
	gluCylinder(quadric, 0.2f*gbStickWidth, 0.2f*gbStickWidth, 2 * height, 30, 30);
}

void DrawJoints(GLfloat height)
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

void DrawCylinderAndJoints(GLfloat height)
{
	void DrawCylinder(GLfloat);
	void DrawJoints(GLfloat);

	DrawCylinder(height);
	DrawJoints(height);
}

void DrawNeoSector(GLfloat aRadius, GLfloat bRadius, GLfloat z, GLfloat color[3], GLfloat minAngle, GLfloat maxAngle)
{
	GLfloat angle;
	glLineWidth(2);
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, z);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*(GLfloat)cos(angle), bRadius*(GLfloat)sin(angle), z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*(GLfloat)cos(angle), bRadius*(GLfloat)sin(angle), z);
	glEnd();

}

void DrawNeoSectorLine(GLfloat aRadius, GLfloat bRadius, GLfloat z, GLfloat color[3], GLfloat minAngle, GLfloat maxAngle)
{
	GLfloat angle;
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glColor3f(color[0], color[1], color[2]);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*(GLfloat)cos(angle), bRadius*(GLfloat)sin(angle), z);
	glEnd();
}

void DrawNeoGoggles(GLfloat radius)
{

	GLfloat color[3] = { (GLfloat)0.9, (GLfloat)0.9, (GLfloat)0.9 };
	GLfloat lensRadius = (radius - radius / 15 - 2 * radius / 6) / 2;
	GLfloat middleCurveRadius = radius / 15;
	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	DrawNeoSectorLine(middleCurveRadius, middleCurveRadius / 4, 0.0f, color, 3.145f, 2 * 3.145f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-(lensRadius + middleCurveRadius), 0.0f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	DrawNeoSector(lensRadius, lensRadius / 1.5f, 0.0f, color, 0, 3.145f);
	DrawNeoSector(lensRadius, lensRadius / 3.0f, 0.0f, color, 3.145f, 2 * 3.145f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(lensRadius + middleCurveRadius, 0.0f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	DrawNeoSector(lensRadius, lensRadius / 1.5f, 0.0f, color, 0, 3.145f);
	DrawNeoSector(lensRadius, lensRadius / 3.0f, 0.0f, color, 3.145f, 2 * 3.145f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-(2 * lensRadius + middleCurveRadius), 0.0f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glRotatef(-20, 0.0f, 1.0f, 0.0f);
	quadric = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 1.0f);
	gluCylinder(quadric, 0.03f, 0.03f, radius, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2 * lensRadius + middleCurveRadius, 0.0f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glRotatef(20, 0.0f, 1.0f, 0.0f);
	quadric = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 1.0f);
	gluCylinder(quadric, 0.03f, 0.03f, radius, 30, 30);
	glPopMatrix();

}

void DrawHead(GLfloat radius)
{
	GLdouble equation[4] = { 0.0f, 0.0f, 1.0f, 0.25f };


	//Sonny Corleone - Bow
	gbStickWidth = 0.9f;
	gbStickHeight = 0.75f;
	//glRotatef(-80, 0.0f, 0.0f, 1.0f);

	quadric = gluNewQuadric();
	glColor3f(NEO_COLOR_RED, NEO_COLOR_GREEN, NEO_COLOR_BLUE);
	gluSphere(quadric, radius, 30, 30);

	glRotatef(90, 0.0f, 0.0f, 1.0f);
	glRotatef(body, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -radius, 0.0f);
	DrawNeoGoggles(radius);
}

void DrawStickMan()
{
	GLfloat length = gbStickHeight;

	glPushMatrix();
	glTranslatef(-length*(GLfloat)sin(body*3.145/180), 0.0f, -length*(GLfloat)cos(body*3.145 / 180));
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

	glTranslatef(2 * (length + 0.5f)*(GLfloat)sin(body / 180.0f*3.145), 0.0f, 2 * (length + 0.5f)*(GLfloat)cos(body / 180.0f*3.145));

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

