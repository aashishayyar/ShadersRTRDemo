#pragma once

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define PI 3.1415926535898

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include<math.h>

//function prototype
void initialize(void);
void uninitialize(void);
void display();
void update();

//function prototype
void resize(int, int);
void ToggleFullscreen(void);
void uninitialize(void);

// methods to draw sword
void drawSword();
void drawCircleForSwordHandle();


