#include "sword.h"


//Prototype Of WndProc() declared Globally
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global variable declarations
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbActiveWindow = false;
bool gbEscapeKeyIsPressed = false;
bool gbFullscreen = false;

GLUquadric *quadric;
GLfloat rotateAngle = 0;
GLint count = 0;

//main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("RTROGL");
	bool bDone = false;

	//code
	//initializing members of struct WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;

	//Registering Class
	RegisterClassEx(&wndclass);

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	//Create Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szClassName,
		TEXT("OpenGL Fixed Function Pipeline Using Native Windowing : gluPerspective template"),
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

	//Message Loop
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
				update();
				display();
				if (gbEscapeKeyIsPressed == true)
					bDone = true;
			}
		}
	}

	uninitialize();
	return((int)msg.wParam);
}

//WndProc()
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//code
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
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullscreen(void)
{
	//variable declarations
	MONITORINFO mi;

	//code
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

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	resize(WIN_WIDTH, WIN_HEIGHT);
}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f,0.0f,-5.0f);
	//glRotatef(rotateAngle, 1.0f, 1.0f, 1.0f);
	glScalef(1.0f, 1.8f, 1.0f);
	drawSword();

	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.9f,0.7f,1.0f);
	drawCircleForSwordHandle();

	SwapBuffers(ghdc);
}

void drawCylinder()
{
	// lower side of sword
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, -1.1f, -5.0f);
	glRotatef(rotateAngle, 1.0f, 1.0f, 1.0f);
	if (count == 0)
	{
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		count++;
	}
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.10f, 0.05f, 0.5f, 30, 30);
}

void drawSword()
{
	void drawHorizontalHandle();

	glColor3f(0.2f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	glVertex3f(0.05f, -0.85f, 0.0f);
	glVertex3f(-0.05f, -0.85f, 0.0f);
	glVertex3f(-0.05f, -0.60f, 0.0f);
	glVertex3f(0.05f, -0.60f, 0.0f);

	glEnd();

	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_LINES);

	glVertex3f(-0.05f, -0.85f, 0.0f);
	glVertex3f(-0.05f, -0.60f, 0.0f);

	glVertex3f(0.05f, -0.85f, 0.0f);
	glVertex3f(0.05f, -0.60f, 0.0f);

	glEnd();


	drawHorizontalHandle();

	// main sword
	glBegin(GL_QUADS);
	glColor3f(0.80f, 0.80f, 0.80f);

	glVertex3f(0.10f, 0.80f, 0.0f);
	glVertex3f(-0.10f, 0.80f, 0.0f);
	glVertex3f(-0.10f, -0.565f, 0.0f);
	glVertex3f(0.10f,-0.565f,0.0f);
	
	glEnd();

	// upper triangle of sword
	glBegin(GL_TRIANGLES);
	glColor3f(0.80f, 0.80f, 0.80f);

	glVertex3f(0.10f, 0.80f, 0.0f);
	glVertex3f(-0.10f, 0.80f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glEnd();
}

void drawHorizontalHandle()
{
	// Handle horizontal bar
	glBegin(GL_QUADS);
	glColor3f(0.50f, 0.50f, 0.50f);

	// front face
	glVertex3f(0.40f, -0.57f, 0.05f);
	glVertex3f(-0.40f, -0.57f, 0.05f);
	glVertex3f(-0.40f, -0.60f, 0.05f);
	glVertex3f(0.40f, -0.60f, 0.05f);

	// back face
	//glColor3f(1.0f, 1.0f, 0.0f);

	glVertex3f(0.40f, -0.57f, -0.05f);
	glVertex3f(-0.40f, -0.57f, -0.05f);
	glVertex3f(-0.40f, -0.60f, -0.05f);
	glVertex3f(0.40f, -0.60f, -0.05f);


	// right face
	//glColor3f(1.0f, 1.0f, 0.0f);

	glVertex3f(0.40f, -0.57f, -0.05f);
	glVertex3f(0.40f, -0.57f, 0.05f);
	glVertex3f(0.40f, -0.60f, 0.05f);
	glVertex3f(0.40f, -0.60f, -0.05f);
	

	// left face
	///glColor3f(1.0f, 1.0f, 0.0f);

	glVertex3f(-0.40f, -0.57f, 0.05f);
	glVertex3f(-0.40f, -0.57f, -0.05f);
	glVertex3f(-0.40f, -0.60f, -0.05f);
	glVertex3f(-0.40f, -0.60f, 0.05f);

	// top face
	//glColor3f(1.0f, 1.0f, 0.0f);

	glVertex3f(0.40f, -0.57f, -0.05f);
	glVertex3f(-0.40f, -0.57f, -0.05f);
	glVertex3f(-0.40f, -0.57f, 0.05f);
	glVertex3f(0.40f, -0.57f, 0.05f);

	// bottom face
	//glColor3f(1.0f, 1.0f, 0.0f);

	glVertex3f(0.40f, -0.60f, 0.05f);
	glVertex3f(-0.40f, -0.60f, 0.05f);
	glVertex3f(-0.40f, -0.60f, -0.05f);
	glVertex3f(0.40f, -0.60f, -0.05f);

	glEnd();
}

void drawCircleForSwordHandle()
{
	// mooth of sword
	/**GLfloat radius = 0.05f;

	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);

	for (GLfloat angle = 0.0f;angle < 2.0f * PI;angle = angle + 0.0001f)
	{
		glVertex3f(cos(angle)*radius, sin(angle)*radius, 0.0f);
	}
	glEnd();**/

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();
	glColor3f(0.80f, 0.80f, 0.80f);
	gluSphere(quadric, 0.1f, 30, 30);

	
}

void resize(int width, int height)
{
	//code
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/ (GLfloat)height,0.1f,100.0f);
}

void uninitialize(void)
{
	//UNINITIALIZATION CODE

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

void update()
{
	rotateAngle = rotateAngle + 0.03f;
	if (rotateAngle == 360.0f)
	{
		rotateAngle = 0.0f;
	}
}
