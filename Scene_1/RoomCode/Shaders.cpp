#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Header_Manishar.h"
#include "ClockHeader.h"
#include <math.h>
#include"Matrix.h"

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
	
	/*
	centerLookAt.z = -50.0f;
	arrayOfObjectInfo[3].centerOflookAt.x = 0.0f;
	arrayOfObjectInfo[3].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[3].centerOflookAt.z = -50.0f;
	arrayOfObjectInfo[3].speed = 0.02f;
	arrayOfObjectInfo[3].endPosition = -50.0f;

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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, centerLookAt.x, centerLookAt.y, centerLookAt.z, 0.0f, 1.0f, 0.0f);

	drawRoom();
	drawClock();
//	drawMatrixDoor();
	if (objectsIteration >= 2) { // Change if order in arrayObjectInfo gets change.
		drawMatrixRoom();
	}
	SwapBuffers(ghdc);
}

void drawMatrixDoor() {
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(matrixDoorPosition.x, matrixDoorPosition.y, matrixDoorPosition.z);
		glVertex3f(matrixDoorPosition.x + 10.0f, matrixDoorPosition.y, matrixDoorPosition.z);
		glVertex3f(matrixDoorPosition.x + 10.0f, 0.0f, matrixDoorPosition.z);
		glVertex3f(matrixDoorPosition.x, 0.0f, matrixDoorPosition.z);
	glEnd();
	glPopMatrix();
}

#pragma Matrix Room
void drawMatrixRoom() {
	glPushMatrix();
	glTranslatef(matrixRoomPosition.x, matrixRoomPosition.y, matrixRoomPosition.z);

	//BACK
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -gfWidthOfRoom);
	giTempNumberOfCharacterOnX = giNumberOfCharOnX;
	giNumberOfCharOnX = giNumberOfCharOnX + 34;
	DrawWall();
	giNumberOfCharOnX = giTempNumberOfCharacterOnX;
	glPopMatrix();
	
	//TOP
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -(gfHeightOfRoom));
	giTempNumberOfCharacterOnY = giNumberOfCharOnY;
	giNumberOfCharOnY = giNumberOfCharOnY + 1;
	DrawWall();
	giNumberOfCharOnY = giTempNumberOfCharacterOnY;
	glPopMatrix();
	
	//LEFT
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left 
	DrawWall();
	glPopMatrix();

	//RIGHT
	glPushMatrix();
	glTranslatef(gfHeightOfRoom, 0.0f, 0.0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left 
	DrawWall();
	glPopMatrix();

	//BOTTOM

	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	DrawWall();
	glPopMatrix();
	glPopMatrix();
}

void StoreWall() {
	DWORD dwTotalNumberOfCharacters = 0;
	int RandomNumber = 0;
	dwTotalNumberOfCharacters = (giNumberOfCharOnX*giNumberOfCharOnY);
	if (piRandomWallNumbers == NULL) {
		piRandomWallNumbers = (int *)malloc(sizeof(int)*(dwTotalNumberOfCharacters));
		if (piRandomWallNumbers == NULL)
		{
			//ERROR HANDLING
		}
		else
		{
			dwMaximumCharaFromWall = dwTotalNumberOfCharacters;
		}
	}
	if (dwMaximumCharaFromWall < dwTotalNumberOfCharacters) {
		piRandomWallNumbers = (int *)realloc(piRandomWallNumbers, (sizeof(int)*(dwTotalNumberOfCharacters - dwMaximumCharaFromWall)));
		if (piRandomWallNumbers == NULL)
		{
			//ERROR HANDLING
		}
		else {
			for (DWORD i = dwMaximumCharaFromWall; i < dwTotalNumberOfCharacters; i++)
			{
				RandomNumber = rand() % 27;
				piRandomWallNumbers[i] = RandomNumber;
			}
			dwMaximumCharaFromWall = dwTotalNumberOfCharacters;
		}
	}
	if ((gbWallFilled == FALSE)) {
		for (DWORD i = 0; i < dwTotalNumberOfCharacters; i++) {
			RandomNumber = rand() % 27;
			piRandomWallNumbers[i] = RandomNumber;
		}
		gbWallFilled = TRUE;
	}
	if (gbDisplayedFirstWall == FALSE) {
		gbDisplayedFirstWall = TRUE;
		dwDisplayedFirstWall = GetTickCount();
		dwSavedTickCount = dwDisplayedFirstWall;
	}
	dwGetTickCount = GetTickCount();
	if ((dwGetTickCount - dwSavedTickCount) >= gdwSpeedOfWallChange)
	{
		dwSavedTickCount = dwGetTickCount;
		gbWallFilled = FALSE;
	}
}

void RandomCharacter(int RandomNumber) {
	for (int i = 0; i < 7; i++)
	{
		giSevenSgment[i] = 0;
	}
	switch (RandomNumber)
	{
	case 0x0:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x1:
		giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x2:
		giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 0x3:
		giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = giSevenSgment[4] = giSevenSgment[3] = 1;
		break;
	case 0x4:
		giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[4] = 1;
		break;
	case 0x5:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[4] = giSevenSgment[3] = 1;
		break;
	case 0x6:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[3] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 0x7:
		giSevenSgment[0] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x8:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x9:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 10:	//a
		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 11:	//b
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[6] = 1;
		break;
	case 12:	//c
		giSevenSgment[6] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 13:	//d
		giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 14:	//e
		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[1] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 15:	//f
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[6] = 1;
		break;
	case 16:	//g	Added 3 to differentiate from 9
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[3] = 1;
		break;
	case 17:	//h
		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 18:	//j
		giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 19:	//L 
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 20:	//n
		giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[6] = 1;
		break;
	case 21:	//o
		giSevenSgment[2] = giSevenSgment[6] = giSevenSgment[3] = giSevenSgment[4] = 1;
		break;
	case 22:	//q	
		giSevenSgment[1] = giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[6] = 1;
		break;
	case 23:	//p
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 24:	//s	
		giSevenSgment[1] = giSevenSgment[0] = giSevenSgment[3] = giSevenSgment[6] = giSevenSgment[4] = 1;
		break;
	case 25:	//t
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[6] = 1;
		break;
	case 26:	//y	Add 3 to differentiate from 4
		giSevenSgment[1] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	}
	return;
}

void DrawCharacter() {
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(gfMatrixCharRed, gfMatrixCharGreen, gfMatrixCharBlue);
	/*4th LINE*/
	if (giSevenSgment[4] == 1)
	{
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), gfCurrentY, gfCurrentZ);
	}
	/*3rd LINE*/
	if (giSevenSgment[3] == 1)
	{
		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);
	}
	/*2nd LINE*/
	if (giSevenSgment[2] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);
	}
	/*6th LINE*/
	if (giSevenSgment[6] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY), (gfCurrentZ));
	}
	/*1st LINE*/
	if (giSevenSgment[1] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
		glVertex3f((gfCurrentX + .00f), (gfCurrentY + gfHeightOfLine), (gfCurrentZ + 0.0f));
	}
	/*0th LINE*/
	if (giSevenSgment[0] == 1)
	{
		glVertex3f(gfCurrentX, (gfCurrentY + gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);
	}

	/*5th LINE*/
	if (giSevenSgment[5] == 1)
	{
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), gfCurrentY, gfCurrentZ);
	}
	glEnd();
}

void DrawWall() {
	int iCounter = 0;
	int iRandomCharacterCount = giNumberOfCharOnX *giNumberOfCharOnY;
	StoreWall();
	for (int j = 0; j < giNumberOfCharOnY; j++)
	{
		for (int i = 0; i < giNumberOfCharOnX; i++)
		{
			RandomCharacter(piRandomWallNumbers[iCounter]);
			iCounter++;
			if (iCounter >= iRandomCharacterCount)
			{
				iCounter = 0;
			}
			//HERE WE DRAW ACTUAL CHARACTER 
			DrawCharacter();

			gfCurrentX = gfCurrentX + gfCommonXDistance;
		}
		gfWidthOfRoom = gfCurrentX;
		gfCurrentX = 0.0f;
		gfCurrentY = gfCurrentY + gfCommonYDistance + 0.1f;
	}
	gfHeightOfRoom = gfCurrentY;
	gfCurrentY = 0.0f;
	return;
}

#pragma Room
void drawRoom() {
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	int size = 27;
	int count = 1;
	glLineWidth(0.5f);
	glBegin(GL_LINES);
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	for (float i = count; i <= size; i += count) { //Floor
		glVertex3f(-size, 0, i);
		glVertex3f(size, 0, i);
		glVertex3f(-size, 0, -i);
		glVertex3f(size, 0, -i);
		glVertex3f(i, 0, -size);
		glVertex3f(i, 0, size);
		glVertex3f(-i, 0, -size);
		glVertex3f(-i, 0, size);
	}

	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex3f(roomDepth.xCor, roomDepth.yCor, -roomDepth.zCor); //Back
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, -roomDepth.zCor);
	glVertex3f(-roomDepth.xCor, 0.0f, -roomDepth.zCor);
	glVertex3f(roomDepth.xCor, 0.0f, -roomDepth.zCor);

	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-roomDepth.xCor, 0.0f, -roomSize.zCor); //Right
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, -roomSize.zCor);
	glVertex3f(-roomSize.xCor, roomDepth.yCor, roomSize.zCor);
	glVertex3f(-roomSize.xCor, 0.0f, roomSize.zCor);

	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(roomDepth.xCor, 0.0f, -roomSize.zCor); //Left
	glVertex3f(roomDepth.xCor, roomDepth.yCor, -roomSize.zCor);
	glVertex3f(roomSize.xCor, roomDepth.yCor, roomSize.zCor);
	glVertex3f(roomSize.xCor, 0.0f, roomSize.zCor);

	glEnd();
	glPopMatrix();
}

#pragma clock 
void drawClock() {
	// function declaration
	void drawClockSquare(void);
	void drawClockTimeNumbers(void);
	void drawClockSecondHand(void);
	void drawClockMinutehand(void);
	void drawClockHourHand(void);
	void drawClockNumbers();

	//Fill this struct for camera movement

	glPushMatrix(); //1
	glTranslatef(watchPosition.x, watchPosition.y, watchPosition.z);
	glPushMatrix(); //2
	//	drawClockNumbers();
	glPopMatrix();
	glPushMatrix(); //3
	drawClockSquare();
	drawClockTimeNumbers();
	glPopMatrix();
	glPushMatrix(); //4
	drawClockSecondHand();
	drawClockMinutehand();
	drawClockHourHand();
	glPopMatrix();
	glPopMatrix();
}
void updateSecondAngle(void) {
	gfSecondAngle = gfSecondAngle - (6.0f * PI / (180.0f));
	gfMinuteAngle = gfMinuteAngle - (6.0f * PI / (180.0f * 60.0f));
	gfHourAngle = gfHourAngle - (6.0f * PI / (180.0f * 60.0f * 12.0f));
}
void drawClockSquare() {

	glBegin(GL_QUADS);
	glColor3f((GLfloat)130.0f / (GLfloat) 255.0f, (GLfloat)82.0f / (GLfloat) 255.0f, (GLfloat)1.0f / (GLfloat) 255.0f);
	glVertex3f(-gfClockOuterLength, gfClockOuterLength, -0.05f);
	glVertex3f(gfClockOuterLength, gfClockOuterLength, -0.05f);
	glVertex3f(gfClockOuterLength, -gfClockOuterLength, -0.05f);
	glVertex3f(-gfClockOuterLength, -gfClockOuterLength, -0.05f);
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
	TCHAR str[255];
	int iNumberCounter = 0;
	void drawNumbers(int);

	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < giCirclePoints; i++) {
		float angle = (GLfloat)(2 * PI * i) / (GLfloat)giCirclePoints;
		if (i % 90 == 0) {
			glLineWidth(3.0f);
			glBegin(GL_LINES);
			glVertex3f(gfClockStepMin * (GLfloat)sin(angle), gfClockStepMin * (GLfloat)cos(angle), 0.0f);
			glVertex3f((gfClockStepMax)* (GLfloat)sin(angle), (gfClockStepMax)* (GLfloat)cos(angle), 0.0f);
			glEnd();
			drawNumbers(iNumberCounter);
			iNumberCounter++;
		}
		else if (i % 60 == 0) {
			glBegin(GL_LINES);
			glVertex3f((gfClockStepMin + 0.3f)  * (GLfloat)sin(angle), (gfClockStepMin + 0.3f) * (GLfloat)cos(angle), 0.0f);
			glVertex3f((gfClockStepMax + 0.3f)* (GLfloat)sin(angle), (gfClockStepMax + 0.3f)* (GLfloat)cos(angle), 0.0f);
			glEnd();
			drawNumbers(iNumberCounter);
			iNumberCounter++;
		}
		else if (i % 30 == 0) {
			glBegin(GL_LINES);
			glVertex3f((gfClockStepMin + 0.3f)  * (GLfloat)sin(angle), (gfClockStepMin + 0.3f) * (GLfloat)cos(angle), 0.0f);
			glVertex3f((gfClockStepMax + 0.3f)* (GLfloat)sin(angle), (gfClockStepMax + 0.3f)* (GLfloat)cos(angle), 0.0f);
			glEnd();
			drawNumbers(iNumberCounter);
			iNumberCounter++;

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
void drawClockNumbers() {
	int counter = 0;
	void drawNumbers(int);
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < giCirclePoints; i++) {
		float angle = 2 * PI * i / giCirclePoints;
		if (i % 30 == 0) {
			glPushMatrix();
			glTranslatef((gfClockStepMin)  * (GLfloat)sin(angle), (gfClockStepMin) * (GLfloat)cos(angle), 1.0f);
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

		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberTwelveDistanceFromOriginX, -gfNumberOneLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 1:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberOneDistanceFromOriginX, 0.0f + gfNumberOneDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberOneDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberOneDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberOneDistanceFromOriginX, 0.0f + gfNumberOneDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberOneDistanceFromOriginX, -gfNumberOneLengthY + gfNumberOneDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 2:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, 0.0f + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, 0.0f + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, 0.0f + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glEnd();

		break;
	case 3:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberThreeDistanceFromOriginX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, 0.0f, 0.0f);

		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f + gfNumberThreeDistanceFromOriginX, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMaxLengthY, 0.0f);
		glEnd();
		break;
	case 4:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberFourDistanceFromOriginX, 0.0f + gfNumberFourDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberFourDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFourDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberFourDistanceFromOriginX, 0.0f + gfNumberFourDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFourDistanceFromOriginX, -0.2f + gfNumberFourDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberFourDistanceFromOriginX, -0.2f + gfNumberFourDistanceFromOriginY, 0.0f);
		glVertex3f(0.1f + gfNumberFourDistanceFromOriginX, -0.2f + gfNumberFourDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 5:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, 0.0f + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, 0.0f + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, 0.0f + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 6:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, 0.0f + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, 0.0f + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, 0.0f + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 7:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberSevenDistanceFromOriginX, 0.0f + gfNumberSevenDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberSevenDistanceFromOriginX, 0.0f + gfNumberSevenDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberSevenDistanceFromOriginX, 0.0f + gfNumberSevenDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberSevenLengthX + gfNumberSevenDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSevenDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 8:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glEnd();
		//glPopMatrix();
		break;
	case 9:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glEnd();
		break;
	case 10:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX, 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX, 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberTenDistanceFromOriginX, -gfNumberOneLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glEnd();

		break;
	case 11:
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberElevenDistanceFromOriginX, -gfNumberOneLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, -gfNumberMaxLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, -gfNumberOneLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glEnd();

		glPopMatrix();

		break;
	default:
		break;
	}
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
