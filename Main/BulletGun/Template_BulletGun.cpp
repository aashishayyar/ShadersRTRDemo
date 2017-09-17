#include"BulletGun_Header.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define PI 3.1415926535898

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
		TEXT("Abhishek_Khapekar_79 | Bullet_Gun"),
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

		case 'E':
			RotateGun = (RotateGun + 3) % 360;
			break;

		case 'e':
			RotateGun = (RotateGun - 3) % 360;
			break;

		case 'F':
		case 'f':
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

	glClearColor(0.0f, 0.0f, 0.0f,0.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	resize(WIN_WIDTH, WIN_HEIGHT);
}//initialize

void DrawCylinder(float base, float top, float height )
{
	quadric = gluNewQuadric();
	gluCylinder(quadric, base, top, height, 20, 20);
}

void DrawCircle(float redius)
{
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0.0f; angle <= 2.0*PI; angle = angle + 0.01f)
	{
		glVertex3f(cos(angle)*redius, sin(angle)*redius, 0.0f);
	}
	glEnd();
}
void display(void)
{
	//function prototype
	void CUBE(void);
	void FireStickDecoration(void);

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glScalef(0.70f,0.70f,0.70f);

	glPushMatrix();

		glRotatef((GLfloat)RotateGun, 0.0f, 1.0f, 0.0f);
		//Middle Gray Cylinder part
		glPushMatrix();
			base = top = 0.3,height = 2.2;
			glTranslatef(-1.0f, 0.1f, 0.0f);
			glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
			glColor3f(0.70f, 0.70f, 0.70f);//Gray final
			DrawCylinder(base, top, height);
			DrawCircle(base);
		glPopMatrix();

		//first Pipe part 
		glPushMatrix();
			base = top = 0.1f, height = 1.3f;
			glTranslatef(-2.0f, 0.05f, 0.0f);
			glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
			glColor3f(0.81f,0.71f,0.23f);
			DrawCylinder(base, top, height);
			DrawCircle(base);
			//yellow
			base = top = 0.12f, height = 0.3f;
			glTranslatef(0.0f, 0.0f, -0.3f);
			glColor3f(1.0f, 1.0f, 0.0f);
			DrawCylinder(base, top, height);
			glColor3f(0.0f, 0.0f, 0.0f);
			DrawCircle(base);
		glPopMatrix();

		//Upper small pipe stick
		glPushMatrix();
		base = top = 0.08f, height = 0.3f;
			glTranslatef(-1.3f, 0.2f, 0.0f);
			glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
			glColor3f(0.80f, 0.80f, 0.80f);//Light Gray final
			DrawCylinder(base, top, height);
			glColor3f(0.0f, 0.0f, 0.0f);
			DrawCircle(base);
		glPopMatrix();

		//Top Camera (cylinder)
		glPushMatrix();
		base = top = 0.1f, height = 0.9f;
			glTranslatef(0.2f, 0.5f, 0.0f);
			glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
			glColor3f(0.80f,0.80f,0.80f);//Light Gray final
			DrawCylinder(base, top, height);
			DrawCircle(base);
		glPopMatrix();

		//TOP cube
		glPushMatrix();
			glTranslatef(0.5f, -0.3f, 0.0f);
			glScalef(0.40f, 0.10f, 0.15f);
			CUBE();
		glPopMatrix();

		//down left cube
		glPushMatrix();
			glTranslatef(0.2f, -0.6f, 0.0f);
			glScalef(0.10f, 0.30f, 0.15f);
			CUBE();
		glPopMatrix();

		//down right cube
		glPushMatrix();
			glTranslatef(1.0f, -0.45f, 0.0f);
			glScalef(0.10f, 0.30f, 0.15f);
			glColor3f(0.35f, 0.16f, 0.14f);//Brown final
			CUBE();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.6f,-0.4f,0.0f);
			FireStickDecoration();
			//back side of gun
			glPushMatrix();
			base = 0.2f, top = 0.3f, height = 1.5f;
				glTranslatef(0.4f, 0.5f, 0.0f);
				glRotatef(RotateAngle, 0.0f, 1.0f, 0.0f);
				glRotatef(RotateAngle-70.0f, 1.0f, 0.0f, 1.0f);
				glColor3f(0.35f,0.16f,0.14f);//Brown final
				DrawCylinder(base, top, height);
				glTranslatef(0.0f, 0.0f, 1.5f);
				DrawCircle(top);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();//OUTER stack


	SwapBuffers(ghdc);
}//display

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

void CUBE(void)
{
	//glScalef(0.70f, 0.10f, 0.20f);
	glBegin(GL_QUADS);
	
	//Top face
	//glColor3f(1.0f, 0.0f, 0.0f);//Red
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	//Bottom face
	//glColor3f(0.0f, 1.0f, 0.0f);//Green
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	//front face 
	//glColor3f(0.0f, 0.0f, 1.0f);//Blue
	glVertex3f(1.0f, 1.0f, 1.0f);//right-top
	glVertex3f(-1.0f, 1.0f, 1.0f);//left-top
	glVertex3f(-1.0f, -1.0f, 1.0f);//left-bottom
	glVertex3f(1.0f, -1.0f, 1.0f);//right-bottom

	//Back face
	//glColor3f(0.0f, 1.0f, 1.0f);//
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//Right face
	//glColor3f(1.0f, 0.0f, 1.0f);//Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//left face
	//glColor3f(1.0f, 1.0f, 0.0f);//yellow
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}

void FireStickDecoration(void)
{
	float angle;
	GLfloat red = 0.4f;

	glPushMatrix();
		GLint circle_points = 1000; //try using 1000 or 10000
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glLineWidth(7.0f);
		glBegin(GL_LINE_LOOP);
		glColor3f(0.80f, 0.80f, 0.80f);//
		for (int i = 0; i < circle_points; i++)
		{
			angle = 1 * PI * i / circle_points;
			glVertex2f(cos(angle)*red, sin(angle)*red);
		}
		glEnd();
	glPopMatrix();

	glTranslatef(0.15f, 0.1f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.0f, -0.1f, 0.0f);
	glVertex3f(-0.2f, -0.4f, 0.0f);
	glEnd();
}