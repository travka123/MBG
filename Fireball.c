#include "Fireball.h"

#include <math.h>

#include "EntitiesManager.h"
#include "PlayerManager.h"
#include "MapManager.h"

#define FIREBALL_SPEED 0.025
#define DAMAGE_RADIUS 0.4
#define HIT_DAMAGE 30

void* FireballSpecialDataInit()
{
	FireballSpecialData* sd = (FireballSpecialData*)malloc(sizeof(FireballSpecialData));
	sd->angle = 0;
	return sd;
}

void FireballOnAction(int entityNum)
{
	if (EntityDistanceToPlayer(entityNum) < DAMAGE_RADIUS)
	{
		DamagePlayer(HIT_DAMAGE);
		DeleteEntity(entityNum);
	}
	else
	{
		FireballSpecialData* sd = GetEntitySpecialData(entityNum);
		double angle = sd->angle;
		PointD entityCords = GetEntityCords(entityNum);
		if (GetDistanceBeforeWall(entityCords.x, entityCords.y, angle).distance < DAMAGE_RADIUS)
		{
			DeleteEntity(entityNum);
		}
		else
		{
			entityCords.x += FIREBALL_SPEED * cos(angle);
			entityCords.y += FIREBALL_SPEED * sin(angle);
			SetEntityCords(entityNum, entityCords);
		}
	}
}

void FireballOnGettingDamage(int entityNum, int damage)
{
}
