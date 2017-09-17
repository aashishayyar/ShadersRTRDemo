#include"MachineGunHeader.h"

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


//variable for Gun drsign
GLUquadric *quadric = NULL;
float GunRotate = 0;

//for translating half circle
float ZAxis;

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
		TEXT("Abhishek_Khapekar_79 | Machine_Gun"),
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
			GunRotate = ((int)GunRotate + 3) % 360;
			break;

		case 'e':
			GunRotate = ((int)GunRotate - 3) % 360;
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

void DrawCircle(float redius)
{
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0.0f; angle <= 2.0*PI; angle = angle + 0.01f)
	{
		glVertex3f(cos(angle)*redius, sin(angle)*redius, 0.0f);
	}
	glEnd();
}

void DrawHalfCircle(float ZAxis)
{
	float angle;
	GLfloat red = 1.3f;
	GLint circle_points = 1000; //try using 1000 or 10000

	glTranslatef(0.0f, 0.5f, ZAxis);
	glScalef(0.60f, 1.0f, 1.0f);
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
}

void DrawCylinder(float base ,float top,float height)
{
	glColor3f(0.70f, 0.70f, 0.70f);//Gray final
	quadric = gluNewQuadric();
	gluCylinder(quadric, base, top, height, 10, 10);
}

void DrawCube(void)
{
	glBegin(GL_QUADS);

	//Top face
	glColor3f(0.70f, 0.70f, 0.70f);//Gray final
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	//Bottom face
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	//front face 
	glVertex3f(1.0f, 1.0f, 1.0f);//right-top
	glVertex3f(-1.0f, 1.0f, 1.0f);//left-top
	glVertex3f(-1.0f, -1.0f, 1.0f);//left-bottom
	glVertex3f(1.0f, -1.0f, 1.0f);//right-bottom

	//Back face
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//Right face
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//left face
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}

void DrawMachineGun(void)
{
	glPushMatrix();
	glRotatef((GLfloat)GunRotate, 0.0f, 1.0f, 0.0f);
	//glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

		//main cylinder
		glPushMatrix();
		base = top = redius = 0.6f;
		height = 2.0f;
			
		DrawCylinder(base,top,height);
		//glColor3f(1.0f, 1.0f, 0.0f);
		DrawCircle(redius);

		//glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, height);
		DrawCircle(redius);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, height + 1.0F);
			DrawCircle(redius);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, height + 1.8F);
		DrawCircle(redius);
		glPopMatrix();

		//front pipes
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, height);
			base = top = redius = 0.12f;
			DrawCylinder(base, top, height + 0.5F);
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, height + 0.5F);
			DrawCircle(redius);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.33f, 0.0f, height);
			base = top = redius = 0.12f;
			DrawCylinder(base, top, height + 0.5F);
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, height + 0.5F);
			DrawCircle(redius);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.33f, 0.0f, height);
			base = top = redius = 0.12f;
			DrawCylinder(base, top, height + 0.5F);
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, height + 0.5F);
			DrawCircle(redius);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.2f, 0.35f, height);
			base = top = redius = 0.12f;
			DrawCylinder(base, top, height + 0.5F);
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, height + 0.5F);
			DrawCircle(redius);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.2f, -0.35f, height);
			base = top = redius = 0.12f;
			DrawCylinder(base, top, height + 0.5F);
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, height + 0.5F);
			DrawCircle(redius);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.15f, 0.35f, height);
			base = top = redius = 0.12f;
			DrawCylinder(base, top, height + 0.5F);
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, height + 0.5F);
			DrawCircle(redius);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.15f, -0.35f, height);
			base = top = redius = 0.12f;
			DrawCylinder(base, top, height + 0.5F);
			glTranslatef(0.0f, 0.0f, height + 0.5F);
			glColor3f(0.0f, 0.0f, 0.0f);
			DrawCircle(redius);
		glPopMatrix();

		//main cylinder left
		glPushMatrix();
			base = top = redius = 0.3f, height = 1.5f;
			glTranslatef(-0.7f, -0.5f, 0.0f);
			DrawCylinder(base, top, height);
			glColor3f(1.0f, 1.0f, 0.0f);
			DrawCircle(redius);
			glTranslatef(0.0f, 0.0f, height);
			DrawCircle(redius);
		glPopMatrix();

		//main cylinder right
		glPushMatrix();
			base = top = redius = 0.3f, height = 1.5f;
			glTranslatef(0.7f, -0.5f, 0.0f);
			DrawCylinder(base, top, height);
			glColor3f(1.0f, 1.0f, 0.0f);
			DrawCircle(redius);
			glTranslatef(0.0f, 0.0f, height);
			DrawCircle(redius);
		glPopMatrix();

		//BACK PIPE
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -height);
			base = top = redius = 0.15f;
			DrawCylinder(base, top, height+0.5f);
			glColor3f(0.0f, 0.0f, 0.0f);
			DrawCircle(redius);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0F, -0.2F, -1.0f);
			glScalef(0.30f,0.70f,0.10f);
			DrawCube();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.0F, 0.5F, -1.0f);
			glScalef(0.30f, 0.10f, 1.0f);
			DrawCube();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0F, 0.5F, 0.0f);
			glScalef(0.30f, 0.30f, 0.10f);
			DrawCube();
		glPopMatrix();

		glPushMatrix();
			DrawHalfCircle(2.0f);
		glPopMatrix();
				
		glPushMatrix();
			DrawHalfCircle(1.9f);
		glPopMatrix();
		
		glPushMatrix();
		DrawHalfCircle(1.8f);
		glPopMatrix();
		
		glPushMatrix();
			DrawHalfCircle(1.7f);
		glPopMatrix();

		glPushMatrix();
			DrawHalfCircle(1.6f);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, 0.9f, 1.0f);
			glScalef(0.30f, 0.10f, 1.1f);
			DrawCube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0F, 0.7F, 1.8f);
		glScalef(0.85f, 0.20f, 0.20f);
		DrawCube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.5F, 1.1F, 1.8f);
		glScalef(0.06f, 0.3f, 0.1f);
		DrawCube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.5F, 1.1F, 1.8f);
		glScalef(0.06f, 0.3f, 0.1f);
		DrawCube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.0F, 1.4F, 1.8f);
		glScalef(0.55f, 0.05f, 0.1f);
		DrawCube();
		glPopMatrix();

		glPushMatrix();
		base = top = redius = 0.2f,height = 1.0f;
		glTranslatef(0.0f, 1.5f, -1.5f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		DrawCylinder(base, top, height);
		DrawCircle(redius);
		glPopMatrix();
	

	glPopMatrix();	
}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glTranslatef(0.0f, 0.0f, -12.0f);


	DrawMachineGun();

	/*GunRotate = GunRotate + 0.1f;
	if (GunRotate >= 360.0f)
		GunRotate = 0.0f;*/

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