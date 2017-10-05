#pragma once
//Function Prototypes

void DrawMachineGunCircle(float redius);

void DrawMachineGunHalfCircle(float ZAxis);

void DrawMachineGunCylinder(float base, float top, float height);

void DrawmachineGunCube(void);

void DrawMachineGun(void);

void updateMachineGun(void);

//Variable for Machine Gun
extern GLUquadric *quadric;

extern float GunRotateMG;

extern GLfloat angleMG;

extern GLfloat baseMG, topMG, radiusMG, heightMG;
