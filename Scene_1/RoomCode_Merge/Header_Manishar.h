#pragma once
//If room size is changed, changed depth of room
struct RoomSize {
	GLfloat xCor = 17.0f;
	GLfloat yCor = 20.0f;
	GLfloat zCor = 18.0f;
};
RoomSize roomSize;

struct RoomDepth {
	GLfloat xCor = roomSize.xCor + 10.0f;
	GLfloat yCor = roomSize.yCor + 20.0f;
	GLfloat zCor = 18.0f;
};
RoomDepth roomDepth;
