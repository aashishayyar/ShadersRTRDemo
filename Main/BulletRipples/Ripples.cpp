
#include <Windows.h>
#include <gl/GL.h>
#include <GL\GLU.h>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbActiveWindow = false;
bool gbIsEscapeKeyPressed = false;
bool gbFullscreen = false;
void resize(int, int);
float gfXranslateCounter = -3.2;
GLfloat xPara;
GLfloat yPara;
GLint circle_points = 1000000;
GLfloat angle;
#define PI 3.1415926535898
GLUquadric *quadric = NULL;
static GLfloat incenter = 0.0f;
float gfXRippleTranslateCounter = 0.0;
float radius = 0.6;

struct Point
{
	GLfloat xAxis;
	GLfloat yAxis;
};

struct Color
{
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	void initialize(void);
	void uninitialize(void);
	void display(void);

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("OGL Bullet");
	bool bDone = false;

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = CreateSolidBrush(RGB(1, 1, 1));
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = szClassName;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		szClassName,
		TEXT("OpenGL Bullet"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		0,
		0,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ghwnd = hwnd;

	initialize();

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

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
				if (gbIsEscapeKeyPressed == true)
					bDone = true;
				display();
			}
		}

	}

	uninitialize();
	return (int(msg.wParam));

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	void resize(int, int);
	void ToggleFullscreen(void);
	void uninitialize(void);

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
			gbIsEscapeKeyPressed = true;
			break;

		case 0x46: //for 'f' or 'F'
			if (gbFullscreen == false)
			{
				ToggleFullscreen();
				gbFullscreen = true;
			}
			else
			{
				ToggleFullscreen();
				gbFullscreen = false;
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

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}


void ToggleFullscreen(void)
{
	MONITORINFO mi;

	if (gbFullscreen == false)
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
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}

}


void initialize(void)
{

	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 8;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

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
}


void display(void)
{
	void drawBullet1(void);
	void drawBullet2(void);
	void drawBullet3(void);
	void drawRippledBullet(void);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	 drawBullet2();
	
	drawRippledBullet();
	
	SwapBuffers(ghdc);

}

void drawCircle(GLfloat radius, Point incenter, Color color)
{
	GLint circle_points = 100;
	GLfloat angle;

	glBegin(GL_POINTS);

	glColor3f(color.red, color.green, color.blue);

	for (int i = 0.0f; i<circle_points; i++)
	{
		angle = 2 * PI * i / circle_points;
		glVertex3f(cos(angle)*radius + incenter.xAxis,
			sin(angle)*radius + incenter.yAxis, 0.0f);
	}

	glEnd();

}

void drawRippledBullet()
{
	void drawCircle(GLfloat, Point, Color);

	drawCircle(radius, Point{ gfXRippleTranslateCounter-=0.001,0.0f }, Color{ 1.0f, 1.0f,1.0f});

	glTranslatef(0.0, 0.0, -1.0);
	drawCircle(radius, Point{ gfXRippleTranslateCounter -= 0.0001,0.0f }, Color{ 0.8f,0.8f,0.8f });
	glTranslatef(0.0, 0.0, -1.3);
	drawCircle(radius+0.1, Point{ gfXRippleTranslateCounter-=0.000001,0.0f }, Color{ 0.6f,0.6f,0.6f });
	glTranslatef(0.0, 0.0, -1.6);
	drawCircle(radius + 0.1, Point{ gfXRippleTranslateCounter -= 0.000001,0.0f }, Color{ 0.6f,0.6f,0.6f });
	glTranslatef(0.0, 0.0, -1.9);
	drawCircle(radius + 0.1, Point{ gfXRippleTranslateCounter -= 0.000001,0.0f }, Color{ 0.6f,0.6f,0.6f });
	glTranslatef(0.0, 0.0, -2.3);
	drawCircle(radius+0.2, Point{ gfXRippleTranslateCounter-=0.00001,0.0f }, Color{ 0.4f,0.4f,0.4f });
	glTranslatef(0.0, 0.0, -2.6);
	drawCircle(radius+0.2, Point{ gfXRippleTranslateCounter-=0.0001,0.0f }, Color{ 0.2f,0.2f,0.2f });
	glTranslatef(0.0, 0.0, -2.9);
	drawCircle(radius+0.2, Point{ gfXRippleTranslateCounter -= 0.0001,0.0f }, Color{ 0.1f,0.1f,0.1f });
	glTranslatef(0.0, 0.0, -3.2);
	drawCircle(radius+0.2, Point{ gfXRippleTranslateCounter -= 0.0001,0.0f }, Color{ 0.1f,0.1f,0.1f });
	glTranslatef(0.0, 0.0, -3.6);

}

void drawBullet1()
{
	glColor3f((GLfloat)218 / 255, (GLfloat)165 / 255, (GLfloat)32 / 255);

	glTranslatef(0.0f, 0.0f, -7.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();

	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

	glColor3f(0.4f, 0.9f, 1.0f);

	glColor3f((GLfloat)218 / 255, (GLfloat)165 / 255, (GLfloat)32 / 255);

	gluCylinder(quadric, 0.70, 0.70, 2.0, 30, 30);

	glTranslatef(0.0, 0.0, 2.0);
	gluCylinder(quadric, 0.70, 0.5, 1.0, 30, 30);

	glTranslatef(0.0, 0.0, -2.1);
	gluCylinder(quadric, 0.60, 0.60, 1.0, 30, 30);
	glTranslatef(0.0, 0.0, -0.1);
	gluCylinder(quadric, 0.70, 0.70, 0.1, 30, 30);
}


void drawBullet2()
{
	glColor3f((GLfloat)218 / 255, (GLfloat)165 / 255, (GLfloat)32 / 255);

	
	glTranslatef(gfXranslateCounter, 0.0f, -7.0f);

	if (gfXranslateCounter<=0.0)
	{
		gfXRippleTranslateCounter = -gfXranslateCounter;
	}
	else
	{
		gfXRippleTranslateCounter = gfXranslateCounter;
	}
	
	gfXranslateCounter += 0.001;

	if (gfXranslateCounter == -3.1)
	{
		gfXranslateCounter = -3.2;
	}

	glScalef(0.5f, 0.5f, 0.5f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();

	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

	glColor3f(0.4f, 0.9f, 1.0f);

	glColor3f((GLfloat)218 / 255, (GLfloat)165 / 255, (GLfloat)32 / 255);

	gluCylinder(quadric, 0.70, 0.70, 2.0, 30, 30);

	glTranslatef(0.0, 0.0, 2.0);
	
	gluSphere(quadric, 0.70, 30, 30);
	glTranslatef(0.0, 0.0, -2.1);
	gluCylinder(quadric, 0.60, 0.60, 1.0, 30, 30);
	glTranslatef(0.0, 0.0, -0.1);
	gluCylinder(quadric, 0.70, 0.70, 0.1, 30, 30);
}

void drawBullet3()
{
	glColor3f((GLfloat)218 / 255, (GLfloat)165 / 255, (GLfloat)32 / 255);

	glTranslatef(0.0f, 0.0f, -7.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();

	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

	glColor3f((GLfloat)218 / 255, (GLfloat)165 / 255, (GLfloat)32 / 255);

	gluCylinder(quadric, 0.70, 0.70, 2.0, 30, 30);

	glTranslatef(0.0, 0.0, 2.0);
	gluCylinder(quadric, 0.70, 0.5, 1.0, 30, 30);

	glTranslatef(0.0, 0.0, -2.1);
	gluCylinder(quadric, 0.60, 0.60, 1.0, 30, 30);
	glTranslatef(0.0, 0.0, -0.1);
	gluCylinder(quadric, 0.70, 0.70, 0.1, 30, 30);
	
	glTranslatef(0.0, 0.0, 3.2);
	gluCylinder(quadric, 0.5, 0.0, 0.5, 30, 30);
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
	if (gbFullscreen == true)
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

}

