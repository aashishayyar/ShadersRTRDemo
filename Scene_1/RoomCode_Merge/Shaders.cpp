#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Main_Header.h""
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	void moveCamera();

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
				moveCamera();
				display();
			}
		}
	}
	uninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	void display(void);
	void resize(int, int);
	void toggleFullscreen(void);
	void uninitialised(void);
	void updateSecondAngle(void);

	switch (iMsg)
	{
	case WM_CREATE:
		//SetTimer(hwnd, IDT_TIMER_SECOND, 1000, NULL);
		SetTimer(hwnd, IDT_TIMER_MINUTE, 1000 * 11, NULL);
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
		default:
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_TIMER_SECOND:
			//MessageBox(hwnd, TEXT("1 second"), TEXT("Second"), MB_OK);
			updateSecondAngle();
		case IDT_TIMER_MINUTE:
			if (objectsIteration < numberOfObjects) {
				currentObject = arrayOfObjectInfo[objectsIteration];
				objectsIteration++;
			}
		default:
			break;
		}
		break;
	case WM_ERASEBKGND:
		return(0);
		break;

	default:
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void moveCamera() {
	if (cameraPosition.y < currentObject.centerOflookAt.y) {
		cameraPosition.y = cameraPosition.y + currentObject.speed;
	}
	if (centerLookAt.y < currentObject.centerOflookAt.y) {
		centerLookAt.y = centerLookAt.y + currentObject.speed;
	}
	if (cameraPosition.x < currentObject.centerOflookAt.x) {
		cameraPosition.x = cameraPosition.x + currentObject.speed;
	}
	if (centerLookAt.x < currentObject.centerOflookAt.x) {
		centerLookAt.x = centerLookAt.x + currentObject.speed;
	}
	//If it is greater decrease value
	if (cameraPosition.y > currentObject.centerOflookAt.y) {
		cameraPosition.y = cameraPosition.y - currentObject.speed;
	}
	if (centerLookAt.y > currentObject.centerOflookAt.y) {
		centerLookAt.y = centerLookAt.y - currentObject.speed;
	}
	if (cameraPosition.x > currentObject.centerOflookAt.x) {
		cameraPosition.x = cameraPosition.x - currentObject.speed;
	}
	if (centerLookAt.x > currentObject.centerOflookAt.x) {
		centerLookAt.x = centerLookAt.x - currentObject.speed;
	}
	if (currentObject.isRotation == false) {
		if (cameraPosition.z > currentObject.endPosition) {
			cameraPosition.z = cameraPosition.z - currentObject.speed;
		}
		if (cameraPosition.z < currentObject.endPosition) {
			cameraPosition.z = cameraPosition.z + currentObject.speed;
		}
	}
	else if (currentObject.isRotation == true) {
		switch (currentObject.axisOfRotation) {
		case 1://X Axis

			break;
		case 2://Y Axis
			if (currentObject.startAngle < currentObject.endAngle) {
				if (currentObject.isCameraFixed == true) {
					centerLookAt.z = cos(currentObject.startAngle) * currentObject.rotationRadius.z;
					centerLookAt.x = sin(currentObject.startAngle) * currentObject.rotationRadius.x;
				}
				else {
					cameraPosition.z = cos(currentObject.startAngle) * currentObject.rotationRadius.z;
					cameraPosition.x = sin(currentObject.startAngle) *  currentObject.rotationRadius.x;
				}
				currentObject.startAngle = currentObject.startAngle + currentObject.speed;
			}
			break;
		case 3://Z Axis

			break;
		default:
			break;
		}
	}
}

void resetLookAtCenter() {
	centerLookAt.x = 0.0f;
	centerLookAt.y = roomSize.yCor / 2.0f;
	centerLookAt.z = 0.0f;
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

void fillCameraObjectInfo() {
	//Initialising currentObject to room coodinates
	currentObject.centerOflookAt.x = centerLookAt.x;
	currentObject.centerOflookAt.y = centerLookAt.y;
	currentObject.centerOflookAt.z = centerLookAt.z;
	currentObject.endPosition = cameraPosition.z;
	currentObject.speed = 0.001f;
	currentObject.isRotation = false;
	//currentObject.axisOfRotation = 2;
	//currentObject.startAngle = 0.0f;
	//currentObject.endAngle = 90.0f;

	//ObjectCameraInfo for watchInfo;
	centerLookAt.z = -50.0f;
	arrayOfObjectInfo[0].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[0].centerOflookAt.y = watchPosition.y;
	arrayOfObjectInfo[0].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[0].speed = 0.01f;
	arrayOfObjectInfo[0].endPosition = watchPosition.z + 10.0f;
	arrayOfObjectInfo[0].isRotation = false;

	//For Matrix Room
	centerLookAt.z = -79.0f;
	arrayOfObjectInfo[1].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[1].centerOflookAt.y = watchPosition.y;
	arrayOfObjectInfo[1].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[1].speed = 0.11f;
	arrayOfObjectInfo[1].endPosition = matrixRoomPosition.z - 29;
	arrayOfObjectInfo[1].isRotation = false;

	
	//centerLookAt.z = -50.0f;
	arrayOfObjectInfo[2].centerOflookAt.x = 0.0f;
	arrayOfObjectInfo[2].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[2].centerOflookAt.z = -20.0f;
	arrayOfObjectInfo[2].speed = 0.2f;
	arrayOfObjectInfo[2].endPosition = -20.0f;
	arrayOfObjectInfo[2].isRotation = false;
	
	
	arrayOfObjectInfo[3].centerOflookAt.x = centerLookAt.x;
	arrayOfObjectInfo[3].centerOflookAt.y = centerLookAt.y;
	arrayOfObjectInfo[3].centerOflookAt.z = centerLookAt.z;
	arrayOfObjectInfo[3].speed = 0.05f;
	arrayOfObjectInfo[3].endPosition = watchPosition.z + 50.0;
	arrayOfObjectInfo[3].isRotation = false;


	/*
	arrayOfObjectInfo[3].isRotation = true;
	arrayOfObjectInfo[3].axisOfRotation = 2; // 2 for y axis 
	arrayOfObjectInfo[3].startAngle = 0.0f;
	arrayOfObjectInfo[3].endAngle = 1.0f;
	arrayOfObjectInfo[3].isCameraFixed = true;
	arrayOfObjectInfo[3].rotationRadius.x = -10.0f;
	arrayOfObjectInfo[3].rotationRadius.z = -50.0f;

	//To reset camera to original position
	arrayOfObjectInfo[2].centerOflookAt.x = centerLookAt.x;
	arrayOfObjectInfo[2].centerOflookAt.y = centerLookAt.y;
	arrayOfObjectInfo[2].centerOflookAt.z = centerLookAt.z;
	arrayOfObjectInfo[2].speed = 0.1f;
	arrayOfObjectInfo[2].endPosition = 35.0f;
	arrayOfObjectInfo[2].isRotation = false;

	arrayOfObjectInfo[3].centerOflookAt.x = matrixDoorPosition.x;
	arrayOfObjectInfo[3].centerOflookAt.y = matrixDoorPosition.y;
	arrayOfObjectInfo[3].centerOflookAt.z = matrixDoorPosition.z;
	arrayOfObjectInfo[3].speed = 0.01f;
	arrayOfObjectInfo[3].endPosition = matrixDoorPosition.z;
	arrayOfObjectInfo[3].isRotation = false;
	*/
}

void display(void) {
	void drawRoom();
	void drawClock();
	void DrawCharacter();
	void drawMatrixDoor();
	void drawMatrixRoom();
	void drawMatrixDoor();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, centerLookAt.x, centerLookAt.y, centerLookAt.z, 0.0f, 1.0f, 0.0f);

	drawRoom();
	glPushMatrix();
		glTranslatef(watchPosition.x, watchPosition.y, watchPosition.z);
		drawClock();
	glPopMatrix();
	if (objectsIteration >= 2 && objectsIteration <=3) { // Change if order in arrayObjectInfo gets change.
		glPushMatrix();
			glTranslatef(matrixRoomPosition.x, matrixRoomPosition.y, matrixRoomPosition.z);
			drawMatrixRoom();
		glPopMatrix();
	}
	//drawMatrixDoor();
	SwapBuffers(ghdc);
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
