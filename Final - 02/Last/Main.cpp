#include "Main.h"
#include "logo.h"
#include "Main_Room.h"
#include "LegoWalk.h"
#include "Main_auxiliary_variable.h"
#include "Bullet.h"
#include "ShadersBullets.h"
//#include "DropLines.h"

FILE *fp;

extern float gfTranslateNeoX;
extern float gfTranslateNeoZ;
extern bool gbStopLegoCharacters;
extern float gfNeoRotate_Y;
extern float gfBulletTranslateX;
extern struct TranslateLine *ptrTranslateLine;
extern int *piRandomLineNumbers;
extern int giCountBullet;
extern float yFreeFall;
bool dropShadersBullets = false;
bool deleteShadersBullets = false;
	
int giCurrentCreditLego = 0;

GLfloat change = 0.5f;
int delayRipple = 1;
int sceneIndex = 1;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"winmm.lib")

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

float moveX = -8.0;
float moveY = 5.0;
float moveZ = 9.0;
extern bool dropShadersBullets;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	void initialize(void);
	void display(void);
	void uninitialize(void);
	void toggleFullscreen();
	void update();

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("SHADERS");
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

	PlaySound(sound[0], NULL, SND_ASYNC);

	toggleFullscreen();
	gbFullScreen = true;

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
//		PlaySound(sound[0], NULL, SND_ASYNC);
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
			fprintf(fp, "gfTranslateNeoX : %f\tgfTranslateNeoZ : %f\tgfRotateneo : %f\tgfBulletTranslateX : %f\n", gfTranslateNeoX, gfTranslateNeoZ, gfNeoRotate_Y, gfBulletTranslateX);
			CameraSteady = true;
			break;

		case 'X':
			moveX += 0.5;
			if (moveX >= 0.0)
			{
				moveX = -10.0;
			}
			break;

		case 'Y':
			moveY += 0.5;
			if (moveY >= 20.0)
			{
				moveY = -10.0;
			}
			break;

		case 'Z':
			moveZ += 0.5;
			if (moveZ >= 10.0)
			{
				moveZ = -10.0;
			}
			break;

		default:
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_TIMER_SECOND:
			if (giDoorMovementTimer < 21) {
				giDoorMovementTimer++;
			}
			updateSecondAngle();
			break;
		case IDT_TIMER_MINUTE:
			if (objectsIteration < numberOfObjects) {
				fprintf(fp, "WNDPROC : objIter : %d\n", objectsIteration);
				currentObject = arrayOfObjectInfo[objectsIteration];
				
				switch (objectsIteration)
				{
				case 3:
	//				PlaySound(sound[1], NULL, SND_ASYNC);
					break;
				case 5:
					PlaySound(sound[2], NULL, SND_ASYNC);
					break;
				case 13:
					PlaySound(sound[3], NULL, SND_ASYNC);
					break;
				case 15:
					PlaySound(sound[4], NULL, SND_ASYNC);
					break;
				case 18:
					PlaySound(sound[5], NULL, SND_ASYNC);
					break;
				}
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
	//objectsIteration = 8;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	resize(WIN_WIDTH, WIN_HEIGHT);
}

void CreditStart()
{
	void DropLines();
	int i = 0;

	//glPushMatrix();
	//glTranslatef(1.0f, 5.0f, -5.0f);
	//DropLines();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(-1.0f, 5.0f, -5.0f);
	//DropLines();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(3.0f, 5.0f, -5.0f);
	//DropLines();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(-3.0f, 5.0f, -5.0f);
	//DropLines();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(6.0f, 5.0f, -5.0f);
	//DropLines();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(-6.0f, 5.0f, -5.0f);
	//DropLines();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(drap, 5.0f, -5.0f);
	//DropLines();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(-drap, 5.0f, -5.0f);
	//DropLines();
	//glPopMatrix();

	//drap += 0.001f;
	int speed = 1;
	for (i = 0; i < giCurrentCreditLego; i++)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -15.0f);
		ShowLegoCharacterAnimation(i);
		glPopMatrix();
	}
	if (i >= 2)
	{
		speed = 10;
	}
	else
	{
		speed = 1;
	}

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -15.0f);
	UpdateLegoCharacterAnimation(&giCurrentCreditLego, i, speed);
	ShowLegoCharacterAnimation(i);
	glPopMatrix();
}
void display(void) {
	void drawShaders();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (objectsIteration == 21) {
		CreditStart();
	}
	else {
		MainRoom();
		DrawNeo();
		legoCharaters();
		if (sceneIndex == 3 || objectsIteration >= 16) {
			if (objectsIteration == 20) {
				dropShadersBullets = true;
			}
			if (!deleteShadersBullets)
				drawShaders();
			if (objectsIteration <= 18) {
				DrawMultipleBulletFireEffect();
			}
			//DrawMultipleBulletFireEffect();
			updateNeoHandUp();
		}
		if (objectsIteration == 13)
			raiseLegoHand();
	}
	SwapBuffers(ghdc);
}

void drawShaders() {
	glPushMatrix();
	glTranslatef(0.0, 5.0, 0.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	//glTranslatef(0.0, 5.0, 0.0);
	// draw SHADERS
	if(giCountBullet >= 10) 
	drawShaderCharacter('S');
	if (giCountBullet >= 25)
	drawShaderCharacter('H');
	if (giCountBullet >= 40)
	drawShaderCharacter('A');
	if (giCountBullet >= 55)
	drawShaderCharacter('D');
	if (giCountBullet >= 70)
	drawShaderCharacter('E');
	if (giCountBullet >= 85)
	drawShaderCharacter('R');
	if (giCountBullet >= 100)
	drawShaderCharacter('s');
	glPopMatrix();
}
void legoCharaters() {
	
	if (objectsIteration == 3 || objectsIteration == 4)
		logoAnimation(change);
	if (objectsIteration == 2)
		logoFadeInEffect();

	if (objectsIteration == 2 || objectsIteration == 3 || objectsIteration == 4 || objectsIteration == 9 || objectsIteration == 10 || objectsIteration == 11 || objectsIteration == 12 || objectsIteration == 13 || objectsIteration == 14 || objectsIteration == 15 || objectsIteration == 16 || objectsIteration == 17 || objectsIteration == 18  || objectsIteration == 19)
	{
		if (objectsIteration <= 8)
			drawLogo();
		glPushMatrix();
		glTranslatef(legoCharactersPosition.x, legoCharactersPosition.y, legoCharactersPosition.z);
		DrawLegoCharacters();
		if (gbStopLegoCharacters == false)
		{
			updateAllCharacters();
		}
		else if (Scene2)
		{
			updateHandAction(3);
//			raiseLegoHand();
			glPushMatrix();
			if (objectsIteration == 13 || objectsIteration == 14 || objectsIteration == 15) {
				//if (delayRipple >= 10) 
				{
					DrawSingleBulletWithRipples();
				}
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void update(void) {
	moveCamera();
	if (sceneIndex != 3) {
		moveNeo();
	}
	updateDoorAngle();
	if (Scene2 && gfBulletTranslateX >= 50.0f)
		dodgeBullet();
	
	// add timer here for firig effect
	updateMultipleBulletFire();
	
	if (dropShadersBullets) {
		yFreeFall += 0.1;
		if (yFreeFall >= 6.0) {
			deleteShadersBullets = true;
		}
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
	if (ptrTranslateLine != NULL)
	{
		free(ptrTranslateLine);
		ptrTranslateLine = NULL;
	}
	if (piRandomLineNumbers != NULL)
	{
		free(piRandomLineNumbers);
		piRandomLineNumbers = NULL;
	}
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