//-------------------------------------------------------------------------
// HEAD RELATED VARIABLES
//-------------------------------------------------------------------------

float stickyManColor[] = { 1.0f,0.0f,0.0f };	// Red color
float headTransX = 0.0f;		// starting point of translation for sticky man
float headNumberOfSides = 360;	// Number of vertices for triangle fans

float headCenterX = -1.5f;	// Center of circle on X axis
float headCenterY = 1.0f;		// Center of circle on Y axis
float headCenterZ = 0.0f;		// Center of circle on Z axis

// pi is nothing but ratio of circumference of circle to diameter and mostly its 3.14
// but if we initilialize doublePI to 3.14 then it will draw only half filled circle and we want full 360 degree circle
// and to acheive doublePI variable is initialized to double of PI value
float doublePI = 2.0f*3.14;

float headRadius = 0.2f;		// head radius

//-------------------------------------------------------------------------
// VENTRAL BODY RELATED VARIABLES
//-------------------------------------------------------------------------

float vbColor[] = { 1.0f,0.0f,0.0f };	// Red color

float vbXPoint = -1.5f;		// X axis point for ventral body
float vbYPoint = 0.8f;		// Y axis point for ventral body
float vbZPoint = 0.0f;		// Z axis point for ventral body

float vbBase = 0.03f;		// Specifies the radius of the cylinder at Z = 0.
float vbTop = 0.03f;		// Specifies the radius of the cylinder at Z = height
float vbHeight = 1.0f;	// Specifies the height of the cylinder
int vbSlices = 70.0f;		// Specifies the number of subdivisions around the X axis
int vbStacks = 70.0f;		// Specifies the number of subdivisions along the X axis

float vbShoulderLength = 0.3f;		// shoulder length
float vbThighLength = 0.3f;		// thigh length
float vbStartLeftElbowAngle = 338.0f;		// starting angle for left elbow
float vbStartLeftElbowAngleLimit = 368.0f;		// limit for angle of left elbow
float vbStartLeftShoulderAngle = 50.0f;	// starting angle for left shoulder
float vbStartLeftShoulderAngleLimit = 80.0f;	// limit for angle of left shoulder
float vbHandSpeed = 0.1f;		// hand speed#pragma once
