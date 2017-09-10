#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<math.h>
#include "ClockHeader.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")


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
				//update();
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
	case WM_CREATE:
		SetTimer(hwnd, IDT_TIMER_SECOND, 1000, NULL);
		break;
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
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_TIMER_SECOND:
			//MessageBox(hwnd, TEXT("1 second"), TEXT("Second"), MB_OK);
			updateSecondAngle();
		default:
			break;
		}
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
	void drawClockSquare(void);
	void drawClockTimeNumbers(void);
	void drawClockSecondHand(void);
	void drawClockMinutehand(void);
	void drawClockHourHand(void);
	void drawClockNumbers();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -12.0f);
	glPushMatrix();
	drawClockNumbers();
	glPopMatrix();
	glPushMatrix();
	drawClockSquare();
	drawClockTimeNumbers();
	glPopMatrix();
	glPushMatrix();
	drawClockSecondHand();
	drawClockMinutehand();
	drawClockHourHand();
	glPopMatrix();
	SwapBuffers(ghdc);
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

void drawClockSquare() {

	glBegin(GL_QUADS);
	glColor3f( (GLfloat)130.0f / (GLfloat) 255.0f, (GLfloat)82.0f / (GLfloat) 255.0f, (GLfloat)1.0f / (GLfloat) 255.0f);
	glVertex3f(-gfClockOuterLength, gfClockOuterLength, 0.0f);
	glVertex3f(gfClockOuterLength, gfClockOuterLength, 0.0f);
	glVertex3f(gfClockOuterLength, -gfClockOuterLength, 0.0f);
	glVertex3f(-gfClockOuterLength, -gfClockOuterLength, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-gfClockLength, gfClockLength, 0.0f);
	glVertex3f(gfClockLength, gfClockLength, 0.0f);
	glVertex3f(gfClockLength, -gfClockLength, 0.0f);
	glVertex3f(-gfClockLength, -gfClockLength, 0.0f);
	glEnd();
	glLineWidth(1.0f);
}

void drawClockTimeNumbers() {
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < giCirclePoints; i++) {
		float angle = (GLfloat)(2 * PI * i)/ (GLfloat)giCirclePoints;
		if (i % 90 == 0) {
			glVertex3f( gfClockStepMin * (GLfloat)sin(angle), gfClockStepMin * (GLfloat)cos(angle), 0.0f);
			glVertex3f((gfClockStepMax)* (GLfloat)sin(angle), (gfClockStepMax)* (GLfloat)cos(angle), 0.0f);
		}
		else if (i% 60 == 0) {
			glVertex3f((gfClockStepMin + 0.3f)  * (GLfloat)sin(angle), (gfClockStepMin + 0.3f) * (GLfloat)cos(angle), 0.0f);
			glVertex3f((gfClockStepMax + 0.3f)* (GLfloat)sin(angle), (gfClockStepMax + 0.3f)* (GLfloat)cos(angle), 0.0f);
		}
		else if (i% 30 == 0) {
	
			glVertex3f((gfClockStepMin + 0.3f)  * (GLfloat)sin(angle), (gfClockStepMin + 0.3f) * (GLfloat)cos(angle), 0.0f);
			glVertex3f((gfClockStepMax + 0.3f)* (GLfloat)sin(angle), (gfClockStepMax + 0.3f)* (GLfloat)cos(angle), 0.0f);
		
		}

	}
	glEnd();
}

void drawClockSecondHand(void) {

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gfClockSecondHandRadious * (GLfloat)cos(gfSecondAngle), gfClockSecondHandRadious * (GLfloat)sin(gfSecondAngle), 0.0f);
	glEnd();
}
void drawClockMinutehand(void) {
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gfClockMinuteHandRadious * (GLfloat)cos(gfMinuteAngle), gfClockMinuteHandRadious * (GLfloat)sin(gfMinuteAngle), 0.0f);
	glEnd();
}
void drawClockHourHand(void) {
	glLineWidth(4.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gfClockHourHandRadious  * (GLfloat)cos(gfHourAngle), gfClockHourHandRadious  * (GLfloat)sin(gfHourAngle), 0.0f);
	glEnd();
}

void updateSecondAngle(void) {
	gfSecondAngle = gfSecondAngle - (6.0f * PI / (180.0f));
	gfMinuteAngle = gfMinuteAngle - (6.0f * PI / (180.0f * 60.0f ));
	gfHourAngle = gfHourAngle - (6.0f * PI / (180.0f * 60.0f * 12.0f));
}
void drawClockNumbers() {
	int counter = 0;
	void drawNumbers(int);
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < giCirclePoints; i++) {
		float angle = 2 * PI * i / giCirclePoints;
		if (i % 30 == 0) {
			glPushMatrix();
			glTranslatef((gfClockStepMin )  * (GLfloat)sin(angle), (gfClockStepMin ) * (GLfloat)cos(angle), 1.0f);
			drawNumbers(counter);
			glPopMatrix();
			counter++;
		}
	}
	glPopMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);

}

void drawNumbers(int iClockNumberKeys) {

	switch (iClockNumberKeys)
	{
	case 0:
		glTranslatef(-0.1f, - 0.25f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberOneLengthX, -gfNumberOneLengthY, 0.0f);
		glEnd();
		glTranslatef(0.15f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);
		glEnd();
		break;
	case 1:
		glTranslatef(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberOneLengthX, -gfNumberOneLengthY, 0.0f);
		glEnd();
		break;
	case 2:
		glPushMatrix();
		glTranslatef(-0.15f, 0.15f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);
		glEnd();
		glPopMatrix();
		break;
	case 3:
		glPushMatrix();
		glTranslatef(-0.4f, 0.15f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, 0.0f, 0.0f);

		glVertex3f(gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);

		glVertex3f(gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);
		glEnd();
		glPopMatrix();
		break;
	case 4:
		glPushMatrix();
		glTranslatef(-0.1f, 0.15f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -0.2f, 0.0f);

		glVertex3f(-gfNumberMinLengthX, -0.2f, 0.0f);
		glVertex3f(0.1f, -0.2f, 0.0f);
		glEnd();
		glPopMatrix();
		break;
	case 5:
		glPushMatrix();
		glTranslatef(0.0f, 0.35f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);

		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(-gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);
		glEnd();
		glPopMatrix();
		break;
	case 6:
		glPushMatrix();
		glTranslatef(0.1f, 0.55f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);

		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(-gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(-gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glEnd();
		glPopMatrix();
		break;
	case 7:
		glPushMatrix();
		glTranslatef(-0.1f, 0.3f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(gfNumberSevenLengthX, -gfNumberMaxLengthY, 0.0f);
		glEnd();
		glPopMatrix();
		break;
	case 8:
		glPushMatrix();
		glTranslatef(0.15f, 0.1f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);

		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(-gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(-gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);

		glEnd();
		glPopMatrix();
		break;
	case 9:
		glPushMatrix();
		// Number 9
		glTranslatef(0.4f, 0.15f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);

		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(-gfNumberMinLengthX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -gfNumberMinLengthY, 0.0f);

		glEnd();
		glPopMatrix();
		break;
	case 10:	
		glTranslatef(0.1f, 0.15f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberOneLengthX, -gfNumberOneLengthY, 0.0f);
		glEnd();
		glTranslatef(0.25f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);

		glVertex3f(-gfNumberMinLengthX, 0.0f, 0.0f);
		glVertex3f(-gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(-gfNumberMinLengthX, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();

		break;
	case 11:
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberOneLengthX, -gfNumberOneLengthY, 0.0f);
		glEnd();
		glTranslatef(0.2f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-gfNumberOneLengthX, -gfNumberOneLengthY, 0.0f);
		glEnd();
		glPopMatrix();
		break;
	default:
		break;
	}

}
