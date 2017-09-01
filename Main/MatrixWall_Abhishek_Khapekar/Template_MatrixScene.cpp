#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include "MatrixHeader(Abhishek).h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//prototype of WndProc()
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbActiveWindow = false;
bool gbEscapeKeyIsPressed = false;
bool gbFullScreen = false;

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function prototype
	void initialize(void);
	void display(void);
	void uninitialize(void);
	void update(void);

	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("RTROGL");
	bool bDone = false;

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;

	//Register class
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szClassName,
		TEXT("Abhishek_Khapekar_79 | MatrixScene"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		0,
		0,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	//initialize
	initialize();

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//message loop
	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = true;
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

				//call to render function
				display();

				update();
			}
		}//else
	}//while

	uninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function prototype
	void resize(int, int);
	void ToggleFullScreen(void);
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

	case WM_ERASEBKGND:
		return(0);
		break;

	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CHAR:
		switch (wParam)
		{
		case VK_ESCAPE:
			gbEscapeKeyIsPressed = true;
			break;

		case 'f':
		case 'F':
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
		}//inner switch
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}//outer switch
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}//WndProc()

void ToggleFullScreen(void)
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

		ShowCursor(TRUE);
	}
}

void initialize(void)
{
	//function prototypes
	void resize(int, int);

	//variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	//Initialization of structure 'PIXELFORMATDESCRIPTOR'
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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	resize(WIN_WIDTH, WIN_HEIGHT);
}//initialize

void update(void)
{
	//for translating the 'Y' axis
	yPos = yPos - 0.1f;

	if (yPos <= -6.0f)
		yPos = 5.0f;
	//code for shifting charactter to y axis
	if (count == 0.6f)
		count = count + 0.05f;
	if (count == 0.8f)
		count = count + 0.1f;
	if (count == 1.0f)
		count = count + 0.2f;
	if (count == 3.0f)
		count = 0.5f;
}

void display(void)
{
	//function Prototype
	void DrawSevenSegment(void);
	void animation(void);

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(0.0f, 0.0f, -12.0f);
	xPos = GLfloat(rand() % -40)*0.2f;
	glScalef(0.80f, 0.80f, 0.80f);

	animation();
	
	animation();

	animation();
	
	glTranslatef(-7.0f, 0.0f, 0.0f);
	//glScalef(0.80f, 0.80f, 0.80f);
	//xPos = GLfloat(rand() % -40)*0.2f;

	animation();

	animation();

	animation();
	
	SwapBuffers(ghdc);
}//display

void DrawSevenSegment(void)
{
	glLineWidth(4.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	//a
	glVertex3f(ax, ay, 0.0f);
	glVertex3f(ax1, ay1, 0.0f);

	//b
	glVertex3f(bx, by, 0.0f);
	glVertex3f(bx1, by1, 0.0f);

	//c
	glVertex3f(cx, cy, 0.0f);
	glVertex3f(cx1, cy1, 0.0f);

	//d
	glVertex3f(dx, dy, 0.0f);
	glVertex3f(dx1, dy1, 0.0f);

	//e
	glVertex3f(ex, ey, 0.0f);
	glVertex3f(ex1, ey1, 0.0f);

	//f
	glVertex3f(fx, fy, 0.0f);
	glVertex3f(fx1, fy1, 0.0f);

	//g
	glVertex3f(gx, gy, 0.0f);
	glVertex3f(gx1, gy1, 0.0f);

	switch (no)
	{
	case 0:
		glColor3f(0.0f, 0.0f, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;

	case 1:
		glColor3f(0.0f, 0.0f, 0.0f);
		//a
		glVertex3f(ax, ay, 0.0f);
		glVertex3f(ax1, ay1, 0.0f);
		//d
		glVertex3f(dx, dy, 0.0f);
		glVertex3f(dx1, dy1, 0.0f);
		//e
		glVertex3f(ex, ey, 0.0f);
		glVertex3f(ex1, ey1, 0.0f);
		//f
		glVertex3f(fx, fy, 0.0f);
		glVertex3f(fx1, fy1, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;

	case 2:
		glColor3f(0.0f, 0.0f, 0.0f);
		//c
		glVertex3f(cx, cy, 0.0f);
		glVertex3f(cx1, cy1, 0.0f);
		//f
		glVertex3f(fx, fy, 0.0f);
		glVertex3f(fx1, fy1, 0.0f);
		break;

	case 3:
		glColor3f(0.0f, 0.0f, 0.0f);
		//e
		glVertex3f(ex, ey, 0.0f);
		glVertex3f(ex1, ey1, 0.0f);
		//f
		glVertex3f(fx, fy, 0.0f);
		glVertex3f(fx1, fy1, 0.0f);
		break;

	case 4:
		glColor3f(0.0f, 0.0f, 0.0f);
		//a
		glVertex3f(ax, ay, 0.0f);
		glVertex3f(ax1, ay1, 0.0f);
		//e
		glVertex3f(ex, ey, 0.0f);
		glVertex3f(ex1, ey1, 0.0f);
		//d
		glVertex3f(dx, dy, 0.0f);
		glVertex3f(dx1, dy1, 0.0f);
		break;

	case 5:
		glColor3f(0.0f, 0.0f, 0.0f);
		//b
		glVertex3f(bx, by, 0.0f);
		glVertex3f(bx1, by1, 0.0f);
		//e
		glVertex3f(ex, ey, 0.0f);
		glVertex3f(ex1, ey1, 0.0f);
		break;

	case 6:
		glColor3f(0.0f, 0.0f, 0.0f);
		//b
		glVertex3f(bx, by, 0.0f);
		glVertex3f(bx1, by1, 0.0f);
		break;

	case 7:
		glColor3f(0.0f, 0.0f, 0.0f);
		//d
		glVertex3f(dx, dy, 0.0f);
		glVertex3f(dx1, dy1, 0.0f);
		//e
		glVertex3f(ex, ey, 0.0f);
		glVertex3f(ex1, ey1, 0.0f);
		//f
		glVertex3f(fx, fy, 0.0f);
		glVertex3f(fx1, fy1, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;

	case 8:
		//Auto Design
		break;

	case 9:
		glColor3f(0.0f, 0.0f, 0.0f);
		//e
		glVertex3f(ex, ey, 0.0f);
		glVertex3f(ex1, ey1, 0.0f);
		break;

	case 10:
		glColor3f(0.0f, 0.0f, 0.0f);
		//d
		glVertex3f(dx, dy, 0.0f);
		glVertex3f(dx1, dy1, 0.0f);
		break;

	case 11:
		//Auto design
		break;

	case 12:
		glColor3f(0.0f, 0.0f, 0.0f);
		//b
		glVertex3f(bx, by, 0.0f);
		glVertex3f(bx1, by1, 0.0f);
		//c
		glVertex3f(cx, cy, 0.0f);
		glVertex3f(cx1, cy1, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;

	case 13:
		glColor3f(0.0f, 0.0f, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;

	case 14:
		glColor3f(0.0f, 0.0f, 0.0f);
		//b
		glVertex3f(bx, by, 0.0f);
		glVertex3f(bx1, by1, 0.0f);
		//c
		glVertex3f(cx, cy, 0.0f);
		glVertex3f(cx1, cy1, 0.0f);
		break;

	case 15:
		glColor3f(0.0f, 0.0f, 0.0f);
		//b
		glVertex3f(bx, by, 0.0f);
		glVertex3f(bx1, by1, 0.0f);
		//c
		glVertex3f(cx, cy, 0.0f);
		glVertex3f(cx1, cy1, 0.0f);
		//d
		glVertex3f(dx, dy, 0.0f);
		glVertex3f(dx1, dy1, 0.0f);
		break;

	case 16:
		glColor3f(0.0f, 0.0f, 0.0f);
		//b
		glVertex3f(bx, by, 0.0f);
		glVertex3f(bx1, by1, 0.0f);
		break;

	case 17:
		glColor3f(0.0f, 0.0f, 0.0f);
		//a
		glVertex3f(ax, ay, 0.0f);
		glVertex3f(ax1, ay1, 0.0f);
		//d
		glVertex3f(dx, dy, 0.0f);
		glVertex3f(dx1, dy1, 0.0f);
		break;

	case 18:
		glColor3f(0.0f, 0.0f, 0.0f);
		//a
		glVertex3f(ax, ay, 0.0f);
		glVertex3f(ax1, ay1, 0.0f);
		//b
		glVertex3f(bx, by, 0.0f);
		glVertex3f(bx1, by1, 0.0f);
		//c
		glVertex3f(cx, cy, 0.0f);
		glVertex3f(cx1, cy1, 0.0f);
		//d
		glVertex3f(dx, dy, 0.0f);
		glVertex3f(dx1, dy1, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;

	case 19:
		glColor3f(0.0f, 0.0f, 0.0f);
		//a
		glVertex3f(ax, ay, 0.0f);
		glVertex3f(ax1, ay1, 0.0f);
		//f
		glVertex3f(fx, fy, 0.0f);
		glVertex3f(fx1, fy1, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;

	case 20:
		//skiping 'K'
		break;

	case 21://L
		glColor3f(0.0f, 0.0f, 0.0f);
		//a
		glVertex3f(ax, ay, 0.0f);
		glVertex3f(ax1, ay1, 0.0f);
		//b
		glVertex3f(bx, by, 0.0f);
		glVertex3f(bx1, by1, 0.0f);
		//c
		glVertex3f(cx, cy, 0.0f);
		glVertex3f(cx1, cy1, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;

	case 22://M
			//skiping 'M'
		break;

	case 23://N
			//skiping 'N'
		break;

	case 24://O
		glColor3f(0.0f, 0.0f, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;

	case 25://P
		glColor3f(0.0f, 0.0f, 0.0f);
		//c
		glVertex3f(cx, cy, 0.0f);
		glVertex3f(cx1, cy1, 0.0f);
		//d
		glVertex3f(dx, dy, 0.0f);
		glVertex3f(dx1, dy1, 0.0f);
		break;

	case 26://Q
			//skiping 'Q'
		break;

	case 27://R
			//skiping 'R'
		break;

	case 28://s
		glColor3f(0.0f, 0.0f, 0.0f);
		//b
		glVertex3f(bx, by, 0.0f);
		glVertex3f(bx1, by1, 0.0f);
		//e
		glVertex3f(ex, ey, 0.0f);
		glVertex3f(ex1, ey1, 0.0f);
		break;

	case 29://T
			//skiping 'T'
		break;

	case 30:
		glColor3f(0.0f, 0.0f, 0.0f);
		//a
		glVertex3f(ax, ay, 0.0f);
		glVertex3f(ax1, ay1, 0.0f);
		//g
		glVertex3f(gx, gy, 0.0f);
		glVertex3f(gx1, gy1, 0.0f);
		break;
	}
	glEnd();
}

void animation(void)
{
	//function prototype
	void DrawSevenSegment(void);

	glPushMatrix();
	xPos = GLfloat(rand() % -40)*0.2f;
	glTranslatef(xPos, yPos, 0.0f);
	for (loop = 0; loop < 36; loop++)
	{
		no = rand() % 36 * 0.2f;
		DrawSevenSegment();
		glTranslatef(0.0f, count, 0.0f);
	}
	glPopMatrix();
}

void resize(int width, int height)
{
	//code
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}//resize

void uninitialize(void)
{
	//code
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
}//uninitialize