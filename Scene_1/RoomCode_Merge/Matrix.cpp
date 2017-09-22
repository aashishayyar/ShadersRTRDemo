#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
//#include "Header_Manishar.h"
//#include "ClockHeader.h"
#include <math.h>
#include"Matrix.h"


#pragma Matrix Room

void drawMatrixDoor() {
	glPushMatrix();
	GLfloat widthOfDoor = 10.0f;
	glTranslatef(0.0f, 0.0f, 0.0f);
	giTempNumberOfCharacterOnX = giNumberOfCharOnX;
	giTempNumberOfCharacterOnY = giNumberOfCharOnY;

	giNumberOfCharOnY = giNumberOfCharOnX = widthOfDoor * 3;
	
	DrawWall();
	giNumberOfCharOnX = giTempNumberOfCharacterOnX;
	giNumberOfCharOnY = giTempNumberOfCharacterOnY;

	glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(0.0f, widthOfDoor, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(widthOfDoor, 0.0f, 0.0f);
			glVertex3f(widthOfDoor, widthOfDoor, 0.0f);
		glEnd();

	glPopMatrix();
}

void drawMatrixRoom() {
	//glPushMatrix();
	//glTranslatef(matrixRoomPosition.x, matrixRoomPosition.y, matrixRoomPosition.z);

	//BACK
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -gfWidthOfRoom);
	giTempNumberOfCharacterOnX = giNumberOfCharOnX;
	giNumberOfCharOnX = giNumberOfCharOnX + 34;
	DrawWall();
	giNumberOfCharOnX = giTempNumberOfCharacterOnX;
	glPopMatrix();

	//TOP
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -(gfHeightOfRoom));
	giTempNumberOfCharacterOnY = giNumberOfCharOnY;
	giNumberOfCharOnY = giNumberOfCharOnY + 1;
	DrawWall();
	giNumberOfCharOnY = giTempNumberOfCharacterOnY;
	glPopMatrix();

	//LEFT
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left 
	DrawWall();
	glPopMatrix();

	//RIGHT
	glPushMatrix();
	glTranslatef(gfHeightOfRoom, 0.0f, 0.0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left 
	DrawWall();
	glPopMatrix();

	//BOTTOM

	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	DrawWall();
	glPopMatrix();
	//glPopMatrix();
}

void StoreWall() {
	DWORD dwTotalNumberOfCharacters = 0;
	int RandomNumber = 0;
	dwTotalNumberOfCharacters = (giNumberOfCharOnX*giNumberOfCharOnY);
	if (piRandomWallNumbers == NULL) {
		piRandomWallNumbers = (int *)malloc(sizeof(int)*(dwTotalNumberOfCharacters));
		if (piRandomWallNumbers == NULL)
		{
			//ERROR HANDLING
		}
		else
		{
			dwMaximumCharaFromWall = dwTotalNumberOfCharacters;
		}
	}
	if (dwMaximumCharaFromWall < dwTotalNumberOfCharacters) {
		piRandomWallNumbers = (int *)realloc(piRandomWallNumbers, (sizeof(int)*(dwTotalNumberOfCharacters - dwMaximumCharaFromWall)));
		if (piRandomWallNumbers == NULL)
		{
			//ERROR HANDLING
		}
		else {
			for (DWORD i = dwMaximumCharaFromWall; i < dwTotalNumberOfCharacters; i++)
			{
				RandomNumber = rand() % 27;
				piRandomWallNumbers[i] = RandomNumber;
			}
			dwMaximumCharaFromWall = dwTotalNumberOfCharacters;
		}
	}
	if ((gbWallFilled == FALSE)) {
		for (DWORD i = 0; i < dwTotalNumberOfCharacters; i++) {
			RandomNumber = rand() % 27;
			piRandomWallNumbers[i] = RandomNumber;
		}
		gbWallFilled = TRUE;
	}
	if (gbDisplayedFirstWall == FALSE) {
		gbDisplayedFirstWall = TRUE;
		dwDisplayedFirstWall = GetTickCount();
		dwSavedTickCount = dwDisplayedFirstWall;
	}
	dwGetTickCount = GetTickCount();
	if ((dwGetTickCount - dwSavedTickCount) >= gdwSpeedOfWallChange)
	{
		dwSavedTickCount = dwGetTickCount;
		gbWallFilled = FALSE;
	}
}

void RandomCharacter(int RandomNumber) {
	for (int i = 0; i < 7; i++)
	{
		giSevenSgment[i] = 0;
	}
	switch (RandomNumber)
	{
	case 0x0:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x1:
		giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x2:
		giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 0x3:
		giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = giSevenSgment[4] = giSevenSgment[3] = 1;
		break;
	case 0x4:
		giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[4] = 1;
		break;
	case 0x5:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[4] = giSevenSgment[3] = 1;
		break;
	case 0x6:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[3] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 0x7:
		giSevenSgment[0] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x8:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x9:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 10:	//a
		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 11:	//b
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[6] = 1;
		break;
	case 12:	//c
		giSevenSgment[6] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 13:	//d
		giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 14:	//e
		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[1] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 15:	//f
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[6] = 1;
		break;
	case 16:	//g	Added 3 to differentiate from 9
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[3] = 1;
		break;
	case 17:	//h
		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 18:	//j
		giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 19:	//L 
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 20:	//n
		giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[6] = 1;
		break;
	case 21:	//o
		giSevenSgment[2] = giSevenSgment[6] = giSevenSgment[3] = giSevenSgment[4] = 1;
		break;
	case 22:	//q	
		giSevenSgment[1] = giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[6] = 1;
		break;
	case 23:	//p
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 24:	//s	
		giSevenSgment[1] = giSevenSgment[0] = giSevenSgment[3] = giSevenSgment[6] = giSevenSgment[4] = 1;
		break;
	case 25:	//t
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[6] = 1;
		break;
	case 26:	//y	Add 3 to differentiate from 4
		giSevenSgment[1] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	}
	return;
}

void DrawCharacter() {
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(gfMatrixCharRed, gfMatrixCharGreen, gfMatrixCharBlue);
	/*4th LINE*/
	if (giSevenSgment[4] == 1)
	{
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), gfCurrentY, gfCurrentZ);
	}
	/*3rd LINE*/
	if (giSevenSgment[3] == 1)
	{
		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);
	}
	/*2nd LINE*/
	if (giSevenSgment[2] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);
	}
	/*6th LINE*/
	if (giSevenSgment[6] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY), (gfCurrentZ));
	}
	/*1st LINE*/
	if (giSevenSgment[1] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
		glVertex3f((gfCurrentX + .00f), (gfCurrentY + gfHeightOfLine), (gfCurrentZ + 0.0f));
	}
	/*0th LINE*/
	if (giSevenSgment[0] == 1)
	{
		glVertex3f(gfCurrentX, (gfCurrentY + gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);
	}

	/*5th LINE*/
	if (giSevenSgment[5] == 1)
	{
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), gfCurrentY, gfCurrentZ);
	}
	glEnd();
}

void DrawWall() {
	int iCounter = 0;
	int iRandomCharacterCount = giNumberOfCharOnX *giNumberOfCharOnY;
	StoreWall();
	for (int j = 0; j < giNumberOfCharOnY; j++)
	{
		for (int i = 0; i < giNumberOfCharOnX; i++)
		{
			RandomCharacter(piRandomWallNumbers[iCounter]);
			iCounter++;
			if (iCounter >= iRandomCharacterCount)
			{
				iCounter = 0;
			}
			//HERE WE DRAW ACTUAL CHARACTER 
			DrawCharacter();

			gfCurrentX = gfCurrentX + gfCommonXDistance;
		}
		gfWidthOfRoom = gfCurrentX;
		gfCurrentX = 0.0f;
		gfCurrentY = gfCurrentY + gfCommonYDistance + 0.1f;
	}
	gfHeightOfRoom = gfCurrentY;
	gfCurrentY = 0.0f;
	return;
}