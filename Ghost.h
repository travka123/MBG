#pragma once

typedef struct _GhostSpecialData
{
	int health;
	int coolDown;
} GhostSpecialData;

void* GhostSpecialDataInit();

void GhostOnAction(int entityNum);

void GhostOnGettingDamage(int entityNum, int damage);