void DrawLinesWall();
void DrawMatrixLine(int iColumnNumber,int giNumberOfLinesAcrossZ);
void TranslateLines();
void StoreLines();

struct TranslateLine
{
  BOOL bTraslationOn;
  float fValueOfY;
  int iZOrderOfLine;

}*ptrTranslateLine = NULL;

DWORD dwSavedTickCountForLineTranslation = 0;
DWORD dwGetTickCountForLineTranslation	 = 0;
DWORD dwTimeDiffForLineTranslation		 = 800;


float gfMaxUpperYForLineTranslation = 8.5f;
float gfMaxLowerYForLineTranslation = -4.0;
float gfValueForDownYTranslation	= 0.02f;
float gfHeightOfMatrixLine = 0.0f;

float gfLengthOfCorridoor  = 10.0f;
float gfDistanceAcrossZ	   = 1.0f; 
int giNumberOfLinesAcrossZ = 5;
