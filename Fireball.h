#pragma once

typedef struct _FireballSpecialData
{
	double angle;
} FireballSpecialData;

void* FireballSpecialDataInit();

void FireballOnAction(int entityNum);

void FireballOnGettingDamage(int entityNum, int damage);