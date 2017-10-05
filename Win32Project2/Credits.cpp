#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"Credits.h"

void UpdateLegoCharacterAnimation(int *currentLego, int i, int speed)
{
	if (gfTranslateLegoCharZ[i] <= -15.0f)
	{
		gfTranslateLegoCharZ[i] = gfTranslateLegoCharZ[i] + 0.075f*speed;
		gfTranslateLegoNameZ[i] = gfTranslateLegoNameZ[i] + 0.08f*speed;
	}
	else
	{
		if (*currentLego < 3 && i == *currentLego)
			*currentLego = *currentLego + 1;
	}
}

void ShowLegoCharacterAnimation(int currentLegoCharacter)
{
	void DrawSingleLegoCharacters(int);

	glPushMatrix();
		glTranslatef(gfTranslateLegoCharX[currentLegoCharacter], gfTranslateLegoCharY, gfTranslateLegoCharZ[currentLegoCharacter]);
		DrawSingleLegoCharacters(currentLegoCharacter);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, gfTranslateLegoCharZ[currentLegoCharacter]+30.0f);
		DrawCreditsName(currentLegoCharacter);
	glPopMatrix();

}

/*void RandomCharacter(int RandomNumber) {
	for (int i = 0; i < 7; i++) {
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
}*/

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

void DrawCreditsName(int currentLego)
{
	int *intArray= NULL;
	switch (currentLego)
	{
	case 3:
		intArray = Vito;
		break;
	case 2:
		intArray = Michael;
		break;
	case 1:
		intArray = Sonny;
		break;
	case 0:
		intArray = Luca;
		break;
	default:
		return;
	}

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

	
	//glPushMatrix();
	//glTranslatef(0.0f, -0.5f, 0.0f);
	//DrawCreditsName(Sonny);
	//glTranslatef(0.0f, -0.5f, 0.0f);
	//DrawCreditsName(Neo);
	//glTranslatef(0.0f, -0.5f, 0.0f);
	//DrawCreditsName(Neo);
	//glPopMatrix();
}




/*Functions from Matrix.h*/


