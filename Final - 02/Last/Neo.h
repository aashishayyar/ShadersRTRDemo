#pragma once
extern FILE *fp;

extern int objectsIteration;

bool NeoStage1 = true;
bool NeoStage2 = false;
bool NeoStage3 = false;
bool NeoStage4 = false;
bool NeoStage5 = false;
bool NeoStage6 = false;

extern bool Scene2;
extern int sceneIndex;

extern float gfBulletTranslateX;
bool CameraSteady = false;

#define INITIAL_NEO_TRANSLATE_X   50.0f
#define INITIAL_NEO_TRANSLATE_Y    6.0f
#define INITIAL_NEO_TRANSLATE_Z  -50.0f

#define NEO_COLOR_RED   0.0f
#define NEO_COLOR_GREEN 0.0f
#define NEO_COLOR_BLUE  0.0f

GLfloat gfNeoRotate_Y = 180.0f;

GLfloat gbStickWidth  = 1.0f;
GLfloat gbStickHeight = 1.0f;

int giNeoDirection = 1;

GLfloat gfNeoTheta = 0.0f;
GLfloat gfNeoSpeed	  = 2.5f;
GLfloat gfTranslateNeoX = 0.0f;
GLfloat gfTranslateNeoY = 0.0f;
GLfloat gfTranslateNeoZ = 0.0f;
// Below 3 variables are use for the logic of walking man.
bool gbOneLeg = true; // 1 for Left and 2 for Right
bool gbIsLeftLeg = false;
bool gbIsLeftArm = false;
bool gbHeadPosition = false;

GLfloat body = 0;
GLfloat lNeck = -30;
GLfloat rNeck = 0;
GLfloat lElbow = 45;
GLfloat rElbow = 45;

GLfloat lHip = 20;
GLfloat rHip = 0;
GLfloat lKnee = -40;
GLfloat rKnee = 0;

GLfloat lAnkle = 90;
GLfloat rAnkle = 90;

GLUquadric *quadric = NULL;

// it updates the angle of Hip, Knee and Neck to create the walking action
void updateNormalWalk();

// draws a single cylinder
void DrawCylinder(float height);

// draws sphere at the end of the cylinder
void DrawJoints(float height);

// wrapper to draw the cylinder and joints.
void DrawCylinderAndJoints(float height);

// draws different type of heads for different persons.
void DrawHead(float radius);

// Draws the complete stick man.
void DrawStickMan();
void dodgeBullet();

extern struct CameraPosition {
	GLfloat x ;
	GLfloat y ;
	GLfloat z ;
};

extern struct CameraPosition cameraPosition;
