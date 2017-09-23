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

extern float gbAngle;

extern float lArm[4];
extern int giLArmDirection[4];

extern float rArm[4];
extern int giRArmDirection[4];

extern float lLeg[4];
extern int giLLegDirection[4];

extern float rLeg[4];
extern int giRLegDirection[4];


void updateNormalWalk(int currentStickMan);
void updateAllCharacters();