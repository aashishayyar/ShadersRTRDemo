#include "Main.h"
#include "Room.h"
#include "Matrix.h"
#include "Clock.h"

extern float moveZ;
extern int delayRipple;

void MainRoom(void) {
	void drawMatrixDoor();
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, centerLookAt.x, centerLookAt.y, centerLookAt.z, 0.0f, 1.0f, 0.0f);

	drawRoom();
	drawClock();
	if (objectsIteration >= 3 && objectsIteration <= 8) { // Change if order in arrayObjectInfo gets change.
		drawMatrixRoom();
	}
}

void moveCamera(void) {

	if (objectsIteration == 12) { //Lego
		gfCameraMoveZ += 0.1f;
		gfCameraMoveX -= 0.2f;
		cameraPosition.x = gfCameraMoveX;
		cameraPosition.y = 5.0f;
		cameraPosition.z = gfCameraMoveZ;
		centerLookAt.x = -7.0f;
		centerLookAt.y = 5.0f;
		centerLookAt.z =  gfCameraMoveZ;
	}
	if (objectsIteration == 18) { //Shaders
		if (moveZ > -0.5) {
			moveZ = moveZ - 0.1;
		}
		cameraPosition.x = moveZ;
		cameraPosition.y = 5.0f;
		cameraPosition.z = 0.0f;
		centerLookAt.x = 0.0f;
		centerLookAt.y = 5.0f;
		centerLookAt.z = 0.0f;
	}
	/*
	if (objectsIteration == 19) { //Shaders
		cameraPosition.x = -5.5;
		cameraPosition.y = 5.0f;
		cameraPosition.z = 0.0f;
		centerLookAt.x = 5.0f;
		centerLookAt.y = 5.0f;
		centerLookAt.z = 0.5f;
	}
	*/
	if (objectsIteration == 13) { //Gun
		/*delayRipple = delayRipple + 1;
		cameraPosition.x = -9.0;
		cameraPosition.y = 5.5f;
		cameraPosition.z = 1.5f;
		centerLookAt.x = 8.0f;
		centerLookAt.y = 5.5f;
		centerLookAt.z = 0.0f;
		*/
		cameraPosition.x = 8.0;
		cameraPosition.y = 7.5f;
		cameraPosition.z = 1.5f;
		centerLookAt.x = -8.0f;
		centerLookAt.y = 7.5f;
		centerLookAt.z = 0.0f;
	}
	else {
		if (cameraPosition.y < currentObject.centerOflookAt.y) {
			cameraPosition.y = cameraPosition.y + currentObject.speed;
		}
		if (centerLookAt.y < currentObject.centerOflookAt.y) {
			centerLookAt.y = centerLookAt.y + currentObject.speed;
		}
		if (cameraPosition.x < currentObject.centerOflookAt.x) {
			cameraPosition.x = cameraPosition.x + currentObject.speed;
		}
		if (centerLookAt.x < currentObject.centerOflookAt.x) {
			centerLookAt.x = centerLookAt.x + currentObject.speed;
		}
		//If it is greater decrease value
		if (cameraPosition.y > currentObject.centerOflookAt.y) {
			cameraPosition.y = cameraPosition.y - currentObject.speed;
		}
		if (centerLookAt.y > currentObject.centerOflookAt.y) {
			centerLookAt.y = centerLookAt.y - currentObject.speed;
		}
		if (cameraPosition.x > currentObject.centerOflookAt.x) {
			cameraPosition.x = cameraPosition.x - currentObject.speed;
		}
		if (centerLookAt.x > currentObject.centerOflookAt.x) {
			centerLookAt.x = centerLookAt.x - currentObject.speed;
		}
		if (currentObject.isRotation == false) {
			if (cameraPosition.z > currentObject.endPosition) {
				cameraPosition.z = cameraPosition.z - currentObject.speed;
			}
			if (cameraPosition.z < currentObject.endPosition) {
				cameraPosition.z = cameraPosition.z + currentObject.speed;
			}
		}
		else if (currentObject.isRotation == true) {
			switch (currentObject.axisOfRotation) {
			case 1://X Axis

				break;
			case 2://Y Axis
				if (currentObject.startAngle < currentObject.endAngle) {
					if (currentObject.isCameraFixed == true) {
						centerLookAt.z = cos(currentObject.startAngle) * currentObject.rotationRadius.z;
						centerLookAt.x = sin(currentObject.startAngle) * currentObject.rotationRadius.x;
					}
					else {
						cameraPosition.z = cos(currentObject.startAngle) * currentObject.rotationRadius.z;
						cameraPosition.x = sin(currentObject.startAngle) *  currentObject.rotationRadius.x;
					}
					currentObject.startAngle = currentObject.startAngle + currentObject.speed;
				}
				break;
			case 3://Z Axis

				break;
			default:
				break;
			}
		}
	}
}

void resetLookAtCenter() {
	centerLookAt.x = 0.0f;
	centerLookAt.y = roomSize.yCor / 2.0f;
	centerLookAt.z = 0.0f;
}

void fillCameraObjectInfo() {
	//Initialising currentObject to room coodinates
	currentObject.centerOflookAt.x = watchPosition.x;
	currentObject.centerOflookAt.y = watchPosition.y;
	currentObject.centerOflookAt.z = watchPosition.z;
	currentObject.endPosition = 50.0f;
	currentObject.speed = 0.003f;
	currentObject.isRotation = false;
	//currentObject.axisOfRotation = 2;
	//currentObject.startAngle = 0.0f;
	//currentObject.endAngle = 90.0f;

	int arrayIndex = 0;

	arrayIndex = 0;
	//ObjectCameraInfo for watchInfo;
	centerLookAt.z = -50.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 0.005f;
	arrayOfObjectInfo[arrayIndex].endPosition = 50.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	//Same object to focus on lego charaters
	arrayIndex = 1;
	centerLookAt.z = -50.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.0f;
	arrayOfObjectInfo[arrayIndex].endPosition = 40.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 2;
	centerLookAt.z = -50.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.0f;
	arrayOfObjectInfo[arrayIndex].endPosition = 40.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 3;
	centerLookAt.z = -50.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.5f;
	arrayOfObjectInfo[arrayIndex].endPosition = 22.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 4;
	//ObjectCameraInfo for watchInfo;
	centerLookAt.z = -50.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = watchPosition.y;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 0.1f;
	arrayOfObjectInfo[arrayIndex].endPosition = watchPosition.z + 10.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 5;
	//For Matrix Room
	centerLookAt.z = -79.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = watchPosition.y - 5.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 0.1f;
	arrayOfObjectInfo[arrayIndex].endPosition = matrixRoomPosition.z - 27.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 6; //Index check for Neo charater
					//For Matrix Room to reset at center
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = 0.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = -20.0f;
	arrayOfObjectInfo[arrayIndex].speed = 0.07f;
	arrayOfObjectInfo[arrayIndex].endPosition = -20.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 7;
	//Same object to keep Neo rotating
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = 0.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = -20.0f;
	arrayOfObjectInfo[arrayIndex].speed = 0.1f;
	arrayOfObjectInfo[arrayIndex].endPosition = -20.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	//Object to make camera set to original position within room
	arrayIndex = 8;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 0.9f;
	arrayOfObjectInfo[arrayIndex].endPosition = 30.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 9;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.2f;
	arrayOfObjectInfo[arrayIndex].endPosition = 30.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 10;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.2f;
	arrayOfObjectInfo[arrayIndex].endPosition = 30.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 11;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = -8.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 0.5f;
	arrayOfObjectInfo[arrayIndex].endPosition = 23.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 12;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 0.7f;
	arrayOfObjectInfo[arrayIndex].endPosition = 30.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 13;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.2f;
	arrayOfObjectInfo[arrayIndex].endPosition = 28.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 14;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.2f;
	arrayOfObjectInfo[arrayIndex].endPosition = 28.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 15;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.2f;
	arrayOfObjectInfo[arrayIndex].endPosition = 34.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 16;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.2f;
	arrayOfObjectInfo[arrayIndex].endPosition = 34.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 17;
	/*
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = 2.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = -1.0f;
	arrayOfObjectInfo[arrayIndex].speed = 0.5f;
	arrayOfObjectInfo[arrayIndex].endPosition = 0.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;
	*/
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.2f;
	arrayOfObjectInfo[arrayIndex].endPosition = 0.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;

	arrayIndex = 18;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.x = watchPosition.x;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[arrayIndex].centerOflookAt.z = watchPosition.z;
	arrayOfObjectInfo[arrayIndex].speed = 1.2f;
	arrayOfObjectInfo[arrayIndex].endPosition = 28.0f;
	arrayOfObjectInfo[arrayIndex].isRotation = false;
	/*
	centerLookAt.z = -50.0f;
	arrayOfObjectInfo[3].centerOflookAt.x = 0.0f;
	arrayOfObjectInfo[3].centerOflookAt.y = 10.0f;
	arrayOfObjectInfo[3].centerOflookAt.z = -50.0f;
	arrayOfObjectInfo[3].speed = 0.02f;
	arrayOfObjectInfo[3].endPosition = -50.0f;

	arrayOfObjectInfo[3].isRotation = true;
	arrayOfObjectInfo[3].axisOfRotation = 2; // 2 for y axis
	arrayOfObjectInfo[3].startAngle = 0.0f;
	arrayOfObjectInfo[3].endAngle = 1.0f;
	arrayOfObjectInfo[3].isCameraFixed = true;
	arrayOfObjectInfo[3].rotationRadius.x = -10.0f;
	arrayOfObjectInfo[3].rotationRadius.z = -50.0f;

	//To reset camera to original position
	arrayOfObjectInfo[2].centerOflookAt.x = centerLookAt.x;
	arrayOfObjectInfo[2].centerOflookAt.y = centerLookAt.y;
	arrayOfObjectInfo[2].centerOflookAt.z = centerLookAt.z;
	arrayOfObjectInfo[2].speed = 0.1f;
	arrayOfObjectInfo[2].endPosition = 35.0f;
	arrayOfObjectInfo[2].isRotation = false;

	arrayOfObjectInfo[3].centerOflookAt.x = matrixDoorPosition.x;
	arrayOfObjectInfo[3].centerOflookAt.y = matrixDoorPosition.y;
	arrayOfObjectInfo[3].centerOflookAt.z = matrixDoorPosition.z;
	arrayOfObjectInfo[3].speed = 0.01f;
	arrayOfObjectInfo[3].endPosition = matrixDoorPosition.z;
	arrayOfObjectInfo[3].isRotation = false;
	*/
}

void drawMatrixDoor() {
	glPushMatrix();
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(matrixDoorPosition.x, matrixDoorPosition.y, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x + 10.0f, matrixDoorPosition.y, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x + 10.0f, 0.0f, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x, 0.0f, matrixDoorPosition.z);
	glEnd();
	glLineWidth(4.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(matrixDoorPosition.x, matrixDoorPosition.y, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x, 0.0f, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x + 10.0f, matrixDoorPosition.y, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x + 10.0f, 0.0f, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x, matrixDoorPosition.y, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x + 10.0f, matrixDoorPosition.y, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x, 0.0f, matrixDoorPosition.z);
	glVertex3f(matrixDoorPosition.x + 10.0f, 0.0f, matrixDoorPosition.z);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(matrixDoorPosition.x, 0.5f, matrixDoorPosition.z + 1.0f);
	giTempNumberOfCharacterOnX = giNumberOfCharOnX;
	giTempNumberOfCharacterOnY = giNumberOfCharOnY;
	giTempWidthOfLine = gfWidthOfLine;
	giTempHeightOfLine = gfHeightOfLine;
	giNumberOfCharOnX = 7.0f;
	giNumberOfCharOnY = 8.0f;
	gfWidthOfLine = 0.3f;
	gfHeightOfLine = 0.3f;
	gfTempCommonXDistance = gfCommonXDistance;
	gfTempCommonYDistance = gfCommonYDistance;
	gfCommonXDistance = (gfWidthOfLine * 5);
	gfCommonYDistance = (gfHeightOfLine * 5);
	DrawWall();
	giNumberOfCharOnX = giTempNumberOfCharacterOnX;
	giNumberOfCharOnY = giTempNumberOfCharacterOnY;
	gfWidthOfLine = giTempWidthOfLine;
	gfHeightOfLine = giTempHeightOfLine;
	gfCommonXDistance = gfTempCommonXDistance;
	gfCommonYDistance = gfTempCommonYDistance;
	glPopMatrix();
}

#pragma Matrix Room
void drawMatrixRoom() {
	glPushMatrix();
	glTranslatef(matrixRoomPosition.x, matrixRoomPosition.y, matrixRoomPosition.z);

	//BACK
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -gfWidthOfRoom);
	giTempNumberOfCharacterOnX = giNumberOfCharOnX;
	giNumberOfCharOnX = giNumberOfCharOnX + 34;
	DrawWall();
	giNumberOfCharOnX = giTempNumberOfCharacterOnX;
	glPopMatrix();

	//TOP
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -(gfHeightOfRoom));
	giTempNumberOfCharacterOnY = giNumberOfCharOnY;
	giNumberOfCharOnY = giNumberOfCharOnY + 1;
	DrawWall();
	giNumberOfCharOnY = giTempNumberOfCharacterOnY;
	glPopMatrix();

	//LEFT
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left 
	DrawWall();
	glPopMatrix();

	//RIGHT
	glPushMatrix();
	glTranslatef(gfHeightOfRoom, 0.0f, 0.0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //Left 
	DrawWall();
	glPopMatrix();

	//BOTTOM

	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	DrawWall();
	glPopMatrix();
	glPopMatrix();
}

void StoreWall() {
	DWORD dwTotalNumberOfCharacters = 0;
	int RandomNumber = 0;
	dwTotalNumberOfCharacters = (giNumberOfCharOnX*giNumberOfCharOnY);
	if (piRandomWallNumbers == NULL) {
		piRandomWallNumbers = (int *)malloc(sizeof(int)*(dwTotalNumberOfCharacters));
		if (piRandomWallNumbers == NULL)
		{
			//ERROR HANDLING
		}
		else
		{
			dwMaximumCharaFromWall = dwTotalNumberOfCharacters;
		}
	}
	if (dwMaximumCharaFromWall < dwTotalNumberOfCharacters) {
		piRandomWallNumbers = (int *)realloc(piRandomWallNumbers, (sizeof(int)*(dwTotalNumberOfCharacters - dwMaximumCharaFromWall)));
		if (piRandomWallNumbers == NULL)
		{
			//ERROR HANDLING
		}
		else {
			for (DWORD i = dwMaximumCharaFromWall; i < dwTotalNumberOfCharacters; i++)
			{
				RandomNumber = rand() % 27;
				piRandomWallNumbers[i] = RandomNumber;
			}
			dwMaximumCharaFromWall = dwTotalNumberOfCharacters;
		}
	}
	if ((gbWallFilled == FALSE)) {
		for (DWORD i = 0; i < dwTotalNumberOfCharacters; i++) {
			RandomNumber = rand() % 27;
			piRandomWallNumbers[i] = RandomNumber;
		}
		gbWallFilled = TRUE;
	}
	if (gbDisplayedFirstWall == FALSE) {
		gbDisplayedFirstWall = TRUE;
		dwDisplayedFirstWall = GetTickCount();
		dwSavedTickCount = dwDisplayedFirstWall;
	}
	dwGetTickCount = GetTickCount();
	if ((dwGetTickCount - dwSavedTickCount) >= gdwSpeedOfWallChange)
	{
		dwSavedTickCount = dwGetTickCount;
		gbWallFilled = FALSE;
	}
}

void RandomCharacter(int RandomNumber) {
	for (int i = 0; i < 17; i++) {
		giSevenSgment[i] = 0;
	}
	switch (RandomNumber)
	{
	case 0x0:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x1:
		giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x2:
		giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 0x3:
		giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = giSevenSgment[4] = giSevenSgment[3] = 1;
		break;
	case 0x4:
		giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[4] = 1;
		break;
	case 0x5:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[4] = giSevenSgment[3] = 1;
		break;
	case 0x6:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[3] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 0x7:
		giSevenSgment[0] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x8:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 0x9:
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 10:	//a
		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 11:	//b
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[6] = 1;
		break;
	case 12:	//c
		giSevenSgment[6] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 13:	//d
		giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 14:	//e
		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[1] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 15:	//f
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[6] = 1;
		break;
	case 16:	//g	Added 3 to differentiate from 9
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[3] = 1;
		break;
	case 17:	//h
		giSevenSgment[0] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 18:	//j
		giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 19:	//L 
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 20:	//n
		giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[6] = 1;
		break;
	case 21:	//o
		giSevenSgment[2] = giSevenSgment[6] = giSevenSgment[3] = giSevenSgment[4] = 1;
		break;
	case 22:	//q	
		giSevenSgment[1] = giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[6] = 1;
		break;
	case 23:	//p
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[0] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 24:	//s	
		giSevenSgment[1] = giSevenSgment[0] = giSevenSgment[3] = giSevenSgment[6] = giSevenSgment[4] = 1;
		break;
	case 25:	//t
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[6] = 1;
		break;
	case 26:	//y	Add 3 to differentiate from 4
		giSevenSgment[1] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 27:	//M
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[9] = giSevenSgment[7] = 1;
		break;
	case 28:	//I
		giSevenSgment[0] = giSevenSgment[11] = giSevenSgment[12] = giSevenSgment[3] = 1;
		break;
	case 29:	//Y
		giSevenSgment[7] = giSevenSgment[9] = giSevenSgment[12] = 1;
		break;
	case 30:	//T
		giSevenSgment[0] = giSevenSgment[11] = giSevenSgment[12] = 1;
		break;
	case 31:	//A
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[5] = giSevenSgment[4] = giSevenSgment[0] = giSevenSgment[6] = 1;
		break;
	case 32:	//L
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 33:	//C
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = 1;
		break;
	case 34:	//H
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[6] = 1;
		break;
	case 35:	//E
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[6] = 1;
		break;
	case 36:	//O
		giSevenSgment[0] = giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 37:	//N
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[4] = giSevenSgment[5] = giSevenSgment[7] = giSevenSgment[8] = 1;
		break;
	case 38:	//R
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[0] = giSevenSgment[6] = giSevenSgment[5] = giSevenSgment[15] = 1;
		break;
	case 39:	//V
		giSevenSgment[13] = giSevenSgment[14] = 1;
		break;
	case 40:	//U
		giSevenSgment[1] = giSevenSgment[2] = giSevenSgment[3] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;
	case 41:
		giSevenSgment[0] = giSevenSgment[3] = giSevenSgment[16] = giSevenSgment[4] = giSevenSgment[5] = 1;
		break;

	}
	return;
}

void DrawCharacter() {

	float fCreditsCentreOfTopLineX = ((gfCurrentX)+(gfCurrentX + gfWidthOfLine)) / 2;
	float fCreditsCentreOfTopLineY = (gfCurrentY + gfHeightOfLine);
	float fCreditsCentreOfTopLineZ = gfCurrentZ;

	float fCreditsCentreOfMidLineX = (gfCurrentX + (gfCurrentX + gfWidthOfLine)) / 2;
	float fCreditsCentreOfMidLineY = gfCurrentY;
	float fCreditsCentreOfMidLineZ = gfCurrentZ;

	float fCreditsCentreOfBotLineX = (gfCurrentX + (gfCurrentX + gfWidthOfLine)) / 2;
	float fCreditsCentreOfBotLineY = (gfCurrentY - gfHeightOfLine);
	float fCreditsCentreOfBotLineZ = gfCurrentZ;

	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(gfMatrixCharRed, gfMatrixCharGreen, gfMatrixCharBlue);

	/*16th Line  i.e. 2nd TOP to 4th BOTTOM  */
	if (giSevenSgment[16] == 1)
	{
		glVertex3f((gfCurrentX + gfDistanceForD), (gfCurrentY + gfHeightOfLine), gfCurrentZ);	//TOP OF 2ndLINE
		glVertex3f((gfCurrentX + gfDistanceForD), (gfCurrentY - gfHeightOfLine), gfCurrentZ); 	//BOTTOM OF 4th LINE
	}
	/*15th Line  i.e. 2nd TOP to 4th BOTTOM  */
	if (giSevenSgment[15] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);	//TOP OF 2ndLINE
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ); 	//BOTTOM OF 4th LINE
	}
	/*14th Line  i.e. 1st TOP to BOTTOM CENTRE */
	if (giSevenSgment[14] == 1)
	{
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);	//TOP OF 5th LINE
		glVertex3f(fCreditsCentreOfBotLineX, fCreditsCentreOfBotLineY, fCreditsCentreOfBotLineZ);					//CENTRE OF BOTTOM LINE
	}

	/*13th Line  i.e. 1st TOP to BOTTOM CENTRE */
	if (giSevenSgment[13] == 1)
	{
		glVertex3f((gfCurrentX), (gfCurrentY + gfHeightOfLine), (gfCurrentZ));  //TOP OF 1st LINE
		glVertex3f(fCreditsCentreOfBotLineX, fCreditsCentreOfBotLineY, fCreditsCentreOfBotLineZ);					//CENTRE OF BOTTOM LINE
	}

	/*12th Line  i.e. MidCentre to BOTTOM CENTRE */
	if (giSevenSgment[12] == 1)
	{
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					//CENTRE OF MIDDLE LINE
		glVertex3f(fCreditsCentreOfBotLineX, fCreditsCentreOfBotLineY, fCreditsCentreOfBotLineZ);			//CENTRE OF TOP LINE
	}

	/*11th Line  i.e. TOP CENTRE to MidCentre */
	if (giSevenSgment[11] == 1)
	{
		glVertex3f(fCreditsCentreOfTopLineX, fCreditsCentreOfTopLineY, fCreditsCentreOfTopLineZ);			//CENTRE OF TOP LINE
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					//CENTRE OF MIDDLE LINE
	}

	/*10th Line  i.e. MidCentre to 2nd Bottom*/
	if (giSevenSgment[10] == 1)
	{
		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);		// Bottom OF 2nd Line
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					//CENTRE OF MIDDLE LINE
	}

	/*9th Line  i.e. 5th Top to MidCentre*/
	if (giSevenSgment[9] == 1)
	{
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);	//TOP OF 5th LINE
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					//CENTRE OF MIDDLE LINE
	}

	/*8th Line ---> i.e. MidCentre to 4th Bottom*/
	if (giSevenSgment[8] == 1)
	{
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);  //BOTTOM OF LINE 4
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);										//CENTRE OF MIDDLE LINE
	}

	/*7th Line ---> i.e. 1st Top to MidCentre*/
	if (giSevenSgment[7] == 1)
	{
		glVertex3f((gfCurrentX), (gfCurrentY + gfHeightOfLine), (gfCurrentZ));  //TOP OF 1st LINE	
		glVertex3f(fCreditsCentreOfMidLineX, fCreditsCentreOfMidLineY, gfCurrentZ);					  //CENTRE OF MIDDLE LINE
	}

	/*4th LINE*/
	if (giSevenSgment[4] == 1)
	{
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), gfCurrentY, gfCurrentZ);
	}
	/*3rd LINE*/
	if (giSevenSgment[3] == 1)
	{
		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY - gfHeightOfLine), gfCurrentZ);
	}
	/*2nd LINE*/
	if (giSevenSgment[2] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
		glVertex3f(gfCurrentX, (gfCurrentY - gfHeightOfLine), gfCurrentZ);
	}
	/*6th LINE*/
	if (giSevenSgment[6] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY), (gfCurrentZ));
	}
	/*1st LINE*/
	if (giSevenSgment[1] == 1)
	{
		glVertex3f(gfCurrentX, gfCurrentY, gfCurrentZ);
		glVertex3f((gfCurrentX + .00f), (gfCurrentY + gfHeightOfLine), (gfCurrentZ + 0.0f));
	}
	/*0th LINE*/
	if (giSevenSgment[0] == 1)
	{
		glVertex3f(gfCurrentX, (gfCurrentY + gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);
	}

	/*5th LINE*/
	if (giSevenSgment[5] == 1)
	{
		glVertex3f((gfCurrentX + gfWidthOfLine), (gfCurrentY + gfHeightOfLine), gfCurrentZ);
		glVertex3f((gfCurrentX + gfWidthOfLine), gfCurrentY, gfCurrentZ);
	}
	glEnd();
}

void DrawWall() {
	int iCounter = 0;
	int iMidY = giNumberOfCharOnY / 2;
	int iMidX = giNumberOfCharOnX / 2;
	int Astro[] = { 31,24,30,38,36,27,35,41,28,33,36,27,23 };
	int iAstroCounter = 0;

	int iRandomCharacterCount = giNumberOfCharOnX *giNumberOfCharOnY;
	StoreWall();
	for (int j = 0; j < giNumberOfCharOnY; j++)
	{
		for (int i = 0; i < giNumberOfCharOnX; i++)
		{
			if ((j == iMidY) && (i> iMidX - 7 && i < iMidX + 7))
			{
				RandomCharacter(Astro[iAstroCounter]);
				iAstroCounter++;
			}
			else
			{
				RandomCharacter(piRandomWallNumbers[iCounter]);
			}
			iCounter++;
			if (iCounter >= iRandomCharacterCount)
			{
				iCounter = 0;
			}
			//HERE WE DRAW ACTUAL CHARACTER 
			DrawCharacter();

			gfCurrentX = gfCurrentX + gfCommonXDistance;
		}
		gfWidthOfRoom = gfCurrentX;
		gfCurrentX = 0.0f;
		gfCurrentY = gfCurrentY + gfCommonYDistance + 0.1f;
	}
	gfHeightOfRoom = gfCurrentY;
	gfCurrentY = 0.0f;
	return;
}

#pragma Room
void drawRoom() {
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	int size = 40.0f;
	int count = 5;
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	for (float i = -size; i <= size; i += count) { //Floor
		glVertex3f(-size, 0, i);
		glVertex3f(size, 0, i);

		//glVertex3f(-size, 0, -i);
		//glVertex3f(size, 0, -i);
		glVertex3f(i, 0, -size);
		glVertex3f(i, 0, size);
		//glVertex3f(-i, 0, -size);
		//glVertex3f(-i, 0, size);
	}
	
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(175.0f/255, 175.0f/255, 175.0f/255);
	glVertex3f(size, 0.0f, size);
	glVertex3f(-size, 0.0f, size);
	glVertex3f(-size, 0.0f, -size);
	glVertex3f(size, 0.0f, -size);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, -roomDepth.zCor);
	glVertex3f(-roomDepth.xCor, 0.0f, -roomDepth.zCor);
	glVertex3f(roomDepth.xCor - 10.5f, 0.0f, -roomDepth.zCor);
	glVertex3f(roomDepth.xCor - 10.5f, (roomDepth.yCor / 2.0f) - 5.0f, -roomDepth.zCor);
	glVertex3f(roomDepth.xCor, (roomDepth.yCor / 2.0f) - 5.0f, -roomDepth.zCor);
	glVertex3f(roomDepth.xCor, roomDepth.yCor, -roomDepth.zCor);
	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex3f(roomDepth.xCor, roomDepth.yCor, -roomDepth.zCor); //Back
	glVertex3f(roomDepth.xCor - 0.5f, roomDepth.yCor, -roomDepth.zCor);
	glVertex3f(roomDepth.xCor - 0.5f, 0.0f, -roomDepth.zCor);
	glVertex3f(roomDepth.xCor, 0.0f, -roomDepth.zCor);

	/*
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex3f(roomDepth.xCor, roomDepth.yCor, -roomDepth.zCor); //Back
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, -roomDepth.zCor);
	glVertex3f(-roomDepth.xCor, 0.0f, -roomDepth.zCor);
	glVertex3f(roomDepth.xCor, 0.0f, -roomDepth.zCor);

	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-roomDepth.xCor, 0.0f, -roomSize.zCor); //Right
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, -roomSize.zCor);
	glVertex3f(-roomSize.xCor, roomDepth.yCor, roomSize.zCor);
	glVertex3f(-roomSize.xCor, 0.0f, roomSize.zCor);

	*/

	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(roomDepth.xCor, 0.0f, -roomSize.zCor); //Left
	glVertex3f(roomDepth.xCor, roomDepth.yCor, -roomSize.zCor);
	glVertex3f(roomDepth.xCor, roomDepth.yCor, roomSize.zCor);
	glVertex3f(roomDepth.xCor, 0.0f, roomSize.zCor);

	glEnd();

	glPushMatrix();
	glTranslatef(roomDepth.xCor - 0.5f, 0.0f, -roomSize.zCor);
	glScalef(1.0f, 0.75f, 1.0f);
	glPushMatrix();
	glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	if (NeoStage4 == true || NeoStage5 == true) {
		glRotatef(65.0f, 0.0f, 1.0f, 0.0f);
	}
	drawDoor();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10.0f, 21.0f, 0.001f);
	drawDoorFrame();
	glPopMatrix();
	glPopMatrix();

	glBegin(GL_POLYGON);

	glColor3f(0.2f, 0.2f, 0.2f);
	//Right
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, -roomSize.zCor);
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, 0.0f);
	glVertex3f(-roomDepth.xCor, (roomDepth.yCor / 2.0f) - 5.0f, 0.0f);
	glVertex3f(-roomDepth.xCor, (roomDepth.yCor / 2.0f) - 5.0f, -10.0f);
	glVertex3f(-roomDepth.xCor, 0.0f, -10.0f);
	glVertex3f(-roomDepth.xCor, 0.0f, -roomSize.zCor);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-roomDepth.xCor, 0.0f, roomSize.zCor);
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, roomSize.zCor);
	glVertex3f(-roomDepth.xCor, roomDepth.yCor, 0.0f);
	glVertex3f(-roomDepth.xCor, 0.0f, 0.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(-roomDepth.xCor, 0.0f, -10.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 0.75f, 1.0f);
	glPushMatrix();
	glRotatef(gfDoorRotationAngle, 0.0f, 1.0f, 0.0f);
	drawDoor();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10.0f, roomDepth.yCor / 2.0f + 1.0f, 0.01f);
	drawDoorFrame();
	glPopMatrix();

	glPopMatrix();;

	glPopMatrix();
}

#pragma clock 
void drawClock() {
	// function declaration
	void drawClockSquare(void);
	void drawClockTimeNumbers(void);
	void drawClockSecondHand(void);
	void drawClockMinutehand(void);
	void drawClockHourHand(void);
	void drawClockNumbers();

	//Fill this struct for camera movement

	glPushMatrix(); //1
	glTranslatef(watchPosition.x, watchPosition.y, watchPosition.z);
	glScalef(1.5f, 1.5f, 1.0f);
	glPushMatrix(); //2
					//	drawClockNumbers();
	glPopMatrix();
	glPushMatrix(); //3
	drawClockSquare();
	drawClockTimeNumbers();
	glPopMatrix();
	glPushMatrix(); //4
	drawClockSecondHand();
	drawClockMinutehand();
	drawClockHourHand();
	glPopMatrix();
	glPopMatrix();
}
void updateSecondAngle(void) {
	gfSecondAngle = gfSecondAngle - (6.0f * PI / (180.0f));
	gfMinuteAngle = gfMinuteAngle - (6.0f * PI / (180.0f * 60.0f));
	gfHourAngle = gfHourAngle - (6.0f * PI / (180.0f * 60.0f * 12.0f));
}
void drawClockSquare() {

	glBegin(GL_QUADS);
	glColor3f((GLfloat)130.0f / (GLfloat) 255.0f, (GLfloat)82.0f / (GLfloat) 255.0f, (GLfloat)1.0f / (GLfloat) 255.0f);
	glVertex3f(-gfClockOuterLength, gfClockOuterLength, -0.05f);
	glVertex3f(gfClockOuterLength, gfClockOuterLength, -0.05f);
	glVertex3f(gfClockOuterLength, -gfClockOuterLength, -0.05f);
	glVertex3f(-gfClockOuterLength, -gfClockOuterLength, -0.05f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-gfClockLength, gfClockLength, 0.0f);
	glVertex3f(gfClockLength, gfClockLength, 0.0f);
	glVertex3f(gfClockLength, -gfClockLength, 0.0f);
	glVertex3f(-gfClockLength, -gfClockLength, 0.0f);
	glEnd();
	glLineWidth(1.0f);
}
void drawClockTimeNumbers() {
	TCHAR str[255];
	int iNumberCounter = 0;
	void drawNumbers(int);

	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < giCirclePoints; i++) {
		float roomAngle = (GLfloat)(2 * PI * i) / (GLfloat)giCirclePoints;
		if (i % 90 == 0) {
			glLineWidth(3.0f);
			glBegin(GL_LINES);
			glVertex3f(gfClockStepMin * (GLfloat)sin(roomAngle), gfClockStepMin * (GLfloat)cos(roomAngle), 0.0f);
			glVertex3f((gfClockStepMax)* (GLfloat)sin(roomAngle), (gfClockStepMax)* (GLfloat)cos(roomAngle), 0.0f);
			glEnd();
			drawNumbers(iNumberCounter);
			iNumberCounter++;
		}
		else if (i % 60 == 0) {
			glBegin(GL_LINES);
			glVertex3f((gfClockStepMin + 0.3f)  * (GLfloat)sin(roomAngle), (gfClockStepMin + 0.3f) * (GLfloat)cos(roomAngle), 0.0f);
			glVertex3f((gfClockStepMax + 0.3f)* (GLfloat)sin(roomAngle), (gfClockStepMax + 0.3f)* (GLfloat)cos(roomAngle), 0.0f);
			glEnd();
			drawNumbers(iNumberCounter);
			iNumberCounter++;
		}
		else if (i % 30 == 0) {
			glBegin(GL_LINES);
			glVertex3f((gfClockStepMin + 0.3f)  * (GLfloat)sin(roomAngle), (gfClockStepMin + 0.3f) * (GLfloat)cos(roomAngle), 0.0f);
			glVertex3f((gfClockStepMax + 0.3f)* (GLfloat)sin(roomAngle), (gfClockStepMax + 0.3f)* (GLfloat)cos(roomAngle), 0.0f);
			glEnd();
			drawNumbers(iNumberCounter);
			iNumberCounter++;

		}

	}
	glEnd();
}
void drawClockSecondHand(void) {

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gfClockSecondHandRadious * (GLfloat)cos(gfSecondAngle), gfClockSecondHandRadious * (GLfloat)sin(gfSecondAngle), 0.0f);
	glEnd();
}
void drawClockMinutehand(void) {
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gfClockMinuteHandRadious * (GLfloat)cos(gfMinuteAngle), gfClockMinuteHandRadious * (GLfloat)sin(gfMinuteAngle), 0.0f);
	glEnd();
}
void drawClockHourHand(void) {
	glLineWidth(4.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gfClockHourHandRadious  * (GLfloat)cos(gfHourAngle), gfClockHourHandRadious  * (GLfloat)sin(gfHourAngle), 0.0f);
	glEnd();
}
void drawClockNumbers() {
	int counter = 0;
	void drawNumbers(int);
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < giCirclePoints; i++) {
		float roomAngle = 2 * PI * i / giCirclePoints;
		if (i % 30 == 0) {
			glPushMatrix();
			glTranslatef((gfClockStepMin)  * (GLfloat)sin(roomAngle), (gfClockStepMin) * (GLfloat)cos(roomAngle), 1.0f);
			drawNumbers(counter);
			glPopMatrix();
			counter++;
		}
	}
	glPopMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);

}
void drawNumbers(int iClockNumberKeys) {

	switch (iClockNumberKeys)
	{
	case 0:

		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberTwelveDistanceFromOriginX, -gfNumberOneLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, 0.0f + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfTwoDigitDistance + gfNumberTwelveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwelveDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 1:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberOneDistanceFromOriginX, 0.0f + gfNumberOneDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberOneDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberOneDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberOneDistanceFromOriginX, 0.0f + gfNumberOneDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberOneDistanceFromOriginX, -gfNumberOneLengthY + gfNumberOneDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 2:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, 0.0f + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, 0.0f + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, 0.0f + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMinLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTwoDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberTwoDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTwoDistanceFromOriginY, 0.0f);
		glEnd();

		break;
	case 3:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberThreeDistanceFromOriginX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, 0.0f, 0.0f);

		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, 0.0f, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(0.0f + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);

		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMinLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMaxLengthY, 0.0f);

		glVertex3f(0.0f + gfNumberThreeDistanceFromOriginX, -gfNumberMaxLengthY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberThreeDistanceFromOriginX, -gfNumberMaxLengthY, 0.0f);
		glEnd();
		break;
	case 4:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberFourDistanceFromOriginX, 0.0f + gfNumberFourDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberFourDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFourDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberFourDistanceFromOriginX, 0.0f + gfNumberFourDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFourDistanceFromOriginX, -0.2f + gfNumberFourDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberFourDistanceFromOriginX, -0.2f + gfNumberFourDistanceFromOriginY, 0.0f);
		glVertex3f(0.1f + gfNumberFourDistanceFromOriginX, -0.2f + gfNumberFourDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 5:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, 0.0f + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, 0.0f + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, 0.0f + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMinLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberFiveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberFiveDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberFiveDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 6:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, 0.0f + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, 0.0f + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, 0.0f + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberSixDistanceFromOriginX, -gfNumberMinLengthY + gfNumberSixDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 7:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberSevenDistanceFromOriginX, 0.0f + gfNumberSevenDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberSevenDistanceFromOriginX, 0.0f + gfNumberSevenDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberMinLengthX + gfNumberSevenDistanceFromOriginX, 0.0f + gfNumberSevenDistanceFromOriginY, 0.0f);
		glVertex3f(gfNumberSevenLengthX + gfNumberSevenDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberSevenDistanceFromOriginY, 0.0f);
		glEnd();
		break;
	case 8:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, 0.0f + gfNumberEightDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberEigthDistanceFromOriginX, -gfNumberMinLengthY + gfNumberEightDistanceFromOriginY, 0.0f);

		glEnd();
		//glPopMatrix();
		break;
	case 9:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberNineDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, 0.0f + gfNumberNineDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberNineDistanceFromOriginX, -gfNumberMinLengthY + gfNumberNineDistanceFromOriginY, 0.0f);

		glEnd();
		break;
	case 10:
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX, 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX, 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberTenDistanceFromOriginX, -gfNumberOneLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);

		glVertex3f(-gfNumberMinLengthX + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);

		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), -gfNumberMaxLengthY + gfNumberTenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberTenDistanceFromOriginX + (gfTwoDigitDistance * 2), 0.0f + gfNumberTenDistanceFromOriginY, 0.0f);
		glEnd();

		break;
	case 11:
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX, -gfNumberMaxLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberElevenDistanceFromOriginX, -gfNumberOneLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, -gfNumberMaxLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(0.0f + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, 0.0f + gfNumberElevenDistanceFromOriginY, 0.0f);
		glVertex3f(-gfNumberOneLengthX + gfNumberElevenDistanceFromOriginX + gfTwoDigitDistance, -gfNumberOneLengthY + gfNumberElevenDistanceFromOriginY, 0.0f);
		glEnd();

		glPopMatrix();

		break;
	default:
		break;
	}
}