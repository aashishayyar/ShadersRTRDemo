#include"Main.h"
#include"Credits.h"

void RandomCharacter(int RandomNumber);
void DrawCharacter();


void DecideCreditsCharacter(int RandomNumber)
{

	for (int i = 0; i < 16; i++)
	{
		giTwelveSgment[i] = 0;
	}
	switch (RandomNumber)
	{
	case 0x0:
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[5] = 1;
		break;
	case 0x1:
		giTwelveSgment[4] = giTwelveSgment[5] = 1;
		break;
	case 0x2:
		giTwelveSgment[0] = giTwelveSgment[5] = giTwelveSgment[6] = giTwelveSgment[2] = giTwelveSgment[3] = 1;
		break;
	case 0x3:
		giTwelveSgment[0] = giTwelveSgment[5] = giTwelveSgment[6] = giTwelveSgment[4] = giTwelveSgment[3] = 1;
		break;
	case 0x4:
		giTwelveSgment[1] = giTwelveSgment[6] = giTwelveSgment[5] = giTwelveSgment[4] = 1;
		break;
	case 0x5:
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[6] = giTwelveSgment[4] = giTwelveSgment[3] = 1;
		break;
	case 0x6:
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[4] = giTwelveSgment[3] = giTwelveSgment[5] = giTwelveSgment[6] = 1;
		break;
	case 0x7:
		giTwelveSgment[0] = giTwelveSgment[4] = giTwelveSgment[5] = 1;
		break;
	case 0x8:
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[5] = 1;
		break;
	case 0x9:
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[5] = giTwelveSgment[6] = 1;
		break;
	case 10:	//a
		giTwelveSgment[0] = giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[5] = giTwelveSgment[6] = 1;
		break;
	case 11:	//b
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[6] = 1;
		break;
	case 12:	//c
		giTwelveSgment[6] = giTwelveSgment[2] = giTwelveSgment[3] = 1;
		break;
	case 13:	//d
		giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[5] = giTwelveSgment[6] = 1;
		break;
	case 14:	//e
		giTwelveSgment[0] = giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[1] = giTwelveSgment[5] = giTwelveSgment[6] = 1;
		break;
	case 15:	//f
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[6] = 1;
		break;
	case 16:	//g	Added 3 to differentiate from 9
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[6] = giTwelveSgment[5] = giTwelveSgment[4] = giTwelveSgment[3] = 1;
		break;
	case 17:	//h
		giTwelveSgment[0] = giTwelveSgment[2] = giTwelveSgment[4] = giTwelveSgment[5] = giTwelveSgment[6] = 1;
		break;
	case 18:	//j
		giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[5] = 1;
		break;
	case 19:	//L 
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = 1;
		break;
	case 20:	//n
		giTwelveSgment[2] = giTwelveSgment[4] = giTwelveSgment[6] = 1;
		break;
	case 21:	//o
		giTwelveSgment[2] = giTwelveSgment[6] = giTwelveSgment[3] = giTwelveSgment[4] = 1;
		break;
	case 22:	//q	
		giTwelveSgment[1] = giTwelveSgment[0] = giTwelveSgment[5] = giTwelveSgment[4] = giTwelveSgment[6] = 1;
		break;
	case 23:	//p
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[0] = giTwelveSgment[5] = giTwelveSgment[6] = 1;
		break;
	case 24:	//s	
		giTwelveSgment[1] = giTwelveSgment[0] = giTwelveSgment[3] = giTwelveSgment[6] = giTwelveSgment[4] = 1;
		break;
	case 25:	//t
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[6] = 1;
		break;
	case 26:	//y	Add 3 to differentiate from 4
		giTwelveSgment[1] = giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[5] = giTwelveSgment[6] = 1;
		break;
	case 27:	//M
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[4] = giTwelveSgment[5] = giTwelveSgment[9] = giTwelveSgment[7] = 1;
		break;
	case 28:	//I
		giTwelveSgment[0] = giTwelveSgment[11] = giTwelveSgment[12] = giTwelveSgment[3] = 1;
		break;
	case 29:	//Y
		giTwelveSgment[7] = giTwelveSgment[9] = giTwelveSgment[12] = 1;
		break;
	case 30:	//T
		giTwelveSgment[0] = giTwelveSgment[11] = giTwelveSgment[12] = 1;
		break;
	case 31:	//A
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[5] = giTwelveSgment[4] = giTwelveSgment[0] = giTwelveSgment[6] = 1;
		break;
	case 32:	//L
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = 1;
		break;
	case 33:	//C
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = 1;
		break;
	case 34:	//H
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[4] = giTwelveSgment[5] = giTwelveSgment[6] = 1;
		break;
	case 35:	//E
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[6] = 1;
		break;
	case 36:	//O
		giTwelveSgment[0] = giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[5] = 1;
		break;
	case 37:	//N
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[4] = giTwelveSgment[5] = giTwelveSgment[7] = giTwelveSgment[8] = 1;
		break;
	case 38:	//R
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[0] = giTwelveSgment[6] = giTwelveSgment[5] = giTwelveSgment[15] = 1;
		break;
	case 39:	//V
		giTwelveSgment[13] = giTwelveSgment[14] = 1;
		break;
	case 40:	//U
		giTwelveSgment[1] = giTwelveSgment[2] = giTwelveSgment[3] = giTwelveSgment[4] = giTwelveSgment[5] = 1;
		break;


	}
	return;
}
void DrawCreditsCharacter()
{
	float fCreditsCentreOfTopLineX = ((gfCreditsCurrentX)+(gfCreditsCurrentX + gfCreditsWidthOfLine)) / 2;
	float fCreditsCentreOfTopLineY = (gfCreditsCurrentY + gfCreditsHeightOfLine);
	float fCreditsCentreOfTopLineZ = gfCreditsCurrentZ;

	float fCreditsCentreOfMidLineX = (gfCreditsCurrentX + (gfCreditsCurrentX + gfCreditsWidthOfLine)) / 2;
	float fCreditsCentreOfMidLineY = gfCreditsCurrentY;
	float fCreditsCentreOfMidLineZ = gfCreditsCurrentZ;

	float fCreditsCentreOfBotLineX = (gfCreditsCurrentX + (gfCreditsCurrentX + gfCreditsWidthOfLine)) / 2;
	float fCreditsCentreOfBotLineY = (gfCreditsCurrentY - gfCreditsHeightOfLine);
	float fCreditsCentreOfBotLineZ = gfCreditsCurrentZ;

	glBegin(GL_LINES);

	glColor3f(gfCreditsCharRed, gfCreditsCharGreen, gfCreditsCharBlue);

	/*15th Line  i.e. 2nd TOP to 4th BOTTOM  */
	if (giTwelveSgment[15] == 1)
	{
		glVertex3f(gfCreditsCurrentX, gfCreditsCurrentY, gfCreditsCurrentZ);	//TOP OF 2ndLINE
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), (gfCreditsCurrentY - gfCreditsHeightOfLine), gfCreditsCurrentZ); 	//BOTTOM OF 4th LINE
	}
	/*14th Line  i.e. 1st TOP to BOTTOM CENTRE */
	if (giTwelveSgment[14] == 1)
	{
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), (gfCreditsCurrentY + gfCreditsHeightOfLine), gfCreditsCurrentZ);	//TOP OF 5th LINE
		glVertex3f(fCreditsCentreOfBotLineX, fCreditsCentreOfBotLineY, fCreditsCentreOfBotLineZ);					//CENTRE OF BOTTOM LINE
	}

	/*13th Line  i.e. 1st TOP to BOTTOM CENTRE */
	if (giTwelveSgment[13] == 1)
	{
		glVertex3f((gfCreditsCurrentX), (gfCreditsCurrentY + gfCreditsHeightOfLine), (gfCreditsCurrentZ));  //TOP OF 1st LINE
		glVertex3f(fCreditsCentreOfBotLineX, fCreditsCentreOfBotLineY, fCreditsCentreOfBotLineZ);					//CENTRE OF BOTTOM LINE
	}

	/*12th Line  i.e. MidCentre to BOTTOM CENTRE */
	if (giTwelveSgment[12] == 1)
	{
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCreditsCurrentZ);					//CENTRE OF MIDDLE LINE
		glVertex3f(fCreditsCentreOfBotLineX, fCreditsCentreOfBotLineY, fCreditsCentreOfBotLineZ);			//CENTRE OF TOP LINE
	}

	/*11th Line  i.e. TOP CENTRE to MidCentre */
	if (giTwelveSgment[11] == 1)
	{
		glVertex3f(fCreditsCentreOfTopLineX, fCreditsCentreOfTopLineY, fCreditsCentreOfTopLineZ);			//CENTRE OF TOP LINE
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCreditsCurrentZ);					//CENTRE OF MIDDLE LINE
	}

	/*10th Line  i.e. MidCentre to 2nd Bottom*/
	if (giTwelveSgment[10] == 1)
	{
		glVertex3f(gfCreditsCurrentX, (gfCreditsCurrentY - gfCreditsHeightOfLine), gfCreditsCurrentZ);		// Bottom OF 2nd Line
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCreditsCurrentZ);					//CENTRE OF MIDDLE LINE
	}

	/*9th Line  i.e. 5th Top to MidCentre*/
	if (giTwelveSgment[9] == 1)
	{
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), (gfCreditsCurrentY + gfCreditsHeightOfLine), gfCreditsCurrentZ);	//TOP OF 5th LINE
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCreditsCurrentZ);					//CENTRE OF MIDDLE LINE
	}

	/*8th Line ---> i.e. MidCentre to 4th Bottom*/
	if (giTwelveSgment[8] == 1)
	{
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), (gfCreditsCurrentY - gfCreditsHeightOfLine), gfCreditsCurrentZ);  //BOTTOM OF LINE 4
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCreditsCurrentZ);										//CENTRE OF MIDDLE LINE
	}

	/*7th Line ---> i.e. 1st Top to MidCentre*/
	if (giTwelveSgment[7] == 1)
	{
		glVertex3f((gfCreditsCurrentX), (gfCreditsCurrentY + gfCreditsHeightOfLine), (gfCreditsCurrentZ));  //TOP OF 1st LINE	
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCreditsCurrentZ);					  //CENTRE OF MIDDLE LINE
	}

	/*4th LINE*/
	if (giTwelveSgment[4] == 1)
	{
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), (gfCreditsCurrentY - gfCreditsHeightOfLine), gfCreditsCurrentZ);
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), gfCreditsCurrentY, gfCreditsCurrentZ);
	}
	/*3rd LINE*/
	if (giTwelveSgment[3] == 1)
	{
		glVertex3f(gfCreditsCurrentX, (gfCreditsCurrentY - gfCreditsHeightOfLine), gfCreditsCurrentZ);
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), (gfCreditsCurrentY - gfCreditsHeightOfLine), gfCreditsCurrentZ);
	}
	/*2nd LINE*/
	if (giTwelveSgment[2] == 1)
	{
		glVertex3f(gfCreditsCurrentX, gfCreditsCurrentY, gfCreditsCurrentZ);
		glVertex3f(gfCreditsCurrentX, (gfCreditsCurrentY - gfCreditsHeightOfLine), gfCreditsCurrentZ);
	}
	/*6th LINE*/
	if (giTwelveSgment[6] == 1)
	{
		glVertex3f(gfCreditsCurrentX, gfCreditsCurrentY, gfCreditsCurrentZ);
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), (gfCreditsCurrentY), (gfCreditsCurrentZ));
	}
	/*1st LINE*/
	if (giTwelveSgment[1] == 1)
	{
		glVertex3f(gfCreditsCurrentX, gfCreditsCurrentY, gfCreditsCurrentZ);
		glVertex3f((gfCreditsCurrentX), (gfCreditsCurrentY + gfCreditsHeightOfLine), (gfCreditsCurrentZ));
	}
	/*0th LINE*/
	if (giTwelveSgment[0] == 1)
	{
		glVertex3f(gfCreditsCurrentX, (gfCreditsCurrentY + gfCreditsHeightOfLine), gfCreditsCurrentZ);
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), (gfCreditsCurrentY + gfCreditsHeightOfLine), gfCreditsCurrentZ);
	}

	/*5th LINE*/
	if (giTwelveSgment[5] == 1)
	{
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), (gfCreditsCurrentY + gfCreditsHeightOfLine), gfCreditsCurrentZ);
		glVertex3f((gfCreditsCurrentX + gfCreditsWidthOfLine), gfCreditsCurrentY, gfCreditsCurrentZ);
	}
	glEnd();
}
void DrawCreditsName(int intArray[])
{
	int i = 0;
	gfCreditsCurrentX = 0.0f;
	gfCreditsCurrentY = 0.0f;
	gfCreditsCurrentZ = 0.0f;
	while (1)
	{
		DecideCreditsCharacter(intArray[i]);
		DrawCreditsCharacter();
		i++;
		if (intArray[i] == '\0')
		{
			break;
		}
		gfCreditsCurrentX = gfCreditsCurrentX + gfCreditsCommonXDistance;
	}
}
void DisplayCredits()
{
	int Vito[] = { 39,28,30,36,'\0' };
	int Sonny[] = { 24,36,37,37,29,'\0' };
	int Michael[] = { 27,28,33,34,31,35,32,'\0' };
	int Luc[] = { 32,40,33,'\0' };
	int Neo[] = { 37,35,36 ,'\0' };

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	DrawCreditsName(Sonny);
	glTranslatef(0.0f, -0.5f, 0.0f);
	DrawCreditsName(Neo);
	glTranslatef(0.0f, -0.5f, 0.0f);
	DrawCreditsName(Neo);
	glPopMatrix();
}



void StoreLine()
{
	int iTotalNumberOfCharacters = giNumberOfCharOnX*giNumberOfCharOnY*giNumberOfLinesAcrossZ;
	int RandomNumber = 0;
	if (piRandomLineNumbers == NULL)
	{
		piRandomLineNumbers = (int *)malloc(sizeof(int)*(iTotalNumberOfCharacters));
		if (piRandomLineNumbers == NULL)
		{
			//ERROR HANDLING
		}
	}
	if (gbLinesFilled == FALSE)
	{
		for (int i = 0; i < iTotalNumberOfCharacters; i++)
		{
			RandomNumber = rand() % 27;
			piRandomLineNumbers[i] = RandomNumber;
		}
		gbLinesFilled = TRUE;
	}
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
void DrawMatrixLine(int iColumnNumber, int giNumberOfLinesAcrossZ)
{
	int iCounter = 0;
	int iRandomCharacterCount = giNumberOfCharOnX *giNumberOfCharOnY;
	StoreLine();
	//for(int j = 0; j < giNumberOfCharOnX; j++)
	//{
	for (int i = 0; i < giNumberOfCharOnY; i++)
	{
		RandomCharacter(piRandomLineNumbers[((giNumberOfLinesAcrossZ*giNumberOfCharOnX) + i + iColumnNumber)]);
		iCounter++;
		if (iCounter >= iRandomCharacterCount)
		{
			iCounter = 0;
		}
		//HERE WE DRAW ACTUAL CHARACTER 
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

		gfCurrentY = gfCurrentY + gfCommonYDistance + 0.1f;
	}
	gfHeightOfMatrixLine = gfCurrentY;
	gfCurrentY = 0.0f;
}
void DrawLinesWall()
{
	glPushMatrix();
	for (int i = 0; i < giNumberOfLinesAcrossZ; i++)
	{
		for (int j = 0; j < giNumberOfCharOnX; j++)
		{
			glPushMatrix();
			glTranslatef(0.0f, ptrTranslateLine[(i*giNumberOfCharOnX) + j].fValueOfY, 0.0f);
			DrawMatrixLine(j, i);
			gfCurrentX = gfCurrentX + gfCommonXDistance;
			glPopMatrix();

		}
		gfCurrentX = 0.0f;
		glTranslatef(0.0f, 0.0f, -gfDistanceAcrossZ);

	}

	glPopMatrix();
}
void TranslateLines()
{
	int iRandomX, iRandomZ;
	if (ptrTranslateLine == NULL)
	{
		ptrTranslateLine = (struct TranslateLine *)calloc((giNumberOfCharOnX*giNumberOfLinesAcrossZ), sizeof(struct TranslateLine));
		if (ptrTranslateLine == NULL)
		{
			//ERROR HANDLING
		}
		for (int j = 0; j < giNumberOfLinesAcrossZ; j++)
		{
			for (int i = 0; i < giNumberOfCharOnX; i++)
			{
				ptrTranslateLine[(j*giNumberOfCharOnX) + i].bTraslationOn = FALSE;
				ptrTranslateLine[(j*giNumberOfCharOnX) + i].fValueOfY = gfMaxUpperYForLineTranslation;
				ptrTranslateLine[(j*giNumberOfCharOnX) + i].iZOrderOfLine = j;
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

		iRandomX = rand() % giNumberOfCharOnX;
		iRandomZ = (rand() % giNumberOfLinesAcrossZ) + 1;	//TO AVOID THE NUMBER 0 As we are multiplying it below
		ptrTranslateLine[(iRandomZ*giNumberOfCharOnX) + iRandomX].bTraslationOn = TRUE;
		//(ptrTranslateLine +giNumberOfLinesAcrossZ*giNumberOfCharOnX + iRandomX)->bTraslationOn = TRUE;

	}

	for (int j = 0; j < giNumberOfLinesAcrossZ; j++)
	{
		for (int i = 0; i < giNumberOfCharOnX; i++)
		{
			if (ptrTranslateLine[(j * giNumberOfCharOnX) + i].bTraslationOn == TRUE)
			{
				ptrTranslateLine[(j * giNumberOfCharOnX) + i].fValueOfY = ptrTranslateLine[(j * giNumberOfCharOnX) + i].fValueOfY - gfValueForDownYTranslation;

				if (ptrTranslateLine[(j * giNumberOfCharOnX) + i].fValueOfY <= (gfMaxLowerYForLineTranslation - gfHeightOfMatrixLine))
				{
					ptrTranslateLine[(j * giNumberOfCharOnX) + i].fValueOfY = gfMaxUpperYForLineTranslation;
				}
			}
		}
	}

}

/*Functions from Matrix.h*/


