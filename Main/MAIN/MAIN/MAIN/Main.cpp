#include "Main.h"
#include "logo.h"
#include "Main_Room.h"
#include "LegoWalk.h"
#include <stdio.h>
FILE *fp;

extern float gfTranslateX;
extern bool gbStopLegoCharacters;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//Prototype Of WndProc() declared Globally
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global variable declarations
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD style;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbActiveWindow = false;
bool gbEscapeKeyPressed = false;
bool gbFullScreen = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	void initialize(void);
	void display(void);
	void uninitialize(void);
	void update();

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("RTROGL");
	bool bDone = false;

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

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szClassName,
		TEXT("OpenGL"),
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

	initialize();

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
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
				if (gbEscapeKeyPressed == true)
					bDone = true;
				update();
				display();
			}
		}
	}
	uninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void resize(int, int);
	void toggleFullscreen(void);
	void uninitialize(void);

	switch (iMsg)
	{
	case WM_CREATE:
		fopen_s(&fp, "MyDebug.txt", "w");
		SetTimer(hwnd, IDT_TIMER_SECOND, 1000, NULL);
		SetTimer(hwnd, IDT_TIMER_MINUTE, 1000 * 16, NULL);
		break;
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
			if (gbEscapeKeyPressed == false)
			{
				gbEscapeKeyPressed = true;
			}
			break;
		case 0x46://F
			toggleFullscreen();
			break;
		case 'L':
			fprintf(fp, "gfTranslateX : %f\n", gfTranslateX);
			CameraSteady = true;
			break;
		default:
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_TIMER_SECOND:
			if (giDoorMovementTimer < 6) {
				giDoorMovementTimer++;
			}
			updateSecondAngle();
			break;
		case IDT_TIMER_MINUTE:
			if (objectsIteration < numberOfObjects) {
				currentObject = arrayOfObjectInfo[objectsIteration];
				objectsIteration++;
			}
			break;
		default:
			break;
		}
		break;
	case WM_ERASEBKGND:
		return(0);
		break;
	case WM_CLOSE:
		fclose(fp);
		uninitialize();
		break;
	case WM_DESTROY:
		KillTimer(hwnd, IDT_TIMER_SECOND);
		KillTimer(hwnd, IDT_TIMER_MINUTE);
		fclose(fp);
		uninitialize();
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void toggleFullscreen(void) {
	BOOL isWindowPlacement;
	BOOL isMonitorInfo;

	if (gbFullScreen == false) {
		gbFullScreen = true;
		style = GetWindowLong(ghwnd, GWL_STYLE);
		//Does it include overlappedwindow
		if (style & WS_OVERLAPPEDWINDOW)
		{
			//To get hmonitor call monitor from window
			MONITORINFO monitorInfo;
			monitorInfo.cbSize = sizeof(MONITORINFO);
			HMONITOR hmonitor = MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY);
			isMonitorInfo = GetMonitorInfo(hmonitor, &monitorInfo);
			isWindowPlacement = GetWindowPlacement(ghwnd, &wpPrev);
			if (isWindowPlacement && isMonitorInfo)
			{
				SetWindowLong(ghwnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd,
					HWND_TOP,
					monitorInfo.rcMonitor.left,
					monitorInfo.rcMonitor.top,
					monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
					monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(false);
	}
	else {
		gbFullScreen = false;
		SetWindowLong(ghwnd, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,
			HWND_TOP,
			0,//It is taken care by setwindowplacement
			0,
			0,
			0,
			SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
		ShowCursor(true);
	}
}

void initialize(void) {
	void resize(int, int);
	void fillCameraObjectInfo(void);

	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glDepthFunc(GL_LEQUAL);
	fillCameraObjectInfo();
	resize(WIN_WIDTH, WIN_HEIGHT);
}

void display(void) {
	void legoCharaters();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	MainRoom();
	DrawNeo();
	legoCharaters();
	SwapBuffers(ghdc);
}

void legoCharaters() {
	if (objectsIteration == 1 || objectsIteration == 2) {
		glPushMatrix();
		glTranslatef(legoCharactersPosition.x, legoCharactersPosition.y, legoCharactersPosition.z);
		DrawLegoCharacters();
		drawLogo();
		updateAllCharacters();
		if (gbStopLegoCharacters)
		{
			updateAllCharacters();
		}
		glPopMatrix();
	}
}

void update(void) {
	moveCamera();
	moveNeo();
	updateDoorAngle();
}

void resize(int width, int height) {
	//code
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
}

void uninitialize(void) {
	if (gbFullScreen == true) {
		style = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
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