#include"Main.h"

//variables for animation
extern GLfloat translate_r_y= 0.0f;
extern GLfloat change_r = 0.001f;

extern GLfloat translate_e_y = -4.3f;
extern GLfloat change_e =  0.001f;

extern GLfloat translate_h_y= 0.0f;
extern GLfloat change_h = 0.001f;

extern GLfloat translate_t_y = -0.3f;
extern GLfloat change_t = 0.001f;

extern GLfloat translate_f_y = -0.4f;
extern GLfloat change_f = 0.001f;

//variables for fade in/out
extern GLfloat r_front = 0.0f;
extern GLfloat g_front = 0.0f;
extern GLfloat b_front = 0.0f;

extern GLfloat r_back = 0.0f;
extern GLfloat g_back = 0.0f;
extern GLfloat b_back = 0.0f;

//methods
void drawLogo(void);
void logoAnimation(void);
void logoFadeInEffect(void);
void logoFadeOutEffect(void);