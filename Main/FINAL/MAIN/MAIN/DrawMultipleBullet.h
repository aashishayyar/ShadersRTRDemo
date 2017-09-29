#pragma once
#include"Main.h"
#include "Bullet.h"

void DrawMultipleBulletFireEffect(void);
void updateMultipleBulletFire(void);
void drawCharacter(byte bChar);


extern int gfCurrentCharacterIndex;

//variable for placing Shaders
extern int giCountBullet;

//variable for Shaders Drawing
static float rotateSingleBullet;
static int extra1;
static int extra2;
extern float zShift;
extern float leftShift;
extern float xLShift ;//6.0;
extern float xTest;

// for changing position of whole 'Shaders'
extern float xBulletCord;
extern float yBulletCord;
extern float zBulletCord;

typedef struct bullCords {
	float xCord;
	float yCord;
	float zCord;
	float bulletScale;
} bulletData;
