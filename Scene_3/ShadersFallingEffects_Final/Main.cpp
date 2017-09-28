/**********************************************************************************
Description -> v1.0 :		 Normal 3D bullet drawn
modified v2.0: Creates bullets of different sizes and at diferrent
location (with function)
modified v3.0: bullets are placed in 3D space so as to draw shape of
gsroupname "Shaders"
modified v4.0: Added x-axis shifting argument for characters
modified v5.0: Added more characters
modified v6.0: refined code with array of srtuctures for placing bullets
Key Controls -> s --> Rotate clockwise
d --> Rotate anticlockwise
r --> Rotate camera - actual video - uncomment gluLookAt() to make it work
p --> translate
Priyanka Bhasme
************************************************************************************/

// Header files
#include<Windows.h>
#include<gl\GL.h>
#include<stdio.h>
#include<gl\GLU.h>
#include<math.h>
#include"Main.h"

// Pragma
#pragma comment(lib, "opengl32.lib")
// we need this to link
#pragma comment(lib, "glu32.lib")

// macros declaration 
#define WINWIDTH 800
#define WINHEIGHT 800
// for calculating anlges
#define PI 3.1415926535898
// ask sir - how error goes when curly brackets are added????????????
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
DWORD dwStyle;

GLUquadric *quadric = NULL;

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIndtance, LPSTR lpszCmdLine, int nCmdShow)
{

	//function prototype
	void initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);

	//	variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTROGL");

	// code
	// initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	// make window color blue
	wndclass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register above class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("Bullets"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		0,
		0,
		WINWIDTH,
		WINHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	initialize();

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//Message Loop
	while (gbDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				gbDone = true;
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
					gbDone = true;
				update();
				display();

			}
		}
	}

	uninitialize();
	return((int)msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	// code
	//function prototype
	//void display(void);

	void resize(int, int);
	void ToggleFullscreen(void);
	void uninitialize(void);

	//code
	switch (iMsg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0)
			gbActiveWindow = true;
		else
			gbActiveWindow = false;
		break;
		/*case WM_PAINT:
		display();
		break;
		case WM_ERASEBKGND:
		return(0);*/
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CHAR:
		switch (wParam)
		{

		case 's':
			rotateSingleBullet += 0.5;
			if (rotateSingleBullet >= 360.0) {
				rotateSingleBullet = 0.0;
			}
			break;

		case 'd':
			rotateSingleBullet -= 0.5;
			if (rotateSingleBullet <= 0.0) {
				rotateSingleBullet = 360.0;
			}
			break;

		case 'x':
			//extra1 = (extra1 + 7) % 360;
			xTest += 0.05f;
			if (xTest >= 8.0) {
				xTest = 8.0;
			}
			break;

		case 'Z':
			//extra1 = (extra1 - 7) % 360;
			zShift += 0.5;
			if (zShift > 0.0) {
				zShift = -18.0;
				//zShift = -4.0;
			}
			break;

		case 'r':
			anglePyramid += 0.007f;
			if (anglePyramid >= 360) {
				anglePyramid = 0.0;
			}
			break;

		case 'q':
			void FallNow_();
			InitBullets();
			FallNow_();
			break;

		default:
			break;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			gbEscapeKeyIsPressed = true;
			break;

		case 0x46: //for 'f' or 'F'
			if (gbFullScreen == false)
			{
				ToggleFullscreen();
				gbFullScreen = true;
			}
			else
			{
				ToggleFullscreen();
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



void ToggleFullscreen(void)
{
	//variable declarations
	MONITORINFO mi;

	//code
	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
				gwSideofTriangle = 2.0;
			}
		}
		ShowCursor(FALSE);
	}

	else
	{
		//code
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		gwSideofTriangle = WINWIDTH;
		ShowCursor(TRUE);
	}
}



void initialize(void) {

	/**/

	void InitBullets();

	InitBullets();
	/**/
	
	//function prototypes
	void resize(int, int);

	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	//Initialization of pfd structure
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;  // change for 3d effect


	ghdc = GetDC(ghwnd);

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0) {

		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == false) {

		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	ghrc = wglCreateContext(ghdc);

	if (ghrc == NULL) {

		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;

	}

	if (wglMakeCurrent(ghdc, ghrc) == false) {

		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	// first OpenGL call
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// for 3D
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// could not get what difference it makes observed same thing. Ask Sir??
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // to avoid distortion due to perspective view
	glShadeModel(GL_SMOOTH);  // to avoid alaizing

	resize(WINWIDTH, WINHEIGHT);
}

void display(void) {

	void drawBullet(float xCord, float yCord, float zCord, float bulletScale);
	//void drawCharacter(void);
	void drawCharacter(byte bChar);
	void drawGraphPaper(void);
	//void drawCharacterTest(void);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // GL_DEPTH_BUFFER_BIT - For 3D
	glMatrixMode(GL_MODELVIEW);
	// comment out to remove graph
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -6.0);
	drawGraphPaper();


	// Necessary code starts here
	glLoadIdentity();

	gluLookAt(0.0, 0.0, zShift, 0.0f, 0.0f, -6.0f, 0.0f, 1.0f, 0.0f); // working properly
																	  //gluLookAt(cos(anglePyramid)*8.0, 0.0f, sin(anglePyramid)*8.0 -8.0, 0.0f, 0.0f, -8.0f, 0.0f, 1.0f, 0.0f); // actual video effect


																	  // draw SHADERS
	drawCharacter('S');
	drawCharacter('H');
	drawCharacter('A');
	drawCharacter('D');
	drawCharacter('E');
	drawCharacter('R');
	drawCharacter('s');
	SwapBuffers(ghdc);

}


void drawCharacter(byte bChar) {

	/**/
	void FallNow_();
	FallNow_();
	return;
	/**/

	void drawBullet(float xCord, float yCord, float zCord, float bulletScale);

	switch (bChar) {

	case 'S':
		glPushMatrix();
		for (int i = 0; i < 18; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionS[i].xCord, positionS[i].yCord, positionS[i].zCord, positionS[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'H':

		glPushMatrix();
		for (int i = 0; i < 13; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionH[i].xCord, positionH[i].yCord, positionH[i].zCord, positionH[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'A':

		glPushMatrix();
		for (int i = 0; i < 15; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionA[i].xCord, positionA[i].yCord, positionA[i].zCord, positionA[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'D':

		glPushMatrix();
		for (int i = 0; i < 16; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionD[i].xCord, positionD[i].yCord, positionD[i].zCord, positionD[i].bulletScale);
		}
		glPopMatrix();
		break;

	case 'E':

		glPushMatrix();
		for (int i = 0; i < 12; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionE[i].xCord, positionE[i].yCord, positionE[i].zCord, positionE[i].bulletScale);
		}
		glPopMatrix();
		break;


	case 'R':

		glPushMatrix();
		for (int i = 0; i < 16; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionR[i].xCord, positionR[i].yCord, positionR[i].zCord, positionR[i].bulletScale);
		}
		glPopMatrix();
		break;

	case 's':

		glPushMatrix();
		for (int i = 0; i < 11; i++) {
			glPopMatrix();
			glPushMatrix();
			drawBullet(positionLastS[i].xCord, positionLastS[i].yCord, positionLastS[i].zCord, positionLastS[i].bulletScale);
		}
		glPopMatrix();
		break;


	}
}


/* x,y,z cords give position of bullet
BulleteScale --> size of bullet*/
void drawBullet(float xCord, float yCord, float zCord, float bulletScale) {
	


	/**/
	//glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//depth prev now after rotate, it's position on current x means actual z-axis
	//keep initial depth fixed as -3.0, and adjust with zCord param
	/*FALLING EFFECT*/

	glTranslatef(xOriginalCord + xCord, yOriginalCord + yCord, zOriginalCord + zCord);

	glPushMatrix(); // save initial position
					//glRotatef(90, 0.0, 1.0, 0.0);
					//gluLookAt(xTest, 0.0, 15.0 , 0.0, 0.0, -5.0, 0.0f, 1.0f, 0.0f);
	glRotatef(180, 0.0, 1.0, 0.0); // temporary
								   //gluLookAt(0.0, 0.0f, -xTest, 0.0, 0.0, xTest-5.0, 0.0f, 1.0f, 0.0f); //zoomout effect

	glRotatef((GLfloat)rotateSingleBullet, 0.0, 1.0, 0.0);
	//glTranslatef(0.0, 0.0, zShift);

	//glTranslatef(xCord, yCord, zCord);
	//here xCord --> depth and zCord --> position on x screen / x-axis -- >IMP

	//glTranslatef(0.0, -0.5, 0.0); 

	glPushMatrix(); // save position of first object which will rotate around the initial point
	glColor3f(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0);
	quadric = gluNewQuadric();

	// inner disk back of the bullet
	gluDisk(quadric, 0.001, 0.35*bulletScale, 20, 20);

	//yellowinsh shade
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadric = gluNewQuadric();

	// outer disk back of the bullet
	gluDisk(quadric, 0.35*bulletScale, 0.5*bulletScale, 20, 20);

	// now we will draw second object which is related to the first one
	// back cylinder
	glPopMatrix(); // actually not needed since we didn't change the position

	glPushMatrix(); // save the previous position
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5*bulletScale, 0.5*bulletScale, 0.08*bulletScale, 20, 20);
	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.08*bulletScale); // since we have rotated the whole matrix by hard
											  // coded 90 degrees first, so every axis got shifted and +z takes place of +x
											  //glRotatef((GLfloat)extra1, 0.0, 0.0, 1.0);
											  //glTranslatef(0.0, -0.5, 0.0);

	glPushMatrix();
	glColor3f(184.0 / 255.0, 134.0 / 255.0, 11.0 / 255.0);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix(); // translated position by 0.05

	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix(); // save the previous position second cylinder
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.4*bulletScale, 0.4*bulletScale, 0.15*bulletScale, 20, 20);

	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.15*bulletScale);
	glPushMatrix();
	glColor3f(184.0 / 255.0, 134.0 / 255.0, 11.0 / 255.0);
	//glColor3f(0.6, 0.2, 0.0);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.01, 0.5*bulletScale, 20, 20);

	glPopMatrix();

	//glTranslatef(0.0, 0.0, 0.5);
	glPushMatrix();
	glColor3f(0.9, 0.7, 0.2);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.5*bulletScale, 0.5*bulletScale, 1.3*bulletScale, 20, 20);

	glPopMatrix();

	//glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 1.3*bulletScale);
	glPushMatrix(); // save the previous position second cylinder
	glScalef(1.0, 1.0, 2.0);
	glColor3f(210.0 / 255.0, 105.0 / 255.0, 30.0 / 255.0);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.5*bulletScale, 20, 20);

	glPopMatrix();
	glPopMatrix();

}


// draw graph paper

void drawGraphPaper(void) {

	float xIndex = 0.0f;
	float yIndex = 0.0f;
	glLineWidth(1.5f);
	//start drawing graph
	glBegin(GL_LINES);
	//glColor3f(0.4f, 0.4f, 0.4f);
	//glVertex3f(-1.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, -1.0f, 0.0f);
	//glEnd();

	//glLineWidth(1.0f);
	//glBegin(GL_LINES);
	glColor3f(0.4f, 0.4f, 0.4f);
	for (xIndex = -5.0f; xIndex < 5.0f; (xIndex += 1.0f))
	{
		glVertex3f(xIndex, 5.0f, 0.0f);
		glVertex3f(xIndex, -5.0f, 0.0f);
	}


	for (yIndex = -5.0f; yIndex < 5.0f; (yIndex += 1.0f))
	{
		glVertex3f(5.0f, yIndex, 0.0f);
		glVertex3f(-5.0f, yIndex, 0.0f);
	}
	glEnd();
	// end of graph
}


// update rotation angles
void update(void) {

	//anglePyramid += 0.007f;
	//if (anglePyramid >= 360) {
	//	anglePyramid = 0.0;
	//}

}

void resize(int width, int height) {
	if (height == 0) {
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION); // change matrix mode to projection
	glLoadIdentity();
	//glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}

void uninitialize(void) {

	if (gbFullScreen == true) {
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER |
			SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(ghrc);
	ghrc = NULL;

	DestroyWindow(ghwnd);
}



/*FALLING BULLET CODE PRAVEEN*/
void InitBullets()
{

	int i = 0;
	int j = 0;
	int c = 0;


	for (c = 0; c < 7; c++)
	{
		switch (c)
		{
		case 0: //s
			for (int j = 0; j < 18; j++)
			{
				falling_bullets_[i]._pGLUBullets = gluNewQuadric();

				falling_bullets_[i]._BulletStopPosition = -3.0f;
				falling_bullets_[i]._IsBulletFalling = true;

				falling_bullets_[i]._BulletBounce = -2.2f;
				falling_bullets_[i]._BulletSpeed = 0.053f;

				falling_bullets_[i]._BulletPositionX = positionS[j].xCord;
				falling_bullets_[i]._BulletFallingStartPositionY = positionS[j].yCord;
				falling_bullets_[i]._BulletDepthZ = positionS[j].zCord;
				falling_bullets_[i]._bulletScale = positionS[j].bulletScale;

				falling_bullets_[i]._BulletIncrementalAngle = 1.0f;
				falling_bullets_[i]._BullletAngle = 10.0f;
				i++;
			}
			break;


		case 1: //h
			for (int j = 0; j < 13; j++)
			{
				falling_bullets_[i]._pGLUBullets = gluNewQuadric();

				falling_bullets_[i]._BulletStopPosition = -3.0f;
				falling_bullets_[i]._IsBulletFalling = true;

				falling_bullets_[i]._BulletBounce = -2.5f;
				falling_bullets_[i]._BulletSpeed = 0.053f;

				falling_bullets_[i]._BulletPositionX = positionH[j].xCord;
				falling_bullets_[i]._BulletFallingStartPositionY = positionH[j].yCord;
				falling_bullets_[i]._BulletDepthZ = positionH[j].zCord;
				falling_bullets_[i]._bulletScale = positionH[j].bulletScale;

				falling_bullets_[i]._BulletIncrementalAngle = 1.0f;
				falling_bullets_[i]._BullletAngle = 10.0f;
				i++;
			}
			break;

		case 2://a
			for (int j = 0; j < 15; j++)
			{
				falling_bullets_[i]._pGLUBullets = gluNewQuadric();

				falling_bullets_[i]._BulletStopPosition = -3.5f;
				falling_bullets_[i]._IsBulletFalling = true;

				falling_bullets_[i]._BulletBounce = -2.8f;
				falling_bullets_[i]._BulletSpeed = 0.053f;

				falling_bullets_[i]._BulletPositionX = positionA[j].xCord;
				falling_bullets_[i]._BulletFallingStartPositionY = positionA[j].yCord;
				falling_bullets_[i]._BulletDepthZ = positionA[j].zCord;
				falling_bullets_[i]._bulletScale = positionA[j].bulletScale;

				falling_bullets_[i]._BulletIncrementalAngle = 1.0f;
				falling_bullets_[i]._BullletAngle = 10.0f;
				i++;
			}
			break;

		case 3://d
			for (int j = 0; j < 16; j++)
			{
				falling_bullets_[i]._pGLUBullets = gluNewQuadric();

				falling_bullets_[i]._BulletStopPosition = -3.5f;
				falling_bullets_[i]._IsBulletFalling = true;

				falling_bullets_[i]._BulletBounce = -2.7f;
				falling_bullets_[i]._BulletSpeed = 0.053f;

				falling_bullets_[i]._BulletPositionX = positionD[j].xCord;
				falling_bullets_[i]._BulletFallingStartPositionY = positionD[j].yCord;
				falling_bullets_[i]._BulletDepthZ = positionD[j].zCord;
				falling_bullets_[i]._bulletScale = positionD[j].bulletScale;

				falling_bullets_[i]._BulletIncrementalAngle = 1.0f;
				falling_bullets_[i]._BullletAngle = 10.0f;
				i++;
			}
			break;

		case 4://e
			for (int j = 0; j < 12; j++)
			{
				falling_bullets_[i]._pGLUBullets = gluNewQuadric();

				falling_bullets_[i]._BulletStopPosition = -3.8f;
				falling_bullets_[i]._IsBulletFalling = true;

				falling_bullets_[i]._BulletBounce = -2.9f;
				falling_bullets_[i]._BulletSpeed = 0.053f;

				falling_bullets_[i]._BulletPositionX = positionE[j].xCord;
				falling_bullets_[i]._BulletFallingStartPositionY = positionE[j].yCord;
				falling_bullets_[i]._BulletDepthZ = positionE[j].zCord;
				falling_bullets_[i]._bulletScale = positionE[j].bulletScale;

				falling_bullets_[i]._BulletIncrementalAngle = 1.0f;
				falling_bullets_[i]._BullletAngle = 10.0f;
				i++;
			}
			break;

		case 5: //r
			for (int j = 0; j < 16; j++)
			{
				falling_bullets_[i]._pGLUBullets = gluNewQuadric();

				falling_bullets_[i]._BulletStopPosition = -3.0f;
				falling_bullets_[i]._IsBulletFalling = true;

				falling_bullets_[i]._BulletBounce = -2.8f;
				falling_bullets_[i]._BulletSpeed = 0.053f;

				falling_bullets_[i]._BulletPositionX = positionR[j].xCord;
				falling_bullets_[i]._BulletFallingStartPositionY = positionR[j].yCord;
				falling_bullets_[i]._BulletDepthZ = positionR[j].zCord;
				falling_bullets_[i]._bulletScale = positionR[j].bulletScale;

				falling_bullets_[i]._BulletIncrementalAngle = 1.0f;
				falling_bullets_[i]._BullletAngle = 10.0f;
				i++;
			}
			break;

		case 6: //s
			for (int j = 0; j < 11; j++)
			{
				falling_bullets_[i]._pGLUBullets = gluNewQuadric();

				falling_bullets_[i]._BulletStopPosition = -3.5f;
				falling_bullets_[i]._IsBulletFalling = true;

				falling_bullets_[i]._BulletBounce = -2.7f;
				falling_bullets_[i]._BulletSpeed = 0.053f;

				falling_bullets_[i]._BulletPositionX = positionLastS[j].xCord;
				falling_bullets_[i]._BulletFallingStartPositionY = positionLastS[j].yCord;
				falling_bullets_[i]._BulletDepthZ = positionLastS[j].zCord;
				falling_bullets_[i]._bulletScale = positionLastS[j].bulletScale;

				falling_bullets_[i]._BulletIncrementalAngle = 1.0f;
				falling_bullets_[i]._BullletAngle = 10.0f;
				
				i++;
			}
			break;
		}
	}
}



void FallNow_()
{
	void  drawBullet(float xCord, float yCord, float zCord, float bulletScale);

	for (auto i = 0; i < MAX_FALLING_BULLETS_; i++)
	{
		glPushMatrix();

		if (falling_bullets_[i]._BulletBounce <= falling_bullets_[i]._BulletStopPosition)
			drawBullet(falling_bullets_[i]._BulletPositionX, falling_bullets_[i]._BulletFallingStartPositionY, falling_bullets_[i]._BulletDepthZ- moveBack, falling_bullets_[i]._bulletScale);


		/*Falling Down*/
		if (falling_bullets_[i]._BulletFallingStartPositionY >= falling_bullets_[i]._BulletStopPosition && falling_bullets_[i]._IsBulletFalling)
		{	
			falling_bullets_[i]._BulletFallingStartPositionY = falling_bullets_[i]._BulletFallingStartPositionY - goingDownSpeed;
		}
		/**/
		else
		{

			/*Going Up*/
			falling_bullets_[i]._IsBulletFalling = false;

			if (falling_bullets_[i]._BulletFallingStartPositionY <= falling_bullets_[i]._BulletBounce)
			{
				falling_bullets_[i]._BulletFallingStartPositionY = (falling_bullets_[i]._BulletFallingStartPositionY + goingUpSpeed);
			}
			/**/
			else
			{
				/*Adjust bounce and Speed of bullet here*/
				falling_bullets_[i]._IsBulletFalling = true;
				falling_bullets_[i]._BulletBounce = (falling_bullets_[i]._BulletBounce - 0.05f); // adjust constant value to number of bounce

			}
		}
			

		/*Draw Bullets here*/

		drawBullet(falling_bullets_[i]._BulletPositionX, falling_bullets_[i]._BulletFallingStartPositionY, falling_bullets_[i]._BulletDepthZ- moveBack, falling_bullets_[i]._bulletScale);

		/**/
		glPopMatrix();
	}

}
/**/