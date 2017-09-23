#pragma once


extern GLUquadric *quadric;

extern float gfFaceHeight;
extern float gfFaceWidth;
extern float gfNeckHeight;
extern float gfNeckWidth;
extern float gfArmHeight;
extern float gfArmWidth;
extern float gfChestUpperWidth;
extern float gfChestLowerWidth;
extern float gfChestWidth;
extern float gfChestHeight;

extern float gfLegWidth;
extern float gfLegHeight;
extern float gfLegCylHeight;
extern float gfLegCylRadius;

extern float gfFootHeight;
extern float gfFootWidth;
extern float gfFootLength;

extern float gfSpeed;
extern float gfTranslateX;
extern float gfTranslateY;
extern float gfTranslateZ[4];

extern float gbAngle;

extern float lArm[4];
extern int giLArmDirection[4];

extern float rArm[4];
extern int giRArmDirection[4];

extern float lLeg[4];
extern int giLLegDirection[4];

extern float rLeg[4];
extern int giRLegDirection[4];



void DrawCircle(float radius);
void DrawSector(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle);
void DrawSectorLine(float aRadius, float bRadius, float z, float color[3], float minAngle, float maxAngle);
void DrawSquare(float vertice1[3], float vertice2[3], float vertice3[3], float vertice4[3], float color[3]);
void DrawCubiod(float points[10][3], float color[3]);
void DrawNeck();
void DrawCylinder(float height, float radius, float color[3]);
void DrawJoints(float height, float radius, float color[3]);
void DrawWrist(float height, float radius, float color[3]);
void DrawBiceps(float height, float radius, float color[3]);
void DrawForeArm(float height, float radius, float color[3]);
void DrawHead(int currentStickMan);
void DrawHand(int direction, int currentStickMan);
void DrawThigh();
void DrawLeg(int direction, int currentStickMan);
void DrawLegSeparation();
void DrawLegoCharacters();