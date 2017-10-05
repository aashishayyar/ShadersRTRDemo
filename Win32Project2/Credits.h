#pragma once
#include"Util.h"
int giTwelveSgment[16];
float gfTranslateLegoCharX[4] = { -22.f, -15.0f, -5.0f, 2.0f };
void UpdateLegoCharacterAnimation(int *, int, int);

float gfCreditsCharRed = 1.0f;
float gfCreditsCharGreen = 1.0f;
float gfCreditsCharBlue = 1.0f;

float gfCreditsCurrentX = 0.0f;
float gfCreditsCurrentY = 0.0f;
float gfCreditsCurrentZ = 0.0f;

float gfCreditsWidthOfLine = 0.07f;
float gfCreditsHeightOfLine = 0.07f;

float gfCreditsCommonXDistance = (gfCreditsWidthOfLine * 2);
float gfCreditsCommonYDistance = (gfCreditsHeightOfLine * 2);
float gfCeditsSpaceBetnWords = (gfCreditsCommonXDistance * 2);

/*DROP LINES*/
/*
void DrawMatrixLine(int iColumnNumber, int giNumberOfLinesAcrossZ);

struct TranslateLine
{
	BOOL bTraslationOn;
	float fValueOfY;
	int iZOrderOfLine;

}*ptrTranslateLine = NULL;

int *piRandomLineNumbers= NULL;

DWORD dwSavedTickCountForLineTranslation = 0;
DWORD dwGetTickCountForLineTranslation = 0;
DWORD dwTimeDiffForLineTranslation = 800;


float gfMaxUpperYForLineTranslation = 8.5f;
float gfMaxLowerYForLineTranslation = -8.0;
float gfValueForDownYTranslation = 0.005f;
float gfHeightOfMatrixLine = 0.0f;

float gfLengthOfCorridoor = 10.0f;
float gfDistanceAcrossZ = 1.0f;

int giNumberOfLinesAcrossZ = 5;
BOOL gbLinesFilled = FALSE;

/*MATRIX_WALL.h*/

int *piRandomLineNumbers= NULL;
extern int giSevenSgment[17];// = { 0,0,0,0,0,0,0 };

extern float gfWidthOfLine;// = 0.05f;
extern float gfHeightOfLine;// = 0.05f;
extern float gfCommonXDistance;//  = (gfWidthOfLine * 10);
extern float gfCommonYDistance;// = (gfHeightOfLine * 2);

extern float gfCurrentX;// = 0.0f;
extern float gfCurrentY;// = 0.0f;
extern float gfCurrentZ;// = 0.0f;

extern float gfMatrixCharRed;// = 0.0f;
extern float gfMatrixCharGreen;// = 1.0f;
extern float gfMatrixCharBlue;// = 0.0f;

extern int giNumberOfCharOnX;// = 10;
extern int giNumberOfCharOnY;// = 30;

extern DWORD gdwSpeedOfWallChange;// = 2000;


extern DWORD dwSavedTickCount; // = 0;
extern DWORD dwGetTickCount; // = 0;
extern DWORD dwDisplayedFirstWall; // = 0;

extern BOOL gbWallFilled; // = FALSE;
extern BOOL gbDisplayedFirstWall;// = FALSE;

void DrawCharacter();
void RandomCharacter(int RandomNumber);
//extern void DrawSingleLegoCharacters(int currentLegoCharacter);

//variable for Lego character
extern bool gbEscapeKeyIsPressed;

//function prototype for Lego Character 

extern void DrawLegoCharacters(int currentLegoCharacter);

void DrawCreditsName(int);

void UpdateLegoCharacterAnimation(int *, int);


int Vito[] = { 39,28,30,36,'\0' };		//3
int Sonny[] = { 24,36,37,37,29,'\0' };	//1	
int Michael[] = { 27,28,33,34,31,35,32,'\0' };	//2
int Luca[] = { 32,40,33,31,'\0' };	//0
int Neo[] = { 37,35,36 ,'\0' };

float drap = 0.0f;

//variable for lego character animaton
float gfTranslateLegoCharY = -4.0f;
float gfTranslateLegoCharZ[4] = { -40.0f, -40.0f, -40.0f, -40.0f };

float gfTranslateLegoNameX = -0.0f;
float gfTranslateLegoNameY = -2.0f;
float gfTranslateLegoNameZ[4] = { -0.0f, -0.0f, -0.0f, -0.0f };

//extern float fCreditsCentreOfMidLineX;