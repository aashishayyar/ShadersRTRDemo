//COMMON VARIABLES FOR MATRIX WALL AND 
// DROPED LINES WHICH ARE GOING TO BE 
//CHANGED ACCORDING TO CALL
//FOR MATRIX WALL & DROP LINES
int giSevenSgment[] = {0,0,0,0,0,0,0};			

float gfWidthOfLine  = 0.05f;
float gfHeightOfLine = 0.05f;
float gfCommonXDistance = (gfWidthOfLine*4) ;
float gfCommonYDistance = (gfHeightOfLine*4);


float gfCurrentX	   = 0.0f;
float gfCurrentY	   = 0.0f;
float gfCurrentZ	   = 0.0f;

float gfMatrixCharRed   = 0.0f;
float gfMatrixCharGreen = 1.0f;
float gfMatrixCharBlue  = 0.0f;

int giNumberOfCharOnX      = 40;
int giNumberOfCharOnY      = 50;

void DrawCharacter();
void RandomCharacter(int RandomNumber);


/*
*
*VARIABLE AND FUNCTION DECLARATION
* FOR MATRIX WALL
*
*/

float gfWidthOfMatrixWallChar     = 0.07f;	
float gfHeightOfMatrixWallChar    = 0.07f;

int giNumberOfCharOnXMatrixWall      = 200;
int giNumberOfCharOnYMatrixWall      = 150;

float gfWidthOfRoom;
float gfHeightOfRoom;

int giTempNumberOfCharacterOnY;
int giTempNumberOfCharacterOnX;
int *piRandomWallNumbers = NULL;
int *piRandomLineNumbers = NULL;

DWORD gdwSpeedOfWallChange = 1000;
DWORD dwSavedTickCount		= 0;
DWORD dwGetTickCount		= 0;
DWORD dwDisplayedFirstWall	= 0;

DWORD dwMaximumCharaFromWall = 0;

BOOL gbWallFilled		   = FALSE;
BOOL gbDisplayedFirstWall  = FALSE;
BOOL gbAllocateMemoryAgain = FALSE;


//void DrawRoom();			THAT FUNCTION HAS TO BE IN MAIN.h OF FINAL PROJECT
void DrawWall();
void StoreWall();


/*
*
*VARIABLE AND FUNCTION DECLARATION
* FOR DropLines
*
*/

float gfWidthOfDropLineChar     = 0.04f;	
float gfHeightOfDropLineChar    = 0.04f;

int giNumberOfCharOnXDropLines		= 50;
int giNumberOfCharOnYDropLines      = 25;

DWORD dwSavedTickCountForLineTranslation = 0;
DWORD dwGetTickCountForLineTranslation	 = 0;
DWORD dwTimeDiffForLineTranslation		 = 2000;

struct TranslateLine
{
  BOOL bTraslationOn;
  float fValueOfY;
  int iZOrderOfLine;

}*ptrTranslateLine = NULL;




float gfMaxUpperYForLineTranslation = 15.5f;
float gfMaxLowerYForLineTranslation = -15.0;
float gfValueForDownYTranslation	= 0.01f;
float gfHeightOfMatrixLine = 0.0f;			 //THAT VARIABLE GETS RESOLVED WHILE CALCULATING 

float gfLengthOfCorridoor  = 10.0f;			//NOT USED FOR NOW....USEFUL WHEN WE MERGE MATRIX_ROOM AND DROP_LINES
float gfDistanceAcrossZ	   = 1.5f;			//DISTANCE ACROSS Z-AXIS 

int giNumberOfLinesAcrossZ = 5;

BOOL gbLinesFilled		  = FALSE;


void DrawLinesWall();
void DrawMatrixLine(int iColumnNumber,int giNumberOfLinesAcrossZ);
void TranslateLines();
void StoreLines();


