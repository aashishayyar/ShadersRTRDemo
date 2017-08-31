int giSevenSgment[] = {0,0,0,0,0,0,0};			

float gfLeftTop_X      =  -0.5f;
float gfLeftTop_Y      =   0.5f;
float gfLeftBottom_X   =  -0.5f;
float gfLeftBottom_Y   =  -0.5f;
float gfRightBottom_X  =   0.5f;
float gfRightBottom_Y  =  -0.5f;
float gfRightTop_X	   =   0.5f;
float gfRightTop_Y	   =   0.5f;
float gfCordinate_Z	   =  -1.0f;	
float gfHeight = gfLeftTop_Y -gfLeftBottom_Y;

float gfCommonDistance = 0.10f;
float gfWidthOfQuads   = 0.02f;	

float gfMatrixCharRed   = 0.0f;
float gfMatrixCharGreen = 1.0f;
float gfMatrixCharBlue  = 0.0f;


void DrawCharacter();
void RandomCharacter();