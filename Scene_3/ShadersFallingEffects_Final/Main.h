#pragma once
/**********************************************************************************
Description -> v1.0 :		 Normal 3D bullet drawn Header file
Priyanka Bhasme
************************************************************************************/

float anglePyramid, angleRect, angleDetla;
int rotationsCount = 10000;
float gwSideofTriangle = 2.0f;
bool gbFullScreen, gbEscapeKeyIsPressed, gbActiveWindow = false;
bool gbDone;


// additional vars
static float rotateSingleBullet = 0;
static int extra1 = 0;
static int extra2 = 0;
float zShift = 0.0;
float leftShift = -5.0;
float xLShift = 0.0;//6.0;
float xTest = -8.0;

// for changing position of whole 'Shaders'
float xOriginalCord = 0.0;
float yOriginalCord = 0.0;
float zOriginalCord = -8.0;   // this is the distance between camera and the characters

							  // structure to hold bullets co-ordinates
typedef struct bullCords {
	float xCord;
	float yCord;
	float zCord;
	float bulletScale;
} bulletData;

// bullets spaced for character 'S'
bulletData positionS[18] = {
	{ -4.6, 1.5, -3.0, 0.2 },
	{ -4.5, 1.7, -1.0, 0.3 },
	{ -4.8, 2.0, -1.0, 0.25 },
	{ -4.8, 1.7, -2.5, 0.3 },
	{ -4.8, 1.6, -0.5, 0.4 },
	{ -4.7, 1.2, 0.0, 0.3 },
	{ -5.2, 1.0, -0.4, 0.35 },
	{ -5.8, 0.7, -1.0, 0.4 },
	{ -4.9, 0.35, 0.0, 0.3 },
	{ -5.0, 0.1, -0.5, 0.4 },
	{ -4.3, -0.1, 0.2, 0.4 },
	{ -4.6, -0.4, 0.0, 0.45 },
	{ -5.15, -0.75, -0.7, 0.35 },
	{ -5.5, -1.0, -1.0, 0.4 },
	{ -6.4, -1.5, -2.0, 0.4 },
	{ -6.5, -1.75, -1.7, 0.25 },
	{ -6.8, -2.0, -1.8, 0.2 },
	{ -6.45, -2.05, -1.0, 0.15 }
};

// bullets spaced for character 'H'
bulletData positionH[13] = {
	{ -3.0, 0.65, -1.0, 0.4 },
	{ -2.5, 0.25, 0.5, 0.3 },
	{ -2.85, 0.0, -0.5, 0.4 },
	{ -2.35, -0.3, 1.0, 0.3 },
	{ -2.8, -0.7, -0.4, 0.35 },
	{ -2.35, -0.9, 1.0, 0.35 },
	{ -4.0, 0.65, -1.0, 0.4 },
	{ -3.4, 0.25, 0.3, 0.3 },
	{ -3.8, -0.05, -0.5, 0.35 },
	{ -3.35, -0.3, 0.5, 0.3 },
	{ -3.75, -0.65, -0.4, 0.35 },
	{ -3.35, -0.9, 0.5, 0.4 },
	{ -2.6, -0.2, 1.5, 0.3 }
};

// bullets spaced for character 'A'
bulletData positionA[15] = {
	{ -1.0, 0.5, -0.0, 0.35 },
	{ -1.1, 0.2, -1.5, 0.5 },
	{ -0.9, -0.2, 0.5, 0.35 },
	{ -0.9, -0.1, -2.0, 0.2 },
	{ -0.85f, -0.55, 0.5, 0.35 },
	{ -1.0, -1.0, -1.0, 0.5 },
	{ -0.7, -0.9, 1.0, 0.2 },
	{ -2.5, 0.1, -2.5, 0.5 },
	{ -1.8, -0.25, 0.5, 0.3 },
	{ -2.15, -0.65, -1.0, 0.4 },
	{ -1.65, -0.8, 1.0, 0.3 },
	{ -2.2, 0.5, -1.5, 0.4 },
	{ -2.0, 0.8, -3.0, 0.65 },
	{ -1.5, -0.3, 0.5, 0.3 },
	{ -1.6, -0.4, -2.5, 0.5 }
};

// bullets spaced for character 'D'
bulletData positionD[16] = {
	{ -0.3, 0.7, -1.2, 0.5 },
	{ 0.12, 0.6, -0.5, 0.35 },
	{ 0.45, 0.4, 1.0, 0.4 },
	{ 0.75, 0.3, 0.0, 0.3 },
	{ 1.1, 0.0, -2.5, 0.55 },
	{ 0.8, -0.3, 0.2, 0.3 },
	{ 0.6, -0.5, 1.8, 0.3 },
	{ 0.45, -0.85, 0.0, 0.3 },
	{ 0.2, -1.0, -0.8, 0.45 },
	{ -0.2, -1.0, 0.0, 0.35 },
	{ 0.2, -1.0, -0.8, 0.45 },
	{ 0.2, -1.0, -0.8, 0.45 },
	{ -0.2, -0.8, -0.0, 0.2 },
	{ -0.2, -0.4, 2.0, 0.3 },
	{ -0.25, -0.2, -1.0, 0.4 },
	{ -0.2, 0.2, 1.0, 0.4 }
};

// bullets spaced for character 'E'
bulletData positionE[12] = {
	{ 2.0, 0.7, -2.2, 0.5 },
	{ 2.0, 0.6, -0.2, 0.3 },
	{ 2.5, 0.6, -1.0, 0.4 },
	{ 1.9, 0.3, -2.0, 0.4 },
	{ 1.35, -0.1, 1.0, 0.35 },
	{ 1.35, -0.1, 2.5, 0.2 },
	{ 2.0, -0.1, 1.0, 0.3 },
	{ 2.1, -0.75, -3.0, 0.55 },
	{ 1.4, -0.9, 0.3, 0.35 },
	{ 1.6, -0.8, 0.6, 0.28 },
	{ 2.0, -0.9, 0.0, 0.3 },
	{ 3.0, -1.2, -2.8, 0.5 }
};

// bullets spaced for character 'R'
bulletData positionR[16] = {
	{ 3.3, 0.6, -0.8, 0.4 },
	{ 3.8, 0.6, -1.0, 0.3 },
	{ 3.8, 0.35, -0.2, 0.3 },
	{ 4.2f, 0.03, -1.0, 0.3 },
	{ 3.8f, -0.2, -0.5, 0.3 },
	{ 3.9, -0.4, -1.5, 0.3 },
	{ 4.4, -0.7, -2.0, 0.35 },
	{ 3.7, -0.85, 0.0, 0.3 },
	{ 4.5, -1.3, -1.3, 0.25 },
	{ 2.4, 0.15, 1.5, 0.25 },
	{ 3.5, -0.1, -1.5, 0.4 },
	{ 2.0, -0.25, 2.5, 0.2 },
	{ 3.7, -0.8, -2.0, 0.4 },
	{ 2.95, -0.95, 0.0, 0.35 },
	{ 3.5, -1.18, 1.0, 0.18 },
	{ 5.1, -1.9, -2.0, 0.2 }
};

// bullets spaced for character 's'
bulletData positionLastS[11] = {
	{ 5.9, 0.5, -0.8, 0.2 },
	{ 5.5, 0.6, -0.6, 0.3 },
	{ 4.8, 0.52, 0.0, 0.3 },
	{ 2.8, 0.22, 3.0, 0.2 },
	{ 4.8, 0.05, -0.5, 0.35 },
	{ 5.1, -0.1, -0.6, 0.4 },
	{ 5.5, -0.3, -0.4, 0.3 },
	{ 4.0, -0.43, 2.0, 0.2 },
	{ 6.75, -1.1, -2.5, 0.4 },
	{ 5.2, -1.1, -0.6, 0.3 },
	{ 4.0, -0.95, 1.0, 0.2 }
};


/*=== PRaveens Falling merge====================*/

bool _isTOstartSlowMotion = false;

typedef struct {

	GLUquadric *_pGLUBullets = nullptr;

	GLfloat _BulletStopPosition;

	GLboolean _IsBulletFalling;

	GLfloat _BulletBounce;
	GLfloat _BulletSpeed;

	GLfloat _BulletPositionX;
	GLfloat _BulletFallingStartPositionY;
	GLfloat _BulletDepthZ;
	GLfloat  _bulletScale;
	GLfloat _BullletAngle;

	GLfloat _BulletIncrementalAngle;

}FALLING_BULLETS_;

const int _s = 18, h = 13, a = 15, d = 16, e = 12, r = 16, s_ = 11;
int const MAX_FALLING_BULLETS_ = (_s + h + a + d + e + r + s_);
FALLING_BULLETS_ falling_bullets_[MAX_FALLING_BULLETS_];


void InitBullets();
void FallNow_();
float moveBack=3;
float goingUpSpeed = 0.095f;
float goingDownSpeed = 0.1f;
/*===================*/

