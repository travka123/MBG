#include "MedicKit.h"

#include "EntitiesManager.h"
#include "PlayerManager.h"

void MedicKitOnAction(int entityNum)
{
	if (EntityDistanceToPlayer(entityNum) < 0.2)
	{
		HealPlayer(25);
		DeleteEntity(entityNum);
	}
	
}

void MedicKitOnGettingDamage(int entityNum, int damage)
{
}
