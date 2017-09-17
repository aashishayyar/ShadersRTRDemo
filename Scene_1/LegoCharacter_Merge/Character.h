#include "Main.h"

// Functtion prototypes for generic lego character
void updateNormalWalk(int);
void update();
void DrawCircle(float);
void DrawSquare(float, float, float, float, float);
void DrawCubiod(float, float);
void DrawFace();
void DrawNeck();
void DrawCylinder(float, float);
void DrawJoints(float, float);
void DrawWrist(float, float);
void DrawBiceps(float, float);
void DrawForeArm(float, float);
void DrawHead(int);
void DrawChest();
void DrawHand(int, int);
void DrawThigh();
void DrawFoot();
void DrawLeg(int, int);
void DrawLegSeparation();

// Variables for generic lego character
float gfFaceHeight = 1.5f;
float gfFaceWidth = 0.8f;
float gfNeckHeight = 1.7f;
float gfNeckWidth = 0.5f;
float gfArmHeight = 1.0f;
float gfArmWidth = 0.25f;
float gfChestUpperWidth = 1.0f;
float gfChestLowerWidth = 1.3f;
float gfChestWidth = 0.7f;
float gfChestHeight = 2.2f;

float gfLegWidth = 0.5f;
float gfLegHeight = 1.2f;
float gfLegCylHeight = 1.0f;
float gfLegCylRadius = 0.75f;

float gfFootHeight = 0.35f;
float gfFootWidth = 0.5f;
float gfFootLength = 0.65f;

int i = 0;		// used for for-loop during lego character rendering
GLUquadric *quadric = NULL;

float gfSpeed = 0.5f;
float gfTranslateX = 0.0f;
float gfTranslateY = 0.0f;

float gbAngle = 0.0f;

float lArm[4] = { 30, 70, 30, 70 };
int giLArmDirection[4] = { 1,1,1,1 };

float rArm[4] = { 70, 30, 70, 30 };
int giRArmDirection[4] = { 1,1,1,1 };

float lLeg[4] = { 20, -20, 20, -20 };
int giLLegDirection[4] = { 1,1,1,1 };

float rLeg[4] = { -20 , 20, -20, 20 };
int giRLegDirection[4] = { 1,1,1,1 };


//******************* LUCA BRACY RELATED FUNCTION PROTOTYPES *******************//

// chest design function prototype for luca bracy
void DrawChestDesign_LucaBracy(GLfloat topX, GLfloat topZ);

// face design function prototype for luca bracy
void DrawFaceDesign_LucaBracy(GLfloat topX, GLfloat topZ);

void DrawArcUsingGL_POINTS_LucaBracy(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat r, GLfloat startAngle, GLfloat endAngle, GLfloat pointSize);
void DrawSphere_LucaBracy(GLfloat, GLint, GLint);

//******************* LUCA BRACY RELATED VARIABLES *******************//

// Eyebrow
GLfloat lb_eyebrowRadius = 0.5f;
GLfloat lb_eyebrowThickness = 3.0f;
GLfloat lb_eyebrowStartAngle = 1.17f;
GLfloat lb_eyebrowEndAngle = 1.75f;

// Mustache
GLfloat lb_mustacheRadius = 0.8f;
GLfloat lb_mustacheThickness = 2.0f;
GLfloat lb_mustacheStartAngle = 1.3f;
GLfloat lb_mustacheEndAngle = 1.8f;