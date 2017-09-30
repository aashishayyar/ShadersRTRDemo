#pragma once

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <stdio.h>

extern bool CameraSteady;

extern void DrawLegoCharacters();

void UpdateLegoCharacterAnimation(int *, int);
void DrawCreditsName(int);
void ShowLegoCharacterAnimation(int currentLegoCharacter);

extern int Sonny[];// = { 24,36,37,37,29,'\0' };
extern int Vito[]; // = { 39,28,30,36,'\0' };
extern int Sonny[]; // = { 24,36,37,37,29,'\0' };
extern int Michael[]; // = { 27,28,33,34,31,35,32,'\0' };
extern int Luc[]; // = { 32,40,33,'\0' };
extern int Neo[]; // = { 37,35,36 ,'\0' };
extern float drap;


void MainRoom(void);
void DrawNeo(void);
void updateNeoHandUp();
void updateNeoHandDown();
void drawLogo(void);
void moveNeo(void);