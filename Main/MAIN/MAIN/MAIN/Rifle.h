#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<math.h>

extern GLUquadric *quadric;
extern HDC ghdc;
extern int RotateGun;

//rotate the each part of the Gun
extern float RotateAngle;

void DrawRifle(void);

void CUBE(void);

void FireStickDecoration(void);
