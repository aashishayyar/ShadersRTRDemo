#pragma once

void drawRoom(void);
void drawDoor(void);
void drawDoorFrame(void);

#define numberOfObjects 9

GLfloat windowWidth;
GLfloat windowHeight;
bool gbZoomIn = 1;
GLfloat roomAngle = 0.0f;
GLfloat prevAngle = 0.0f;

int objectsIteration = 0;

//If room size is changed, changed depth of room
struct RoomSize {
	GLfloat xCor = 17.0f;
	GLfloat yCor = 20.0f;
	GLfloat zCor = 18.0f;
}roomSize;

struct RoomDepth {
	GLfloat xCor = roomSize.xCor + 10.0f;
	GLfloat yCor = roomSize.yCor + 20.0f;
	GLfloat zCor = 18.0f;
}roomDepth;

//Struct required for gluLookAt
struct CameraPosition {
	GLfloat x = 0.0f;
	GLfloat y = 25.0f;
	GLfloat z = -6.0f;
}cameraPosition;

struct CenterOfLookAt {
	GLfloat x = 0.0f;
	GLfloat y = 25.0f;
	GLfloat z = -10.0f;
}centerLookAt;

struct XYZCoordinates {
	GLfloat x = 0.0f;
	GLfloat y = 0.0f;
	GLfloat z = 0.0f;
};

struct ObjectCameraInfo { //this structure
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

ObjectCameraInfo currentObject;
ObjectCameraInfo arrayOfObjectInfo[numberOfObjects];

//Define position of each object
struct WatchPosition {
	GLfloat x = 0.0f;
	GLfloat y = 25.0f;
	GLfloat z = -16.0f;
}watchPosition;

struct MatrixDoorPosition {
	GLfloat x = 15.0f;
	GLfloat y = 12.0f;
	GLfloat z = -17.0f;
}matrixDoorPosition;

struct MatrixWallPosition {
	GLfloat x = -20.0f;
	GLfloat y = 0.0f;
	GLfloat z = -30.0f;
}matrixRoomPosition;

struct LegoCharactersPosition {
	GLfloat x = -29.0f;
	GLfloat y = 6.5f;
	GLfloat z = -3.0f;
};
LegoCharactersPosition legoCharactersPosition;

//int lookAtAxis = 1.0f;
//bool isRotating = false;

GLfloat zoom = 5.0f;
GLfloat speed = 0.004f;
//GLfloat matrixWallDepth = -40.0f;
//GLfloat watchPosition = (roomSize.yCor / 1.55);
extern FILE *fp;

struct DoorPosition {
	GLfloat x =    0.0f;
	GLfloat y =   17.0f;
	GLfloat z = -21.05f;
};
struct DoorPosition doorPosition;

extern float gfDoorRotationAngle;


