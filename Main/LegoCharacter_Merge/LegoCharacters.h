#include"Main.h"

GLfloat angle = 0.0f,nextRadius = 1.0f;
#define circle_points 1000


GLfloat gfFaceHeight = 1.5f;
GLfloat gfFaceWidth = 0.8f;
GLfloat gfNeckHeight = 1.7f;
GLfloat gfNeckWidth = 0.5f;
GLfloat gfArmHeight = 1.0f;
GLfloat gfArmWidth = 0.25f;
GLfloat gfChestUpperWidth = 1.0f;
GLfloat gfChestLowerWidth = 1.3f;
GLfloat gfChestWidth = 0.7f;
GLfloat gfChestHeight = 2.2f;

GLfloat gfLegWidth = 0.5f;
GLfloat gfLegHeight = 1.2f;
GLfloat gfLegCylHeight = 1.0f;
GLfloat gfLegCylRadius = 0.75f;

GLfloat gfFootHeight = 0.35f;
GLfloat gfFootWidth = 0.5f;
GLfloat gfFootLength = 0.65f;

GLfloat gfSpeed = 0.5f;
GLfloat gfTranslateX = -35.0f;
GLfloat gfTranslateY = 0.0f;

GLfloat gbAngle = 0.0f;

GLfloat lArm[4] = { 30, 70, 30, 70 };
int giLArmDirection[4] = { 1,1,1,1 };

GLfloat rArm[4] = { 70, 30, 70, 30 };
int giRArmDirection[4] = { 1,1,1,1 };

GLfloat lLeg[4] = { 20, -20, 20, -20 };
int giLLegDirection[4] = { 1,1,1,1 };

GLfloat rLeg[4] = { -20 , 20, -20, 20 };
int giRLegDirection[4] = { 1,1,1,1 };


GLUquadric *quadric = NULL;

// it updates the angle of Hip, Knee and Neck to create the walking action
void updateNormalWalk(int currentStickMan);

// global update which is been called to update the angles of all the stick man 
void update();

// draws a single cylinder
void DrawCylinder(GLfloat height);

// draws sphere at the end of the cylinder
void DrawJoints(GLfloat height);

// wrapper to draw the cylinder and joints.
void DrawCylinderAndJoints(GLfloat height);

// draws different type of heads for different persons.
void DrawHead(int currentStickMan, GLfloat radius);

// Draws the complete stick man.
void DrawStickMan(int currentStickMan);

