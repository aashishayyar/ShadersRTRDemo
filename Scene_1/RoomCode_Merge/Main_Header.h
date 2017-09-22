#include <gl/GL.h>
#include <gl/GLU.h>

#define numberOfObjects 4
#define IDT_TIMER_MINUTE 2
#define IDT_TIMER_SECOND 1

#pragma once
GLfloat angle = 0.0f;
int objectsIteration = 0;

extern struct RoomSize {
	GLfloat xCor = 17.0f;
	GLfloat yCor = 20.0f;
	GLfloat zCor = 18.0f;
};
extern RoomSize roomSize;

//Struct required for gluLookAt
struct CameraPosition {
	GLfloat x = 0.0f;
	GLfloat y = 10.0f;
	GLfloat z = 35.0f;
};
CameraPosition cameraPosition;

struct CenterOfLookAt {
	GLfloat x = 0.0f;
	GLfloat y = roomSize.yCor / 3.0f;
	GLfloat z = 0.0f;
};
CenterOfLookAt centerLookAt;

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
};
WatchPosition watchPosition;

struct MatrixDoorPosition {
	GLfloat x = 5.0f;
	GLfloat y = 10.0f;
	GLfloat z = -16.0f;
};
MatrixDoorPosition matrixDoorPosition;

struct MatrixWallPosition {
	GLfloat x = -20.0f;
	GLfloat y = 0.0f;
	GLfloat z = -30.0f;
};
MatrixWallPosition matrixRoomPosition;

GLfloat zoom = 5.0f;
GLfloat speed = 0.004f;
