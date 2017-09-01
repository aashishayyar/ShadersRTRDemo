/******************************************************************** 
Description : Creates bullets of different sizes and at diferrent
			  location (with function) 

Key Controls : S,s --> Rotate |  p --> translate

Priyanka Bhasme
*********************************************************************/

// Header files
#include<Windows.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include<math.h>

// Pragma
#pragma comment(lib, "opengl32.lib")
// we need this to link
#pragma comment(lib, "glu32.lib")


// macros declaration 
#define WINWIDTH 800
#define WINHEIGHT 800
// for calculating anlges
#define PI 3.1415926535898


float anglePyramid, angleRect, angleDetla;
int rotationsCount = 10000;
float gwSideofTriangle = 2.0f;
bool gbFullScreen, gbEscapeKeyIsPressed, gbActiveWindow = false;
bool gbDone;
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
DWORD dwStyle;
// ask sir - how error goes when curly brackets are added????????????
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

// additional vars for robotic arm
static int shoulder = 0;
static int elbow = 0;
static int extra1 = 0;
static int extra2 = 0;
float zShift = -4.0;

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
		case 'E':
			elbow = (elbow + 3) % 360;
			break;

		case 'e':
			elbow = (elbow - 3) % 360;
			break;

		case 'S':
			shoulder = (shoulder + 3) % 360;
			break;

		case 's':
			shoulder = (shoulder - 3) % 360;
			break;

		case 'P':
			extra1 = (extra1 + 7) % 360;
			break;

		case 'p':
			//extra1 = (extra1 - 7) % 360;
			zShift += 0.5;
			if (zShift > 8.0) {
				zShift = -8.0;
			}
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

	void drawTriangle(float traiangleScale);
	void drawGraphPaper(void);
	void drawRectangle(float rectScale);
	void drawPyramid(void);
	void drawCube(void);
	void drawBullet(float xCord, float yCord, float zCord, float bulletScale);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // GL_DEPTH_BUFFER_BIT - For 3D
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(-cos(anglePyramid)*1.0, -sin(anglePyramid)*1.0, 0.0,0.0, 0.0, -2.0, 0.0f, 1.0f, 0.0f);
	gluLookAt(0.0, 0.0f, 10.0, 0.0, 0.0, -3.0, 0.0f, 1.0f, 0.0f);
	// random bullets drawn for testing
	drawBullet(1.0, -1.0, 1.0, 0.5);
	drawBullet(1.0, 1.0, 1.0, 1.0);
	drawBullet(-1.5, 2.0, 2.0, 0.5);
	drawBullet(0.5, 0.0, 1.0, 0.3);

	drawBullet(-3.0, 0.0, 0.0, 1.0);
	drawBullet(1.0, 4.0, 1.0, 0.4);
	drawBullet(1.5, -2.0, 2.0, 0.5);
	drawBullet(4.5, 6.0, 1.0, 0.3);

    //drawBullet(0.0, 0.0, 0.0, 1.0);
	SwapBuffers(ghdc);

}

/* x,y,z cords give position of bullet
 BulleteScale --> size of bullet*/
void drawBullet(float xCord, float yCord, float zCord, float bulletScale) {	

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//gluLookAt(cos(anglePyramid)*3.0, 0.0f, sin(anglePyramid)*3.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//depth prev now after rotate, it's position on current x means actual z-axis
	//keep initial depth fixed as -3.0, and adjust with zCord param
	glTranslatef(xCord, yCord, -8.0+zCord);
	
	glPushMatrix(); // save initial position
	glRotatef(90, 0.0, 1.0, 0.0);
	//gluLookAt(cos(anglePyramid)*1.0, 2.0f, sin(anglePyramid)*1.0, 0.0, 0.0, -3.0, 0.0f, 1.0f, 0.0f);
	glRotatef((GLfloat)shoulder, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, zShift);
	//glTranslatef(xCord, yCord, zCord);
	//here xCord --> depth and zCord --> position on x screen / x-axis

	//glTranslatef(0.0, -0.5, 0.0); 

	glPushMatrix(); // save position of first object which will rotate around the initial point
	glColor3f(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0);
	quadric = gluNewQuadric();
	//gluSphere(quadric, 0.5, 20, 20);
	// inner disk back of the bullet
	gluDisk(quadric, 0.001, 0.35*bulletScale, 20, 20);

	//yellowinsh shade
	glColor3f(218.0 / 255.0, 168.0 / 255.0, 32.0 / 255.0);
	quadric = gluNewQuadric();
	//gluSphere(quadric, 0.5, 20, 20);
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




// update rotation angles
void update(void) {

	anglePyramid += 0.0005f;
	if (anglePyramid >= 360) {
		anglePyramid = 0.0;
	}


}


// draw Pyramid
void drawPyramid(void) {

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f); // red appex

	glColor3f(0.0f, 1.0f, 0.0f); // front face left bottom
	glVertex3f(-1.0f, -1.0f, 1.0f);// green

	glColor3f(0.0f, 0.0f, 1.0f); // front face 
	glVertex3f(1.0f, -1.0f, 1.0f); // blue


	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f); // red appex

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f); // red appex

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f); // red appex


	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f); // red appex

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f); // red appex

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f); // red appex


	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f); // red appex

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f); // red appex

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f); // red appex


	glEnd();

}



//draw rectangle
void drawRectangle(float rectScale) {

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-rectScale, rectScale, 0.0f);
	glVertex3f(-rectScale, -rectScale, 0.0f);
	glVertex3f(rectScale, -rectScale, 0.0f);
	glVertex3f(rectScale, rectScale, 0.0f);
	glEnd();
}


// draws triangle
void drawTriangle(float traiangleScale) {

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, traiangleScale, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-traiangleScale, -traiangleScale, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(traiangleScale, -traiangleScale, 0.0f);
	glEnd();

}


// draw graph paper

void drawGraphPaper(void) {

	float xIndex = 0.0f;
	float yIndex = 0.0f;
	glLineWidth(3.0f);
	//start drawing graph
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glEnd();

	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	for (xIndex = -0.95f; xIndex < 1.0f; (xIndex += 0.05f))
	{
		glVertex3f(xIndex, 1.0f, 0.0f);
		glVertex3f(xIndex, -1.0f, 0.0f);
	}


	for (yIndex = -0.95f; yIndex < 1.0f; (yIndex += 0.05f))
	{
		glVertex3f(1.0f, yIndex, 0.0f);
		glVertex3f(-1.0f, yIndex, 0.0f);
	}
	glEnd();
	// end of graph


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
	/* Queries :
	1. How can we see the object with FOV angle zero degrees??
	2. Why glTranslate doesn't work when FOV is zero?
	and why it works when FOV is 45?
	*/
	//gluPerspective(0.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);
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