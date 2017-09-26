#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<math.h>
#include "DoorHeader.h"
void drawWall(void) {


	glBegin(GL_POLYGON);
	glColor3f(67.0f / 255.0f, 72.0f / 255.0f, 76.0f / 255.0f);
	glVertex3f(-40.0f, 22.0f, 0.0f);
	glVertex3f(-40.0f, -22.0f, 0.0f);
	glVertex3f(0.0f, -22.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 22.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(40.0f, 22.0f, 0.0f);
	glVertex3f(40.0f, -22.0f, 0.0f);
	glVertex3f(10.0f, -22.0f, 0.0f);
	glVertex3f(10.0f, 22.0f, 0.0f);
	glEnd();

}

void drawDoor(void) {

	glPushMatrix();

	glRotatef(gfDoorRotationAngle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f((GLfloat)gfDoorMainColor[0], (GLfloat)gfDoorMainColor[1], (GLfloat)gfDoorMainColor[2]);
	// Front face
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, gfDoorLength, 0.0f);
	glVertex3f(gfDoorWidth, gfDoorLength, 0.0f);
	glVertex3f(gfDoorWidth, 0.0f, 0.0f);

	//Back face
	glVertex3f(0.0f, 0.0f, -gfDoorThickness);
	glVertex3f(0.0f, gfDoorLength, -gfDoorThickness);
	glVertex3f(gfDoorWidth, gfDoorLength, -gfDoorThickness);
	glVertex3f(gfDoorWidth, 0.0f, -gfDoorThickness);

	//Left face
	glVertex3f(0.0f, 0.0f, gfDoorThickness);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, gfDoorLength, 0.0f);
	glVertex3f(0.0f, gfDoorLength, -gfDoorThickness);

	//Right Face
	glVertex3f(gfDoorWidth, 0.0f, -gfDoorThickness);
	glVertex3f(gfDoorWidth, 0.0f, 0.0f);
	glVertex3f(gfDoorWidth, gfDoorLength, 0.0f);
	glVertex3f(gfDoorWidth, gfDoorLength, -gfDoorThickness);

	//Top Face
	glVertex3f(gfDoorWidth, 0.0f, -gfDoorThickness);
	glVertex3f(0.0f, 0.0f, -gfDoorThickness);
	glVertex3f(0.0f, 0.0f, 0.0);
	glVertex3f(gfDoorWidth, 0.0f, 0.0);

	//Bottom Face
	glVertex3f(gfDoorWidth, gfDoorLength, -gfDoorThickness);
	glVertex3f(0.0f, gfDoorLength, -gfDoorThickness);
	glVertex3f(0.0f, gfDoorLength, 0.0);
	glVertex3f(gfDoorWidth, gfDoorLength, 0.0);

	glEnd();


	glBegin(GL_QUADS);
	glColor3f(gfDoorDesignInnerColor[0], gfDoorDesignInnerColor[1], gfDoorDesignInnerColor[2]);

	//Door Upper Middle Part
	//Back
	glVertex3f(gfDoorBackFaceUpperDesignStartX, gfDoorBackFaceUpperDesignStartY, 0.0f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, gfDoorBackFaceUpperDesignStartY, 0.0f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), 0.0f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), 0.0f);
	//Front
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, gfDoorFrontFaceUpperDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, gfDoorFrontFaceUpperDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), gfDoorDesignThickness);

	glColor3f(gfDoorDesginEdgeColor[0], gfDoorDesginEdgeColor[1], gfDoorDesginEdgeColor[2]);
	//Left	
	glVertex3f(gfDoorBackFaceUpperDesignStartX, gfDoorBackFaceUpperDesignStartY, 0.0f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, gfDoorFrontFaceUpperDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), gfDoorDesignThickness);
	glVertex3f(gfDoorBackFaceUpperDesignStartX, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), 0.0f);

	//Right
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, gfDoorBackFaceUpperDesignStartY, 0.0f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, gfDoorFrontFaceUpperDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), gfDoorDesignThickness);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), 0.0f);

	//Top
	glVertex3f(gfDoorBackFaceUpperDesignStartX, gfDoorBackFaceUpperDesignStartY, 0.0f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, gfDoorBackFaceUpperDesignStartY, 0.0f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, gfDoorFrontFaceUpperDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, gfDoorFrontFaceUpperDesignStartY, gfDoorDesignThickness);
	//Bottom
	glVertex3f(gfDoorBackFaceUpperDesignStartX, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), 0.0f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), 0.0f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), gfDoorDesignThickness);



	//Door Lower Middle Part
	glColor3f(gfDoorDesignInnerColor[0], gfDoorDesignInnerColor[1], gfDoorDesignInnerColor[2]);
	//Back
	glVertex3f(gfDoorBackFaceLowerDesignStartX, gfDoorBackFaceLowerDesignStartY, 0.0f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, gfDoorBackFaceLowerDesignStartY, 0.0f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), 0.0f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), 0.0f);
	//Front
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, gfDoorFrontFaceLowerDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, gfDoorFrontFaceLowerDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), gfDoorDesignThickness);

	glColor3f(gfDoorDesginEdgeColor[0], gfDoorDesginEdgeColor[1], gfDoorDesginEdgeColor[2]);
	//Left	
	glVertex3f(gfDoorBackFaceLowerDesignStartX, gfDoorBackFaceLowerDesignStartY, 0.0f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, gfDoorFrontFaceLowerDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), gfDoorDesignThickness);
	glVertex3f(gfDoorBackFaceLowerDesignStartX, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), 0.0f);

	//Right
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, gfDoorBackFaceLowerDesignStartY, 0.0f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, gfDoorFrontFaceLowerDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), gfDoorDesignThickness);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), 0.0f);

	//Top
	glVertex3f(gfDoorBackFaceLowerDesignStartX, gfDoorBackFaceLowerDesignStartY, 0.0f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, gfDoorBackFaceLowerDesignStartY, 0.0f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, gfDoorFrontFaceLowerDesignStartY, gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, gfDoorFrontFaceLowerDesignStartY, gfDoorDesignThickness);

	//Bottom
	glVertex3f(gfDoorBackFaceLowerDesignStartX, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), 0.0f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), 0.0f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), gfDoorDesignThickness);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), gfDoorDesignThickness);

	// Door Back Side Design

	glColor3f(gfDoorDesignInnerColor[0], gfDoorDesignInnerColor[1], gfDoorDesignInnerColor[2]);

	//Door Upper Middle Part - Back side
	//Back
	glVertex3f(gfDoorBackFaceUpperDesignStartX, gfDoorBackFaceUpperDesignStartY, -0.5f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, gfDoorBackFaceUpperDesignStartY, -0.5f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), -0.5f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), -0.5f);
	//Front
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, gfDoorFrontFaceUpperDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, gfDoorFrontFaceUpperDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), -0.55f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), -0.55f);

	glColor3f(gfDoorDesginEdgeColor[0], gfDoorDesginEdgeColor[1], gfDoorDesginEdgeColor[2]);
	//Left	
	glVertex3f(gfDoorBackFaceUpperDesignStartX, gfDoorBackFaceUpperDesignStartY, -0.5f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, gfDoorFrontFaceUpperDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), -0.55f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), -0.5f);

	//Right
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, gfDoorBackFaceUpperDesignStartY, -0.5f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, gfDoorFrontFaceUpperDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), -0.55f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), -0.5f);

	//Top
	glVertex3f(gfDoorBackFaceUpperDesignStartX, gfDoorBackFaceUpperDesignStartY, -0.5f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, gfDoorBackFaceUpperDesignStartY, -0.5f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, gfDoorFrontFaceUpperDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, gfDoorFrontFaceUpperDesignStartY, -0.55f);
	//Bottom
	glVertex3f(gfDoorBackFaceUpperDesignStartX, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), -0.5f);
	glVertex3f(gfDoorBackFaceUpperDesignStartX + gfDoorBackFaceUpperDesignWidth, (gfDoorBackFaceUpperDesignStartY + gfDoorBackFaceUpperDesignHeight), -0.5f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX + gfDoorFrontFaceUpperDesignWidth, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), -0.55f);
	glVertex3f(gfDoorFrontFaceUpperDesignStartX, (gfDoorFrontFaceUpperDesignStartY + gfDoorFrontFaceUpperDesignHeight), -0.55f);



	//Door Lower Middle Part - Back Side
	glColor3f(gfDoorDesignInnerColor[0], gfDoorDesignInnerColor[1], gfDoorDesignInnerColor[2]);
	//Back
	glVertex3f(gfDoorBackFaceLowerDesignStartX, gfDoorBackFaceLowerDesignStartY, -0.5f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, gfDoorBackFaceLowerDesignStartY, -0.5f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), -0.5f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), -0.5f);
	//Front
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, gfDoorFrontFaceLowerDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, gfDoorFrontFaceLowerDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), -0.55f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), -0.55f);

	glColor3f(gfDoorDesginEdgeColor[0], gfDoorDesginEdgeColor[1], gfDoorDesginEdgeColor[2]);
	//Left	
	glVertex3f(gfDoorBackFaceLowerDesignStartX, gfDoorBackFaceLowerDesignStartY, -0.5f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, gfDoorFrontFaceLowerDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), -0.55f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), -0.5f);

	//Right
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, gfDoorBackFaceLowerDesignStartY, -0.5f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, gfDoorFrontFaceLowerDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), -0.55f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), -0.5f);

	//Top
	glVertex3f(gfDoorBackFaceLowerDesignStartX, gfDoorBackFaceLowerDesignStartY, -0.5f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, gfDoorBackFaceLowerDesignStartY, -0.5f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, gfDoorFrontFaceLowerDesignStartY, -0.55f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, gfDoorFrontFaceLowerDesignStartY, -0.55f);

	//Bottom
	glVertex3f(gfDoorBackFaceLowerDesignStartX, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), -0.5f);
	glVertex3f(gfDoorBackFaceLowerDesignStartX + gfDoorBackFaceLowerDesignWidth, (gfDoorBackFaceLowerDesignStartY + gfDoorBackFaceLowerDesignHeight), -0.5f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX + gfDoorFrontFaceLowerDesignWidth, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), -0.55f);
	glVertex3f(gfDoorFrontFaceLowerDesignStartX, (gfDoorFrontFaceLowerDesignStartY + gfDoorFrontFaceLowerDesignHeight), -0.55f);


	glEnd();
	glPopMatrix();


}

void drawDoorKnob(void) {
	glPushMatrix();
	glRotatef(gfDoorRotationAngle, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glScalef(5.0f, 5.0f, 5.0f);
	glBegin(GL_QUADS);
	glColor3f(27.0f / 255.0f, 25.0f / 255.0f, 28.0f / 255.0f);
	//Front
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	//Back
	glVertex3f(-1.0f, -1.0f, -0.15f);
	glVertex3f(1.0f, -1.0f, -0.15f);
	glVertex3f(1.0f, 1.0f, -0.15f);
	glVertex3f(-1.0f, 1.0f, -0.15f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	knobHead = gluNewQuadric();
	knobCylinder = gluNewQuadric();
	gluQuadricDrawStyle(knobCylinder, GLU_FILL);
	gluCylinder(knobCylinder, 1.0f, 1.0f, 2.0f, 50, 5);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 2.0f);
	gluSphere(knobHead, 1.5f, 10, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawDoorFrame(void) {
	glColor3f((GLfloat) 128.0f / (GLfloat) 255.0f, (GLfloat)94.0f / (GLfloat) 255.0f, (GLfloat)59.0f / (GLfloat) 255.0f);
	glBegin(GL_QUADS);
	glVertex3f(-0.8f, 0.0f, 0.0f);
	glVertex3f(-0.8f, -21.0f, 0.0f);
	glVertex3f(-0.1f, -21.0f, 0.0f);
	glVertex3f(-0.1f, -0.8f, 0.0f);


	glVertex3f(10.8f, 0.0f, 0.0f);
	glVertex3f(10.8f, -21.0f, 0.0f);
	glVertex3f(10.1f, -21.0f, 0.0f);
	glVertex3f(10.1f, -0.8f, 0.0f);


	glVertex3f(-0.8f, 0.0f, 0.0f);
	glVertex3f(10.8f, 0.0f, 0.0f);
	glVertex3f(10.1f, -0.8f, 0.0f);
	glVertex3f(-0.1f, -0.8f, 0.0f);

	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.1f, -0.8f, 0.0f);
	glVertex3f(-0.8f, 0.0f, 0.0f);
	glVertex3f(10.8f, 0.0f, 0.0f);
	glVertex3f(10.1f, -0.8f, 0.0f);
	glVertex3f(-0.1f, -0.8f, 0.0f);
	glVertex3f(10.1f, -0.8f, 0.0f);

	glVertex3f(-0.1f, -0.8f, 0.0f);
	glVertex3f(-0.1f, -21.0f, 0.0f);
	glVertex3f(10.1f, -0.8f, 0.0f);
	glVertex3f(10.1f, -21.0f, 0.0f);
	glEnd();
}

void updateDoorAngle(void) {

	if (gbDoorMovement && giDoorMovementTimer == 6) {
		gfDoorRotationAngle = gfDoorRotationAngle + 0.01f;
		if (gfDoorRotationAngle >= 80.0f) {
			gfDoorRotationAngle = 0.0f;
			gbDoorMovement = false;
		}
	}
}