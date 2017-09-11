#include"StickMans.h"

int giDirection = 1;

//main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function prototype
	void initialize(void);
	void uninitialize(void);
	void display(void);

	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("RTROGL");
	bool bDone = false;

	int width = 0, height = 0;
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

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

	//Create Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szClassName,
		TEXT("OpenGL Fixed Function Pipeline Using Native Windowing : Stick Man"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		(width - WIN_WIDTH) / 2,
		(height - WIN_HEIGHT) / 2,
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
				if (gbEscapeKeyIsPressed == true)
					bDone = true;
				display();
			}
		}
	}

	uninitialize();
	return((int)msg.wParam);
}

//WndProc()
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function prototype
	void resize(int, int);
	void ToggleFullscreen(void);
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
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			gbEscapeKeyIsPressed = true;
			break;
		case 0x46:
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
			mi.cbSize = sizeof(MONITORINFO);
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

	//PlaySound(TEXT("beatit.wav"), NULL, SND_FILENAME | SND_ASYNC);

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

void updateNormalWalk(int currentStickMan)
{
	int i = currentStickMan;
	if (body[i]<90)
		body[i] = body[i] + gfSpeed;

	if (gbIsLeftArm[i])
	{
		lNeck[i] -= gfSpeed;
		rNeck[i] += gfSpeed;
		if (rNeck[i] > 10)
		{
			gbIsLeftArm[i] = false;
		}
	}
	else
	{
		lNeck[i] += gfSpeed;
		rNeck[i] -= gfSpeed;
		if (lNeck[i] > 10)
		{
			gbIsLeftArm[i] = true;
		}
	}

	if (gbOneLeg[i] == 1)
	{
		if (gbIsLeftLeg[i])
		{
			lKnee[i] = lKnee[i] + 4 * gfSpeed;
			if (lKnee[i] > -10.0f)
			{
				gbOneLeg[i] = false;
			}
		}
		else
		{
			rKnee[i] = rKnee[i] + 4 * gfSpeed;
			if (rKnee[i] > -10.0f)
			{
				gbOneLeg[i] = false;
			}
		}
	}
	else
	{
		if (gbIsLeftLeg[i])
		{
			lHip[i] -= gfSpeed;

			rHip[i] += gfSpeed;
			rKnee[i] = rKnee[i] - 2 * gfSpeed;

			if (rHip[i] > 20.0f)
			{
				gbOneLeg[i] = true;
				gbIsLeftLeg[i] = false;
			}
		}
		else
		{
			rHip[i] -= gfSpeed;

			lHip[i] += gfSpeed;
			lKnee[i] = lKnee[i] - 2 * gfSpeed;

			if (lHip[i] > 20.0f)
			{
				gbOneLeg[i] = true;
				gbIsLeftLeg[i] = true;
			}

		}
	}
}

void update()
{
	int i = 0;

	if (body[i] < 80 && giDirection == 1)
	{
		gfSpeed = 0.03f;
		gfTheta += gfSpeed / 4;
	}
	else
	{
		gfSpeed = 0.07f;
		giDirection = -1;
		gfTheta -= gfSpeed / 4;
	}
	if (body[i] < 0 && giDirection == -1)
	{
		;
	}
	else
	{
		for (i = 0; i < 1; i++)
		{
			gfTranslateX = -(2 * (1.25 + 0.75)*sin(3.14*body[i] / 180)) + 2 * 0.75* sin(3.14 * gfTheta / 180) + 2 * 0.75* sin(3.14 * gfTheta / 180);
			gfTranslateY = -(2 * (1.25 + 0.75) - 2 * (1.25 + 0.75)*cos(3.14*body[i] / 180) - (2 * (0.75) - 2 * 0.75*cos(gfTheta * 3.14 / 180)) - (2 * (0.75) - 2 * 0.75*cos(gfTheta * 3.14 / 180)));

			body[i] = body[i] + giDirection * gfSpeed;
			lHip[i] = 10 + body[i] - gfTheta;
			rHip[i] = -10 + body[i] - gfTheta;
			lKnee[i] = -body[i] - gfTheta;
			rKnee[i] = -body[i] - gfTheta;
			lAnkle[i] = lAnkle[i] + giDirection *gfSpeed / 2;
			rAnkle[i] = rAnkle[i] + giDirection *gfSpeed / 2;
			lNeck[i] = lNeck[i] + giDirection *1.7*gfSpeed;
			rNeck[i] = rNeck[i] - giDirection *gfSpeed / 5;

		}
		/*updateNormalWalk(i);*/
	}
}

void DrawCylinder(float height)
{
	quadric = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 1.0f);
	gluCylinder(quadric, 0.2f*gbStickWidth, 0.2f*gbStickWidth, 2*height, 30, 30);
}

void DrawJoints(float height)
{
	quadric = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 1.0f);
	gluSphere(quadric, 0.2f*gbStickWidth, 30, 30);

	glTranslatef(0.0f, 0.0f, 2*height);

	quadric = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 1.0f);
	gluSphere(quadric, 0.2f*gbStickWidth, 30, 30);

	glTranslatef(0.0f, 0.0f, -2*height);
}

void DrawCylinderAndJoints(float height)
{
	void DrawCylinder(float);
	void DrawJoints(float);

	DrawCylinder(height);
	DrawJoints(height);
}

void DrawHead(int currentStickMan, float radius)
{
	GLdouble equation[4] = { 0.0f, 0.0f, 1.0f, 0.25f };
	switch (currentStickMan)
	{
	case 0://Vito Corleone - Bow and red flower
		gbStickWidth = 0.9f;
		gbStickHeight = 0.75f;

		quadric = gluNewQuadric();
		glColor3f(1.0f, 1.0f, 1.0f);
		gluSphere(quadric, radius, 30, 30);

		//glTranslatef(0.25f, 0.0f, 1.2f);
		//quadric = gluNewQuadric();
		//glColor3f(1.0f, 0.0f, 0.0f);
		//gluCylinder(quadric, 0.15f, 0.1f, 0.3f, 30, 30);

		//quadric = gluNewQuadric();
		//glColor3f(0.0f, 1.0f, 0.0f);
		//gluCylinder(quadric, 0.05f, 0.05f, 0.5f, 30, 30);

		break;
	case 1://Michael Corleone - Tie and Hat
		gbStickWidth = 0.8f;
		gbStickHeight = 0.77f;

		glRotatef(90, 0.0f, 0.0f, 1.0f);

		glClipPlane(GL_CLIP_PLANE0, equation);
		glEnable(GL_CLIP_PLANE0);
		quadric = gluNewQuadric();
		glColor3f(1.0f, 1.0f, 1.0f);
		gluSphere(quadric, radius, 30, 30);
		glDisable(GL_CLIP_PLANE0);

		glPushMatrix();
		//glRotatef(-25.0f, 0.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, -0.25);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			quadric = gluNewQuadric();
			glColor3f(1.0f, 1.0f, 1.0f);
			gluCylinder(quadric, radius*1.4, radius * 1.5, 0.1f, 30, 30);
			glTranslatef(0.0f, 0.0f, -radius + 0.15);

			quadric = gluNewQuadric();
			glColor3f(1.0f, 1.0f, 1.0f);
			gluCylinder(quadric, radius / 2, radius, radius - 0.15, 30, 30);
		glPopMatrix();
		break;
	case 2://Sonny Corleone - Bow
		gbStickWidth = 0.7f;
		gbStickHeight = 0.72f;

		quadric = gluNewQuadric();
		glColor3f(1.0f, 1.0f, 1.0f);
		gluSphere(quadric, radius, 30, 30);

		break;
	case 3://Lucca Brassi - Tie and Cigar
		gbStickWidth = 1.2f;
		gbStickHeight = 0.77f;

		quadric = gluNewQuadric();
		glColor3f(1.0f, 1.0f, 1.0f);
		gluSphere(quadric, radius, 30, 30);

		glTranslatef(0.0f, 0.0f, 0.6f);
		glRotatef(110, 0.0f, 1.0f, 0.0f);
		quadric = gluNewQuadric();
		glColor3f(0.5f, 0.25f, 0.0f);
		gluCylinder(quadric, 0.1f, 0.1f, 1.3f, 30, 30);

		quadric = gluNewQuadric();
		glColor3f(0.8f, 0.8f, 0.8f);
		gluCylinder(quadric, 0.08f, 0.08f, 1.4f, 30, 30);
		break;
	}
}

void DrawStickMan(int currentStickMan)
{
	float length = gbStickHeight;

	glPushMatrix();
		glTranslatef(-length * sin(body[currentStickMan] * 3.145/180), 0.0f, -length*cos(body[currentStickMan]*3.145/180 ));
		DrawHead(currentStickMan, length);
	glPopMatrix();

	glPushMatrix();
		//Draw Left Neck to Elbow part
		glRotatef((GLfloat)lNeck[currentStickMan], 0.0f, 1.0f, 0.0f);

		glPushMatrix();
			DrawCylinderAndJoints(length);
		glPopMatrix();

		//Draw Left Elbow
		glTranslatef(0.0f, 0.0f, length * 2);
		glRotatef((GLfloat)lElbow[currentStickMan], 0.0f, 1.0f, 0.0f);

		glPushMatrix();
			DrawCylinderAndJoints(length);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();
		//Draw Right Neck to Elbow part
			glRotatef((GLfloat)rNeck[currentStickMan], 0.0f, 1.0f, 0.0f);

			glPushMatrix();
				DrawCylinderAndJoints(length);
			glPopMatrix();

			//Draw Right Elbow
			glTranslatef(0.0f, 0.0f, length * 2);
			glRotatef((GLfloat)rElbow[currentStickMan], 0.0f, 1.0f, 0.0f);

			glPushMatrix();
				DrawCylinderAndJoints(length);
			glPopMatrix();

	glPopMatrix();

	glPushMatrix();
		glRotatef((GLfloat)body[currentStickMan], 0.0f, 1.0f, 0.0f);
		DrawCylinderAndJoints(length + 0.5f);
	glPopMatrix();

	glTranslatef(2 * (length + 0.5f)*sin(body[currentStickMan] / 180.0f*3.145), 0.0f, 2 * (length + 0.5f)*cos(body[currentStickMan] / 180.0f*3.145));

	glPushMatrix();

		glPushMatrix();

		//Draw Right Leg to Knee part
			glRotatef((GLfloat)rHip[currentStickMan], 0.0f, 1.0f, 0.0f);

			glPushMatrix();
				DrawCylinderAndJoints(length);
			glPopMatrix();

			//Draw Right Knee
			glTranslatef(0.0f, 0.0f, length * 2);
			glRotatef((GLfloat)rKnee[currentStickMan], 0.0f, 1.0f, 0.0f);

			glPushMatrix();
				DrawCylinderAndJoints(length);
			glPopMatrix();

			//Draw Right Ankle
			glTranslatef(0.0f, 0.0f, length * 2);
			glRotatef((GLfloat)rAnkle[currentStickMan], 0.0f, 1.0f, 0.0f);

			glPushMatrix();
				DrawCylinderAndJoints(length / 4);
			glPopMatrix();

		glPopMatrix();

		glPushMatrix();

			//Draw Left Leg to Knee part
			glRotatef((GLfloat)lHip[currentStickMan], 0.0f, 1.0f, 0.0f);

			glPushMatrix();
				DrawCylinderAndJoints(length);
			glPopMatrix();

			//Draw Left Knee
			glTranslatef(0.0f, 0.0f, length * 2);
			glRotatef((GLfloat)lKnee[currentStickMan], 0.0f, 1.0f, 0.0f);

			glPushMatrix();
				DrawCylinderAndJoints(length);
			glPopMatrix();

			//Draw Left Ankle
			glTranslatef(0.0f, 0.0f, length * 2);
			glRotatef((GLfloat)lAnkle[currentStickMan], 0.0f, 1.0f, 0.0f);

			glPushMatrix();
				DrawCylinderAndJoints(length / 4);
			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}

void debug()
{

	glBegin(GL_LINES);
	glColor3f(1.0f, 0, 0);
	glVertex3f(-15.0f, 0.0f, 0.0f);
	glVertex3f(15.0f, 0.0f, 0.0f);

	glVertex3f(0.0f, -15.0f, 0.0f);
	glVertex3f(0.0f, 15.0f, 0.0f);

	glVertex3f(-15.0f, -2 * 1.25f, 0.0f);
	glVertex3f(15.0f, -2 * 1.25f, 0.0f);

	glVertex3f(-15.0f, -(2 * (1.25f + 0.75f)), 0.0f);
	glVertex3f(15.0f, -(2 * (1.25f + 0.75f)), 0.0f);

	glVertex3f(-15.0f, -(2 * (1.25f + 0.75f + 0.75f)), 0.0f);
	glVertex3f(15.0f, -(2 * (1.25f + 0.75f + 0.75f)), 0.0f);

	glEnd();
}
void display(void)
{
	int i = 0;
	float translateX = gfTranslateX;
	//code 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//View Transformations

	//Model Transformations
	for (i = 0; i < 1; i++)
	{
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -18.0f);
			//debug();
			glTranslatef(translateX, gfTranslateY, 0.0f);
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			DrawStickMan(i);
		glPopMatrix();
	}

	update();
	SwapBuffers(ghdc);
}

void resize(int width, int height)
{
	//code
	if (height == 0)
		height = 1;
	if (width == 0)
		width = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height)
		gluPerspective(45.0f, 1.0f*(GLfloat)height / (GLfloat)width, 0.1f, 100.0f);
	else
		gluPerspective(45.0f, 1.0f*(GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
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
