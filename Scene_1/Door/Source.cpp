#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<math.h>
#include "DoorHeader.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool gbIsActiveWindow = false;
bool gbIsFullscreen = false;
bool gbIsEscapedKeyPressed = false;
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle = NULL;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstancec, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Shader Demo");
	bool bDone = false;

	// Function declaration
	void initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);

	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(GetStockObject(BLACK_BRUSH));
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;

	RegisterClassEx(&wndClass);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Clock Demo"),
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

	while (bDone == false) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				bDone = true;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			if (gbIsActiveWindow == true) {
				update();
				display();
				if (gbIsEscapedKeyPressed == true) {
					bDone = true;
				}
			}
		}
	}
	uninitialize();
	return (int)(msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	// Function declaration
	void ToggleFullscreen(void);
	void resize(int, int);
	void updateSecondAngle();
	switch (iMsg) {
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0) {
			gbIsActiveWindow = true;
		}
		else {
			gbIsActiveWindow = false;
		}
		break;
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			gbIsEscapedKeyPressed = true;
			break;
		case 0x46:
			ToggleFullscreen();
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullscreen(void) {

	MONITORINFO mi;

	if (gbIsFullscreen == false) {
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle && WS_OVERLAPPEDWINDOW) {
			mi = { sizeof(MONITORINFO) };
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi)) {
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, (mi.rcMonitor.right - mi.rcMonitor.left), (mi.rcMonitor.bottom - mi.rcMonitor.top), SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
		gbIsFullscreen = true;
	}
	else {

		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
		gbIsFullscreen = false;

	}
}

void initialize() {

	// function declaration
	void resize(int, int);
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	ghdc = GetDC(ghwnd);
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0) {
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE) {
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL) {
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}
	if (wglMakeCurrent(ghdc, ghrc) == FALSE) {
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	resize(WIN_WIDTH, WIN_HEIGHT);
}

void resize(int width, int height) {
	if (height == 0) {
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, GLfloat(width) / GLfloat(height), 0.1f, 100.0f);
}

void display(void) {

	// function declaration
	void drawWall(void);
	void drawDoor(void);
	void drawDoorKnob(void);
	void drawDoorFrame(void);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -50.0f);
	glBegin(GL_LINES);
	/*glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(40.0f, 0.0f, 0.0f);
	glVertex3f(-40.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 22.0f, 0.0f);
	glVertex3f(0.0f, -22.0f, 0.0f);
	glVertex3f(10.0f, 22.0f, 0.0f);
	glVertex3f(10.0f, -22.0f, 0.0f);*/
	glEnd();
	
	drawWall();
	glPushMatrix();
	drawDoor();
	glPopMatrix();
	//drawDoorKnob();
	drawDoorFrame();

	SwapBuffers(ghdc);
}

void drawWall(void) {

	
	glBegin(GL_POLYGON);
	glColor3f( 67.0f/255.0f, 72.0f / 255.0f, 76.0f / 255.0f);
	glVertex3f(-40.0f, 22.0f, 0.0f);
	glVertex3f(-40.0f, -22.0f, 0.0f);
	glVertex3f(0.0f, -22.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 22.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(40.0f, 22.0f, 0.0f);
	glVertex3f(40.0f, -22.0f, 0.0f);
	glVertex3f(10.0f, -22.0f, 0.0f);
	glVertex3f(10.0f, 22.0f, 0.0f);
	glEnd();
	glPushMatrix();
	//glTranslatef(-5.0f, 0.0f, 0.0f);
/*	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(40.0f, 0.0f, 0.0f);
	glVertex3f(-40.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 22.0f, 0.0f);
	glVertex3f(0.0f, -22.0f, 0.0f);
	glEnd();
	*/

}

void drawDoor(void) {
	
	glRotatef(gfDoorRotationAngle, 0.0f, 1.0f, 0.0f);
	
	glBegin(GL_QUADS);
	glColor3f((GLfloat) gfDoorMainColor[0], (GLfloat)gfDoorMainColor[1], (GLfloat)gfDoorMainColor[2]);
	// Front face
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, - gfDoorLength, 0.0f);
	glVertex3f(10.0f, - gfDoorLength, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	//Back face
	glVertex3f(0.0f, 0.0f, - gfDoorThickness);
	glVertex3f(0.0f, -gfDoorLength, - gfDoorThickness);
	glVertex3f(10.0f, -gfDoorLength, - gfDoorThickness);
	glVertex3f(10.0f, 0.0f, - gfDoorThickness);

	//Left face
	glVertex3f(0.0f, 0.0f, -gfDoorThickness);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -gfDoorLength, 0.0f);
	glVertex3f(0.0f, -gfDoorLength, -gfDoorThickness);
	
	//Right Face
	glVertex3f(10.0f, 0.0f, -gfDoorThickness);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, -gfDoorLength, 0.0f);
	glVertex3f(10.0f, -gfDoorLength, -gfDoorThickness);

	//Top Face
	glVertex3f(10.0f, 0.0f, -0.5f);
	glVertex3f(0.0f, 0.0f, -0.5f);
	glVertex3f(0.0f, 0.0f, 0.0);
	glVertex3f(10.0f, 0.0f, 0.0);

	//Bottom Face
	glVertex3f(10.0f, -22.0f, -0.5f);
	glVertex3f(0.0f, -22.0f, -0.5f);
	glVertex3f(0.0f, -22.0f, 0.0);
	glVertex3f(10.0f, -22.0f, 0.0);
	glEnd();

	/*
	
	glBegin(GL_QUADS);
	glColor3f(112.0f / 255.0f, 79.0f / 255.0f, 46.0f / 255.0f);
	//Door Upper Middle Part
	//Back
	glVertex3f(2.0f, -3.0f, 0.0f);
	glVertex3f(8.0f, -3.0f, 0.0f);
	glVertex3f(8.0f, -12.0f, 0.0f);
	glVertex3f(2.0f, -12.0f, 0.0f);
	//Front
	glVertex3f(2.2f, -3.2f, 0.05f);
	glVertex3f(7.8f, -3.2f, 0.05f);
	glVertex3f(7.8f, -11.8f, 0.05f);
	glVertex3f(2.2f, -11.8f, 0.05f);
	glColor3f(89.0f / 255.0f, 60.0f / 255.0f, 31.0f / 255.0f);
	//Left	
	glVertex3f(2.0f, -3.0f, 0.0f);
	glVertex3f(2.2f, -3.2f, 0.05f);
	glVertex3f(2.2f, -11.8f, 0.05f);
	glVertex3f(2.0f, -12.0f, 0.0f);

	//Right
	glVertex3f(8.0f, -3.0f, 0.0f);
	glVertex3f(7.8f, -3.2f, 0.05f);
	glVertex3f(7.8f, -11.8f, 0.05f);
	glVertex3f(8.0f, -12.0f, 0.0f);

	//Top
	glVertex3f(2.0f, -3.0f, 0.0f);
	glVertex3f(8.0f, -3.0f, 0.0f);
	glVertex3f(7.8f, -3.2f, 0.05f);	
	glVertex3f(2.2f, -3.2f, 0.05f);
	//Bottom
	glVertex3f(2.0f, -12.0f, 0.0f);
	glVertex3f(8.0f, -12.0f, 0.0f);
	glVertex3f(7.8f, -11.8f, 0.05f);
	glVertex3f(2.2f, -11.8f, 0.05f);


	//Door Lower Middle Part
	glColor3f(112.0f / 255.0f, 79.0f / 255.0f, 46.0f / 255.0f);
	//Back
	glVertex3f(2.0f, -14.0f, 0.0f);
	glVertex3f(8.0f, -14.0f, 0.0f);
	glVertex3f(8.0f, -19.0f, 0.0f);
	glVertex3f(2.0f, -19.0f, 0.0f);
	//Front
	glVertex3f(2.2f, -14.2f, 0.05f);
	glVertex3f(7.8f, -14.2f, 0.05f);
	glVertex3f(7.8f, -18.8f, 0.05f);
	glVertex3f(2.2f, -18.8f, 0.05f);

	glColor3f(89.0f / 255.0f, 60.0f / 255.0f, 31.0f / 255.0f);
	//Left	
	glVertex3f(2.0f, -14.0f, 0.0f);
	glVertex3f(2.2f, -14.2f, 0.05f);
	glVertex3f(2.2f, -18.8f, 0.05f);
	glVertex3f(2.0f, -19.0f, 0.0f);

	//Right
	glVertex3f(8.0f, -14.0f, 0.0f);
	glVertex3f(7.8f, -14.2f, 0.05f);
	glVertex3f(7.8f, -18.8f, 0.05f);
	glVertex3f(8.0f, -19.0f, 0.0f);

	//Top
	glVertex3f(2.0f, -14.0f, 0.0f);
	glVertex3f(2.2f, -14.2f, 0.05f);
	glVertex3f(7.8f, -14.2f, 0.05f);
	glVertex3f(8.0f, -14.0f, 0.0f);
	
	
	//Bottom
	glVertex3f(2.0f, -19.0f, 0.0f);
	glVertex3f(8.0f, -19.0f, 0.0f);
	glVertex3f(7.8f, -18.8f, 0.05f);
	glVertex3f(2.2f, -18.8f, 0.05f);
	glEnd();

	*/
	glPopMatrix();


}

void drawDoorKnob(void) {
	glPushMatrix();
	glRotatef(gfDoorRotationAngle, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glScalef(5.0f, 5.0f, 5.0f);
	glBegin(GL_QUADS);
	glColor3f(27.0f/255.0f, 25.0f / 255.0f, 28.0f / 255.0f);
	//Front
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	//Back
	glVertex3f(-1.0f, -1.0f, -0.15f);
	glVertex3f(1.0f, -1.0f, -0.15f);
	glVertex3f(1.0f, 1.0f, -0.15f);
	glVertex3f(-1.0f, 1.0f, -0.15f);
	glEnd();
	glPopMatrix();
	glPushMatrix();	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	knobHead = gluNewQuadric();
	knobCylinder = gluNewQuadric();
	gluQuadricDrawStyle(knobCylinder, GLU_FILL);
	gluCylinder(knobCylinder, 1.0f, 1.0f, 2.0f, 50, 5);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 2.0f);
	gluSphere(knobHead, 1.5f, 10, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawDoorFrame(void) {
	glColor3f((GLfloat) 128.0f / (GLfloat) 255.0f, (GLfloat)94.0f / (GLfloat) 255.0f, (GLfloat)59.0f / (GLfloat) 255.0f);
	glBegin(GL_QUADS);
	glVertex3f(-0.8, 0.0f, 0.0f);
	glVertex3f(-0.8, -22.0f, 0.0f);
	glVertex3f(-0.1, -22.0f, 0.0f);
	glVertex3f(-0.1, -0.8f, 0.0f);


	glVertex3f(10.8, 0.0f, 0.0f);
	glVertex3f(10.8, -22.0f, 0.0f);
	glVertex3f(10.1, -22.0f, 0.0f);
	glVertex3f(10.1, -0.8f, 0.0f);


	glVertex3f(-0.8, 0.0f, 0.0f);
	glVertex3f(10.8, 0.0f, 0.0f);
	glVertex3f(10.1, -0.8f, 0.0f);
	glVertex3f(-0.1, -0.8f, 0.0f);
	
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.1, -0.8f, 0.0f);
	glVertex3f(-0.8, 0.0f, 0.0f);
	glVertex3f(10.8, 0.0f, 0.0f);
	glVertex3f(10.1, -0.8f, 0.0f);
	glVertex3f(-0.1, -0.8f, 0.0f);
	glVertex3f(10.1, -0.8f, 0.0f);

	glVertex3f(-0.1, -0.8f, 0.0f);
	glVertex3f(-0.1, -22.0f, 0.0f);
	glVertex3f(10.1, -0.8f, 0.0f);
	glVertex3f(10.1, -22.0f, 0.0f);
	glEnd();
}
void uninitialize(void) {
	if (gbIsFullscreen == true) {
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_FRAMECHANGED);
	}
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(ghrc);
	ghrc = NULL;
	ReleaseDC(ghwnd, ghdc);
	ghdc = NULL;
	DestroyWindow(ghwnd);
	ghwnd = NULL;
}

void update(void) {
	
	if (gbDoorMovement) {
		gfDoorRotationAngle = gfDoorRotationAngle + 0.005f;
		if (gfDoorRotationAngle >= 80.0f ) {
			//gfDoorRotationAngle = 0.0f;
			gbDoorMovement = false;
		}
	}
	


	
}