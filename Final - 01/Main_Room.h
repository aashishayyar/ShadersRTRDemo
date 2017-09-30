#pragma once

#define numberOfObjects 19

/* From Clock Header file */
#define IDT_TIMER_SECOND 1
#define IDT_TIMER_MINUTE 2
#define IDT_TIMER_HOUR   3

extern int sceneIndex;
//Struct required for gluLookAt
extern struct CameraPosition {
	GLfloat x = 0.0f;
	GLfloat y = 10.0f;
	GLfloat z = 40.0f;
};
extern struct CameraPosition cameraPosition;

// Required for struct CentreLookAt
extern struct RoomSize {
	GLfloat xCor = 17.0f;
	GLfloat yCor = 20.0f;
	GLfloat zCor = 18.0f;
};
extern struct RoomSize roomSize;

extern struct CenterOfLookAt {
	GLfloat x = 0.0f;
	GLfloat y = 25.0f;
	GLfloat z = -16.0f;
};
extern struct CenterOfLookAt centerLookAt;

/*To Load Matrix room just after camera reaches the end of first room */
extern int objectsIteration;

// Required for ObjectCameraInfo
extern struct XYZCoordinates {
	GLfloat x = 0.0f;
	GLfloat y = 0.0f;
	GLfloat z = 0.0f;
};

// Required for two variables decalred ahead
extern struct ObjectCameraInfo
{
	CenterOfLookAt centerOflookAt;
	GLfloat speed;
	GLfloat endPosition;
	GLfloat startAngle;
	GLfloat endAngle;
	int axisOfRotation;
	bool isRotation;
	bool isCameraFixed;
	XYZCoordinates rotationRadius;
};

extern struct LegoCharactersPosition {
	GLfloat x = -15.0f;
	GLfloat y = 8.5f;
	GLfloat z = -10.0f;
};
extern LegoCharactersPosition legoCharactersPosition;

extern ObjectCameraInfo currentObject;
extern ObjectCameraInfo arrayOfObjectInfo[numberOfObjects];

// Used in WndProc : WM_TIMER : For Ticking Clock
void updateSecondAngle(void);
// Used for LookAt 
void moveCamera(void);

int giDoorMovementTimer = 0;
void updateDoorAngle(void);