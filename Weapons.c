#include "Weapons.h"

#include "PlayerManager.h"
#include "InputManager.h"
#include "EntitiesManager.h"

int weaponCoolDown;
int isClump;

#define PISTOL_DAMAGE 15
#define PISTOL_CD 30

void OnSelectedPistol()
{
	if (IsFiring() && (!isClump))
	{
		if (weaponCoolDown == 0)
		{
			int entityNumber = GetEntityOnPlayerView();
			if (entityNumber != -1)
			{
				DamageEntity(entityNumber, PISTOL_DAMAGE);
			}
			weaponCoolDown = PISTOL_CD;
			isClump = 1;
		}
	}
	if (weaponCoolDown > 0)
	{
		weaponCoolDown--;
		if (weaponCoolDown > PISTOL_CD - 20)
		{
			SetArmTexture(1);
		}
		else
		{
			SetArmTexture(0);
		}
	}
	else
	{
		if (!IsFiring())
		{
			isClump = 0;
		}
		SetArmTexture(0);
	}
}

#define SHOTGUN_DAMAGE 200
#define SHOTGUN_CD 100

void OnSelectedShotgun()
{
	if (IsFiring() && (!isClump))
	{
		if (weaponCoolDown == 0)
		{
			int entityNumber = GetEntityOnPlayerView();
			if (entityNumber != -1)
			{
				double distance = EntityDistanceToPlayer(entityNumber);
				if (distance < 4)
				{
					int damage = (int)(SHOTGUN_DAMAGE / (1.0 + distance * distance));
					DamageEntity(entityNumber, damage);
				}
			}
			weaponCoolDown = SHOTGUN_CD;
			isClump = 1;
		}
	}
	if (weaponCoolDown > 0)
	{
		weaponCoolDown--;
		if (weaponCoolDown > SHOTGUN_CD - 70)
		{
			if (weaponCoolDown > SHOTGUN_CD - 45)
			{
				if (weaponCoolDown > SHOTGUN_CD - 20)
				{
					SetArmTexture(3);
				}
				else
				{
					SetArmTexture(4);
				}
			}
			else
			{
				SetArmTexture(5);
			}
		}
		else
		{
			SetArmTexture(2);
		}
	}
	else
	{
		if (!IsFiring())
		{
			isClump = 0;
		}
		SetArmTexture(2);
	}
}

void OnRechoise(int weapon)
{
	switch (weapon)
	{
		case WEAPON_PISTOL:
			weaponCoolDown = 10;
			break;

		case WEAPON_SHOTGUN:
			weaponCoolDown = 20;
			break;
	}
}

void InitWeapons()
{
	weaponCoolDown = 0;
	isClump = 0;
}
