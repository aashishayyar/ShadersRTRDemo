#pragma once

float gfDoorMainColor[] = { 128.0f / 255.0f, 94.0f / 255.0f, 59.0f / 255.0f };
float gfDoorDesignInnerColor[] = { 112.0f / 255.0f, 79.0f / 255.0f, 46.0f / 255.0f };
float gfDoorDesginEdgeColor[] = { 89.0f / 255.0f, 60.0f / 255.0f, 31.0f / 255.0f };
bool gbDoorMovement = true;
float gfDoorRotationAngle = 0.0f;
GLUquadric *knobHead = NULL;
GLUquadric *knobCylinder = NULL;
float gfDoorWidthStartX = 0.0f;
float gfDoorWidthStartY = 0.0f;
float gfDoorWidthEndX = 10.0f;
float gfDoorWidthEndY = 10.0f;

float gfDoorLength = 22.0f;

float gfDoorThickness = 0.5f;