#include"DrawMultipleBullet.h"

int gfCurrentCharacterIndex = 0;
int giCountBullet = 0; 

struct MultipleBulletPosition
{
	GLfloat	translateMultipleBulletX = -25.0f;
	GLfloat translateMultipleBulletY = 6.0f;
	GLfloat translateMultipleBulletZ = 0.0f;

}MultipleBulletPosition[4];

void DrawMultipleBulletFireEffect()
{
	
	for(gfCurrentCharacterIndex = 0;gfCurrentCharacterIndex <= 3;gfCurrentCharacterIndex++)
	{
		glPushMatrix();
		
		//glTranslatef(8.0f, MultipleBulletPosition[0].translateMultipleBulletY, 10.0f);
		//gluLookAt(0.0, 0.0, zShift, 0.0f, 0.0f, -6.0f, 0.0f, 1.0f, 0.0f);
	//	gluLookAt(cos(anglePyramid)*8.0, 0.0f, sin(anglePyramid)*8.0 - 8.0, 0.0f, 0.0f, -8.0f, 0.0f, 1.0f, 0.0f);
		//glRotatef(90.0, 0.0f, 1.0f, 0.0f);
		/*	if (giCountBullet >= 10)
			{
				glPushMatrix();
				drawCharacter('S');
				glPopMatrix();
			}

			if (giCountBullet >= 25)
			{
				glPushMatrix();
				drawCharacter('H');
				glPopMatrix();
			}

			if (giCountBullet >= 40)
				drawCharacter('A');
	
			if (giCountBullet >= 55)
			{
				glPushMatrix();
				drawCharacter('D');
				glPopMatrix();
			}
	
			if (giCountBullet >= 70)
			{
				glPushMatrix();
				drawCharacter('E');
				glPopMatrix();
			}

			if (giCountBullet >= 85)
			{
				glPushMatrix();
				drawCharacter('R');
				glPopMatrix();
			}

			if (giCountBullet >= 100)
			{
				glPushMatrix();
				drawCharacter('S');
				glPopMatrix();
			}*/
			glPopMatrix();
		
		glScalef(0.7f, 0.7f, 0.7f);
		switch (gfCurrentCharacterIndex)
		{
		case 0:
			glPushMatrix();
				glTranslatef(MultipleBulletPosition[0].translateMultipleBulletX, MultipleBulletPosition[0].translateMultipleBulletY , MultipleBulletPosition[0].translateMultipleBulletZ);
				glRotatef(-100.0f, 0.0f, 1.0f, 0.0f);			
				drawBullet(-1.0f,1.0f,0.0f,1.0f);
				giCountBullet++;
			glPopMatrix();
			break;

		case 1:
			glPushMatrix();
			glTranslatef(MultipleBulletPosition[1].translateMultipleBulletX - 1.0f, MultipleBulletPosition[1].translateMultipleBulletY + 0.5f, MultipleBulletPosition[0].translateMultipleBulletZ + 2.0f);
			glRotatef(-100.0f, 0.0f, 1.0f, 0.0f);
			drawBullet(-1.0f, 1.0f, 0.0f, 1.0f);
			//giCountBullet++;
			glPopMatrix();

			glPushMatrix();
			glTranslatef(MultipleBulletPosition[1].translateMultipleBulletX - 2.0f, MultipleBulletPosition[1].translateMultipleBulletY - 1.0f, MultipleBulletPosition[0].translateMultipleBulletZ + 1.5f);
			glRotatef(-100.0f, 0.0f, 1.0f, 0.0f);
			drawBullet(-1.0f, 1.0f, 0.0f, 1.0f);
			//giCountBullet++;
			glPopMatrix();


		case 2:
			glPushMatrix();
				glTranslatef(MultipleBulletPosition[2].translateMultipleBulletX - 1.5f, MultipleBulletPosition[2].translateMultipleBulletY - 0.8f, MultipleBulletPosition[2].translateMultipleBulletZ - 2.5f);
				glRotatef(-100.0f, 0.0f, 1.0f, 0.0f);
				drawBullet(-1.0f, 1.0f, 0.0f, 1.0f);
				//giCountBullet++;
			glPopMatrix();
			break;

		case 3:
			glPushMatrix();
			glTranslatef(MultipleBulletPosition[2].translateMultipleBulletX - 2.5f, MultipleBulletPosition[2].translateMultipleBulletY - 1.3f, MultipleBulletPosition[2].translateMultipleBulletZ + 3.0f);
			glRotatef(-100.0f, 0.0f, 1.0f, 0.0f);
			drawBullet(-1.0f, 1.0f, 0.0f, 1.0f);
			//giCountBullet++;
			glPopMatrix();
			break;

		case 4:
			glPushMatrix();
			glTranslatef(MultipleBulletPosition[2].translateMultipleBulletX - 2.3f, MultipleBulletPosition[2].translateMultipleBulletY - 1.3f, MultipleBulletPosition[2].translateMultipleBulletZ - 1.0f);
			glRotatef(-100.0f, 0.0f, 1.0f, 0.0f);
			drawBullet(-1.0f, 1.0f, 0.0f, 1.0f);
			//giCountBullet++;
			glPopMatrix();
			break;


		case 5:
			glPushMatrix();
			glTranslatef(MultipleBulletPosition[2].translateMultipleBulletX - 3.5f, MultipleBulletPosition[2].translateMultipleBulletY - 1.3f, MultipleBulletPosition[2].translateMultipleBulletZ + 1.0f);
			glRotatef(-100.0f, 0.0f, 1.0f, 0.0f);
			drawBullet(-1.0f, 1.0f, 0.0f, 1.0f);
			//giCountBullet++;
			glPopMatrix();
			break;
		}
		 
	}
}

void updateMultipleBulletFire(void)
{
	
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			if (MultipleBulletPosition[i].translateMultipleBulletX <= 10.0f)
				MultipleBulletPosition[i].translateMultipleBulletX += 2.0f;
			else
				MultipleBulletPosition[i].translateMultipleBulletX = -10.0f;
			break;

		case 1:
			if (MultipleBulletPosition[i].translateMultipleBulletX <= 10.5f)
				MultipleBulletPosition[i].translateMultipleBulletX += 2.2f;
			else
				MultipleBulletPosition[i].translateMultipleBulletX = -10.0f;
			break;

		case 2:
			if (MultipleBulletPosition[i].translateMultipleBulletX <= 9.5f)
				MultipleBulletPosition[i].translateMultipleBulletX += 2.5f;
			else
				MultipleBulletPosition[i].translateMultipleBulletX = -10.0f;
			break;
		
		case 3:
			if (MultipleBulletPosition[i].translateMultipleBulletX <= 10.3f)
				MultipleBulletPosition[i].translateMultipleBulletX += 3.0f;
			else
				MultipleBulletPosition[i].translateMultipleBulletX = -10.0f;
			break;
		}//switch
	}//for
}//updateMultipleBulletFire

		
	