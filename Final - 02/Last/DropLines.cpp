#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"DropLines.h"
//
//void RandomCharacter(int RandomNumber) {
//	for (int i = 0; i < 17; i++) {
//		giSevenSgment[i] = 0;
//	}
//	switch (RandomNumber)
//	{
//	case 0x0:
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
//		break;
//	case 0x1:
//		giSevenSgment[4] = giSevenSgment[5] = 1;
//		break;
//	case 0x2:
//		giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = giSevenSgment[2] = giSevenSgment[3] = 1;
//		break;
//	case 0x3:
//		giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = giSevenSgment[4] = giSevenSgment[3] = 1;
//		break;
//	case 0x4:
//		giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[4] = 1;
//		break;
//	case 0x5:
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[4] = giSevenSgment[3] = 1;
//		break;
//	case 0x6:
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[3] = giSevenSgment[5] = giSevenSgment[6] = 1;
//		break;
//	case 0x7:
//		giSevenSgment[0] = giSevenSgment[4] = giSevenSgment[5] = 1;
//		break;
//	case 0x8:
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
//		break;
//	case 0x9:
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
//		break;
//	case 10:	//a
//		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
//		break;
//	case 11:	//b
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[6] = 1;
//		break;
//	case 12:	//c
//		giSevenSgment[6] = giSevenSgment[2] = giSevenSgment[3] = 1;
//		break;
//	case 13:	//d
//		giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
//		break;
//	case 14:	//e
//		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[1] = giSevenSgment[5] = giSevenSgment[6] = 1;
//		break;
//	case 15:	//f
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[6] = 1;
//		break;
//	case 16:	//g	Added 3 to differentiate from 9
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[3] = 1;
//		break;
//	case 17:	//h
//		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
//		break;
//	case 18:	//j
//		giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
//		break;
//	case 19:	//L 
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = 1;
//		break;
//	case 20:	//n
//		giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[6] = 1;
//		break;
//	case 21:	//o
//		giSevenSgment[2] = giSevenSgment[6] = giSevenSgment[3] = giSevenSgment[4] = 1;
//		break;
//	case 22:	//q	
//		giSevenSgment[1] = giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[6] = 1;
//		break;
//	case 23:	//p
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = 1;
//		break;
//	case 24:	//s	
//		giSevenSgment[1] = giSevenSgment[0] = giSevenSgment[3] = giSevenSgment[6] = giSevenSgment[4] = 1;
//		break;
//	case 25:	//t
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[6] = 1;
//		break;
//	case 26:	//y	Add 3 to differentiate from 4
//		giSevenSgment[1] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
//		break;
//	case 27:	//M
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[9] = giSevenSgment[7] = 1;
//		break;
//	case 28:	//I
//		giSevenSgment[0] = giSevenSgment[11] = giSevenSgment[12] = giSevenSgment[3] = 1;
//		break;
//	case 29:	//Y
//		giSevenSgment[7] = giSevenSgment[9] = giSevenSgment[12] = 1;
//		break;
//	case 30:	//T
//		giSevenSgment[0] = giSevenSgment[11] = giSevenSgment[12] = 1;
//		break;
//	case 31:	//A
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[0] = giSevenSgment[6] = 1;
//		break;
//	case 32:	//L
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = 1;
//		break;
//	case 33:	//C
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = 1;
//		break;
//	case 34:	//H
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
//		break;
//	case 35:	//E
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[6] = 1;
//		break;
//	case 36:	//O
//		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
//		break;
//	case 37:	//N
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[7] = giSevenSgment[8] = 1;
//		break;
//	case 38:	//R
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[0] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[15] = 1;
//		break;
//	case 39:	//V
//		giSevenSgment[13] = giSevenSgment[14] = 1;
//		break;
//	case 40:	//U
//		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
//		break;
//	case 41:
//		giSevenSgment[0] = giSevenSgment[3] = giSevenSgment[16] = giSevenSgment[4] = giSevenSgment[5] = 1;
//		break;
//
//	}
//	return;
//}

//void DrawCharacter() {
//
//	float fCreditsCentreOfTopLineX = ((gfCurrentX)+(gfCurrentX + gfWidthOfLine)) / 2;
//	float fCreditsCentreOfTopLineY = (gfCurrentY + gfHeightOfLine);
//	float fCreditsCentreOfTopLineZ = gfCurrentZ;
//
//	float fCreditsCentreOfMidLineX = (gfCurrentX + (gfCurrentX + gfWidthOfLine)) / 2;
//	float fCreditsCentreOfMidLineY = gfCurrentY;
//	float fCreditsCentreOfMidLineZ = gfCurrentZ;
//
//	float fCreditsCentreOfBotLineX = (gfCurrentX + (gfCurrentX + gfWidthOfLine)) / 2;
//	float fCreditsCentreOfBotLineY = (gfCurrentY - gfHeightOfLine);
//	float fCreditsCentreOfBotLineZ = gfCurrentZ;
//
//	glLineWidth(1.0f);
//	glBegin(GL_LINES);
//	glColor3f(gfMatrixCharRed, gfMatrixCharGreen, gfMatrixCharBlue);
//
//	/*16th Line  i.e. 2nd TOP to 4th BOTTOM  */
//	if (giSevenSgment[16] == 1)
//	{
//		glVertex3f((gfCurrentX + gfDistanceForD), (gfCurrentY + gfHeightOfLine), gfCurrentZ);	//TOP OF 2ndLINE
//		glVertex3f((gfCurrentX + gfDistanceForD), (gfCurrentY - gfHeightOfLine), gfCurrentZ); 	//BOTTOM OF 4th LINE
//	}
//	/*15th Line  i.e. 2nd TOP to 4th BOTTOM  */
//	if (giSevenSgment[15] == 1)
//	{
//		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);	//TOP OF 2ndLINE
//		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ); 	//BOTTOM OF 4th LINE
//	}
//	/*14th Line  i.e. 1st TOP to BOTTOM CENTRE */
//	if (giSevenSgment[14] == 1)
//	{
//		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);	//TOP OF 5th LINE
//		glVertex3f(fCreditsCentreOfBotLineX, fCreditsCentreOfBotLineY, fCreditsCentreOfBotLineZ);					//CENTRE OF BOTTOM LINE
//	}
//
//	/*13th Line  i.e. 1st TOP to BOTTOM CENTRE */
//	if (giSevenSgment[13] == 1)
//	{
//		glVertex3f((gfCurrentX), (gfCurrentY + gfHeightOfLine), (gfCurrentZ));  //TOP OF 1st LINE
//		glVertex3f(fCreditsCentreOfBotLineX, fCreditsCentreOfBotLineY, fCreditsCentreOfBotLineZ);					//CENTRE OF BOTTOM LINE
//	}
//
//	/*12th Line  i.e. MidCentre to BOTTOM CENTRE */
//	if (giSevenSgment[12] == 1)
//	{
//		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					//CENTRE OF MIDDLE LINE
//		glVertex3f(fCreditsCentreOfBotLineX, fCreditsCentreOfBotLineY, fCreditsCentreOfBotLineZ);			//CENTRE OF TOP LINE
//	}
//
//	/*11th Line  i.e. TOP CENTRE to MidCentre */
//	if (giSevenSgment[11] == 1)
//	{
//		glVertex3f(fCreditsCentreOfTopLineX, fCreditsCentreOfTopLineY, fCreditsCentreOfTopLineZ);			//CENTRE OF TOP LINE
//		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					//CENTRE OF MIDDLE LINE
//	}
//
//	/*10th Line  i.e. MidCentre to 2nd Bottom*/
//	if (giSevenSgment[10] == 1)
//	{
//		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);		// Bottom OF 2nd Line
//		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					//CENTRE OF MIDDLE LINE
//	}
//
//	/*9th Line  i.e. 5th Top to MidCentre*/
//	if (giSevenSgment[9] == 1)
//	{
//		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);	//TOP OF 5th LINE
//		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					//CENTRE OF MIDDLE LINE
//	}
//
//	/*8th Line ---> i.e. MidCentre to 4th Bottom*/
//	if (giSevenSgment[8] == 1)
//	{
//		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);  //BOTTOM OF LINE 4
//		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);										//CENTRE OF MIDDLE LINE
//	}
//
//	/*7th Line ---> i.e. 1st Top to MidCentre*/
//	if (giSevenSgment[7] == 1)
//	{
//		glVertex3f((gfCurrentX), (gfCurrentY + gfHeightOfLine), (gfCurrentZ));  //TOP OF 1st LINE	
//		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					  //CENTRE OF MIDDLE LINE
//	}
//
//	/*4th LINE*/
//	if (giSevenSgment[4] == 1)
//	{
//		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);
//		glVertex3f((gfCurrentX + gfWidthOfLine), gfCurrentY, gfCurrentZ);
//	}
//	/*3rd LINE*/
//	if (giSevenSgment[3] == 1)
//	{
//		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);
//		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);
//	}
//	/*2nd LINE*/
//	if (giSevenSgment[2] == 1)
//	{
//		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
//		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);
//	}
//	/*6th LINE*/
//	if (giSevenSgment[6] == 1)
//	{
//		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
//		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY), (gfCurrentZ));
//	}
//	/*1st LINE*/
//	if (giSevenSgment[1] == 1)
//	{
//		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
//		glVertex3f((gfCurrentX + .00f), (gfCurrentY + gfHeightOfLine), (gfCurrentZ + 0.0f));
//	}
//	/*0th LINE*/
//	if (giSevenSgment[0] == 1)
//	{
//		glVertex3f(gfCurrentX, (gfCurrentY + gfHeightOfLine), gfCurrentZ);
//		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);
//	}
//
//	/*5th LINE*/
//	if (giSevenSgment[5] == 1)
//	{
//		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);
//		glVertex3f((gfCurrentX + gfWidthOfLine), gfCurrentY, gfCurrentZ);
//	}
//	glEnd();
//}

void StoreLines()
{
	if (gbLinesFilled == FALSE)
	{
		for (int i = 0; i < giTotalNumberOfLineCharacters; i++)
		{
			NumberOfLineChar[i] = rand() % 27;
		}
	}

	gbLinesFilled = TRUE;
	if (gbDisplayedFirstWall == FALSE)
	{
		gbDisplayedFirstWall = TRUE;
		dwDisplayedFirstWall = GetTickCount();
		dwSavedTickCount = dwDisplayedFirstWall;
	}
	dwGetTickCount = GetTickCount();
	if ((dwGetTickCount - dwSavedTickCount) >= gdwSpeedOfWallChange)
	{
		dwSavedTickCount = dwGetTickCount;
		gbLinesFilled = FALSE;
	}
}

void DisplayLine(int ColumnNumber)
{
	void DrawCharacter();
	void RandomCharacter(int);
	for (int i = 0; i < CharOnY; i++)
	{
		RandomCharacter(NumberOfLineChar[CharOnX*ColumnNumber] + i);
		DrawCharacter();
		gfCurrentY = gfCurrentY + gfCommonYDistance + 0.1f;
	}
	gfHeightOfMatrixLine = gfCurrentY;
	gfCurrentY = 0.0f;
	

}
void TranslateLines()
{
	int iRandomX, iRandomZ;
	if (ptrTranslateLine == NULL)
	{
		ptrTranslateLine = (struct TranslateLine *)calloc((CharOnX*CharOnZ), sizeof(struct TranslateLine));
		if (ptrTranslateLine == NULL)
		{
			//ERROR HANDLING
		}
		for (int j = 0; j < CharOnZ; j++)
		{
			for (int i = 0; i < CharOnX; i++)
			{
				ptrTranslateLine[(j*CharOnX) + i].bTraslationOn = FALSE;
				ptrTranslateLine[(j*CharOnX) + i].fValueOfY = gfMaxUpperYForLineTranslation;
				ptrTranslateLine[(j*CharOnX) + i].iZOrderOfLine = j;
			}
		}
		//this memory allocation block is going to 
		//be called once, hence use it as a flag value
		dwSavedTickCountForLineTranslation = GetTickCount();
	}
	dwGetTickCountForLineTranslation = GetTickCount();

	if ((dwGetTickCountForLineTranslation - dwSavedTickCountForLineTranslation) > dwTimeDiffForLineTranslation)
	{
		dwSavedTickCountForLineTranslation = dwGetTickCountForLineTranslation;

		iRandomX = rand() % CharOnX;
		iRandomZ = (rand() % CharOnZ) + 1;	//TO AVOID THE NUMBER 0 As we are multiplying it below
		ptrTranslateLine[(iRandomZ*CharOnX) + iRandomX].bTraslationOn = TRUE;
		//(ptrTranslateLine +CharOnZ*CharOnX + iRandomX)->bTraslationOn = TRUE;

	}

	for (int j = 0; j < CharOnZ; j++)
	{
		for (int i = 0; i < CharOnX; i++)
		{
			if (ptrTranslateLine[(j * CharOnX) + i].bTraslationOn == TRUE)
			{
				ptrTranslateLine[(j * CharOnX) + i].fValueOfY = ptrTranslateLine[(j * CharOnX) + i].fValueOfY - gfValueForDownYTranslation;

				if (ptrTranslateLine[(j * CharOnX) + i].fValueOfY <= (gfMaxLowerYForLineTranslation - gfHeightOfMatrixLine))
				{
					ptrTranslateLine[(j * CharOnX) + i].fValueOfY = gfMaxUpperYForLineTranslation;
				}
			}
		}
	}

}
void DisplayMatrixLineWall()
{
	for (int j = 0; j < CharOnZ; j++)
	{

		for (int i = 0; i < CharOnX; i++)
		{
			glPushMatrix();
			glTranslatef(0.0f, ptrTranslateLine[(i*CharOnX) + j].fValueOfY, 0.0f);
			DisplayLine((j*CharOnZ)+i);
			gfCurrentX = gfCurrentX + gfCommonXDistance + 1.0f;
			glPopMatrix();
		}
		gfCurrentX = 0.0f;
		glTranslatef(0.0f, 0.0f, -gfTranslateMatrixLineZ);

	}
}

void DropLines()
{
	glPushMatrix();
	StoreLines();
	TranslateLines();
	DisplayMatrixLineWall();
	glPopMatrix();
}