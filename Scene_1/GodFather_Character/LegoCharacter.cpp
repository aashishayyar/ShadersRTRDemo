#include"LegoCharacter.h"

float gfFaceHeight = 1.5f;
float gfFaceWidth = 0.8f ;
float gfNeckHeight = 1.7f;
float gfNeckWidth = 0.5f;
float gfArmHeight = 1.0f;
float gfArmWidth = 0.25f;
float gfChestUpperWidth = 1.0f;
float gfChestLowerWidth = 1.3f;
float gfChestWidth = 0.7f;
float gfChestHeight = 2.2f;

float gfLegWidth = 0.5f ;
float gfLegHeight = 1.2f;
float gfLegCylHeight = 1.0f; 
float gfLegCylRadius = 0.75f;

float gfFootHeight = 0.35f;
float gfFootWidth = 0.5f;
float gfFootLength = 0.65f;

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

		case 'F':
		case 'f':
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

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	resize(WIN_WIDTH, WIN_HEIGHT);
}

void updateNormalWalk(int currentStickMan)
{
	if (lLeg[currentStickMan] < -20)
	{
		giLLegDirection[currentStickMan] = 1;
	}
	else if (lLeg[currentStickMan] > 20)
	{
		giLLegDirection[currentStickMan] = -1;
	}
	lLeg[currentStickMan] = lLeg[currentStickMan] + giLLegDirection[currentStickMan]* gfSpeed;

	if (rLeg[currentStickMan] < -20)
	{
		giRLegDirection[currentStickMan] = 1;
	}	
	else if (rLeg[currentStickMan] > 20)
	{
		giRLegDirection[currentStickMan] = -1;
	}
	rLeg[currentStickMan] = rLeg[currentStickMan] + giRLegDirection[currentStickMan]* gfSpeed;

	if (lArm[currentStickMan] < 30)
	{
		giLArmDirection[currentStickMan] = 1;
	}
	else if (lArm[currentStickMan] > 70)
	{
		giLArmDirection[currentStickMan] = -1;
	}
	lArm[currentStickMan] = lArm[currentStickMan] + giLArmDirection[currentStickMan]* gfSpeed;

	if (rArm[currentStickMan] < 30)
	{
		giRArmDirection[currentStickMan] = 1;
	}
	else if (rArm[currentStickMan] > 70)
	{
		giRArmDirection[currentStickMan] = -1;
	}
	rArm[currentStickMan] = rArm[currentStickMan] + giRArmDirection[currentStickMan]* gfSpeed;

}

void update()
{
	int i = 0;
	gfTranslateX += gfSpeed / 15;

	for (i = 0; i < 4; i++)
	{
		updateNormalWalk(i);
	}
}

void DrawCircle(float radius)
{
	float angle;
	glLineWidth(2);
	glBegin(GL_POLYGON);
	for (angle = 0.0f; angle < 2 * 3.145; angle = angle + 0.001f)
		glVertex3f(radius*cos(angle), radius*sin(angle), 0.0f);
	glEnd();
}

void DrawSquare(float vertice1[3], float vertice2[3], float vertice3[3], float vertice4[3], float color[3])
{
	glBegin(GL_QUADS);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(vertice1[0], vertice1[1], vertice1[2]);
	glVertex3f(vertice2[0], vertice2[1], vertice2[2]);
	glVertex3f(vertice3[0], vertice3[1], vertice3[2]);
	glVertex3f(vertice4[0], vertice4[1], vertice4[2]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(color[0]+0.1f, color[1]+0.1f, color[2]+0.1f);
	glVertex3f(vertice1[0], vertice1[1], vertice1[2]);
	glVertex3f(vertice2[0], vertice2[1], vertice2[2]);
	glVertex3f(vertice3[0], vertice3[1], vertice3[2]);
	glVertex3f(vertice4[0], vertice4[1], vertice4[2]);
	glEnd();

}

void DrawSector(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle)
{
	float angle;
	glLineWidth(2);
	glPushMatrix();
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, z);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*cos(angle), bRadius*sin(angle), z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*cos(angle), bRadius*sin(angle), z);
	glEnd();
	glPopMatrix();

}

void DrawSectorLine(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle)
{
	float angle;
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (angle = minAngle; angle <maxAngle; angle = angle + 0.001f)
		glVertex3f(aRadius*cos(angle), bRadius*sin(angle), z);
	glEnd();
}

void DrawCubiod(float points[10][3], float color[3])
{
	DrawSquare(points[0], points[1], points[2], points[3], color);//top
	DrawSquare(points[4], points[5], points[6], points[7], color);//bottom
	DrawSquare(points[1], points[5], points[6], points[2], color);//left
	DrawSquare(points[0], points[4], points[7], points[3], color);//right
	DrawSquare(points[0], points[1], points[5], points[4], color);//front
	DrawSquare(points[3], points[2], points[6], points[7], color);//rear
}

void DrawFaceDesign(void)
{
	float height = -gfFaceHeight;
	float topX = gfFaceWidth;
	float topZ = gfFaceWidth;
	float bottomX = gfFaceWidth;
	float color[3] = { 1.0f, 0.5f, 0.25f };

	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;

	glPushMatrix();
	glTranslatef(-topX / 3, height / 3, 0.0f);
	DrawSector(0.15f, 0.15f, -topZ - 0.01f, color, 0.0f, 2 * PI);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX / 3, height / 3, 0.0f);
	DrawSector(0.15f, 0.15, -topZ - 0.01f, color, 0.0f, 2 * PI);
	glPopMatrix();

	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;

	glPushMatrix();
	glTranslatef(-topX / 3, height / 3 + 0.05, 0.0f);
	DrawSector(0.1f, 0.1f, -topZ - 0.03f, color, 0.0f, 2 * PI);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX / 3, height / 3 + 0.05, 0.0f);
	DrawSector(0.1f, 0.1f, -topZ - 0.03f, color, 0.0f, 2 * PI);
	glPopMatrix();

	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;

	glPushMatrix();
	glTranslatef(-topX / 3, height / 3.2f, 0.0f);
	DrawSectorLine(0.25f, 0.25, -topZ - 0.01f, color, 3.145f / 6, 3 * PI / 4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX / 3, height / 3.2f, 0.0f);
	DrawSectorLine(0.25f, 0.25, -topZ - 0.01f, color, 3.145f / 4, 3 * PI / 3.7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4f, -1.0f, -1.81f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 1.0f);
	glVertex3f(-0.36f, 0.1f, 1.0f);
	glVertex3f(-0.4f, 0.2f, 1.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4f, -1.0f, -0.81f);
	glRotatef(180.0, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glVertex3f(-0.36f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.2f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(topX-0.76 , height+0.2 , 0.0f);
	DrawSectorLine(0.25f, 0.25, -topZ - 0.01f, color, 3.145f / 4, 3 * PI / 3.7);
	glPopMatrix();
}
void DrawFace()
{
	float height = -gfFaceHeight;
	float topX = gfFaceWidth;
	float topZ = gfFaceWidth;
	float bottomX = gfFaceWidth;
	float color[3] = { 1.0f, 0.5f, 0.25f };

	float points[10][3] = {
		{ topX, 0, topZ },
		{ -topX, 0, topZ },
		{ -topX, 0, -topZ },
		{ topX, 0, -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(points, color);

	DrawFaceDesign();
}

void DrawNeck()
{
	float height = -gfNeckHeight;
	float topX = gfNeckWidth;
	float topZ = gfNeckWidth;
	float bottomX = gfNeckWidth;
	float color[3] = { 1.0f, 0.5f, 0.25f };

	float points[10][3] = {
		{ topX, 0, topZ },
		{ -topX, 0, topZ },
		{ -topX, 0, -topZ },
		{ topX, 0, -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(points, color);

}

void DrawCylinder(float height, float radius)
{
	quadric = gluNewQuadric();
	glColor3f(0.07f, 0.07f, 0.07f);
	gluCylinder(quadric, radius, radius, height, 30, 30);

	glColor3f(0.07f, 0.07f, 0.07f);
	DrawCircle(radius);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, height);

	glColor3f(0.07f, 0.07f, 0.07f);
	DrawCircle(radius);
	glPopMatrix();
}

void DrawJoints(float height, float radius)
{
	quadric = gluNewQuadric();
	glColor3f(0.07f, 0.07f, 0.07f);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, height);

	quadric = gluNewQuadric();
	glColor3f(0.07f, 0.07f, 0.07f);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, -height);
}

void DrawWrist(float height, float radius)
{
	quadric = gluNewQuadric();
	glColor3f(0.1f, 0.1f, 0.1f);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, height);

	quadric = gluNewQuadric();
	glColor3f(1.0f, 0.5f, 0.25f);
	gluSphere(quadric, radius, 30, 30);

	glTranslatef(0.0f, 0.0f, -height);
}

void DrawBiceps(float height, float radius)
{
	DrawCylinder(height, radius);
	DrawJoints(height, radius);
}

void DrawForeArm(float height, float radius)
{
	DrawCylinder(height, radius);
	DrawWrist(height, radius);
}

void DrawHead(int currentStickMan)
{
	switch (currentStickMan)
	{
	case 0://Vito Corleone - Bow and red flower
		DrawFace();  
		DrawNeck();  
		break;
	case 1://Michael Corleone - Tie and Hat
		DrawFace();
		DrawNeck();
		break;
	case 2://Sonny Corleone - Bow
		DrawFace();
		DrawNeck();
		break;
	case 3://Lucca Brassi - Tie and Cigar
		DrawFace();
		DrawNeck();
		break;
	}
}

void DrawChest()
{
	float chestBottomHeight = 0.3f;
	float height = -(gfChestHeight - chestBottomHeight);
	float topX = gfChestUpperWidth;
	float topZ = gfChestWidth;
	float bottomX = gfChestLowerWidth;
	float color[3] = { 0.0f, 0.0f, 0.0f };

	float points[10][3] = { 
		{ topX, 0, topZ },
		{ -topX, 0, topZ },
		{ -topX, 0, -topZ },
		{ topX, 0, -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{-bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(points, color);

	height = -gfChestHeight;
	topX = gfChestLowerWidth;
	topZ = gfChestWidth;
	bottomX = gfChestLowerWidth;
	
	float pointsChestBottom[10][3] = {
		{ topX, -(gfChestHeight - chestBottomHeight), topZ },
		{ -topX, -(gfChestHeight - chestBottomHeight), topZ },
		{ -topX, -(gfChestHeight - chestBottomHeight), -topZ },
		{ topX, -(gfChestHeight - chestBottomHeight), -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(pointsChestBottom, color);

	DrawSuitGodfather();	
}

void DrawSuitGodfather(void)
{
	GLfloat redius = 1.0f;

	//white dressed
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.7f);
	glScalef(0.4f, 1.3f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < circle_points; i++)
	{
		angle = -1 * PI * i / circle_points;
		glVertex3f(cos(angle)*redius, sin(angle)*redius, 0.0f);
	}
	glEnd();

	//drawing Dress Line
		glLineWidth(2.0f);
		glColor3f(0.5f, 0.5f, 0.5f);
		glPushMatrix();
			glTranslatef(0.0f, -0.1f, -0.2f);
			DrawLinesOnDress();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, -0.12f, -0.0f);
			glRotatef(180.0, 0.0f, 1.0f, 0.0f);
			DrawLinesOnDress();
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	//code for buttons
	//1st
	redius = 0.08f;
	glTranslatef(-0.2f,-0.5f, -0.7f);
	glRotatef(180.0, 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawButtons(redius);

	//2nd
	glTranslatef(0.0f, -0.3f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawButtons(redius);

	//3rd
	glTranslatef(0.0f, -0.7f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawButtons(redius);

	//4th
	glTranslatef(0.0f, -0.3f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawButtons(redius);
	glPopMatrix();

	//toy
	glPushMatrix();
	glScalef(0.25f,0.25f,1.0f);
	glTranslatef(-0.4f, -0.3f, -0.7f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glEnd();

	float angle;
	redius = 0.5f;
	glLineWidth(2);
	glTranslatef(0.5f, -0.2f, 0.0f);
	glBegin(GL_POLYGON);
	for (angle = 0.0f; angle < 2 * 3.145; angle = angle + 0.001f)
		glVertex3f(redius*cos(angle), redius*sin(angle), 0.0f);
	glEnd();

	glTranslatef(0.4f, 0.2f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	redius = 0.2f;
	glLineWidth(2);
	glTranslatef(-0.7f, -0.7f, -0.8f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (angle = 0.0f; angle < 2 * 3.145; angle = angle + 0.001f)
		glVertex3f(redius*cos(angle), redius*sin(angle), 0.0f);
	glEnd();

	redius = 0.1f;
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (angle = 0.0f; angle < 2 * 3.145; angle = angle + 0.001f)
		glVertex3f(redius*cos(angle), redius*sin(angle), 0.0f);
	glEnd();
	glPopMatrix();
}

void DrawButtons(GLfloat redius)
{
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0.0f; angle <= 2.0*PI; angle = angle + 0.01f)
	{
		glVertex3f(cos(angle)*redius, sin(angle)*redius, 0.0f);
	}
	glEnd();
}

void DrawLinesOnDress(void)
{
	glBegin(GL_LINES);

	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, -1.7, 0.1f);

	glVertex3f(-1.3f, 0.2f, 0.1f);
	glVertex3f(-2.0f, -0.1f, 0.1f);

	glVertex3f(-2.0f, -0.1f, 0.1f);
	glVertex3f(-1.7f, -0.4f, 0.1f);

	glVertex3f(-1.0f, -0.1f, 0.1f);
	glVertex3f(-2.0f, -0.5f, 0.1f);

	glVertex3f(-2.0f, -0.5f, 0.1f);
	glVertex3f(-1.4f, -1.7, 0.1f);

	glVertex3f(-1.4f, -1.7, 0.1f);
	glVertex3f(1.4f, -1.7, 0.1f);

	glEnd();
}

void DrawHand(int direction, int currentStickMan)
{
	float armAngle = direction == 1 ? lArm[currentStickMan] : rArm[currentStickMan];

	glPushMatrix();
		glRotatef(armAngle, 1.0f, 0.0f, 0.0f);
		glRotatef(direction*25, 0.0f, 1.0f, 0.0f);
		DrawBiceps(gfArmHeight, gfArmWidth);
		glTranslatef(0.0f, 0.0f, gfArmHeight);
		glRotatef(armAngle, 1.0f, 0.0f, 0.0f);
		DrawForeArm(gfArmHeight, gfArmWidth);
	glPopMatrix();
}

void DrawThigh()
{
	float height = -gfLegHeight;
	float topX = gfLegWidth;
	float topZ = gfLegWidth;
	float bottomX = gfLegWidth;
	float color[3] = { 0.0f, 0.0f, 0.0f };

	float points[10][3] = {
		{ topX, 0, topZ },
		{ -topX, 0, topZ },
		{ -topX, 0, -topZ },
		{ topX, 0, -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(points, color);
}

void DrawFoot()
{
	float height = -gfFootHeight;
	float topX = gfFootWidth;
	float topZ = gfFootLength;
	float bottomX = gfFootWidth;
	float color[3] = { 0.0f, 0.0f, 0.0f };

	float points[10][3] = {
		{ topX, 0, topZ },
		{ -topX, 0, topZ },
		{ -topX, 0, -topZ },
		{ topX, 0, -topZ },
		{ bottomX, height, topZ },
		{ -bottomX, height, topZ },
		{ -bottomX, height, -topZ },
		{ bottomX, height, -topZ },
	};

	DrawCubiod(points, color);
}

void DrawLeg(int direction, int currentStickMan)
{
	float legAngle = direction == 1 ? lLeg[currentStickMan] : rLeg[currentStickMan];

	glRotatef(legAngle, 1.0f, 0.0f, 0.0f);

	glPushMatrix();
		glRotatef(direction* 90, 0.0f, 1.0f, 0.0f);
		DrawCylinder(gfLegCylHeight, gfLegCylRadius);//1,1
	glPopMatrix();

	glPushMatrix();
		glTranslatef(direction* gfLegCylHeight / 2, -gfLegCylRadius+0.25f, 0.0f);
		DrawThigh();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(direction * gfLegCylHeight / 2, -(gfLegCylRadius + gfLegHeight) + 0.25f, -(gfFootLength - gfLegWidth));
		DrawFoot();
	glPopMatrix();
}

void DrawLegSeparation()
{
	glPushMatrix();
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		DrawCylinder(0.4f, gfLegCylRadius);
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

	glVertex3f(-15.0f, -1.0f, 0.0f);
	glVertex3f(15.0f, -1.0f, 0.0f);

	glVertex3f(-15.0f, -1.5, 0.0f);
	glVertex3f(15.0f, -1.5, 0.0f);

	glEnd();
}
void display(void)
{
	int i = 0;
	GLfloat angle = 0.0f;
	//float translateX = gfTranslateX;

	float translateX = 0.0f;
	//code 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*for (i = 0; i < 4; i++)
	{
	*/
		glPushMatrix();
			glTranslatef(translateX, 0.0f, -18.0f);
			glRotatef(180, 0.0f, 1.0f, 0.0f);
			glPushMatrix();
				DrawHead(i);
			glPopMatrix();

			glTranslatef(0.0f, -gfNeckHeight, 0.0f);

			DrawChest();

			glPushMatrix();
				glTranslatef(gfChestUpperWidth, -0.25f, 0.0f);
				DrawHand(1,i);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-gfChestUpperWidth, -0.25f, 0.0f);
				DrawHand(-1,i);
			glPopMatrix();

			glTranslatef(0.0f, -gfChestHeight, 0.0f);

			glPushMatrix();
				glTranslatef(0.2f, 0.0f, 0.0f);
				DrawLeg(1,i);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-0.2f, 0.0f, 0.0f);
				DrawLegSeparation();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.2f, 0.0f, 0.0f);
				DrawLeg(-1,i);
			glPopMatrix();

		glPopMatrix();
		translateX += 4.0f;
		angle += 10.0f;
//	}
//	update();
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
