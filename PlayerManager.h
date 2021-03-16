#pragma once

#include "Declarations.h"

void InitPlayerManager();

PointD GetPlayerCords();
double GetPlayerCameraAngle();

void SetPlayerCords(const PointD cords);
void SetPlayerCameraAngle(const double angle);

int GetPlayerHealth();
int GetPlayerMaxHealth();

void HealPlayer(int healthCount);
void DamagePlayer(int damageCount);

int GetPlayerArmor();
int GetPlayerMaxArmor();
void GivePlayerArmor(int armorCount);

int GetPlayerStamina();
int GetPlayerMaxStamina();

void SetArmTexture(int armTexture);
int GetPlayerArmTexture();

int GetSelectedWeapon();
int TrySelectWeapon(int weapon);
void UnlockPlayerWeapon(int weapon);

void SetPlayerPosition(double x, double y, double angle);

