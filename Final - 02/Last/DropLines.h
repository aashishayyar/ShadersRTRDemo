/*MATRIX.h*/

extern int giSevenSgment[17];

extern float gfWidthOfLine; // = 0.05f;
extern float gfHeightOfLine;// = 0.05f;
extern float gfCommonXDistance; // = (gfWidthOfLine * 4);
extern float gfCommonYDistance; // = (gfHeightOfLine * 4);

extern float gfDistanceForD;// = 0.015f;

extern float gfCurrentX; // = 0.0f;
extern float gfCurrentY;// = 0.0f;
extern float gfCurrentZ;// = 0.0f;

extern float gfMatrixCharRed;//= 0.0f;
extern  float gfMatrixCharGreen;// = 1.0f;
extern  float gfMatrixCharBlue;// = 0.0f;


extern  DWORD gdwSpeedOfWallChange; // = 400;

extern DWORD dwSavedTickCount;// = 0;
extern  DWORD dwGetTickCount;// = 0;
extern DWORD dwDisplayedFirstWall;// = 0;

extern DWORD dwMaximumCharaFromWall;// = 0;

extern BOOL gbWallFilled;// = FALSE;
extern BOOL gbDisplayedFirstWall;// = FALSE;



/*DROP_LINES.h*/


int CharOnZ = 10;
int CharOnY = 25;
int CharOnX = 40;
int giTotalNumberOfLineCharacters = 11250;

long int NumberOfLineChar[11250] = { '\0' };

BOOL gbLinesFilled = FALSE;

float gfTranslateMatrixLineZ = 1.0f;
float gfHeightOfMatrixLine;

struct TranslateLine
{
	BOOL bTraslationOn;
	float fValueOfY;
	int iZOrderOfLine;

}*ptrTranslateLine = NULL;


DWORD dwSavedTickCountForLineTranslation = 0;
DWORD dwGetTickCountForLineTranslation = 0;
DWORD dwTimeDiffForLineTranslation = 50;


float gfMaxUpperYForLineTranslation = 0.0f;
float gfMaxLowerYForLineTranslation = -18.0;
float gfValueForDownYTranslation = 0.01f;

