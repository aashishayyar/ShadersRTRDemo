#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include"Util.h"
#include"LegoWalk.h"

void updateNormalWalk(int currentStickMan)
{
	if (lLeg[currentStickMan] < -20)
	{
		giLLegDirection[currentStickMan] = 1;
	}
	else if (lLeg[currentStickMan] > 20)
	{
		giLLegDirection[currentStickMan] = -1;
	}
	lLeg[currentStickMan] = lLeg[currentStickMan] + giLLegDirection[currentStickMan] * 2* gfSpeed;

	if (rLeg[currentStickMan] < -20)
	{
		giRLegDirection[currentStickMan] = 1;
	}
	else if (rLeg[currentStickMan] > 20)
	{
		giRLegDirection[currentStickMan] = -1;
	}
	rLeg[currentStickMan] = rLeg[currentStickMan] + giRLegDirection[currentStickMan] * 2* gfSpeed;

	if (lArm[currentStickMan] < 30)
	{
		giLArmDirection[currentStickMan] = 1;
	}
	else if (lArm[currentStickMan] > 70)
	{
		giLArmDirection[currentStickMan] = -1;
	}
	lArm[currentStickMan] = lArm[currentStickMan] + giLArmDirection[currentStickMan] * 2* gfSpeed;

	if (rArm[currentStickMan] < 30)
	{
		giRArmDirection[currentStickMan] = 1;
	}
	else if (rArm[currentStickMan] > 70)
	{
		giRArmDirection[currentStickMan] = -1;
	}
	rArm[currentStickMan] = rArm[currentStickMan] + giRArmDirection[currentStickMan] * 2* gfSpeed;

}

void updateAllCharacters()
{
	int i = 0;
	gfTranslateX += gfSpeed / 15;
	if (gfTranslateX >= 8.0f)
		gbStopLegoCharacters = true;
	
		for (i = 0; i < 4; i++)
		{
			if (gfTranslateZ[i] < 3.0f && (i == 1 || i == 3))
			{
				if (gfTranslateX >= -15.0f)
					gfTranslateZ[i] += 0.3 * gfSpeed / 45;
			
			}
			updateNormalWalk(i);
		}
}

void updateHandAction(int currentLegoCharacter)
{
	if (lArm[currentLegoCharacter] < 90)
	{
		lArm[currentLegoCharacter] += 2*gfSpeed;
	}
}
