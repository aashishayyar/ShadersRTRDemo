int giSevenSgment[] = {0,0,0,0,0,0,0};			

float gfWidthOfLine     = 0.05f;	
float gfHeightOfLine    = 0.05f;
float gfCommonXDistance = (gfWidthOfLine*2) ;
float gfCommonYDistance = (gfHeightOfLine*2);


/*FINALIZE THE LEFT SIDE OF THE 6th LINE*
* FOR FINALISING LOCATION OF NEXT CHARACTER 
* VARYING IRRESPECTIVE OF ANY POSITION 
*/

float gfCurrentX	   = 0.0f;
float gfCurrentY	   = 0.0f;
float gfCurrentZ	   = 0.0f;



float gfMatrixCharRed   = 0.0f;
float gfMatrixCharGreen = 1.0f;
float gfMatrixCharBlue  = 0.0f;

int giNumberOfCharOnX      = 050;
int giNumberOfCharOnY      = 025;
DWORD gdwSpeedOfWallChange = 100;

int *piRandomWallNumbers = NULL;

DWORD dwSavedTickCount		= 0;
DWORD dwGetTickCount		= 0;
DWORD dwDisplayedFirstWall	= 0;

BOOL gbWallFilled		  = FALSE;
BOOL gbDisplayedFirstWall = FALSE;

void DrawCharacter();
void RandomCharacter(int RandomNumber);
void StoreWall();