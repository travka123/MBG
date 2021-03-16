#include "Wizard.h"

#include <math.h>

#include "EntitiesManager.h"
#include "PlayerManager.h"
#include "MapManager.h"
#include "Fireball.h"

#define VIEW_DISTANCE 3
#define MAX_HEALTH 150
#define ATTACK_RANGE 2.8
#define COOL_DOWN 280
#define WIZARD_SPEED 0.015

void* WizardSpecialDataInit()
{
	WizardSpecialData* sd = (WizardSpecialData*)malloc(sizeof(WizardSpecialData));
	sd->health = MAX_HEALTH;
	sd->coolDown = 0;
	return sd;
}

void WizardOnAction(int entityNum)
{
	WizardSpecialData* sd = (WizardSpecialData*)GetEntitySpecialData(entityNum);
	double distanceToPlayer = EntityDistanceToPlayer(entityNum);

	if ((sd->coolDown == 0) && (distanceToPlayer < ATTACK_RANGE))
	{
		PointD entityCords = GetEntityCords(entityNum);
		int fireballEntityNum = CreateEntity(entityCords.x, entityCords.y, ENTITY_FIREBALL);
		FireballSpecialData* fireballSD = GetEntitySpecialData(fireballEntityNum);
		fireballSD->angle = GetEntityToPlayerAngle(entityNum);
		sd->coolDown = COOL_DOWN;
	}
	if (((distanceToPlayer < VIEW_DISTANCE) || (sd->health < MAX_HEALTH)) && (distanceToPlayer > ATTACK_RANGE - 0.5))
	{
		double angleEntityToPlayer = GetEntityToPlayerAngle(entityNum);
		PointD entityCords = GetEntityCords(entityNum);
		if (GetDistanceBeforeWall(entityCords.x, entityCords.y, angleEntityToPlayer).distance > distanceToPlayer)
		{
			entityCords.x += cos(angleEntityToPlayer) * WIZARD_SPEED;
			entityCords.y += sin(angleEntityToPlayer) * WIZARD_SPEED;
			SetEntityCords(entityNum, entityCords);
		}
	}
	if (sd->coolDown > 0)
	{
		sd->coolDown--;
		if (sd->coolDown > COOL_DOWN - 40)
		{
			SetEntityTexture(entityNum, 7);
		}
		else
		{
			SetEntityTexture(entityNum, 6);
		}
	}
	else
	{
		SetEntityTexture(entityNum, 6);
	}
}

void WizardOnGettingDamage(int entityNum, int damage)
{
	WizardSpecialData* sd = (WizardSpecialData*)GetEntitySpecialData(entityNum);
	if (damage >= sd->health)
	{
		DeleteEntity(entityNum);
	}
	else
	{
		sd->health -= damage;
	}
}

