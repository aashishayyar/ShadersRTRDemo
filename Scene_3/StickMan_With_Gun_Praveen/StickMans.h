#include <windows.h>
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

float gbStickWidth = 1.0f;
float gbStickHeight = 1.0f;

float gfSpeed = 0.1f;
float gfTranslateX = -SCREEN_X;

// Below 3 variables are use for the logic of walking man.
bool gbOneLeg[4] = { true, false, false, false }; // 1 for Left and 2 for Right
bool gbIsLeftLeg[4] = { false, false, false, false };
bool gbIsLeftArm[4] = { false, false, false, false };

float body[4] = { 0 };
float lNeck[4] = { -30, -25, -20, -15 };
float rNeck[4] = { 0 };
float lElbow[4] = { 45, 45, 45, 45 };
float rElbow[4] = { 45, 45, 45, 45 };

float lHip[4] = { 20, 15, 10, 5 };
float rHip[4] = { 0 , 5, 10, 15 };
float lKnee[4] = { -40, -30, -20, -10 };
float rKnee[4] = { 0 };

float lAnkle[4] = { 90, 90, 90, 90 };
float rAnkle[4] = { 90, 90, 90, 90 };

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
