#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<math.h>

//variable for Cylinder 
GLUquadric *quadric = NULL;

static int RotateGun = 0;

float base; //for base of the cylinder
float top; //for top of the cylinder
float height; //for height of the cylinder

float angle; //used in circle

//rotate the each part of the Gun
float RotateAngle = 90.0f;
