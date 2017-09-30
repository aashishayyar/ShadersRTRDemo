#pragma once
int giSevenSgment[17];

float gfWidthOfLine = 0.075f;
float gfHeightOfLine = 0.075f;
float gfCommonXDistance = (gfWidthOfLine * 4);
float gfCommonYDistance = (gfHeightOfLine * 4);
float gfDistanceForD = 0.015f;

float gfCurrentX = 0.0f;
float gfCurrentY = 0.0f;
float gfCurrentZ = 0.0f;

float gfLineStartingY = -3.0f;	//ARRANGE THAT VALUE LIKE N FROM ANIMATED INDIA
float gfLinePositionZ = 0.0f;	//THAT SHOULD BE RANDOM DEPTH VALUE GENERATED FOR EACH LINE



float gfMatrixCharRed = 0.0f;
float gfMatrixCharGreen = 1.0f;
float gfMatrixCharBlue = 0.0f;

int giNumberOfCharOnX = 100;
int giNumberOfCharOnY = 100;
int giTempNumberOfCharacterOnY;
int giTempNumberOfCharacterOnX;

float giTempHeightOfLine;
float giTempWidthOfLine;
float gfTempCommonXDistance;
float gfTempCommonYDistance;

float gfWidthOfRoom;
float gfHeightOfRoom;


DWORD gdwSpeedOfWallChange = 100;

int *piRandomWallNumbers = NULL;


DWORD dwSavedTickCount = 0;
DWORD dwGetTickCount = 0;
DWORD dwDisplayedFirstWall = 0;

DWORD dwMaximumCharaFromWall = 0;

BOOL gbWallFilled = FALSE;
BOOL gbDisplayedFirstWall = FALSE;

BOOL gbAllocateMemoryAgain = FALSE;

void DrawCharacter();
void RandomCharacter(int RandomNumber);

void DrawRoom();
void DrawWall();
void StoreWall();

void drawMatrixRoom(void);
void DrawMatrixLines();
void StoreLines();
