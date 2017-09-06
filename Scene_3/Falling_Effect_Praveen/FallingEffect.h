#include<gl/GL.h>
#include<GL/glu.h>


typedef struct {

	GLUquadric *_pGLUBullets = nullptr;

	GLfloat _BulletStopPosition;
	
	GLboolean _IsBulletFalling;

	GLfloat _BulletBounce;
	GLfloat _BulletSpeed;

	GLfloat _BulletPositionX;
	GLfloat _BulletFallingStartPositionY; 
	GLfloat _BulletDepthZ;

	GLfloat _BulletR;
	GLfloat _BulletG;
	GLfloat _BulletB;

}FALLING_BULLETS;

int const MAX_FALLING_BULLETS = 15;
FALLING_BULLETS falling_bullets[MAX_FALLING_BULLETS];



void InitializeFallingBulletsEffects()
{

	falling_bullets[0]._pGLUBullets = gluNewQuadric();
	falling_bullets[0]._BulletStopPosition = -1.18f;
	falling_bullets[0]._IsBulletFalling = true;
	falling_bullets[0]._BulletBounce = -0.71f;
	falling_bullets[0]._BulletSpeed = 0.053f;
	falling_bullets[0]._BulletPositionX = 0.0f;
	falling_bullets[0]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[0]._BulletDepthZ = -3.0f;
	falling_bullets[0]._BulletR = 1.0f;
	falling_bullets[0]._BulletG = 1.0f;
	falling_bullets[0]._BulletB = 1.0f;



	falling_bullets[1]._pGLUBullets = gluNewQuadric();
	falling_bullets[1]._BulletStopPosition = -1.18f;
	falling_bullets[1]._IsBulletFalling = true;
	falling_bullets[1]._BulletBounce = -0.89f;
	falling_bullets[1]._BulletSpeed = 0.056f;
	falling_bullets[1]._BulletPositionX = 0.29f;
	falling_bullets[1]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[1]._BulletDepthZ = -3.0f;
	falling_bullets[1]._BulletR = 1.0f;
	falling_bullets[1]._BulletG = 0.0f;
	falling_bullets[1]._BulletB = 0.0f;



	falling_bullets[2]._pGLUBullets = gluNewQuadric();
	falling_bullets[2]._BulletStopPosition = -1.18f;
	falling_bullets[2]._IsBulletFalling = true;
	falling_bullets[2]._BulletBounce = -0.7f;
	falling_bullets[2]._BulletSpeed = 0.045f;
	falling_bullets[2]._BulletPositionX = 0.20f;
	falling_bullets[2]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[2]._BulletDepthZ = -3.0f;
	falling_bullets[2]._BulletR = 0.0f;
	falling_bullets[2]._BulletG = 1.0f;
	falling_bullets[2]._BulletB = 1.0f;



	falling_bullets[3]._pGLUBullets = gluNewQuadric();
	falling_bullets[3]._BulletStopPosition = -1.18f;
	falling_bullets[3]._IsBulletFalling = true;
	falling_bullets[3]._BulletBounce = -0.6f;
	falling_bullets[3]._BulletSpeed = 0.060f;
	falling_bullets[3]._BulletPositionX = 0.30f;
	falling_bullets[3]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[3]._BulletDepthZ = -3.0f;
	falling_bullets[3]._BulletR = 1.0f;
	falling_bullets[3]._BulletG = 0.0f;
	falling_bullets[3]._BulletB = 1.0f;




	falling_bullets[4]._pGLUBullets = gluNewQuadric();
	falling_bullets[4]._BulletStopPosition = -1.18f;
	falling_bullets[4]._IsBulletFalling = true;
	falling_bullets[4]._BulletBounce = -0.8f;
	falling_bullets[4]._BulletSpeed = 0.05f;
	falling_bullets[4]._BulletPositionX = 0.40f;
	falling_bullets[4]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[4]._BulletDepthZ = -3.0f;
	falling_bullets[4]._BulletR = 1.0f;
	falling_bullets[4]._BulletG = 1.0f;
	falling_bullets[4]._BulletB = 0.0f;


	falling_bullets[0]._pGLUBullets = gluNewQuadric();
	falling_bullets[0]._BulletStopPosition = -1.18f;
	falling_bullets[0]._IsBulletFalling = true;
	falling_bullets[0]._BulletBounce = -0.61f;
	falling_bullets[0]._BulletSpeed = 0.053f;
	falling_bullets[0]._BulletPositionX = 0.0f;
	falling_bullets[0]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[0]._BulletDepthZ = -3.0f;
	falling_bullets[0]._BulletR = 1.0f;
	falling_bullets[0]._BulletG = 1.0f;
	falling_bullets[0]._BulletB = 1.0f;



	falling_bullets[1]._pGLUBullets = gluNewQuadric();
	falling_bullets[1]._BulletStopPosition = -1.18f;
	falling_bullets[1]._IsBulletFalling = true;
	falling_bullets[1]._BulletBounce = -0.61f;
	falling_bullets[1]._BulletSpeed = 0.056f;
	falling_bullets[1]._BulletPositionX = -0.80f;
	falling_bullets[1]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[1]._BulletDepthZ = -3.0f;
	falling_bullets[1]._BulletR = 1.0f;
	falling_bullets[1]._BulletG = 0.0f;
	falling_bullets[1]._BulletB = 0.0f;



	falling_bullets[2]._pGLUBullets = gluNewQuadric();
	falling_bullets[2]._BulletStopPosition = -1.18f;
	falling_bullets[2]._IsBulletFalling = true;
	falling_bullets[2]._BulletBounce = -0.86f;
	falling_bullets[2]._BulletSpeed = 0.045f;
	falling_bullets[2]._BulletPositionX = 0.20f;
	falling_bullets[2]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[2]._BulletDepthZ = -3.0f;
	falling_bullets[2]._BulletR = 0.0f;
	falling_bullets[2]._BulletG = 1.0f;
	falling_bullets[2]._BulletB = 1.0f;



	falling_bullets[3]._pGLUBullets = gluNewQuadric();
	falling_bullets[3]._BulletStopPosition = -1.18f;
	falling_bullets[3]._IsBulletFalling = true;
	falling_bullets[3]._BulletBounce = -1.0f;
	falling_bullets[3]._BulletSpeed = 0.060f;
	falling_bullets[3]._BulletPositionX = 0.0f;
	falling_bullets[3]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[3]._BulletDepthZ = -3.0f;
	falling_bullets[3]._BulletR = 1.0f;
	falling_bullets[3]._BulletG = 0.0f;
	falling_bullets[3]._BulletB = 1.0f;




	falling_bullets[4]._pGLUBullets = gluNewQuadric();
	falling_bullets[4]._BulletStopPosition = -1.18f;
	falling_bullets[4]._IsBulletFalling = true;
	falling_bullets[4]._BulletBounce = -0.78f;
	falling_bullets[4]._BulletSpeed = 0.05f;
	falling_bullets[4]._BulletPositionX =- 0.40f;
	falling_bullets[4]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[4]._BulletDepthZ = -3.0f;
	falling_bullets[4]._BulletR = 1.0f;
	falling_bullets[4]._BulletG = 1.0f;
	falling_bullets[4]._BulletB = 0.0f;




	falling_bullets[5]._pGLUBullets = gluNewQuadric();
	falling_bullets[5]._BulletStopPosition = -1.18f;
	falling_bullets[5]._IsBulletFalling = true;
	falling_bullets[5]._BulletBounce = -0.82f;
	falling_bullets[5]._BulletSpeed = 0.053f;
	falling_bullets[5]._BulletPositionX = 0.2f;
	falling_bullets[5]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[5]._BulletDepthZ = -3.0f;
	falling_bullets[5]._BulletR = 1.0f;
	falling_bullets[5]._BulletG = 1.0f;
	falling_bullets[5]._BulletB = 1.0f;



	falling_bullets[6]._pGLUBullets = gluNewQuadric();
	falling_bullets[6]._BulletStopPosition = -1.18f;
	falling_bullets[6]._IsBulletFalling = true;
	falling_bullets[6]._BulletBounce = -0.6f;
	falling_bullets[6]._BulletSpeed = 0.056f;
	falling_bullets[6]._BulletPositionX = 0.02f;
	falling_bullets[6]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[6]._BulletDepthZ = -3.0f;
	falling_bullets[6]._BulletR = 1.0f;
	falling_bullets[6]._BulletG = 0.0f;
	falling_bullets[6]._BulletB = 0.0f;



	falling_bullets[7]._pGLUBullets = gluNewQuadric();
	falling_bullets[7]._BulletStopPosition = -1.18f;
	falling_bullets[7]._IsBulletFalling = true;
	falling_bullets[7]._BulletBounce = -0.74f;
	falling_bullets[7]._BulletSpeed = 0.045f;
	falling_bullets[7]._BulletPositionX = 0.23f;
	falling_bullets[7]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[7]._BulletDepthZ = -3.0f;
	falling_bullets[7]._BulletR = 0.0f;
	falling_bullets[7]._BulletG = 1.0f;
	falling_bullets[7]._BulletB = 1.0f;



	falling_bullets[8]._pGLUBullets = gluNewQuadric();
	falling_bullets[8]._BulletStopPosition = -1.18f;
	falling_bullets[8]._IsBulletFalling = true;
	falling_bullets[8]._BulletBounce = -0.9f;
	falling_bullets[8]._BulletSpeed = 0.060f;
	falling_bullets[8]._BulletPositionX = 0.63f;
	falling_bullets[8]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[8]._BulletDepthZ = -3.0f;
	falling_bullets[8]._BulletR = 1.0f;
	falling_bullets[8]._BulletG = 0.0f;
	falling_bullets[8]._BulletB = 1.0f;




	falling_bullets[9]._pGLUBullets = gluNewQuadric();
	falling_bullets[9]._BulletStopPosition = -1.18f;
	falling_bullets[9]._IsBulletFalling = true;
	falling_bullets[9]._BulletBounce = -0.89f;
	falling_bullets[9]._BulletSpeed = 0.05f;
	falling_bullets[9]._BulletPositionX = 0.80f;
	falling_bullets[9]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[9]._BulletDepthZ = -3.0f;
	falling_bullets[9]._BulletR = 1.0f;
	falling_bullets[9]._BulletG = 1.0f;
	falling_bullets[9]._BulletB = 0.0f;



	falling_bullets[10]._pGLUBullets = gluNewQuadric();
	falling_bullets[10]._BulletStopPosition = -1.18f;
	falling_bullets[10]._IsBulletFalling = true;
	falling_bullets[10]._BulletBounce = -0.72f;
	falling_bullets[10]._BulletSpeed = 0.053f;
	falling_bullets[10]._BulletPositionX = 0.0f;
	falling_bullets[10]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[10]._BulletDepthZ = -3.0f;
	falling_bullets[10]._BulletR = 1.0f;
	falling_bullets[10]._BulletG = 1.0f;
	falling_bullets[10]._BulletB = 1.0f;



	falling_bullets[11]._pGLUBullets = gluNewQuadric();
	falling_bullets[11]._BulletStopPosition = -1.18f;
	falling_bullets[11]._IsBulletFalling = true;
	falling_bullets[11]._BulletBounce = -0.75f;
	falling_bullets[11]._BulletSpeed = 0.056f;
	falling_bullets[11]._BulletPositionX = -0.38f;
	falling_bullets[11]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[11]._BulletDepthZ = -3.0f;
	falling_bullets[11]._BulletR = 1.0f;
	falling_bullets[11]._BulletG = 0.0f;
	falling_bullets[11]._BulletB = 0.0f;



	falling_bullets[12]._pGLUBullets = gluNewQuadric();
	falling_bullets[12]._BulletStopPosition = -1.18f;
	falling_bullets[12]._IsBulletFalling = true;
	falling_bullets[12]._BulletBounce = -0.85f;
	falling_bullets[12]._BulletSpeed = 0.045f;
	falling_bullets[12]._BulletPositionX = -0.30f;
	falling_bullets[12]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[12]._BulletDepthZ = -3.0f;
	falling_bullets[12]._BulletR = 0.0f;
	falling_bullets[12]._BulletG = 1.0f;
	falling_bullets[12]._BulletB = 1.0f;



	falling_bullets[13]._pGLUBullets = gluNewQuadric();
	falling_bullets[13]._BulletStopPosition = -1.18f;
	falling_bullets[13]._IsBulletFalling = true;
	falling_bullets[13]._BulletBounce = -0.8f;
	falling_bullets[13]._BulletSpeed = 0.060f;
	falling_bullets[13]._BulletPositionX = -0.30f;
	falling_bullets[13]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[13]._BulletDepthZ = -3.0f;
	falling_bullets[13]._BulletR = 1.0f;
	falling_bullets[13]._BulletG = 0.0f;
	falling_bullets[13]._BulletB = 1.0f;




	falling_bullets[14]._pGLUBullets = gluNewQuadric();
	falling_bullets[14]._BulletStopPosition = -1.18f;
	falling_bullets[14]._IsBulletFalling = true;
	falling_bullets[14]._BulletBounce = -0.9f;
	falling_bullets[14]._BulletSpeed = 0.05f;
	falling_bullets[14]._BulletPositionX = -0.40f;
	falling_bullets[14]._BulletFallingStartPositionY = 1.5f; //_TranslateY
	falling_bullets[14]._BulletDepthZ = -3.0f;
	falling_bullets[14]._BulletR = 1.0f;
	falling_bullets[14]._BulletG = 1.0f;
	falling_bullets[14]._BulletB = 0.0f;
}



void FallNow()
{
	for (auto i = 0; i < MAX_FALLING_BULLETS; i++)
	{

		glPushMatrix();

		/*Falling Down*/
		if (falling_bullets[i]._BulletFallingStartPositionY >= falling_bullets[i]._BulletStopPosition && falling_bullets[i]._IsBulletFalling)
		{
			//falling_bullets[i]._BulletSpeed = 0.3f;

			falling_bullets[i]._BulletFallingStartPositionY = falling_bullets[i]._BulletFallingStartPositionY - falling_bullets[i]._BulletSpeed;
		}
		/**/
		else
		{

			/*Going Up*/
			falling_bullets[i]._IsBulletFalling = false;

			if (falling_bullets[i]._BulletFallingStartPositionY <= falling_bullets[i]._BulletBounce)
			{
					falling_bullets[i]._BulletFallingStartPositionY = falling_bullets[i]._BulletFallingStartPositionY + falling_bullets[i]._BulletSpeed;
			}
			/**/
			else
			{
				/*Adjust bounce and Speed of bullet here*/
				falling_bullets[i]._IsBulletFalling = true;

				falling_bullets[i]._BulletBounce = falling_bullets[i]._BulletBounce - 0.08f; // adjust constant value to number of bounce

				//falling_bullets[i]._BulletSpeed = falling_bullets[i]._BulletSpeed + 0.01f; //adjust constant value to bullet bounce speed.
				/**/			
			}
		}



		/*Draw Bullets here
		* I have draw sphere instead of Bullets.
		*/
		glTranslatef(falling_bullets[i]._BulletPositionX, falling_bullets[i]._BulletFallingStartPositionY, falling_bullets[i]._BulletDepthZ);
		glColor3f(falling_bullets[i]._BulletR, falling_bullets[i]._BulletG, falling_bullets[i]._BulletB);
		gluSphere(falling_bullets[i]._pGLUBullets, 0.03f, 100.0f, 100.0f);
		/**/


		glPopMatrix();
	}

}