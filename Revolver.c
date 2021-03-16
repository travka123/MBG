#include "Revolver.h"

#include "EntitiesManager.h"
#include "PlayerManager.h"
#include "Weapons.h"

void RevolverOnAction(int entityNum)
{
	if (EntityDistanceToPlayer(entityNum) < 0.2)
	{
		UnlockPlayerWeapon(WEAPON_PISTOL);
		DeleteEntity(entityNum);
	}
}

void RevolverOnGettingDamage(int entityNum, int damage)
{

}