#include<Windows.h>
#include<stdio.h>
#include"Matrix.h"
#include<stdlib.h>	//for rand();

#include<gl/GL.h>
#include<gl/GLU.h>

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


void UpdateAngle();


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
	
	
	DrawRoom();
	
	//DrawMatrixLines();
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



void DrawCharacter()
{
	glBegin(GL_LINES);
			glColor3f(gfMatrixCharRed, gfMatrixCharGreen, gfMatrixCharBlue); 
			/*4th LINE*/
			if(giSevenSgment[4] == 1)
			{
				glVertex3f((gfCurrentX+gfWidthOfLine),(gfCurrentY - gfHeightOfLine),gfCurrentZ);
				glVertex3f((gfCurrentX+gfWidthOfLine),gfCurrentY,gfCurrentZ);
			}
			/*3rd LINE*/
			if(giSevenSgment[3] == 1)
			{
				glVertex3f(gfCurrentX,(gfCurrentY - gfHeightOfLine),gfCurrentZ);
				glVertex3f((gfCurrentX+gfWidthOfLine),(gfCurrentY - gfHeightOfLine),gfCurrentZ);
			}
			/*2nd LINE*/
			if(giSevenSgment[2] == 1)
			{
				glVertex3f(gfCurrentX,gfCurrentY,gfCurrentZ);
				glVertex3f(gfCurrentX,(gfCurrentY - gfHeightOfLine),gfCurrentZ);
			}
			/*6th LINE*/
			if(giSevenSgment[6] == 1)
			{
				glVertex3f(gfCurrentX,gfCurrentY,gfCurrentZ);
				glVertex3f((gfCurrentX+gfWidthOfLine),(gfCurrentY),(gfCurrentZ ));
			}
			/*1st LINE*/
			if(giSevenSgment[1] == 1)
			{
				glVertex3f(gfCurrentX,gfCurrentY,gfCurrentZ);
				glVertex3f((gfCurrentX +.00f),(gfCurrentY + gfHeightOfLine),(gfCurrentZ +0.0f));
			}
			/*0th LINE*/
			if(giSevenSgment[0] == 1)
			{
				glVertex3f(gfCurrentX,(gfCurrentY + gfHeightOfLine),gfCurrentZ);
				glVertex3f((gfCurrentX +gfWidthOfLine ),(gfCurrentY + gfHeightOfLine),gfCurrentZ);
			}

			/*5th LINE*/
			if(giSevenSgment[5] == 1)
			{
				glVertex3f((gfCurrentX +gfWidthOfLine ),(gfCurrentY + gfHeightOfLine),gfCurrentZ);
				glVertex3f((gfCurrentX +gfWidthOfLine ),gfCurrentY,gfCurrentZ);
			}
		glEnd();
}

void DrawWall()
{
	int iCounter = 0;
	int iRandomCharacterCount = giNumberOfCharOnX *giNumberOfCharOnY;
	StoreWall();
	for(int j = 0; j < giNumberOfCharOnY; j++)
	{
		for(int i =0; i < giNumberOfCharOnX; i++)
		{
		  RandomCharacter(piRandomWallNumbers[iCounter]);
		  iCounter++;
		  if(iCounter >= iRandomCharacterCount)
		  {
			  iCounter = 0;
		  }
		  //HERE WE DRAW ACTUAL CHARACTER 
		  DrawCharacter();

		  gfCurrentX = gfCurrentX +  gfCommonXDistance;
		}
		gfWidthOfRoom = gfCurrentX;
	  gfCurrentX = 0.0f;
	  gfCurrentY = gfCurrentY +  gfCommonYDistance + 0.1f;
	}
	gfHeightOfRoom = gfCurrentY;
	gfCurrentY = 0.0f;
	return;
}

void StoreWall()
{
	int iTotalNumberOfCharacters = giNumberOfCharOnX*giNumberOfCharOnY;
	int RandomNumber = 0;
	if(piRandomWallNumbers == NULL)
	{
		piRandomWallNumbers = (int *)malloc(sizeof(int)*(iTotalNumberOfCharacters));
		if(piRandomWallNumbers == NULL)
		{
			//ERROR HANDLING
		}
	}
	if(gbAllocateMemoryAgain == TRUE)
	{
		if(giTempNumberOfCharacterOnX > giNumberOfCharOnX)
		{
			realloc(piRandomWallNumbers,(sizeof(int)*(giTempNumberOfCharacterOnX - giNumberOfCharOnX )));
		}
		else if(giTempNumberOfCharacterOnY > giNumberOfCharOnY)
		{
			realloc(piRandomWallNumbers,(sizeof(int)*(giTempNumberOfCharacterOnY - giNumberOfCharOnY )));
		}
		if(piRandomWallNumbers == NULL)
		{
			//ERROR HANDLING
		}
	}
	if(gbWallFilled == FALSE)
	{
	 for(int i = 0;  i < iTotalNumberOfCharacters; i++)
	 {
		RandomNumber = rand() % 27;
		piRandomWallNumbers[i]= RandomNumber;
	 }
	 gbWallFilled = TRUE;
	}
	if(gbDisplayedFirstWall == FALSE)
	{
		gbDisplayedFirstWall = TRUE;
		dwDisplayedFirstWall = GetTickCount();
		dwSavedTickCount = dwDisplayedFirstWall;
	}
	dwGetTickCount = GetTickCount();
	if((dwGetTickCount - dwSavedTickCount) >= gdwSpeedOfWallChange)
	{
		dwSavedTickCount = dwGetTickCount;
		gbWallFilled = FALSE;
	}

}
void RandomCharacter(int RandomNumber )
{

	for(int i = 0; i < 7; i++)
	{
		giSevenSgment[i] = 0;
	}
	switch(RandomNumber)
	{
		case 0x0:
			giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
			break;
		case 0x1:
			giSevenSgment[4] = giSevenSgment[5]  = 1;
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
			giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[3] = giSevenSgment[5] =giSevenSgment[6]  = 1; 
			break;
		case 0x7:
			giSevenSgment[0] = giSevenSgment[4] = giSevenSgment[5] = 1;
			break;
		case 0x8:
			giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] =  giSevenSgment[3] = giSevenSgment[4]  = giSevenSgment[5] = 1; 
			break;
		case 0x9:
			giSevenSgment[0] = giSevenSgment[1]  = giSevenSgment[3] = giSevenSgment[4]  = giSevenSgment[5] =giSevenSgment[6]  = 1; 
		break;
		case 10:	//a
			giSevenSgment[0] = giSevenSgment[2]  = giSevenSgment[3] = giSevenSgment[4]  = giSevenSgment[5] =giSevenSgment[6]  = 1; 
		break;
		case 11:	//b
			giSevenSgment[1] = giSevenSgment[2]  = giSevenSgment[3] = giSevenSgment[4]   = giSevenSgment[6]  = 1; 
		break;
		case 12:	//c
			giSevenSgment[6] = giSevenSgment[2]  = giSevenSgment[3] = 1;
		break;	
		case 13:	//d
			 giSevenSgment[2]  = giSevenSgment[3] = giSevenSgment[4]  = giSevenSgment[5] =giSevenSgment[6]  = 1; 
		break;
		case 14:	//e
			giSevenSgment[0] = giSevenSgment[2]  = giSevenSgment[3] = giSevenSgment[1]  = giSevenSgment[5] =giSevenSgment[6]  = 1; 
		break;
		case 15:	//f
			giSevenSgment[0] = giSevenSgment[1]  = giSevenSgment[2] = giSevenSgment[6]  = 1;
		break;
		case 16:	//g	Added 3 to differentiate from 9
			giSevenSgment[0] = giSevenSgment[1]  = giSevenSgment[6] = giSevenSgment[5]  = giSevenSgment[4] =giSevenSgment[3]  = 1; 
		break;
		case 17:	//h
			giSevenSgment[0] = giSevenSgment[2]  = giSevenSgment[4]  = giSevenSgment[5] =giSevenSgment[6]  = 1; 
		break;
		case 18:	//j
			giSevenSgment[3] = giSevenSgment[4]  = giSevenSgment[5] = 1;
		break;
		case 19:	//L 
			giSevenSgment[1] = giSevenSgment[2]  = giSevenSgment[3] = 1;
		break;
		case 20:	//n
			giSevenSgment[2] = giSevenSgment[4]  = giSevenSgment[6] = 1;
		break;
		case 21:	//o
			giSevenSgment[2] = giSevenSgment[6]  = giSevenSgment[3] = giSevenSgment[4]  = 1; 
		break;
		case 22:	//q	
			giSevenSgment[1] = giSevenSgment[0]  = giSevenSgment[5] = giSevenSgment[4]  = giSevenSgment[6]  = 1; 
		break;
		case 23:	//p
			giSevenSgment[1] = giSevenSgment[2]  = giSevenSgment[0] = giSevenSgment[5]  = giSevenSgment[6]  = 1; 
		break;
		case 24:	//s	
			giSevenSgment[1] = giSevenSgment[0]  = giSevenSgment[3] = giSevenSgment[6]  = giSevenSgment[4] = 1; 
		break;
		case 25:	//t
			giSevenSgment[1] = giSevenSgment[2]  = giSevenSgment[3] = giSevenSgment[6]  = 1; 
		break;
		case 26:	//y	Add 3 to differentiate from 4
			giSevenSgment[1] = giSevenSgment[3]  = giSevenSgment[4] = giSevenSgment[5]  = giSevenSgment[6] = 1; 
		break;
	}
	return ;
}


void DrawRoom()
{
	//gfLengthOfRoom  = (giNumberOfCharOnY * gfCommonYDistance) + (giNumberOfCharOnY * gfHeightOfLine);
	//gfBreadthOfRoom = (giNumberOfCharOnY * gfCommonXDistance) + (giNumberOfCharOnX * gfWidthOfLine);
	
	glPushMatrix();
	glTranslatef(-10.05f,-8.05f,-20.0f);

	

	
	//LEFT
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left 
	DrawWall();
	glPopMatrix();

	//RIGHT
	glPushMatrix();
	glTranslatef(gfHeightOfRoom,0.0f,0.0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left 
	DrawWall();
	glPopMatrix();

	//BOTTOM

	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); 
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); 
	DrawWall();
	glPopMatrix();


	//TOP
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); 
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f,0.0f,-(gfHeightOfRoom));
	giTempNumberOfCharacterOnY = giNumberOfCharOnY;
	giNumberOfCharOnY = giNumberOfCharOnY + 1;
	gbAllocateMemoryAgain = TRUE;
	DrawWall();
	giNumberOfCharOnY = giTempNumberOfCharacterOnY;
	gbAllocateMemoryAgain = FALSE;
	glPopMatrix();

	//BACK
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-gfWidthOfRoom);
	giTempNumberOfCharacterOnX = giNumberOfCharOnX;
	giNumberOfCharOnX = giNumberOfCharOnX - 25 ;
	gbAllocateMemoryAgain = TRUE;
	DrawWall();
	giNumberOfCharOnX = giTempNumberOfCharacterOnX;
	gbAllocateMemoryAgain = FALSE;
	glPopMatrix();

	glPopMatrix();

}

//void StoreLine()
//{
//	int iTotalNumberOfCharacters = giNumberOfCharOnX*giNumberOfCharOnY;
//	int RandomNumber = 0;
//	if(piRandomWallNumbers == NULL)
//	{
//		piRandomLineNumbers = (int *)malloc(sizeof(int)*(iTotalNumberOfCharacters));
//		if(piRandomLineNumbers== NULL)
//		{
//			//ERROR HANDLING
//		}
//	}
//	if(gbLinesFilled == FALSE)
//	{
//	 for(int i = 0;  i < iTotalNumberOfCharacters; i++)
//	 {
//		RandomNumber = rand() % 27;
//		piRandomLineNumbers[i]= RandomNumber;
//	 }
//	 gbLinesFilled = TRUE;
//	}
//}
//void DrawMatrixLines()
//{
//	int iCounter = 0;
//	int iRandomCharacterCount = giNumberOfCharOnX *giNumberOfCharOnY;
//	StoreLine();
//	for(int j = 0; j < giNumberOfCharOnX; j++)
//	{
//	  for(int i =0; i < giNumberOfCharOnY ; i++)
//	  {
//		  RandomCharacter(piRandomLineNumbers[iCounter]);
//		  iCounter++;
//		  if(iCounter >= iRandomCharacterCount)
//		  {
//			  iCounter = 0;
//		  }
//		  //HERE WE DRAW ACTUAL CHARACTER 
//		  glBegin(GL_LINES);
//			glColor3f(gfMatrixCharRed, gfMatrixCharGreen, gfMatrixCharBlue); 
//			/*4th LINE*/
//			if(giSevenSgment[4] == 1)
//			{
//				glVertex3f((gfCurrentX+gfWidthOfLine),(gfCurrentY - gfHeightOfLine),gfCurrentZ);
//				glVertex3f((gfCurrentX+gfWidthOfLine),gfCurrentY,gfCurrentZ);
//			}
//			/*3rd LINE*/
//			if(giSevenSgment[3] == 1)
//			{
//				glVertex3f(gfCurrentX,(gfCurrentY - gfHeightOfLine),gfCurrentZ);
//				glVertex3f((gfCurrentX+gfWidthOfLine),(gfCurrentY - gfHeightOfLine),gfCurrentZ);
//			}
//			/*2nd LINE*/
//			if(giSevenSgment[2] == 1)
//			{
//				glVertex3f(gfCurrentX,gfCurrentY,gfCurrentZ);
//				glVertex3f(gfCurrentX,(gfCurrentY - gfHeightOfLine),gfCurrentZ);
//			}
//			/*6th LINE*/
//			if(giSevenSgment[6] == 1)
//			{
//				glVertex3f(gfCurrentX,gfCurrentY,gfCurrentZ);
//				glVertex3f((gfCurrentX+gfWidthOfLine),(gfCurrentY),(gfCurrentZ ));
//			}
//			/*1st LINE*/
//			if(giSevenSgment[1] == 1)
//			{
//				glVertex3f(gfCurrentX,gfCurrentY,gfCurrentZ);
//				glVertex3f((gfCurrentX +.00f),(gfCurrentY + gfHeightOfLine),(gfCurrentZ +0.0f));
//			}
//			/*0th LINE*/
//			if(giSevenSgment[0] == 1)
//			{
//				glVertex3f(gfCurrentX,(gfCurrentY + gfHeightOfLine),gfCurrentZ);
//				glVertex3f((gfCurrentX +gfWidthOfLine ),(gfCurrentY + gfHeightOfLine),gfCurrentZ);
//			}
//			/*5th LINE*/
//			if(giSevenSgment[5] == 1)
//			{
//				glVertex3f((gfCurrentX +gfWidthOfLine ),(gfCurrentY + gfHeightOfLine),gfCurrentZ);
//				glVertex3f((gfCurrentX +gfWidthOfLine ),gfCurrentY,gfCurrentZ);
//			}
//		glEnd();
//
//		 gfCurrentY = gfCurrentY +  gfCommonYDistance + 0.1f;	  
//	  }
//	  gfCurrentY = 0.0f;
//	  gfCurrentX = gfCurrentX +  gfCommonXDistance;
//	}
//	gfCurrentX = 0.0f;
//	
//}