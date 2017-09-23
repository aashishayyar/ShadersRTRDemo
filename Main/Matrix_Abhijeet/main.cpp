#include"main.h"


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

#define WIN_WIDTH  800
#define WIN_HEIGHT 600

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};

BOOL gbFullscreen = FALSE;
BOOL gbEscapeKeyIsPressed = FALSE;
BOOL gbActiveWindow = FALSE;

HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;



void initialize(void);
void display(void);
void resize(int width, int height);
void uninitialize(void);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpszCndLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[]= L"WINDOW";

	BOOL bDone = FALSE;

	wndclass.cbSize =sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW |CS_VREDRAW|CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra =0;
	wndclass.lpfnWndProc=WndProc;
	wndclass.lpszClassName =szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance,TEXT("IDI_ICON1"));
	wndclass.hCursor =LoadCursor(NULL,IDC_ARROW);
	wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hbrBackground =(HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("MATRIX GLITCHE"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		0,
		0,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if(NULL == hwnd)
	{
		MessageBox(HWND_DESKTOP,L"ERROR WHILE CreateWindow",L"ERROR",0);
		return 0;
	}
	else
	{
		ghwnd =hwnd;
	}

	initialize();

	ShowWindow(hwnd,iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	while(bDone == FALSE)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message ==  WM_QUIT)
			{
				bDone = TRUE;
			}
			else
			{
				
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if(gbEscapeKeyIsPressed == TRUE)
			{
				bDone = TRUE;
			}
			else
			{
				
				display();
			}
		}
	}

	uninitialize();

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void ToggleFullScreen();
	
	TCHAR szMessage[500]={'\0'};

	switch(iMsg)
	{

	case WM_CREATE:
		break;

	case WM_KEYDOWN:
		if((wParam == 'F') || (wParam == 'f'))
		{
			ToggleFullScreen();
			if(gbFullscreen == FALSE)
			{
				gbFullscreen = TRUE;
			}
			else
			{
				gbFullscreen = FALSE;
			}
		}
		else if(wParam == VK_ESCAPE)
		{
			gbEscapeKeyIsPressed = TRUE;
		}
	break;

	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
	break;
	case VK_ESCAPE:
		
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;	
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

void initialize()
{
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	ZeroMemory(&pfd,sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |PFD_DOUBLEBUFFER ;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	ghdc =GetDC(ghwnd);

	iPixelFormatIndex = ChoosePixelFormat(ghdc,&pfd);
	if(iPixelFormatIndex ==0)
	{
		ReleaseDC(ghwnd,ghdc);
		ghdc = NULL;
	}

	if(SetPixelFormat(ghdc,iPixelFormatIndex,&pfd) == FALSE)
	{
		ReleaseDC(ghwnd,ghdc);
		ghdc = NULL;
	}

	ghrc= wglCreateContext(ghdc);
	if(ghrc == NULL)
	{
		ReleaseDC(ghwnd,ghdc);
		ghdc = NULL;
	}

	if(wglMakeCurrent(ghdc,ghrc) == FALSE)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd,ghdc);
		ghdc = NULL;
	}

	glClearColor(0.0f,0.0f,0.0f, 1.0);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);


	resize(WIN_WIDTH, WIN_HEIGHT);	
	return;
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	gluLookAt(0.0f,0.0f,5.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
	glTranslatef(-3.5f,8.05f,-3.0f);
	
	//DrawRoom();

	glPushMatrix();
	TranslateLines();
	DrawLinesWall();
	glPopMatrix();
	
	SwapBuffers(ghdc);

	return;
  }

void resize(int width, int height)
{
	if(height == 0)
	{
		height = 1;
	}	

	glViewport(0,0,(GLsizei)width,(GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glFrustum(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);

	gluPerspective(45.0f,((GLfloat)width/(GLfloat)height),0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	return;
}


void uninitialize()
{
	if(gbFullscreen == TRUE)
	{
		dwStyle = GetWindowLong(ghwnd,GWL_STYLE);
		SetWindowLong(ghwnd,GWL_STYLE,dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd,&wpPrev);
		SetWindowPos(ghwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_NOZORDER|SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

	wglMakeCurrent(NULL,NULL);

	wglDeleteContext(ghrc);
	ghrc =  NULL;

	ReleaseDC(ghwnd,ghdc);
	ghdc = NULL;

	DestroyWindow(ghwnd);

	return;
}

void ToggleFullScreen()
{
	MONITORINFO mi;

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
		//ShowCursor(FALSE);
	}
	else
	{
	
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}

}


