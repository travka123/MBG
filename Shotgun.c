#include "Revolver.h"

#include "EntitiesManager.h"
#include "PlayerManager.h"
#include "Weapons.h"

void ShotgunOnAction(int entityNum)
{
	if (EntityDistanceToPlayer(entityNum) < 0.2)
	{
		UnlockPlayerWeapon(WEAPON_SHOTGUN);
		DeleteEntity(entityNum);
	}
}

void ShotgunOnGettingDamage(int entityNum, int damage)
{

}