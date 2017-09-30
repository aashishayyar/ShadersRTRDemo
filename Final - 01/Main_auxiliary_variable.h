#include "Main.h"

bool Scene1 = true;
bool Scene2 = false;
bool Scene3 = false;

void dodgeBullet(void);
void DrawMultipleBulletFireEffect();
void updateMultipleBulletFire(void);
void legoCharaters();


LPCWSTR sound[] = { TEXT("./BangBang.wav"), TEXT("./Clock_2.wav"), TEXT("./RunFayRun.wav"),TEXT("./TheMatrix.wav"), TEXT("./MultipleGunFire.wav"),TEXT("./Ending.wav"), TEXT("./BulletFalling.wav")};