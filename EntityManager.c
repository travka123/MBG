#include "EntitiesManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "PlayerManager.h"
#include "Constants.h"
#include "MapManager.h"

#include "MedicKit.h"
#include "Armor.h"
#include "Revolver.h"
#include "Ghost.h"
#include "Shotgun.h"
#include "Wizard.h"
#include "Fireball.h"

int entityCount;

int sizeOfArr;
Entity* entityArray;

int CreateEntity(double x, double y, int entityType)
{
	int entityNumber = entityCount;
	entityCount++;
	if (entityCount > sizeOfArr)
	{
		sizeOfArr += sizeOfArr + 1;
		entityArray = (Entity*)realloc(entityArray, sizeof(Entity) * sizeOfArr);
	}


	entityArray[entityNumber].entityCords.x = x;
	entityArray[entityNumber].entityCords.y = y;
	entityArray[entityNumber].entityType = entityType;

	switch (entityType)
	{
	case ENTITY_MEDICKIT:
		entityArray[entityNumber].entityTexture = 0;
		entityArray[entityNumber].hight = 0.6;
		entityArray[entityNumber].radius = 0.2;
		entityArray[entityNumber].OnAction = MedicKitOnAction;
		entityArray[entityNumber].OnDamage = MedicKitOnGettingDamage;
		entityArray[entityNumber].SpecialData = (void*)malloc(sizeof(1));
		break;

	case ENTITY_ARMOR:
		entityArray[entityNumber].entityTexture = 1;
		entityArray[entityNumber].hight = 0.6;
		entityArray[entityNumber].radius = 0.2;
		entityArray[entityNumber].OnAction = ArmorOnAction;
		entityArray[entityNumber].OnDamage = ArmorOnGettingDamage;
		entityArray[entityNumber].SpecialData = (void*)malloc(sizeof(1));
		break;

	case ENTITY_REVOLVER:
		entityArray[entityNumber].entityTexture = 2;
		entityArray[entityNumber].hight = 0.3;
		entityArray[entityNumber].radius = 0.1;
		entityArray[entityNumber].OnAction = RevolverOnAction;
		entityArray[entityNumber].OnDamage = RevolverOnGettingDamage;
		entityArray[entityNumber].SpecialData = (void*)malloc(sizeof(1));
		break;

	case ENTITY_GHOST:
		entityArray[entityNumber].entityTexture = 3;
		entityArray[entityNumber].hight = 0.45;
		entityArray[entityNumber].radius = 0.15;
		entityArray[entityNumber].OnAction = GhostOnAction;
		entityArray[entityNumber].OnDamage = GhostOnGettingDamage;
		entityArray[entityNumber].SpecialData = (void*)GhostSpecialDataInit();
		break;

	case ENTITY_SHOTGUN:
		entityArray[entityNumber].entityTexture = 5;
		entityArray[entityNumber].hight = 0.8;
		entityArray[entityNumber].radius = 0.5;
		entityArray[entityNumber].OnAction = ShotgunOnAction;
		entityArray[entityNumber].OnDamage = ShotgunOnGettingDamage;
		entityArray[entityNumber].SpecialData = (void*)malloc(sizeof(1));
		break;

	case ENTITY_WIZARD:
		entityArray[entityNumber].entityTexture = 6;
		entityArray[entityNumber].hight = 0.45;
		entityArray[entityNumber].radius = 0.15;
		entityArray[entityNumber].OnAction = WizardOnAction;
		entityArray[entityNumber].OnDamage = WizardOnGettingDamage;
		entityArray[entityNumber].SpecialData = (void*)WizardSpecialDataInit();
		break;

	case ENTITY_FIREBALL:
		entityArray[entityNumber].entityTexture = 8;
		entityArray[entityNumber].hight = 0.2;
		entityArray[entityNumber].radius = 0.2;
		entityArray[entityNumber].OnAction = FireballOnAction;
		entityArray[entityNumber].OnDamage = FireballOnGettingDamage;
		entityArray[entityNumber].SpecialData = (void*)FireballSpecialDataInit();
		break;
	}

	return entityNumber;
}

void DeleteAllEntityes()
{
	for (int i = entityCount - 1; i >= 0; i--)
	{
		DeleteEntity(i);
	}
}

void InitEntityes()
{
	sizeOfArr = 10;
	entityArray = (Entity*)malloc(sizeof(Entity) * sizeOfArr);
	entityCount = 0;
}

int GetEntityesCount()
{
	return entityCount;
}

PointD GetEntityCords(int entityNum)
{
	return (entityArray + entityNum)->entityCords;
}

void SetEntityCords(int entityNum, PointD cords)
{
	entityArray[entityNum].entityCords = cords;
}

double GetEntityRadius(int entityNum)
{
	return (entityArray + entityNum)->radius;
}

double GetEntityHight(int entityNum)
{
	return (entityArray + entityNum)->hight;
}

int GetEntytyTexture(int entityNum)
{
	return (entityArray + entityNum)->entityTexture;
}

void ProcessEntities()
{
	for (int i = entityCount - 1; i >= 0; i--)
	{
		entityArray[i].OnAction(i);
	}
}

double EntityDistanceToPlayer(int entityNum)
{
	PointD playerCords = GetPlayerCords();
	PointD entityCords = GetEntityCords(entityNum);
	double kat1 = playerCords.x - entityCords.x;
	double kat2 = playerCords.y - entityCords.y;
	return sqrt(kat1 * kat1 + kat2 * kat2);
}

void DeleteEntity(int entityNum)
{
	entityCount--;
	free(entityArray[entityNum].SpecialData);
	for (int i = entityNum; i < entityCount; i++)
	{
		entityArray[i] = entityArray[i + 1];
	}
}

int GetEntityOnPlayerView()
{
	SortEntityes();

	double playerAngle = GetPlayerCameraAngle();
	PointD playerCords = GetPlayerCords();

	for (int j = entityCount - 1; j >= 0; j--)
	{
		double distanceToPlayer = EntityDistanceToPlayer(j);
		if (GetDistanceBeforeWall(playerCords.x, playerCords.y, playerAngle).distance > distanceToPlayer)
		{
			PointD eCords = GetEntityCords(j);
			PointD RECords;
			RECords.x = eCords.x - playerCords.x;
			RECords.y = eCords.y - playerCords.y;
			double entityAngle = atan(RECords.y / RECords.x);
			if ((RECords.x < 0) && (RECords.y < 0))
			{
				entityAngle += M_PI;
			}
			else if ((RECords.x < 0))
			{
				entityAngle += M_PI;
			}
			else if (entityAngle < 0)
			{
				entityAngle += M_PI * 2;
			}

			if (playerAngle < 0)
			{
				playerAngle += M_PI * 2;
			}
			double angleDif = fabs(entityAngle - playerAngle);
			int wasNormalized = 0;
			if (angleDif > M_PI + M_PI_2)
			{
				angleDif -= M_PI * 2;
				wasNormalized = 1;
			}
			if (fabs(angleDif) < M_PI_2)
			{
				double offset = distanceToPlayer * tan(fabs(angleDif));
				if (offset < GetEntityRadius(j))
				{
					return j;
				}
			}
		}
	}
	return -1;
}

void DamageEntity(int entityNum, int damage)
{
	entityArray[entityNum].OnDamage(entityNum, damage);
}

void* GetEntitySpecialData(int entityNum)
{
	return entityArray[entityNum].SpecialData;
}

double GetEntityToPlayerAngle(int entityNum)
{
	PointD entityCord = entityArray[entityNum].entityCords;
	PointD playerCord = GetPlayerCords();

	PointD vectorEntityPlayer;
	vectorEntityPlayer.x = playerCord.x - entityCord.x;
	vectorEntityPlayer.y = playerCord.y - entityCord.y;

	double angle = atan(vectorEntityPlayer.y / vectorEntityPlayer.x);
	if (vectorEntityPlayer.x < 0)
	{
		angle += M_PI;
	}
	return angle;
}

void SetEntityTexture(int entityNum, int texture)
{
	entityArray[entityNum].entityTexture = texture;
}

void SortEntityes()
{
	double* DistanceBetwenPlayerAndEntityes = (double*)malloc(sizeof(double) * entityCount);
	if (DistanceBetwenPlayerAndEntityes)
	{
		for (int i = 0; i < entityCount; i++)
		{
			DistanceBetwenPlayerAndEntityes[i] = EntityDistanceToPlayer(i);
		}

		for (int i = 0; i < entityCount - 1; i++)
		{
			if (DistanceBetwenPlayerAndEntityes[i] < DistanceBetwenPlayerAndEntityes[i + 1])
			{
				int rightPlacePos = 0;
				while (DistanceBetwenPlayerAndEntityes[i + 1] < DistanceBetwenPlayerAndEntityes[rightPlacePos])
				{
					rightPlacePos++;
				}
				Entity tempEntity = entityArray[i + 1];
				double tempDist = DistanceBetwenPlayerAndEntityes[i + 1];
				for (int j = i; j >= rightPlacePos; j--)
				{
					entityArray[j + 1] = entityArray[j];
					DistanceBetwenPlayerAndEntityes[j + 1] = DistanceBetwenPlayerAndEntityes[j];
				}
				entityArray[rightPlacePos] = tempEntity;
				DistanceBetwenPlayerAndEntityes[rightPlacePos] = tempDist;
			}
		}
	}
	free(DistanceBetwenPlayerAndEntityes);
}
