#include<windows.h>
#include<stdio.h>
#include<gl/GL.h>
#include <gl/GLU.h>
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <Template.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "glu32.lib")

// Prototype of WndProc declared globally
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void ResetModelView();
void DrawStickyMan();
void DrawHead();
void DrawVentralBody();
void DrawCylinder(GLfloat, GLfloat, GLfloat, GLint, GLint);
void DrawLeftArm();
void DrawRightArm();
void DrawRightLeg();
void DrawLeftLeg();

// Global Variable Declaration
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbActiveWindow = false;
bool gbEscapeKeyIsPressed = false;
bool gbFullScreen = false;

GLUquadric *stickyManQuadric = NULL;

// main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// function prototype

	void display(void);
	void initialize(void);
	void uninitialize(void);

	// Variable Declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("RTR - OGL Using Double Buffer");
	bool bDone = false;
	int iWidth;
	int iHeight;

	// code
	// initializing members of struct WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, NULL);
	wndclass.hCursor = LoadCursor(hInstance, NULL);
	wndclass.hIconSm = LoadIcon(hInstance, NULL);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;

	// Registering Class
	RegisterClassEx(&wndclass);

	// Retrive Width
	iWidth = GetSystemMetrics(SM_CXSCREEN);

	// Retrive Height
	iHeight = GetSystemMetrics(SM_CYSCREEN);

	// Create Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szClassName,
		TEXT("Sticky Man"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		((iWidth - WIN_WIDTH) / 2),
		((iHeight - WIN_HEIGHT) / 2),
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	// Initialize
	initialize();

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// Message Loop
	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				if (gbEscapeKeyIsPressed == true)
					bDone = true;
				display();
			}
		}
	}

	uninitialize();
	return((int)msg.wParam);
}

// WndProc
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Function Prototype
	void resize(int, int);
	void ToggleFullScreen(void);
	void uninitialize(void);

	// Code
	switch (iMsg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0)
			gbActiveWindow = true;
		else
			gbActiveWindow = false;
		break;
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			gbEscapeKeyIsPressed = true;
			break;
		case 0x46:
			if (gbFullScreen == false)
			{
				ToggleFullScreen();
				gbFullScreen = true;
			}
			else
			{
				ToggleFullScreen();
				gbFullScreen = false;
			}
			break;
		default:
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	// Variable Declarations
	MONITORINFO mi;

	// Code
	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle && WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle & WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

void initialize(void)
{
	// Function Prototype
	void resize(int, int);

	// Variable Declaration
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	// Code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	// Initialization of pixel format descriptor
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	ghdc = GetDC(ghwnd);

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// To avoid aliasing
	glShadeModel(GL_SMOOTH);
	// To avoid distortion
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	resize(WIN_WIDTH, WIN_HEIGHT);
}

void display(void)
{
	// Prototype declaration
	void render();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ResetModelView();
	render();
	SwapBuffers(ghdc);
}

// Reset Model-View matrix
void ResetModelView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// render the scene
void render()
{
	// translate view matrix in negative z axis direction(i.e far in terms of viewing volume)
	glTranslatef(0.0f, 0.0f, -4.0f);

	// push matrix for translation of view matrix in z axis direction
	glPushMatrix();

	DrawStickyMan();

	// pop matrix for translation of view matrix in z axis direction
	glPopMatrix();
}

// start drawing sticky man
void DrawStickyMan()
{
	DrawHead();
	DrawVentralBody();
}

// draw head using GL_TRIANGLE_FAN
void DrawHead()
{
	glColor3f(stickyManColor[0], stickyManColor[1], stickyManColor[2]);
	
	// translate head of sticky man in positive X axis direction
	glTranslatef(headTransX, 0.0f, 0.0f);

	// push matrix for head transformation
	glPushMatrix();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(headCenterX, headCenterY, headCenterZ);	// central point for all triangle fans
	
	// loop through to create headNumberOfSides triangle fans
	for (GLfloat i = 0.0f; i <= headNumberOfSides; i=i+1.0f)
	{
		GLfloat X = headCenterX + (headRadius*cos(i*doublePI / headNumberOfSides));
		GLfloat Y = headCenterY + (headRadius*sin(i*doublePI / headNumberOfSides));
		GLfloat Z = headCenterZ;
		glVertex3f(X, Y, Z);
	}
	glEnd();

	if (headTransX <= 1.0f)
	{
		// increase translation of head
		headTransX = headTransX + 0.0003f;
	}
}

// Draw Ventral Body
void DrawVentralBody()
{
	// set how the object will get filled (i.e by point, line or solid) and faces which need to fill (i.e only front, only back or both)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// translate ventral body respective to head
	glTranslatef(headCenterX, (headCenterY-0.2f), headCenterZ);

	// By default, gluCylinder draws a cylinder oriented along the z axis
	// and that's why we will rotate it around X axis by 90 degree
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	// push matrix for ventral body transformation
	glPushMatrix();

	DrawCylinder(vbBase, vbTop, vbHeight, vbSlices, vbStacks);

	DrawLeftArm();

	// pop matrix for ventral body transformation
	glPopMatrix();

	DrawRightArm();

	// pop matrix for ventral body transformation
	glPopMatrix();

	DrawRightLeg();

	// pop matrix for ventral body transformation
	glPopMatrix();

	DrawLeftLeg();
}

// Draw cylinder
void DrawCylinder(GLfloat vbBase, GLfloat vbTop, GLfloat vbHeight, GLint vbSlices, GLint vbStacks)
{
	// The base OpenGL library provides support only for modeling and rendering simple points, lines, and convex filled polygons.
	// The GLU also provides routines to model and render tessellated, polygonal approximations for a variety of 2D and 3D shapes(spheres, cylinders, disks, and parts of disks),
	// which can be calculated with quadric equations
	stickyManQuadric = gluNewQuadric();
	gluCylinder(stickyManQuadric, vbBase, vbTop, vbHeight, vbSlices, vbStacks);
}

// Draw left arm
void DrawLeftArm()
{
	//--------------------------------------------------------
	// Draw left shoulder
	//--------------------------------------------------------

	// rotate left shoulder around it's y axis
	glRotatef(vbStartLeftShoulderAngle, 0.0f, 1.0f, 0.0f);

	// push matrix for left shoulder transformation
	glPushMatrix();

	DrawCylinder(vbBase, vbTop, vbShoulderLength, vbSlices, vbStacks);

	// pop matrix for left shoulder transformation
	glPopMatrix();

	//--------------------------------------------------------
	// Draw left elbow
	//--------------------------------------------------------

	// translate left elbow to end of left shoulder in left shoulder's z axis direction 
	glTranslatef(0.0f, 0.0f, vbShoulderLength);

	// rotate left elbow around it's y axis direction
	glRotatef(vbStartLeftElbowAngle, 0.0f, 1.0f, 0.0f);

	// push matrix for left elbow transformation
	glPushMatrix();

	DrawCylinder(vbBase, vbTop, (vbShoulderLength+0.1f), vbSlices, vbStacks);

	// start animation of moving hand to fire bullet
	if (headTransX > 1.0f) {
		if (vbStartLeftShoulderAngle < vbStartLeftShoulderAngleLimit)
			vbStartLeftShoulderAngle = vbStartLeftShoulderAngle + 0.01f;
		if (vbStartLeftElbowAngle < vbStartLeftElbowAngleLimit)
			vbStartLeftElbowAngle = vbStartLeftElbowAngle + 0.01f;
	}

	// pop matrix for left elbow transformation
	glPopMatrix();
}

// Draw right arm
void DrawRightArm()
{
	//--------------------------------------------------------
	// Draw right shoulder
	//--------------------------------------------------------

	// rotate right shoulder around it's y axis
	glRotatef(310.0f, 0.0f, 1.0f, 0.0f);

	// push matrix for right shoulder transformation
	glPushMatrix();

	DrawCylinder(vbBase, vbTop, vbShoulderLength, vbSlices, vbStacks);

	// pop matrix for right shoulder transformation
	glPopMatrix();

	//--------------------------------------------------------
	// Draw right elbow
	//--------------------------------------------------------

	// translate right elbow to end of right shoulder in right shoulder's z axis direction
	glTranslatef(0.0f, 0.0f, vbShoulderLength);

	// rotate right elbow around it's y axis
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

	// push matrix for right elbow transformation
	glPushMatrix();

	DrawCylinder(vbBase, vbTop, (vbShoulderLength + 0.1f), vbSlices, vbStacks);

	// pop matrix for right elbow transformation
	glPopMatrix();
}

void DrawRightLeg()
{
	//--------------------------------------------------------
	// Draw right thigh
	//--------------------------------------------------------

	// translate right thigh at end of ventral body
	glTranslatef(headCenterX, -0.15f, headCenterZ);

	// then rotate thigh around x axis in 90 degree same as ventral body
	// because by default, gluCylinder draws a cylinder oriented along the z axis
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	// to look proper thigh , rotate around it's y axis
	glRotatef(310.0f, 0.0f, 1.0f, 0.0f);

	// push matrix for left thigh transformation
	glPushMatrix();

	DrawCylinder(vbBase, vbTop, vbThighLength, vbSlices, vbStacks);

	// pop matrix for left thigh transformation
	glPopMatrix();

	//--------------------------------------------------------
	// Draw right leg
	//--------------------------------------------------------

	// translate right leg at end of right thigh
	glTranslatef(0.0f, 0.0f, vbThighLength);

	// rotate right leg around it's y axis
	glRotatef(50.0f, 0.0f, 1.0f, 0.0f);

	// push matrix for left thigh transformation
	glPushMatrix();

	DrawCylinder(vbBase, vbTop, (vbThighLength + 0.1f), vbSlices, vbStacks);

	// pop matrix for left thigh transformation
	glPopMatrix();
}

void DrawLeftLeg()
{
	//--------------------------------------------------------
	// Draw left thigh
	//--------------------------------------------------------

	// translate left thigh at end of ventral body
	glTranslatef(headCenterX, -0.15f, headCenterZ);

	// then rotate left thigh around x axis in 90 degree same as ventral body
	// because by default, gluCylinder draws a cylinder oriented along the z axis
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	// translate left thigh in x axis direction
	glTranslatef(headTransX, 0.0f, 0.0f);

	// to look proper thigh, rotate left thigh around y axis direction
	glRotatef(50.0f, 0.0f, 1.0f, 0.0f);

	// push matrix for left thigh transformation
	glPushMatrix();

	DrawCylinder(vbBase, vbTop, vbThighLength, vbSlices, vbStacks);

	// pop matrix for left thigh transformation
	glPopMatrix();

	//--------------------------------------------------------
	// Draw left leg
	//--------------------------------------------------------

	// translate left leg at end of left thigh
	glTranslatef(0.0f, 0.0f, vbThighLength);

	// rotate left leg around it's y axis
	glRotatef(310.0f, 0.0f, 1.0f, 0.0f);

	// push matrix for left thigh transformation
	glPushMatrix();

	DrawCylinder(vbBase, vbTop, (vbThighLength + 0.1f), vbSlices, vbStacks);

	// pop matrix for left thigh transformation
	glPopMatrix();
}

void resize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void uninitialize(void)
{
	if (gbFullScreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(ghrc);
	ghrc = NULL;

	ReleaseDC(ghwnd, ghdc);
	ghdc = NULL;

	DestroyWindow(ghwnd);
	ghwnd = NULL;

	gluDeleteQuadric(stickyManQuadric);
}