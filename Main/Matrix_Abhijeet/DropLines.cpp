#include"main.h"
#include"Matrix.h"
#include"DropLines.h"

void StoreLine()
{
	int iTotalNumberOfCharacters = giNumberOfCharOnX*giNumberOfCharOnY*giNumberOfLinesAcrossZ;
	int RandomNumber = 0;
	if(piRandomLineNumbers == NULL)
	{
		piRandomLineNumbers = (int *)malloc(sizeof(int)*(iTotalNumberOfCharacters));
		if(piRandomLineNumbers == NULL)
		{
			//ERROR HANDLING
		}
	}
	if(gbLinesFilled == FALSE)
	{
	 for(int i = 0;  i < iTotalNumberOfCharacters; i++)
	 {
		RandomNumber = rand() % 27;
		piRandomLineNumbers[i]= RandomNumber;
	 }
	 gbLinesFilled = TRUE;
	}
	if(gbDisplayedFirstWall == FALSE)
	{
		gbDisplayedFirstWall = TRUE;
		dwDisplayedFirstWall = GetTickCount();
		dwSavedTickCount = dwDisplayedFirstWall;
	}
	dwGetTickCount = GetTickCount();
	if((dwGetTickCount - dwSavedTickCount) >= gdwSpeedOfWallChange)
	{
		dwSavedTickCount = dwGetTickCount;
		gbLinesFilled = FALSE;
	}

}
void DrawMatrixLine(int iColumnNumber,int giNumberOfLinesAcrossZ)
{
	int iCounter = 0;
	int iRandomCharacterCount = giNumberOfCharOnX *giNumberOfCharOnY;
	StoreLine();
	//for(int j = 0; j < giNumberOfCharOnX; j++)
	//{
	  for(int i =0; i < giNumberOfCharOnY ; i++)
	  {
		  RandomCharacter(piRandomLineNumbers[((giNumberOfLinesAcrossZ*giNumberOfCharOnX)+i+ iColumnNumber )]);
		  iCounter++;
		  if(iCounter >= iRandomCharacterCount)
		  {
			  iCounter = 0;
		  }
		  //HERE WE DRAW ACTUAL CHARACTER 
		  glBegin(GL_LINES);
			glColor3f(gfMatrixCharRed, gfMatrixCharGreen, gfMatrixCharBlue); 
			/*4th LINE*/
			if(giSevenSgment[4] == 1)
			{
				glVertex3f((gfCurrentX+gfWidthOfLine),(gfCurrentY - gfHeightOfLine),gfCurrentZ);
				glVertex3f((gfCurrentX+gfWidthOfLine),gfCurrentY,gfCurrentZ);
			}
			/*3rd LINE*/
			if(giSevenSgment[3] == 1)
			{
				glVertex3f(gfCurrentX,(gfCurrentY - gfHeightOfLine),gfCurrentZ);
				glVertex3f((gfCurrentX+gfWidthOfLine),(gfCurrentY - gfHeightOfLine),gfCurrentZ);
			}
			/*2nd LINE*/
			if(giSevenSgment[2] == 1)
			{
				glVertex3f(gfCurrentX,gfCurrentY,gfCurrentZ);
				glVertex3f(gfCurrentX,(gfCurrentY - gfHeightOfLine),gfCurrentZ);
			}
			/*6th LINE*/
			if(giSevenSgment[6] == 1)
			{
				glVertex3f(gfCurrentX,gfCurrentY,gfCurrentZ);
				glVertex3f((gfCurrentX+gfWidthOfLine),(gfCurrentY),(gfCurrentZ ));
			}
			/*1st LINE*/
			if(giSevenSgment[1] == 1)
			{
				glVertex3f(gfCurrentX,gfCurrentY,gfCurrentZ);
				glVertex3f((gfCurrentX +.00f),(gfCurrentY + gfHeightOfLine),(gfCurrentZ +0.0f));
			}
			/*0th LINE*/
			if(giSevenSgment[0] == 1)
			{
				glVertex3f(gfCurrentX,(gfCurrentY + gfHeightOfLine),gfCurrentZ);
				glVertex3f((gfCurrentX +gfWidthOfLine ),(gfCurrentY + gfHeightOfLine),gfCurrentZ);
			}
			/*5th LINE*/
			if(giSevenSgment[5] == 1)
			{
				glVertex3f((gfCurrentX +gfWidthOfLine ),(gfCurrentY + gfHeightOfLine),gfCurrentZ);
				glVertex3f((gfCurrentX +gfWidthOfLine ),gfCurrentY,gfCurrentZ);
			}
		glEnd();

		 gfCurrentY = gfCurrentY +  gfCommonYDistance + 0.1f;	  
	  }
	  gfHeightOfMatrixLine = gfCurrentY;
	  gfCurrentY = 0.0f;	
}
void DrawLinesWall()
{
	glPushMatrix();
	for(int i = 0; i < giNumberOfLinesAcrossZ; i++ )
	{
		for(int j = 0; j < giNumberOfCharOnX; j++)
		{
			glPushMatrix();
			glTranslatef(0.0f,ptrTranslateLine[(i*giNumberOfCharOnX)+j].fValueOfY,0.0f);
			DrawMatrixLine(j,i);
			gfCurrentX = gfCurrentX +  gfCommonXDistance;
			glPopMatrix();
			
		}
		gfCurrentX = 0.0f;
		glTranslatef(0.0f,0.0f, -gfDistanceAcrossZ);
		
	}

	glPopMatrix();
}
void TranslateLines()
{
	int iRandomX,iRandomZ;
	if(ptrTranslateLine == NULL)
	{
		ptrTranslateLine =(struct TranslateLine *)calloc((giNumberOfCharOnX*giNumberOfLinesAcrossZ),sizeof(struct TranslateLine));
		if(ptrTranslateLine == NULL)
		{
			//ERROR HANDLING
		}
		for(int j =0; j < giNumberOfLinesAcrossZ; j++)
		{
			for(int i = 0; i < giNumberOfCharOnX; i++)
			{
				ptrTranslateLine[(j*giNumberOfCharOnX)+i].bTraslationOn = FALSE;
				ptrTranslateLine[(j*giNumberOfCharOnX)+i].fValueOfY     = gfMaxUpperYForLineTranslation;
				ptrTranslateLine[(j*giNumberOfCharOnX)+i].iZOrderOfLine = j;
			}
		}
		//this memory allocation block is going to 
		//be called once, hence use it as a flag value
		dwSavedTickCountForLineTranslation = GetTickCount();
	}
	
	dwGetTickCountForLineTranslation = GetTickCount();

	if((dwGetTickCountForLineTranslation - dwSavedTickCountForLineTranslation) > dwTimeDiffForLineTranslation)
	{
		dwSavedTickCountForLineTranslation = dwGetTickCountForLineTranslation;

		iRandomX = rand() % giNumberOfCharOnX;
		iRandomZ = (rand() % giNumberOfLinesAcrossZ) + 1;	//TO AVOID THE NUMBER 0 As we are multiplying it below
		ptrTranslateLine[(iRandomZ*giNumberOfCharOnX)+iRandomX].bTraslationOn = TRUE;
		//(ptrTranslateLine +giNumberOfLinesAcrossZ*giNumberOfCharOnX + iRandomX)->bTraslationOn = TRUE;

	}
	
  for(int j = 0; j < giNumberOfLinesAcrossZ; j++)
  {
	for(int i = 0; i < giNumberOfCharOnX; i++)
	{
		if(ptrTranslateLine[(j * giNumberOfCharOnX)+i].bTraslationOn == TRUE)
		{
		  ptrTranslateLine[(j * giNumberOfCharOnX) + i].fValueOfY  = ptrTranslateLine[(j * giNumberOfCharOnX) + i].fValueOfY - gfValueForDownYTranslation;
		  
		  if(ptrTranslateLine[(j * giNumberOfCharOnX) + i].fValueOfY <= (gfMaxLowerYForLineTranslation - gfHeightOfMatrixLine))
		  {
			  ptrTranslateLine[(j * giNumberOfCharOnX) + i].fValueOfY = gfMaxUpperYForLineTranslation;
		  }
		}
	}
  }
	
}