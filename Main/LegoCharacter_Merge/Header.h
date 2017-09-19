#include "Main.h"
/*================== Rahul header ============================*/
void DrawChest_LucaBracy(GLfloat topX, GLfloat topZ);
void DrawFace_LucaBracy(GLfloat topX, GLfloat topZ);
void DrawArcUsingGL_POINTS(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat r, GLfloat startAngle, GLfloat endAngle, GLfloat pointSize);
// Draw sphere
void DrawSphere(GLfloat, GLint, GLint);

GLUquadric *quadric_LucaBracy = NULL;

// Eyebrow
GLfloat eyebrowRadius = 0.5f;
GLfloat eyebrowThickness = 3.0f;
GLfloat eyebrowStartAngle = 1.17f;
GLfloat eyebrowEndAngle = 1.75f;

// Mustache
GLfloat mustacheRadius = 0.8f;
GLfloat mustacheThickness = 2.0f;
GLfloat mustacheStartAngle = 1.3f;
GLfloat mustacheEndAngle = 1.8f;