#include "MapManager.h"

#include <math.h>

GameMap gameMap;

long skyColor;
long groundColor;

void SetGameMap(long wight, long hight, unsigned char* byteField)
{
	gameMap.wight = wight;
	gameMap.hight = hight;
	gameMap.byteField = byteField;
}

ColisionData GetDistanceBeforeWall(double x, double y, double angle)
{
	double sinAngle = sin(angle);
	double cosAngle = cos(angle);

	ColisionData DistanceBeforeWallXSearch;
	ColisionData DistanceBeforeWallYSearch;

	DistanceBeforeWallXSearch.distance = 9223372036854775807.0;
	DistanceBeforeWallYSearch.distance = 9223372036854775807.0;
	DistanceBeforeWallXSearch.wallType = 0;
	DistanceBeforeWallYSearch.wallType = 0;
	double temp;

	int incX;
	int incY;

	if ((sinAngle >= 0) && (cosAngle >= 0)) // 1 четверть
	{
		incX = 1;
		incY = 1;
	}
	else if (sinAngle >= 0) // 2 четверть
	{
		incX = -1;
		incY = 1;
	}
	else if (cosAngle >= 0) // 4 четверть
	{
		incX = 1;
		incY = -1;
	}
	else // 3 четверть
	{
		incX = -1;
		incY = -1;
	}

	int mapX;
	int mapY;

	mapX = (int)x;
	mapX = (incX == -1) ? (mapX + 1) : mapX;
	for (int i = 0; i < 30; i++)
	{
		mapX += incX;
		mapY = (int)(y + ((mapX - x) / cosAngle * sinAngle));
		if ((mapX >= 1) && (mapX < gameMap.wight) && (mapY >= 0) && (mapY < gameMap.hight))
		{
			if ((gameMap.byteField[mapY * gameMap.wight + mapX] != 0) || (gameMap.byteField[mapY * gameMap.wight + mapX - 1] != 0))
			{
				DistanceBeforeWallXSearch.distance = fabs((mapX - x) / cosAngle);
				DistanceBeforeWallXSearch.offset = modf(y + ((mapX - x) / cosAngle * sinAngle), &temp);
				DistanceBeforeWallXSearch.wallType = (gameMap.byteField[mapY * gameMap.wight + mapX] != 0) ? (gameMap.byteField[mapY * gameMap.wight + mapX]) : (gameMap.byteField[mapY * gameMap.wight + mapX - 1]);
				break;
			}
		}
		else
		{
			break;
		}
	}

	mapY = (int)y;
	mapY = (incY == -1) ? (mapY + 1) : mapY;
	for (int i = 0; i < 300; i++)
	{
		mapY += incY;
		mapX = (int)(x + ((mapY - y) / sinAngle * cosAngle));
		if ((mapX >= 0) && (mapX < gameMap.wight) && (mapY >= 1) && (mapY < gameMap.hight))
		{
			if ((gameMap.byteField[mapY * gameMap.wight + mapX] != 0) || (gameMap.byteField[mapY * gameMap.wight - gameMap.wight + mapX] != 0))
			{
				DistanceBeforeWallYSearch.distance = fabs((mapY - y) / sinAngle);
				DistanceBeforeWallYSearch.offset = modf(x + ((mapY - y) / sinAngle * cosAngle), &temp);
				DistanceBeforeWallYSearch.wallType = (gameMap.byteField[mapY * gameMap.wight + mapX] != 0) ? gameMap.byteField[mapY * gameMap.wight + mapX] : gameMap.byteField[mapY * gameMap.wight - gameMap.wight + mapX];
				break;
			}
		}
		else
		{
			break;
		}
	}

	if ((DistanceBeforeWallXSearch.distance > 0) && (DistanceBeforeWallYSearch.distance > 0))
	{
		return (DistanceBeforeWallXSearch.distance < DistanceBeforeWallYSearch.distance) ? DistanceBeforeWallXSearch : DistanceBeforeWallYSearch;
	}
	else if (DistanceBeforeWallXSearch.distance > 0)
	{
		return DistanceBeforeWallXSearch;
	}
	return DistanceBeforeWallYSearch;
}

void SetSkyColor(long color)
{
	skyColor = color;
}

long GetSkyColor()
{
	return skyColor;
}

void SetGroundColor(long color)
{
	groundColor = color;
}

long GetGroundColor()
{
	return groundColor;
}
