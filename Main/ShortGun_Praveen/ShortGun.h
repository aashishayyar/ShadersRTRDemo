#include "Main.h"
typedef struct shortgun
{
	GLfloat PISTOL_X;
	GLfloat PISTOL_Y;
	GLfloat PISTOL_Z;

	GLfloat PISTOL_COLOR_RED;
	GLfloat PISTOL_COLOR_GREEN;
	GLfloat PISTOL_COLOR_BLUE;

}SHORTGUN;

typedef struct color
{
	GLfloat PISTOL_COLOR_RED;
	GLfloat PISTOL_COLOR_GREEN;
	GLfloat PISTOL_COLOR_BLUE;

}COLOR;


GLUquadric *_pGLUShortGunFilledPipe = gluNewQuadric();
GLUquadric *_pGLUShortGunWireddPipe = gluNewQuadric();
GLfloat _gShortGunAngle = 0.0f;


const int SHORTGUN_CLIPPER_LENGTH = 16;
SHORTGUN SHORTGUN_CLIPPER[SHORTGUN_CLIPPER_LENGTH] = {

	/*FRONT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, 0.0f ,(96.0f / 255.0f), (96.0f / 255.0f), (96.0f / 255.0f) },
	{ -0.1f, -0.1f, 0.0f ,(160.0f / 255.0f), (160.0f / 255.0f), (160.0f / 255.0f) },
	{ 0.1f, -0.1f, 0.0f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f) },
	/**/

	/*BACK*/
	{ 0.1f, 0.1f, -0.1f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, -0.1f ,(96.0f / 255.0f), (96.0f / 255.0f), (96.0f / 255.0f) },
	{ -0.1f, -0.1f, -0.4f ,(160.0f / 255.0f), (160.0f / 255.0f), (160.0f / 255.0f) },
	{ 0.1f, -0.1f, -0.4f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f) },
	/**/

	/*RIGHT*/
	{ -0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f,-0.1f ,(96.0f / 255.0f), (96.0f / 255.0f), (96.0f / 255.0f) },
	{ -0.1f, -0.1f, -0.4f ,(160.0f / 255.0f), (160.0f / 255.0f), (160.0f / 255.0f) },
	{ -0.1f, -0.1f,0.0f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f) },
	/**/

	/*LEFT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ 0.1f, -0.1f, 0.0f ,(96.0f / 255.0f), (96.0f / 255.0f), (96.0f / 255.0f) },
	{ 0.1f, -0.1f, -0.4f ,(160.0f / 255.0f), (160.0f / 255.0f), (160.0f / 255.0f) },
	{ 0.1f, 0.1f, -0.1f ,(64.0f / 255.0f), (64.0f / 255.0f), (64.0f / 255.0f) }
	/**/

};

const int SHORTGUN_HANDLE_LENGTH = 20;
SHORTGUN SHORTGUN_HANDLE[SHORTGUN_HANDLE_LENGTH] = {


	/*FRONT*/
	{ 0.1f, 0.1f, 0.0f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ -0.1f, 0.1f, 0.0f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1f, -0.4f, -0.2f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ 0.0f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/


	/*BACK*/
	{ 0.1f, 0.1f, -0.3f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ 0.0f, -0.4f, -0.6f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1f, -0.4f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ -0.1f, 0.1f, -0.3f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/


	/*LEFT*/
	{ 0.1f, 0.1f, 0.0f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ 0.1f, 0.1f, -0.3f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ 0.0f, -0.4f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ 0.0f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/

	/*RIGHT*/
	{ -0.1f, 0.1f, 0.0f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ -0.1f, 0.1f, -0.3f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1f, -0.4f, -0.6f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ -0.1f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/


	/*BOTTOM*/
	{ 0.0f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	{ 0.0f, -0.4f, -0.4f ,(102.0f / 255.0f), (51.0f / 255.0f), 0.0f },
	{ -0.1f, -0.4f, -0.4f ,(102.0f / 255.0f), 0.0f, 0.0f },
	{ -0.1f, -0.4f, -0.2f ,(153.0f / 255.0f), (76.0f / 255.0f), 0.0f },
	/**/

};


const int SHORTGUN_TRIGGER_LENGTH = 18;
SHORTGUN SHORTGUN_TRIGGER[] = {

	/*FRONT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, 0.0f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2f, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) },
	/**/

	/*BACK*/
	{ 0.1f, 0.1f, -0.1f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, -0.1f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2f, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) },
	/**/

	/*RIGHT*/
	{ -0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ -0.1f, 0.1f, -0.1f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2f, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) },
	/**/

	/*LEFT*/
	{ 0.1f, 0.1f, 0.0f ,(192.0f / 255.0f), (192.0f / 255.0f), (192.0f / 255.0f) },
	{ 0.1f, 0.1f, -0.1f ,(224.0f / 255.0f), (224.0f / 255.0f), (224.0f / 255.0f) },
	{ 0.0f, -0.2f, 0.0f ,(128.0f / 255.0f), (128.0f / 255.0f), (128.0f / 255.0f) }
	/**/
};


/*API*/
void SHORTGUN_DRAW_FILLED_PIPE(GLdouble radius, GLdouble height,COLOR color);
void SHORTGUN_DRAW_WIRED_PIPE(GLdouble radius, GLdouble height,COLOR color);
void SHORTGUN_DRAW_CLIPPER();
void SHORTGUN_DRAW_HANDLE();
void SHORTGUN_DRAW_TRIGGER();
/**/