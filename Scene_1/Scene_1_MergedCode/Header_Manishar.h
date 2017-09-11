#pragma once
GLfloat windowWidth;
GLfloat windowHeight;
bool gbZoomIn = 1;
GLfloat angle = 0.0f;
GLfloat prevAngle = 0.0f;

//If room size is changed, changed depth of room
struct RoomSize {
	GLfloat xCor = 17.0f;
	GLfloat yCor = 20.0f;
	GLfloat zCor = 18.0f;
}roomSize;

struct RoomDepth {
	GLfloat xCor = roomSize.xCor + 5.0f;
	GLfloat yCor = roomSize.yCor + 10.0f;
	GLfloat zCor = 18.0f;
}roomDepth;

struct CameraPosition {
	GLfloat x = 0.0f;
	GLfloat y = 10.0f;
	GLfloat z = 25.0f;
}cameraPosition;

struct CenterOfLookAt {
	GLfloat x = 0.0f;
	GLfloat y = 6.0f;
	GLfloat z = -50.0f;
}centerLookAt;

struct ObjectCameraInfo {
	CenterOfLookAt startlookAt;
	GLfloat speed;
	CenterOfLookAt endLookAt;
	bool isReverse;
};

struct WatchPosition {
	GLfloat x = 0.0f;
	GLfloat y = 20.0f;
	GLfloat z = -16.0f;
}watchPosition;

struct MatrixWallPosition {
	GLfloat x = -15.0f;
	GLfloat y = -4.0f;
	GLfloat z = -40.0f;
}matrixPosition;

int lookAtAxis = 1.0f;
bool isRotating = false;

GLfloat zoom = 5.0f;
GLfloat speed = 0.1f;
//GLfloat matrixWallDepth = -40.0f;
//GLfloat watchPosition = (roomSize.yCor / 1.55);