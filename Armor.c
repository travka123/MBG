#include "Armor.h"

#include "PlayerManager.h"
#include "EntitiesManager.h"

void ArmorOnAction(int entityNum)
{
	if (EntityDistanceToPlayer(entityNum) < 0.2)
	{
		GivePlayerArmor(25);
		DeleteEntity(entityNum);
	}
}

void ArmorOnGettingDamage(int entityNum, int damage)
{
	
}