#pragma once

#include "Declarations.h"

#define ENTITY_MEDICKIT 0
#define ENTITY_ARMOR 1
#define ENTITY_REVOLVER 2
#define ENTITY_GHOST 3
#define ENTITY_SHOTGUN 4
#define ENTITY_WIZARD 5
#define ENTITY_FIREBALL 6

typedef struct _Entity
{
	unsigned char entityType;
	PointD entityCords;
	double radius;
	double hight;
	int entityTexture;
	void (*OnAction)(int arrpos);
	void (*OnDamage)(int arrpos, int damage);
	void* SpecialData;
} Entity;

void InitEntityes();
int GetEntityesCount();
PointD GetEntityCords(int entityNum);
void SetEntityCords(int entityNum, PointD cords);
double GetEntityRadius(int entityNum);
double GetEntityHight(int entityNum);
int GetEntytyTexture(int entityNum);
void ProcessEntities();
double EntityDistanceToPlayer(int entityNum);
void DeleteEntity(int entityNum);
void SortEntityes();
int GetEntityOnPlayerView();
void DamageEntity(int entityNum, int damage);
void* GetEntitySpecialData(int entityNum);
double GetEntityToPlayerAngle(int entityNum);
void SetEntityTexture(int entityNum, int texture);
int CreateEntity(double x, double y, int entityType);
void DeleteAllEntityes();