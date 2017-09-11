#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define WIN_WIDTH 600
#define WIN_HEIGHT 600
#define SCREEN_X 10.0f

/******** PART OF TEMPLATE ********/

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//Prototype Of WndProc() declared Globally
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global variable declarations
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

/********* END OF TEMPLATE ***********/

bool gbActiveWindow = false;
bool gbEscapeKeyIsPressed = false;
bool gbFullscreen = false;

float gfSpeed = 0.5f;
float gfTranslateX = -35.0f;
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


GLUquadric *quadric = NULL;

// it updates the angle of Hip, Knee and Neck to create the walking action
void updateNormalWalk(int currentStickMan);

// global update which is been called to update the angles of all the stick man 
void update();

// draws a single cylinder
void DrawCylinder(float height);

// draws sphere at the end of the cylinder
void DrawJoints(float height);

// wrapper to draw the cylinder and joints.
void DrawCylinderAndJoints(float height);

// draws different type of heads for different persons.
void DrawHead(int currentStickMan, float radius);

// Draws the complete stick man.
void DrawStickMan(int currentStickMan);

