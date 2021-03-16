#pragma once

typedef struct _GameMap
{
	int wight;
	int hight;
	unsigned char *byteField;
} GameMap;

typedef struct _ColisionData
{
	double distance;
	double offset;
	unsigned char wallType;
} ColisionData;

void SetGameMap(long wight, long hight, unsigned char* byteField);
ColisionData GetDistanceBeforeWall(double x, double y, double angle);

void SetSkyColor(long color);
long GetSkyColor();

void SetGroundColor(long color);
long GetGroundColor();