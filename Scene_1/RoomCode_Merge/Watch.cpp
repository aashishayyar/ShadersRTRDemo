#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
//#include "Header_Manishar.h"
#include "ClockHeader.h"
#include <math.h>
//#include"Matrix.h"

#pragma clock 
void drawClock() {
	// function declaration
	void drawClockSquare(void);
	void drawClockTimeNumbers(void);
	void drawClockSecondHand(void);
	void drawClockMinutehand(void);
	void drawClockHourHand(void);
	void drawClockNumbers();

	//Fill this struct for camera movement

	//glPushMatrix(); //1
	//glTranslatef(watchPosition.x, watchPosition.y, watchPosition.z);
	glPushMatrix(); //2
					//	drawClockNumbers();
	glPopMatrix();
	glPushMatrix(); //3
	drawClockSquare();
	drawClockTimeNumbers();
	glPopMatrix();
	glPushMatrix(); //4
	drawClockSecondHand();
	drawClockMinutehand();
	drawClockHourHand();
	glPopMatrix();
	//glPopMatrix();
}

void updateSecondAngle(void) {
	gfSecondAngle = gfSecondAngle - (6.0f * PI / (180.0f));
	gfMinuteAngle = gfMinuteAngle - (6.0f * PI / (180.0f * 60.0f));
	gfHourAngle = gfHourAngle - (6.0f * PI / (180.0f * 60.0f * 12.0f));
}

void drawClockSquare() {

	glBegin(GL_QUADS);
	glColor3f((GLfloat)130.0f / (GLfloat) 255.0f, (GLfloat)82.0f / (GLfloat) 255.0f, (GLfloat)1.0f / (GLfloat) 255.0f);
	glVertex3f(-gfClockOuterLength, gfClockOuterLength, -0.05f);
	glVertex3f(gfClockOuterLength, gfClockOuterLength, -0.05f);
	glVertex3f(gfClockOuterLength, -gfClockOuterLength, -0.05f);
	glVertex3f(-gfClockOuterLength, -gfClockOuterLength, -0.05f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-gfClockLength, gfClockLength, 0.0f);
	glVertex3f(gfClockLength, gfClockLength, 0.0f);
	glVertex3f(gfClockLength, -gfClockLength, 0.0f);
	glVertex3f(-gfClockLength, -gfClockLength, 0.0f);
	glEnd();
	glLineWidth(1.0f);
}

void drawClockTimeNumbers() {
	TCHAR str[255];
	int iNumberCounter = 0;
	void drawNumbers(int);

	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < giCirclePoints; i++) {
		float angle = (GLfloat)(2 * PI * i) / (GLfloat)giCirclePoints;
		if (i % 90 == 0) {
			glLineWidth(3.0f);
			glBegin(GL_LINES);
			glVertex3f(gfClockStepMin * (GLfloat)sin(angle), gfClockStepMin * (GLfloat)cos(angle), 0.0f);
			glVertex3f((gfClockStepMax)* (GLfloat)sin(angle), (gfClockStepMax)* (GLfloat)cos(angle), 0.0f);
			glEnd();
			drawNumbers(iNumberCounter);
			iNumberCounter++;
		}
		else if (i % 60 == 0) {
			glBegin(GL_LINES);
			glVertex3f((gfClockStepMin + 0.3f)  * (GLfloat)sin(angle), (gfClockStepMin + 0.3f) * (GLfloat)cos(angle), 0.0f);
			glVertex3f((gfClockStepMax + 0.3f)* (GLfloat)sin(angle), (gfClockStepMax + 0.3f)* (GLfloat)cos(angle), 0.0f);
			glEnd();
			drawNumbers(iNumberCounter);
			iNumberCounter++;
		}
		else if (i % 30 == 0) {
			glBegin(GL_LINES);
			glVertex3f((gfClockStepMin + 0.3f)  * (GLfloat)sin(angle), (gfClockStepMin + 0.3f) * (GLfloat)cos(angle), 0.0f);
			glVertex3f((gfClockStepMax + 0.3f)* (GLfloat)sin(angle), (gfClockStepMax + 0.3f)* (GLfloat)cos(angle), 0.0f);
			glEnd();
			drawNumbers(iNumberCounter);
			iNumberCounter++;

		}

	}
	glEnd();
}

void drawClockSecondHand(void) {

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gfClockSecondHandRadious * (GLfloat)cos(gfSecondAngle), gfClockSecondHandRadious * (GLfloat)sin(gfSecondAngle), 0.0f);
	glEnd();
}

void drawClockMinutehand(void) {
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gfClockMinuteHandRadious * (GLfloat)cos(gfMinuteAngle), gfClockMinuteHandRadious * (GLfloat)sin(gfMinuteAngle), 0.0f);
	glEnd();
}

void drawClockHourHand(void) {
	glLineWidth(4.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gfClockHourHandRadious  * (GLfloat)cos(gfHourAngle), gfClockHourHandRadious  * (GLfloat)sin(gfHourAngle), 0.0f);
	glEnd();
}

void drawClockNumbers() {
	int counter = 0;
	void drawNumbers(int);
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < giCirclePoints; i++) {
		float angle = 2 * PI * i / giCirclePoints;
		if (i % 30 == 0) {
			glPushMatrix();
			glTranslatef((gfClockStepMin)  * (GLfloat)sin(angle), (gfClockStepMin) * (GLfloat)cos(angle), 1.0f);
			drawNumbers(counter);
			glPopMatrix();
			counter++;
		}
	}
	glPopMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);

}

void drawNumbers(int iClockNumberKeys) {

	switch (iClockNumberKeys)
	{
	case 0:

		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberTwelveDistanceFromOriginX, -gfNumberOneLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 1:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberOneDistanceFromOriginX, 0.0f + gfNumberOneDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberOneDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberOneDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberOneDistanceFromOriginX, 0.0f + gfNumberOneDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberOneDistanceFromOriginX, -gfNumberOneLengthY + gfNumberOneDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 2:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, 0.0f + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, 0.0f + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, 0.0f + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glEnd();

		break;
	case 3:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberThreeDistanceFromOriginX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, 0.0f, 0.0f);

		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f + gfNumberThreeDistanceFromOriginX, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMaxLengthY, 0.0f);
		glEnd();
		break;
	case 4:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberFourDistanceFromOriginX, 0.0f + gfNumberFourDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberFourDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFourDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberFourDistanceFromOriginX, 0.0f + gfNumberFourDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFourDistanceFromOriginX, -0.2f + gfNumberFourDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberFourDistanceFromOriginX, -0.2f + gfNumberFourDistanceFromOriginY, 0.0f);
		glVertex3f(0.1f + gfNumberFourDistanceFromOriginX, -0.2f + gfNumberFourDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 5:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, 0.0f + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, 0.0f + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, 0.0f + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 6:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, 0.0f + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, 0.0f + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, 0.0f + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 7:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberSevenDistanceFromOriginX, 0.0f + gfNumberSevenDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberSevenDistanceFromOriginX, 0.0f + gfNumberSevenDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberSevenDistanceFromOriginX, 0.0f + gfNumberSevenDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberSevenLengthX + gfNumberSevenDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSevenDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 8:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glEnd();
		//glPopMatrix();
		break;
	case 9:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glEnd();
		break;
	case 10:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX, 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX, 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberTenDistanceFromOriginX, -gfNumberOneLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glEnd();

		break;
	case 11:
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberElevenDistanceFromOriginX, -gfNumberOneLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, -gfNumberMaxLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, -gfNumberOneLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glEnd();

		glPopMatrix();

		break;
	default:
		break;
	}
}