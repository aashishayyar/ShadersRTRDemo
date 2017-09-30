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
extern float gfBulletTranslateX;
bool CameraSteady = false;

#define INITIAL_NEO_TRANSLATE_X   50.0f
#define INITIAL_NEO_TRANSLATE_Y    6.0f
#define INITIAL_NEO_TRANSLATE_Z  -50.0f

#define NEO_COLOR_RED   0.0f
#define NEO_COLOR_GREEN 0.0f
#define NEO_COLOR_BLUE  0.0f

GLfloat gfNeoRotate_Y = 180.0f;

float gbStickWidth  = 1.0f;
float gbStickHeight = 1.0f;

int giNeoDirection = 1;

float gfNeoTheta = 0.0f;
float gfNeoSpeed	  = 1.5f;
float gfTranslateNeoX = 0.0f;
float gfTranslateNeoY = 0.0f;
float gfTranslateNeoZ = 0.0f;
// Below 3 variables are use for the logic of walking man.
bool gbOneLeg = true; // 1 for Left and 2 for Right
bool gbIsLeftLeg = false;
bool gbIsLeftArm = false;

float body = 0;
float lNeck = -30;
float rNeck = 0;
float lElbow = 45;
float rElbow = 45;

float lHip = 20;
float rHip = 0;
float lKnee = -40;
float rKnee = 0;

float lAnkle = 90;
float rAnkle = 90;

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