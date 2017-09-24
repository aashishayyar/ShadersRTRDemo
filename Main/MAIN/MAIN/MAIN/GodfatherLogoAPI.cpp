
#include"logo.h"

/*****************Variables dedicated to Godfather Logo*****************/

extern GLfloat translate_r_y = 0.0f;
extern GLfloat change_r = 0.001f;

extern GLfloat translate_e_y = -4.3f;
extern GLfloat change_e = 0.001f;

extern GLfloat translate_h_y = 0.0f;
extern GLfloat change_h = 0.001f;

extern GLfloat translate_t_y = -0.3f;
extern GLfloat change_t = 0.001f;

extern GLfloat translate_f_y = -0.4f;
extern GLfloat change_f = 0.001f;

//variables for fade in/out
extern GLfloat r_front = 1.0f;
extern GLfloat g_front = 1.0f;
extern GLfloat b_front = 1.0f;

extern GLfloat r_back = 1.0f;
extern GLfloat g_back = 1.0f;
extern GLfloat b_back = 1.0f;

int rFlag = 1;

void drawLogo(void)
{
	logoAnimation();
	glPushMatrix();
	
		glTranslatef(8.0f,8.0f,-10.0f);
		glPushMatrix();
			//glTranslatef(0.0f, 0.0f, -20.0f);

			glPolygonMode(GL_FRONT, GL_FILL);
			glColor3f(r_front,g_front,b_front);
			// for letter G
			glPolygonMode(GL_FRONT, GL_FILL);
			glPointSize(5.0);
			glBegin(GL_POLYGON);
			glVertex3f(-2.90f, 0.41f, 0.0f);
			glVertex3f(-6.30f, 0.41f, 0.0f);
			glVertex3f(-6.6f, 0.15f, 0.0f);
			glVertex3f(-5.75f, -0.3f, 0.0f);
			glVertex3f(-3.40f, -0.3f, 0.0f);
			glEnd();

			//glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON);

			glVertex3f(-6.30f, 0.41f, 0.0f);
			glVertex3f(-6.6f, 0.15f, 0.0f);
			glVertex3f(-6.6f, -3.50f, 0.0f);
			glVertex3f(-5.75f, -3.70f, 0.0f);
			glVertex3f(-5.75f, -0.3f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-4.50f, -3.70f, 0.0f);
			glVertex3f(-4.40f, -3.95f, 0.0f);
			glVertex3f(-4.40f, -1.5f, 0.0f);
			glVertex3f(-5.30f, -1.5f, 0.0f);
			glVertex3f(-5.10f, -1.7f, 0.0f);
			glVertex3f(-5.10f, -3.1f, 0.0f);
			glVertex3f(-5.75f, -3.1f, 0.0f);
			glVertex3f(-5.75f, -3.70f, 0.0f);
			glEnd();


			// for letter O
			glPolygonMode(GL_FRONT, GL_FILL);
			glBegin(GL_POLYGON);
			glVertex3f(-4.10f, -1.7f, 0.0f);
			glVertex3f(-4.10f, -3.50f, 0.0f);
			glVertex3f(-3.90f, -3.70f, 0.0f);
			glVertex3f(-2.5f, -3.70f, 0.0f);
			glVertex3f(-2.3f, -3.50f, 0.0f);
			glVertex3f(-2.3f, -1.7f, 0.0f);
			glVertex3f(-2.5f, -1.5f, 0.0f);
			glVertex3f(-3.9f, -1.5f, 0.0f);
			glEnd();


			// inner part of letter O
			glColor3f(r_back,g_back,b_back);
			glBegin(GL_POLYGON);
			glVertex3f(-3.1f, -2.0f, 0.0f);
			glVertex3f(-3.3f, -2.0f, 0.0f);
			glVertex3f(-3.3f, -3.2f, 0.0f);
			glVertex3f(-3.1f, -3.2f, 0.0f);
			glEnd();

			// for letter d
			glColor3f(r_front,g_front,b_front);
			glPolygonMode(GL_FRONT, GL_FILL);
			glBegin(GL_POLYGON);
			glVertex3f(-1.80f, -1.50f, 0.0f);
			glVertex3f(-2.00f, -1.70f, 0.0f);
			glVertex3f(-2.00f, -3.5f, 0.0f);
			glVertex3f(-1.80f, -3.7f, 0.0f);
			glVertex3f(-1.30f, -3.7f, 0.0f);
			glVertex3f(-1.1f, -3.5f, 0.0f);
			glVertex3f(-0.9f, -3.7f, 0.0f);
			glVertex3f(-0.3f, -3.7f, 0.0f);
			glVertex3f(-0.4f, -3.5f, 0.0f);
			glVertex3f(-0.4f, -1.5f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-1.09f, -1.50f, 0.0f);
			glVertex3f(-0.4f, -1.50f, 0.0f);
			glVertex3f(-0.4f, 0.41f, 0.0f);  
			glVertex3f(-1.09f, 0.01f, 0.0f);
			glEnd();

			// inner part of letter d
			glPolygonMode(GL_FRONT, GL_FILL);
			glBegin(GL_POLYGON);
			glColor3f(r_back,g_back,b_back);
			glVertex3f(-1.05f, -2.0f, 0.0f);
			glVertex3f(-1.30f, -2.0f, 0.0f);
			glVertex3f(-1.30f, -3.2f, 0.0f);
			glVertex3f(-1.05f, -3.2f, 0.0f);
			glEnd();


			// for letter f in father
			glPushMatrix();
				glTranslatef(0.0f,translate_f_y,0.0f);
				glBegin(GL_POLYGON);
				glColor3f(r_front,g_front,b_front);
				glVertex3f(0.6f, 0.40f, 0.0f);
				glVertex3f(-0.1f, 0.40f, 0.0f);
				glVertex3f(-0.1f, -3.7f, 0.0f);
				glVertex3f(0.6f, -3.7f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(1.1f, -1.5f, 0.0f);
				glVertex3f(0.6f, -1.5f, 0.0f);
				glVertex3f(0.4f, -2.00f, 0.0f);
				glVertex3f(0.9f, -2.00f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(1.0f, 0.40f, 0.0f);
				glVertex3f(0.4f, 0.40f, 0.0f);
				glVertex3f(0.4f, -0.20f, 0.0f);
				glVertex3f(1.0f, -0.20f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(1.5f, 0.40f, 0.0f);
				glVertex3f(0.8f, 0.40f, 0.0f);
				glVertex3f(0.8f, -0.60f, 0.0f);
				glVertex3f(1.5f, -0.30f, 0.0f);
				glEnd();
			glPopMatrix();


			// for a
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_POLYGON);
			glVertex3f(1.2f, -1.5f, 0.0f);
			glVertex3f(2.2f, -1.5f, 0.0f);
			glVertex3f(2.2f, -2.0f, 0.0f);
			glVertex3f(1.0f, -2.0f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(1.9f, -1.5f, 0.0f);
			glVertex3f(2.5f, -1.5f, 0.0f);
			glVertex3f(2.5f, -3.2f, 0.0f);
			glVertex3f(1.9f, -3.2f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(2.5f, -3.2f, 0.0f);
			glVertex3f(2.5f, -3.7f, 0.0f);
			glVertex3f(1.0f, -3.7f, 0.0f);
			glVertex3f(1.0f, -3.2f, 0.0f);
			glEnd();


			glBegin(GL_POLYGON);
			glVertex3f(1.0f, -2.6f, 0.0f);
			glVertex3f(1.6f, -2.6f, 0.0f);
			glVertex3f(1.6f, -3.2f, 0.0f);
			glVertex3f(1.0f, -3.2f, 0.0f);
			glEnd();


			glBegin(GL_POLYGON);
			glVertex3f(2.0f, -2.6f, 0.0f);
			glVertex3f(2.0f, -2.2f, 0.0f);
			glVertex3f(1.0f, -2.6f, 0.0f);
			glVertex3f(1.2f, -3.0f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glColor3f(r_back,g_back,b_back);
			glVertex3f(2.1f, -3.7f, 0.0f);
			glVertex3f(1.9f, -3.4f, 0.0f);
			glVertex3f(1.7f, -3.7f, 0.0f);
			glEnd();


			// small t in father
			glPushMatrix();
				glTranslatef(0.0f,translate_t_y,0.0f);
				glColor3f(r_front,g_front,b_front);
				glBegin(GL_POLYGON);
				glVertex3f(3.3f, 0.40f, 0.0f);
				glVertex3f(2.6f, 0.10f, 0.0f);
				glVertex3f(2.6f, -3.7f, 0.0f);
				glVertex3f(3.3f, -3.7f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(3.8f, -1.5f, 0.0f);
				glVertex3f(3.0f, -1.5f, 0.0f);
				glVertex3f(3.0f, -2.00f, 0.0f);
				glVertex3f(3.6f, -2.00f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(3.6f, -3.7f, 0.0f);
				glVertex3f(3.0f, -3.7f, 0.0f);
				glVertex3f(3.0f, -3.20f, 0.0f);
				glEnd();
			glPopMatrix();

			// h in father
			glPushMatrix();
				glTranslatef(0.0f,translate_h_y,0.0f);
				glBegin(GL_POLYGON);
				glVertex3f(4.4f, 0.40f, 0.0f);
				glVertex3f(3.7f, 0.10f, 0.0f);
				glVertex3f(3.7f, -3.7f, 0.0f);
				glVertex3f(4.4f, -3.7f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(4.7f, -1.5f, 0.0f);
				glVertex3f(4.1f, -1.5f, 0.0f);
				glVertex3f(4.1f, -2.00f, 0.0f);
				glVertex3f(4.7f, -2.00f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(5.2f, -1.50f, 0.0f);
				glVertex3f(4.6f, -1.50f, 0.0f);
				glVertex3f(4.6f, -3.7f, 0.0f);
				glVertex3f(5.2f, -3.7f, 0.0f);
				glEnd();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.00f, translate_e_y, 0.0f);
				//for letter e of word 'father'
				glPolygonMode(GL_FRONT, GL_FILL);
				glColor3f(r_front,g_front,b_front);
				glBegin(GL_POLYGON);
				glVertex3f(-1.10f, 2.85f, 0.0f);
				glVertex3f(-2.50f, 2.85f, 0.0f);
				glVertex3f(-2.60f, 2.70f, 0.0f);
				glVertex3f(-2.60f, 1.30f, 0.0f);
				glVertex3f(-2.05f, 1.30f, 0.0f);
				glVertex3f(-1.10f, 2.0f, 0.0f);
				glVertex3f(-1.00f, 2.10f, 0.0f);
				glVertex3f(-1.00f, 2.75f, 0.0f);
				glEnd();

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_POLYGON);
				glVertex3f(-2.60f, 0.91f, 0.0f);
				glVertex3f(-2.60f, 1.30f, 0.0f);
				glVertex3f(-2.05f, 1.30f, 0.0f);
				glVertex3f(-2.05f, 0.61f, 0.0f);
				glVertex3f(-2.45f, 0.61f, 0.0f);
				glEnd();

				glPolygonMode(GL_FRONT, GL_FILL);
				glBegin(GL_POLYGON);
				glVertex3f(-1.10f, 0.61f, 0.0f);
				glVertex3f(-1.00f, 0.71f, 0.0f);
				glVertex3f(-1.00f, 1.25f, 0.0f);
				glVertex3f(-1.15f, 1.05f, 0.0f);
				glVertex3f(-2.05f, 1.05f, 0.0f);
				glVertex3f(-2.05f, 0.61f, 0.0f);
				glEnd();

				//inner part of letter e
				glColor3f(r_back,g_back,b_back);
				glBegin(GL_POLYGON);
				glVertex3f(-1.65f, 2.35f, 0.0f);
				glVertex3f(-2.05f, 2.35f, 0.0f);
				glVertex3f(-2.05f, 1.80f, 0.0f);
				glVertex3f(-1.65f, 2.13f, 0.0f);
				glEnd();
			glPopMatrix();


			// letter r in father
			glPushMatrix();
			glTranslatef(4.0f, translate_r_y, 0.0f);
			//glTranslatef(-4.0f, translate_r_y, -20.0f);
				glColor3f(r_front,g_front,b_front);
				glBegin(GL_POLYGON);
				glVertex3f(4.0f, -1.50f, 0.0f);
				glVertex3f(3.3f, -1.50f, 0.0f);
				glVertex3f(3.3f, -3.7f, 0.0f);
				glVertex3f(4.0f, -3.7f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(4.7f, -1.5f, 0.0f);
				glVertex3f(4.0f, -1.5f, 0.0f);
				glVertex3f(4.0f, -2.20f, 0.0f);
				glVertex3f(4.7f, -1.80f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(4.9f, -1.50f, 0.0f);
				glVertex3f(4.3f, -1.50f, 0.0f);
				glVertex3f(4.3f, -2.5f, 0.0f);
				glVertex3f(4.9f, -2.2f, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glColor3f(r_back,g_back,b_back);
				glVertex3f(4.3f, -1.50f, 0.0f);
				glVertex3f(4.0f, -1.50f, 0.0f);
				glVertex3f(4.0f, -1.70f, 0.0f);
				glEnd();
			glPopMatrix();


		// h in THE 
		glPushMatrix();
			//glLoadIdentity();
			glTranslatef(-7.7f, 4.3f, 0.0f);
			glBegin(GL_POLYGON);
			glColor3f(r_front,g_front,b_front);
			glVertex3f(3.8f, 0.05f, 0.0f);
			glVertex3f(3.1f, 0.05f, 0.0f);
			glVertex3f(3.1f, -3.7f, 0.0f);
			glVertex3f(3.8f, -3.7f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(4.5f, -1.4f, 0.0f);
			glVertex3f(3.8f, -1.4f, 0.0f);
			glVertex3f(3.8f, -2.00f, 0.0f);
			glVertex3f(4.5f, -2.00f, 0.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(4.7f, -1.40f, 0.0f);
			glVertex3f(4.1f, -1.40f, 0.0f);
			glVertex3f(4.1f, -3.7f, 0.0f);
			glVertex3f(4.7f, -3.7f, 0.0f);
			glEnd();
		glPopMatrix();

		// For T of word THE
		glPushMatrix();
			//glLoadIdentity();
			glTranslatef(-9.0f, 4.3f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3f(3.55f, 0.05f, 0.0f);
			glVertex3f(2.75f, 0.05f, 0.0f);
			glVertex3f(2.75f, -3.7f, 0.0f);
			glVertex3f(3.55f, -3.7f, 0.0f);
			glEnd();

			glTranslatef(0.0, 1.0, 0.0);
			glBegin(GL_POLYGON);
			glColor3f(r_front,g_front,b_front);
			glVertex3f(4.3f, -1.5f, 0.0f);
			glVertex3f(2.1f, -1.5f, 0.0f);
			glVertex3f(2.1f, -0.95f, 0.0f);
			glVertex3f(4.3f, -0.95f, 0.0f);
			glEnd();
		glPopMatrix();

		//for letter e of word 'The'
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(r_front,g_front,b_front);
		glBegin(GL_POLYGON);
		glVertex3f(-1.10f, 2.85f, 0.0f);
		glVertex3f(-2.50f, 2.85f, 0.0f);
		glVertex3f(-2.60f, 2.70f, 0.0f);
		glVertex3f(-2.60f, 1.30f, 0.0f);
		glVertex3f(-2.05f, 1.30f, 0.0f);
		glVertex3f(-1.10f, 2.0f, 0.0f);
		glVertex3f(-1.00f, 2.10f, 0.0f);
		glVertex3f(-1.00f, 2.75f, 0.0f);
		glEnd();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
		glVertex3f(-2.60f, 0.91f, 0.0f);
		glVertex3f(-2.60f, 1.30f, 0.0f);
		glVertex3f(-2.05f, 1.30f, 0.0f);
		glVertex3f(-2.05f, 0.61f, 0.0f);
		glVertex3f(-2.45f, 0.61f, 0.0f);
		glEnd();

		glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_POLYGON);
		glVertex3f(-1.10f, 0.61f, 0.0f);
		glVertex3f(-1.00f, 0.71f, 0.0f);
		glVertex3f(-1.00f, 1.25f, 0.0f);
		glVertex3f(-1.15f, 1.05f, 0.0f);
		glVertex3f(-2.05f, 1.05f, 0.0f);
		glVertex3f(-2.05f, 0.61f, 0.0f);
		glEnd();

		//inner part of letter e
		glColor3f(r_back,g_back,b_back);
		glBegin(GL_POLYGON);
		glVertex3f(-1.65f, 2.35f, 0.0f);
		glVertex3f(-2.05f, 2.35f, 0.0f);
		glVertex3f(-2.05f, 1.80f, 0.0f);
		glVertex3f(-1.65f, 2.13f, 0.0f);
		glEnd();

		//code for hand 
		glPushMatrix();
			glTranslatef(4.5f, 6.0f, 0.0f);
			glLineWidth(7.0f);
			glColor3f(r_front,g_front,b_front);
			glBegin(GL_LINE_LOOP);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			glVertex3f(-0.9f, -0.8f, 0.0f);
			glVertex3f(-2.2f, -2.0f, 0.0f);
			glVertex3f(-2.25f, -3.1f, 0.0f);
			glVertex3f(-2.0f, -3.15f, 0.0f);
			glVertex3f(-0.8f, -3.5f, 0.0f);
			glVertex3f(-0.4f, -3.3f, 0.0f);  
			glVertex3f(0.7f, -3.8f, 0.0f);
			glVertex3f(1.6f, -2.8f, 0.0f);
			glVertex3f(2.2f, -2.7f, 0.0f);
			glVertex3f(2.2f, -1.6f, 0.0f);
			glVertex3f(1.5f, -0.8f, 0.0f);
			glVertex3f(1.6f, 1.0f, 0.0f);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(-1.3f, -3.35f, 0.0f);
			glVertex3f(-0.9f, -2.2f, 0.0f);

			glVertex3f(-1.8f, -3.20f, 0.0f);
			glVertex3f(-1.6f, -2.35f, 0.0f);

			glVertex3f(1.1f, -3.4f, 0.0f);
			glVertex3f(1.3f, -3.7f, 0.0f);

			glVertex3f(1.3f, -3.7f, 0.0f);
			glVertex3f(2.2f, -2.7f, 0.0f);
			glEnd();

			glLineWidth(3.0f);
			glBegin(GL_LINES);
			glVertex3f(1.1f, -3.4f, 0.0f);
			glVertex3f(1.7f, -3.3f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(-2.2f, -2.2f, 0.0f);
			glVertex3f(-2.25f, -3.0f, 0.0f);
			glVertex3f(-3.50f, -2.8f, 0.0f);
			glVertex3f(-3.20f, -2.0f, 0.0f);
			glEnd();
	
			glBegin(GL_QUADS);
			glVertex3f(1.7f, -1.0f, 0.0f);
			glVertex3f(2.1f, -1.5f, 0.0f);
			glVertex3f(3.05f, -1.15f, 0.0f);
			glVertex3f(2.5f, -0.7f, 0.0f);
			glEnd();
	
			glBegin(GL_QUADS);
			glVertex3f(0.1f, -2.95f, 0.0f);
			glVertex3f(-1.2f, -4.2f, 0.0f);
			glVertex3f(-2.0f, -4.2f, 0.0f);
			glVertex3f(0.1f, -2.0f, 0.0f);
			glEnd();
	
			glBegin(GL_QUADS);
			glVertex3f(1.2f, -2.15f, 0.0f);
			glVertex3f(4.2f, -2.2f, 0.0f);
			glVertex3f(3.8f, -2.85f, 0.0f);
			glVertex3f(1.2f, -2.85f, 0.0f);
			glEnd();
	

			//Strings attached to hand
			glBegin(GL_LINES);
			//string connected to letter f
			glVertex3f(-3.3f,-3.0f,0.0f);
			glVertex3f(-3.3f,-6.1f,0.0f);
	
			//string connected to letter t
			glVertex3f(-1.7f,-4.3f,0.0f);
			glVertex3f(-1.7f,-8.2f,0.0f);

			//string connected to letter h
			glVertex3f(-0.4f,-3.5f,0.0f);
			glVertex3f(-0.4f,-8.2f,0.0f);

			//string connected to letter e
			glVertex3f(1.3f,-3.8f,0.0f);
			glVertex3f(1.3f,-8.0f,0.0f);

			//string connected to letter r 1
			glVertex3f(2.9f,-3.0f,0.0f);
			glVertex3f(2.9f,-8.2f,0.0f);

			//string connected to letter r 1 half
			glVertex3f(2.9f,-2.1f,0.0f);
			glVertex3f(2.9f,-1.3f,0.0f);

			//string connected to letter r 2
			glVertex3f(4.2f,-2.6f,0.0f);
			glVertex3f(4.2f,-8.0f,0.0f);
			glEnd();
		glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void logoAnimation(void)
{

	translate_r_y = translate_r_y + change_r;
	if (translate_r_y < -0.5f)
	{
		change_r = 0.001f;
	}
	else if (translate_r_y > 0.2f)
	{
		change_r = -0.001f;
	}

	translate_e_y = translate_e_y + change_e;
	if(translate_e_y < -4.7f)
	{
		change_e = 0.001f;
	}
	else if(translate_e_y > -3.8f)
	{
		change_e = -0.001f;
	}


	translate_h_y = translate_h_y + change_h;
	if(translate_h_y < -0.6f)
	{
		change_h = 0.001f;
	}
	else if(translate_h_y > 0.5f)
	{
		change_h = -0.001f;
	}


	translate_t_y = translate_t_y + change_t;
	if(translate_t_y < -0.2f)
	{
		change_t = 0.001f;
	}
	else if(translate_t_y > 0.5f)
	{
		change_t = -0.001f;
	}

	translate_f_y = translate_f_y + change_f;
	if(translate_f_y < -0.6f)
	{
		change_f = 0.001f;
	}
	else if(translate_f_y > 0.3f)
	{
		change_f = -0.001f;
	}

}

void logoFadeInEffect(void)
{
	if(r_front <= 1.0f && g_front <= 1.0f && b_front <= 1.0f )
	{
		r_front += 0.001f;
		g_front += 0.001f;
		b_front += 0.001f;
	}
}


void logoFadeOutEffect(void)
{
	if(r_front >= r_back && g_front >= g_back && b_front >= b_back )
	{
		r_front -= 0.001f;
		g_front -= 0.001f;
		b_front -= 0.001f;
	}
}
