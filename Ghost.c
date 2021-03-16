#include "Ghost.h"

#include <math.h>

#include "EntitiesManager.h"
#include "PlayerManager.h"
#include "MapManager.h"

#define VIEW_DISTANCE 3
#define MAX_HEALTH 100
#define ATTACK_RANGE 0.6
#define GHOST_DAMAGE 25
#define COOL_DOWN 180
#define GHOST_SPEED 0.025

void* GhostSpecialDataInit()
{
	GhostSpecialData* sd = (GhostSpecialData*)malloc(sizeof(GhostSpecialData));
	sd->health = MAX_HEALTH;
	sd->coolDown = 0;
	return sd;
}

void GhostOnAction(int entityNum)
{
	GhostSpecialData* sd = (GhostSpecialData*)GetEntitySpecialData(entityNum);
	double distanceToPlayer = EntityDistanceToPlayer(entityNum);

	if ((sd->coolDown == 0) && (distanceToPlayer < ATTACK_RANGE))
	{
		DamagePlayer(GHOST_DAMAGE);
		sd->coolDown = COOL_DOWN;
	}
	if (((distanceToPlayer < VIEW_DISTANCE) || (sd->health < MAX_HEALTH)) && (distanceToPlayer > 0.4))
	{
		double angleEntityToPlayer = GetEntityToPlayerAngle(entityNum);
		PointD entityCords = GetEntityCords(entityNum);
		if (GetDistanceBeforeWall(entityCords.x, entityCords.y, angleEntityToPlayer).distance > distanceToPlayer)
		{
			entityCords.x += cos(angleEntityToPlayer) * GHOST_SPEED;
			entityCords.y += sin(angleEntityToPlayer) * GHOST_SPEED;
			SetEntityCords(entityNum, entityCords);
		}
	}
	if (sd->coolDown > 0)
	{
		sd->coolDown--;
		if (sd->coolDown > 150)
		{
			SetEntityTexture(entityNum, 4);
		}
		else
		{
			SetEntityTexture(entityNum, 3);
		}
	}
	else
	{
		SetEntityTexture(entityNum, 3);
	}
}

void GhostOnGettingDamage(int entityNum, int damage)
{
	GhostSpecialData* sd = (GhostSpecialData*)GetEntitySpecialData(entityNum);
	if (damage >= sd->health)
	{
		DeleteEntity(entityNum);
	}
	else
	{
		sd->health -= damage;
	}
}

