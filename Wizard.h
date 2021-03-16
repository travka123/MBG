#pragma once

#pragma once

typedef struct _WizardSpecialData
{
	int health;
	int coolDown;
} WizardSpecialData;

void* WizardSpecialDataInit();

void WizardOnAction(int entityNum);

void WizardOnGettingDamage(int entityNum, int damage);