#pragma once
extern int objectsIteration;

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

float gfDoorLength = 20.0f;
float gfDoorWidth = -10.0f;
//Upper Middle Design Front Variable
float gfDoorFrontFaceUpperDesignStartX = -2.2f;
float gfDoorFrontFaceUpperDesignStartY = 9.2f;
float gfDoorFrontFaceUpperDesignWidth = -5.6f;
float gfDoorFrontFaceUpperDesignHeight = 8.6f;
//Upper Middle Design Back Variable
float gfDoorBackFaceUpperDesignStartX = -2.0f;
float gfDoorBackFaceUpperDesignStartY = 9.0f;
float gfDoorBackFaceUpperDesignWidth = -6.0f;
float gfDoorBackFaceUpperDesignHeight = 9.0f;

//Lower Middle Design Front Variable
float gfDoorFrontFaceLowerDesignStartX = -2.2f;
float gfDoorFrontFaceLowerDesignStartY = 3.2f;
float gfDoorFrontFaceLowerDesignWidth = -5.6f;
float gfDoorFrontFaceLowerDesignHeight = 4.6f;
//Lower Middle Design Back Variable
float gfDoorBackFaceLowerDesignStartX = -2.0f;
float gfDoorBackFaceLowerDesignStartY = 3.0f;
float gfDoorBackFaceLowerDesignWidth = -6.0f;
float gfDoorBackFaceLowerDesignHeight = 5.0f;


float gfDoorThickness = 0.5f;
float gfDoorDesignThickness = 0.05f;
extern int giDoorMovementTimer;
