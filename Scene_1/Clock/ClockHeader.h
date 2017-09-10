#pragma once
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define IDT_TIMER_SECOND 1
#define IDT_TIMER_MINUTE 2
#define IDT_TIMER_HOUR 3

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
float gfClockOuterLength = 2.3f;
float gfClockLength = 2.0f;
float gfClockStepMin = 1.7f;
float gfClockStepMax = 1.9f;
float gfClockSecondHandRadious = 1.5f;
float gfClockMinuteHandRadious = 1.3f;
float gfClockHourHandRadious = 1.0f;
float PI = 3.14159f;
int giCirclePoints = 360;
float gfSecondAngle = 0.0f;
float gfMinuteAngle = 2.0f;
float gfHourAngle = 1.0f;
int giClockNumber = 0;
float gfNumberMinLengthX = 0.15f;
float gfNumberMaxLengthX = 0.3f;
float gfNumberMinLengthY = 0.15f;
float gfNumberMaxLengthY = 0.3f;
float gfNumberOneLengthX = 0.1f;
float gfNumberOneLengthY = 0.1f;
float gfNumberSevenLengthX = 0.075f;
float gfNumberSevenLengthY = 0.1f;
float gfNumberFourLengthX = 0.1f;
float gfNumberFourLengthY = 0.1f;