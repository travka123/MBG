#include "PlayerManager.h"

typedef struct _Player
{
	PointD playerCords;
	double cameraAngle;

	int health;
	int maxHealth;

	int armor;
	int maxArmor;

	int stamina;
	int maxStamina;

	int armTexture;
	int selectedWeapon;

	unsigned long UnlockedWeapons;
} Player;

Player player;

void InitPlayerManager()
{
	player.playerCords.x = 1.5;
	player.playerCords.y = 1.5;
	player.cameraAngle = 0;

	player.maxArmor = 100;
	player.maxHealth = 100;
	player.maxStamina = 100;

	player.armor = 0;
	player.health = 50;
	player.stamina = 100;

	player.selectedWeapon = -1;
	player.armTexture = -1;

	player.UnlockedWeapons = 0;
}

PointD GetPlayerCords()
{
	return player.playerCords;
}

double GetPlayerCameraAngle()
{
	return player.cameraAngle;
}

void SetPlayerCords(const PointD cords)
{
	player.playerCords = cords;
}

void SetPlayerCameraAngle(const double angle)
{
	player.cameraAngle = angle;
}

int GetPlayerHealth()
{
	return player.health;
}

int GetPlayerMaxHealth()
{
	return player.maxHealth;
}

int GetPlayerArmor()
{
	return player.armor;
}

int GetPlayerMaxArmor()
{
	return player.maxArmor;
}

void GivePlayerArmor(int armorCount)
{
	player.armor += armorCount;
	player.armor = (player.armor <= player.maxArmor) ? (player.armor) : (player.maxArmor);
}

int GetPlayerStamina()
{
	return player.stamina;
}

int GetPlayerMaxStamina()
{
	return player.maxStamina;
}

void SetArmTexture(int armTexture)
{
	player.armTexture = armTexture;
}

int GetPlayerArmTexture()
{
	return player.armTexture;
}

int GetSelectedWeapon()
{
	return player.selectedWeapon;
}

int TrySelectWeapon(int weapon)
{
	if (player.UnlockedWeapons & weapon)
	{
		player.selectedWeapon = weapon;
		return 1;
	}
	return 0;
}

void UnlockPlayerWeapon(int weapon)
{
	int wasUnlocked = player.UnlockedWeapons & weapon;
	player.UnlockedWeapons = player.UnlockedWeapons | weapon;
	if (!wasUnlocked)
	{
		player.selectedWeapon = weapon;
	}
}

void SetPlayerPosition(double x, double y, double angle)
{
	player.playerCords.x = x;
	player.playerCords.y = y;
	player.cameraAngle = angle;
}

void HealPlayer(int healthCount)
{
	player.health += healthCount;
	player.health = (player.health <= player.maxHealth) ? (player.health) : (player.maxHealth);
}

void DamagePlayer(int damageCount)
{
	if (player.armor >= damageCount)
	{
		player.armor -= damageCount;
	}
	else
	{
		damageCount -= player.armor;
		player.armor = 0;
		if (player.health > damageCount)
		{
			player.health -= damageCount;
		}
		else
		{
			player.health = 0;
		}
	}
}
