#include "GameLogic.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

#include "InputManager.h"
#include "PlayerManager.h"
#include "EntitiesManager.h"
#include "MapManager.h"
#include "Constants.h"
#include "Weapons.h"

int lvl;
unsigned short isLvlChangeRequestResived;

void ProcessPlayerMoves()
{
	double xChange = 0;
	double yChange = 0;
	PointD playerCords = GetPlayerCords();
	double playerCameraAngle = GetPlayerCameraAngle();

	double playerCameraAngleSin = sin(playerCameraAngle);
	double playerCameraAngleCos = cos(playerCameraAngle);

	if (IsMoveForwardButtonPresed() != IsMoveBackButtonPresed())
	{
		if (IsMoveForwardButtonPresed())
		{
			xChange += PLAYER_MOVING_SPEED * playerCameraAngleCos;
			yChange += PLAYER_MOVING_SPEED * playerCameraAngleSin;
		}
		else
		{
			xChange -= PLAYER_MOVING_SPEED * playerCameraAngleCos;
			yChange -= PLAYER_MOVING_SPEED * playerCameraAngleSin;
		}
	}

	if (IsMoveLeftButtonPresed() != IsMoveRightButtonPresed())
	{
		if (IsMoveLeftButtonPresed())
		{
			xChange += PLAYER_MOVING_SPEED * playerCameraAngleSin;
			yChange -= PLAYER_MOVING_SPEED * playerCameraAngleCos;
		}
		else
		{
			xChange -= PLAYER_MOVING_SPEED * playerCameraAngleSin;
			yChange += PLAYER_MOVING_SPEED * playerCameraAngleCos;
		}
	}

	ColisionData colData = GetDistanceBeforeWall(playerCords.x, playerCords.y, xChange > 0 ? 0 : M_PI);
	if (colData.distance > STOP_IN_FRONT_OF_WALL_DISTANCE)
	{
		playerCords.x += xChange;
	}
	colData = GetDistanceBeforeWall(playerCords.x, playerCords.y, yChange > 0 ? M_PI_2 : -M_PI_2);
	if (colData.distance > STOP_IN_FRONT_OF_WALL_DISTANCE)
	{
		playerCords.y += yChange;
	}
	SetPlayerCords(playerCords);
}

void ProcessCameraRotation()
{
	double angle = GetPlayerCameraAngle() + GetCameraXOffset() * CAMERA_ROTATION_SPEED;
	while (angle > M_PI * 2)
	{
		angle -= M_PI * 2;
	}
	while (angle < 0)
	{
		angle += M_PI * 2;
	}
	SetPlayerCameraAngle(angle);
	ClearCameraXOffset();
}

void GetLvlConstructFilePath(char *buffer, int bufflen)
{
	sprintf_s(buffer, bufflen, "Levels\\lvl_%d.MBGLC", lvl + 1);

	FILE* f;
	fopen_s(&f, buffer, "r");
	if (f == NULL)
	{
		sprintf_s(buffer, bufflen, "Levels\\WinLevel.MBGLC");
	}
	else
	{
		fclose(f);
	}
}

void SetLevel(char *lvlConstructFilePath)
{
	FILE* constructionFile = NULL;
	int err = fopen_s(&constructionFile, lvlConstructFilePath, "r");
	if (constructionFile)
	{
		long skyColor;
		long groundColor;
		fscanf_s(constructionFile, "%x %x", &skyColor, &groundColor);
		SetSkyColor(skyColor);
		SetGroundColor(groundColor);

		long mapWight;
		long mapHight;
		fscanf_s(constructionFile, "%d %d", &mapWight, &mapHight);

		unsigned char* byteMap = malloc(mapWight * mapHight);
		if (byteMap)
		{
			for (int i = 0; i < mapWight * mapHight; i++)
			{
				int temp;
				fscanf_s(constructionFile, "%d", &temp);
				byteMap[i] = (unsigned char)temp;
			}
		}

		SetGameMap(mapWight, mapHight, byteMap);
		
		double playerX, playerY, playerAngle;
		fscanf_s(constructionFile, "%lf", &playerX);
		fscanf_s(constructionFile, "%lf", &playerY);
		fscanf_s(constructionFile, "%lf", &playerAngle);
		SetPlayerPosition(playerX, playerY, playerAngle);

		DeleteAllEntityes();
		int entityesCount;
		fscanf_s(constructionFile, "%d", &entityesCount);
		for (int i = 0; i < entityesCount; i++)
		{
			double x, y;
			int entityType;
			fscanf_s(constructionFile, "%lf %lf %d", &x, &y, &entityType);
			CreateEntity(x, y, entityType);
		}

		fclose(constructionFile);
	}
}

void GameLogicInit()
{
	lvl = 0;
	isLvlChangeRequestResived = 0;

	char lvlConstructFilePath[80];
	GetLvlConstructFilePath(lvlConstructFilePath, 80);

	if (lvlConstructFilePath != NULL)
	{
		InitInputManager();
		InitWeapons();
		InitEntityes();
		InitPlayerManager();
		SetLevel(lvlConstructFilePath);
	}
	/*
	unsigned char byteImage[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
								 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
								 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
								 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
								 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
								 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
								 1, 0, 2, 0, 1, 0, 0, 0, 0, 1,
								 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
								 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
								 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	
	*/
}

void ProcessPlayerFiring()
{
	switch (GetSelectedWeapon())
	{
		case WEAPON_PISTOL:
			OnSelectedPistol();
			break;

		case WEAPON_SHOTGUN:
			OnSelectedShotgun();
			break;
	}
}

void ProcessPlayerWeaponRechoise()
{
	int choisedWeapon = GetWeaponRechoise();
	if (choisedWeapon != -1)
	{
		int sucsess = TrySelectWeapon(choisedWeapon);
		if (sucsess)
		{
			OnRechoise(choisedWeapon);
		}
		ClearWeaponRechoise();
	}
}

void ProcessPlayerAction()
{
	if (IsActionKeyPresed())
	{
		PointD playerCords = GetPlayerCords();
		double angle = GetPlayerCameraAngle();
		ColisionData colData = GetDistanceBeforeWall(playerCords.x, playerCords.y, angle);
		if ((colData.wallType == 2) || (colData.wallType == 5))
		{
			if (colData.distance < 0.5)
			{
				isLvlChangeRequestResived = 1;
			}
		}
	}
}

void ProcessLevelChange()
{
	if (GetPlayerHealth() == 0)
	{
		SetLevel("Levels\\GameOverLevel.MBGLC");
		isLvlChangeRequestResived = 0;
		HealPlayer(GetPlayerMaxHealth());
	}
	else if (isLvlChangeRequestResived)
	{
		isLvlChangeRequestResived = 0;
		lvl++;

		char lvlConstructFilePath[80];
		GetLvlConstructFilePath(lvlConstructFilePath, 80);
		SetLevel(&lvlConstructFilePath);
	}
}

void ProcessInput()
{	
	ProcessPlayerMoves();
	ProcessCameraRotation();
	ProcessPlayerWeaponRechoise();
	ProcessPlayerFiring();
	ProcessEntities();
	ProcessPlayerAction();
	ProcessLevelChange();
}

