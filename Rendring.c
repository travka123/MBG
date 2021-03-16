#include "Rendring.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

#include "resource.h"
#include "Resolution.h"
#include "PlayerManager.h"
#include "EntitiesManager.h"
#include "MapManager.h"
#include "Constants.h"
#include "EntitiesManager.h"

#define ENTITY_TEXTURES_COUNT 9
#define WALL_TEXTURES_COUNT 8
#define ARM_TEXTURES_COUNT 6

BITMAP* bitmapWallTextures;
BITMAP* bitmapEntityTextures;
BITMAP* bitmapArmTextures;

void SetBMPRes(HINSTANCE hInstance, const unsigned char position, const int resurce, BITMAP* bitmapTextures)
{
	HBITMAP hBmp = LoadBitmap(hInstance, MAKEINTRESOURCE(resurce));
	BITMAP* curBitmap = bitmapTextures + position;
	GetObject(hBmp, sizeof(BITMAP), curBitmap);
	if (curBitmap->bmBits == NULL)
	{
		int bmpSize = curBitmap->bmHeight * curBitmap->bmWidth * curBitmap->bmBitsPixel / 8;
		DWORD* lpPixels = (DWORD*)malloc(bmpSize);
		if (lpPixels)
		{
			GetBitmapBits(hBmp, bmpSize, lpPixels);
			curBitmap->bmBits = lpPixels;
		}
	}
}

void RendringInit(HINSTANCE hInstance)
{

	bitmapWallTextures = (BITMAP*)malloc(sizeof(BITMAP) * WALL_TEXTURES_COUNT);
	bitmapEntityTextures = (BITMAP*)malloc(sizeof(BITMAP) * ENTITY_TEXTURES_COUNT);
	bitmapArmTextures = (BITMAP*)malloc(sizeof(BITMAP) * ARM_TEXTURES_COUNT);

	if (bitmapWallTextures)
	{
		SetBMPRes(hInstance, 0, IDB_BRICKWALL, bitmapWallTextures);
		SetBMPRes(hInstance, 1, IDB_BRICKWALL_EXITDOOR, bitmapWallTextures);
		SetBMPRes(hInstance, 2, IDB_BRICKWALL_EXITDOOR_CLOSED, bitmapWallTextures);
		SetBMPRes(hInstance, 3, IDB_BASHWALL, bitmapWallTextures);
		SetBMPRes(hInstance, 4, IDB_BASHWALL_EXITDOOR, bitmapWallTextures);
		SetBMPRes(hInstance, 5, IDB_BASHWALL_EXITDOOR, bitmapWallTextures);
		SetBMPRes(hInstance, 6, IDB_WIN_WALL, bitmapWallTextures);
		SetBMPRes(hInstance, 7, IDB_GAMEOVER_WALL, bitmapWallTextures);
	}

	if (bitmapEntityTextures)
	{
		SetBMPRes(hInstance, 0, IDB_MEDKIT, bitmapEntityTextures);
		SetBMPRes(hInstance, 1, IDB_ARMOR, bitmapEntityTextures);
		SetBMPRes(hInstance, 2, IDB_REV_ENTITY, bitmapEntityTextures);
		SetBMPRes(hInstance, 3, IDB_GHOST, bitmapEntityTextures);
		SetBMPRes(hInstance, 4, IDB_GHOST_ATTACK, bitmapEntityTextures);
		SetBMPRes(hInstance, 5, IDB_SHOTGUN_ENTITY, bitmapEntityTextures);
		SetBMPRes(hInstance, 6, IDB_WIZARD, bitmapEntityTextures);
		SetBMPRes(hInstance, 7, IDB_WIZARD_ATTACK, bitmapEntityTextures);
		SetBMPRes(hInstance, 8, IDB_FIREBALL, bitmapEntityTextures);
	}

	if (bitmapArmTextures)
	{
		SetBMPRes(hInstance, 0, IDB_REV_STATIC, bitmapArmTextures);
		SetBMPRes(hInstance, 1, IDB_REV_FIRE, bitmapArmTextures);
		SetBMPRes(hInstance, 2, IDB_SHOTGUN_STATIC, bitmapArmTextures);
		SetBMPRes(hInstance, 3, IDB_SHOTGUN_FIRE, bitmapArmTextures);
		SetBMPRes(hInstance, 4, IDB_SHOTGUN_GILZAOUT, bitmapArmTextures);
		SetBMPRes(hInstance, 5, IDB_SHOTGUN_GILZAIN, bitmapArmTextures);
	}
}

void RenderSolidColumn(DWORD* lpPixels, int columnNumber, const ColisionData colData, double dcos)
{
	int resY = GetResY();
	int wallHight = (int)(GetResY() / colData.distance / dcos);
	wallHight = wallHight > resY ? resY : wallHight;
	int rowNumber = (int)((resY - wallHight) / 2);

	for (int i = 0; i < wallHight; i++)
	{
		lpPixels[columnNumber + rowNumber * GetResX()] = 0x00000000;
		rowNumber++;
	}
}

void RenderWallColumn(DWORD* lpDestPixels, const int columnNumber, const double hight, const unsigned char wallType, const double offset)
{
	int resX = GetResX();
	int ResY = GetResY();

	BITMAP* PBitmap = bitmapWallTextures + wallType;
	int bitmapColumn = (int)(PBitmap->bmWidth * offset);

	int rowDrawCount = (int)hight;
	int destStartRow;
	double sourceStartRow;

	if (rowDrawCount > ResY)
	{
		rowDrawCount = ResY;
		destStartRow = 0;
		sourceStartRow = (hight - ResY) / 2 / hight * PBitmap->bmHeight;
	}
	else
	{
		destStartRow = (int)((ResY - hight) / 2);
		sourceStartRow = 0;
	}
	double sourceRowInc = (((double)PBitmap->bmHeight - ((double)sourceStartRow * 2)) / rowDrawCount);

	DWORD* lpSourcePixels = (DWORD*)PBitmap->bmBits;

	for (int i = rowDrawCount - 1; i >= 0; i--)
	{
		DWORD temp = lpSourcePixels[bitmapColumn + (int)sourceStartRow * (PBitmap->bmWidth)];

		lpDestPixels[columnNumber + (destStartRow + i) * resX] = temp;

		sourceStartRow += sourceRowInc;
	}

}

void RenderEntityColumn(DWORD* lpDestPixels, const int columnNumber, const double hight, const unsigned char wallType, const double offset)
{
	int resX = GetResX();
	int ResY = GetResY();

	BITMAP* PBitmap = bitmapEntityTextures + wallType;
	int bitmapColumn = (int)(PBitmap->bmWidth * offset);

	int rowDrawCount = (int)hight;
	int destStartRow;
	double sourceStartRow;

	if (rowDrawCount > ResY)
	{
		rowDrawCount = ResY;
		destStartRow = 0;
		sourceStartRow = (hight - ResY) / 2 / hight * PBitmap->bmHeight;
	}
	else
	{
		destStartRow = (int)((ResY - hight) / 2);
		sourceStartRow = 0;
	}
	double sourceRowInc = (((double)PBitmap->bmHeight - ((double)sourceStartRow * 2)) / rowDrawCount);

	DWORD* lpSourcePixels = (DWORD*)PBitmap->bmBits;

	for (int i = rowDrawCount - 1; i >= 0; i--)
	{
		DWORD temp = lpSourcePixels[bitmapColumn + (int)sourceStartRow * (PBitmap->bmWidth)];
		if ((temp & 0x00FFFFFF) != 0x00FF05AB)
		{
			lpDestPixels[columnNumber + (destStartRow + i) * resX] = temp;
		}
		sourceStartRow += sourceRowInc;
	}

}

double GetAngleDif(double a, double b)
{
	while (a > M_PI * 2)
	{
		a -= M_PI * 2;
	}
	while (a < 0)
	{
		a += M_PI * 2;
	}
	while (b > M_PI * 2)
	{
		b -= M_PI * 2;
	}
	while (b < 0)
	{
		b += M_PI * 2;
	}
	double res = a - b;

}

void DrawBar(DWORD* lpDestPixels, int barSlot, DWORD color, double fill)
{
	int ResX = GetResX();
	int ResY = GetResY();

	

	int pixelLenY = ResY / 20;
	int pixelLenX = ResX / 3;
	int colStart = ResX / 40;

	int rowStart = ResY - pixelLenY - (pixelLenY + ResY / 80) * barSlot - ResY / 40;

	for (int i = rowStart; i < pixelLenY + rowStart; i++)
	{
		for (int j = colStart; j < pixelLenX + colStart; j++)
		{
			lpDestPixels[i * ResX + j] = 0x00000000;
		}
	}

	int pixselOffset = pixelLenY / 8;
	pixelLenY -= pixselOffset * 2;
	pixelLenX -= pixselOffset * 2;
	colStart += pixselOffset;
	rowStart += pixselOffset;

	pixelLenX *= fill;

	for (int i = rowStart; i < pixelLenY + rowStart; i++)
	{
		for (int j = colStart; j < pixelLenX + colStart; j++)
		{
			lpDestPixels[i * ResX + j] = color;
		}
	}
}

void DrawScope(DWORD* lpDestPixels)
{
	int ResX = GetResX();
	int ResY = GetResY();

	for (int i = ResY / 2 - 15; i < ResY / 2 + 15; i++)
	{
		memset(lpDestPixels + i * ResX + ResX / 2 - 3, 0, sizeof(int) * 6);
	}
	for (int i = ResY / 2 - 3; i < ResY / 2 + 3; i++)
	{
		memset(lpDestPixels + i * ResX + ResX / 2 - 15, 0, sizeof(int) * 30);
	}
}

void DrawHud(DWORD* lpDestPixels)
{

	DrawBar(lpDestPixels, 0, 0x001C1C9C, (double)GetPlayerArmor() / GetPlayerMaxArmor());
	DrawBar(lpDestPixels, 1, 0x0000FF00, (double)GetPlayerHealth() / GetPlayerMaxHealth());
	//DrawBar(lpDestPixels, 2, 0x00F0F01F, (double)GetPlayerStamina()/ GetPlayerMaxStamina());
	DrawScope(lpDestPixels);
}

void DrawArmTextures(DWORD* lpPixelsDest, int armTextureNumber)
{
	if (armTextureNumber != -1)
	{
		BITMAP* PBitmapSource = bitmapArmTextures + armTextureNumber;
		DWORD* lpPixelsSource = PBitmapSource->bmBits;

		int ResX = GetResX();
		int ResY = GetResY();

		int BitmapResX = PBitmapSource->bmWidth;
		int BitmapResY = PBitmapSource->bmHeight;
		
		int destX = ResX / 2;
		int destY = ResY / 3 + 45;

		int lengthX = ResX / ((double)3);
		int lengthY = destY - 45;

		double incX = (double)BitmapResX / lengthX;
		double incY = (double)BitmapResY / lengthY;

		double sourceYStart = 0;
		double soureXStart = 0;

		for (int i = destY - 1; i >= destY - lengthY; i--)
		{
			soureXStart = 0;
			for (int j = destX; j < destX + lengthX; j++)
			{
				DWORD temp = lpPixelsSource[(int)((int)sourceYStart * BitmapResX + soureXStart)];
				if ((temp & 0x00FFFFFF) != 0x00FF05AB)
				{
					lpPixelsDest[i * ResX + j] = temp;
				}
				soureXStart += incX;
			}
			sourceYStart += incY;
		}
	}
}

BYTE* GetFrameBits()
{
	int pixelsWight = GetResX();
	int pixelsHight = GetResY();

	int pixelsArrSize = 4 * pixelsWight * pixelsHight;
	int entityesCount = GetEntityesCount();
	BYTE* lpPixels = (BYTE*)malloc(pixelsArrSize);

	DWORD* dest = lpPixels;
	long skyColor = GetSkyColor();
	for (int i = pixelsHight * pixelsWight / 2; i < pixelsHight * pixelsWight; i++)
	{
		dest[i] = skyColor;
	}
	long groundColor = GetGroundColor();
	for (int i = 0; i < pixelsHight * pixelsWight / 2; i++)
	{
		dest[i] = groundColor;
	}

	//Выделение памяти под массивы для оптимизации

	double* DistanceBeforeWalls = (double*)malloc(sizeof(double) * pixelsWight);
	double* DistanceBeforeEntitys = (double*)malloc(sizeof(double) * entityesCount);
	double* EntityesAngle = (double*)malloc(sizeof(double) * entityesCount);
	if (lpPixels && DistanceBeforeWalls && EntityesAngle)
	{
		//Начало рисования в lpPixels стен
		PointD playerCords = GetPlayerCords();
		double playerCameraAngle = GetPlayerCameraAngle();
		double curRenderingAngle = playerCameraAngle - PLAYER_VIEVING_ANGLE / 2;
		double rendreAngleInc = PLAYER_VIEVING_ANGLE / pixelsWight;
		for (int i = 0; i < pixelsWight; i++)
		{
			ColisionData colData = GetDistanceBeforeWall(playerCords.x, playerCords.y, curRenderingAngle);
			DistanceBeforeWalls[i] = colData.distance;
			double wallHight = GetResY() / colData.distance / cos(playerCameraAngle - curRenderingAngle);
			if (colData.wallType == 2)
			{
				colData.wallType = 2;
			}
			if (colData.wallType <= WALL_TEXTURES_COUNT)
			{
				RenderWallColumn((DWORD*)lpPixels, i, wallHight, colData.wallType - 1, colData.offset);
			}
			else
			{
				RenderSolidColumn((DWORD*)lpPixels, i, colData, cos(playerCameraAngle - curRenderingAngle));
			}
			curRenderingAngle += rendreAngleInc;
		}
		//Конец рисования в lpPixels стен
		//Начало рисования в lpPixels сущностей 

		SortEntityes();
		for (int i = 0; i < entityesCount; i++)
		{
			PointD eCords = GetEntityCords(i);
			PointD RECords;
			RECords.x = eCords.x - playerCords.x;
			RECords.y = eCords.y - playerCords.y;
			DistanceBeforeEntitys[i] = sqrt(RECords.x * RECords.x + RECords.y * RECords.y);
			EntityesAngle[i] = atan(RECords.y / RECords.x);
			if ((RECords.x < 0) && (RECords.y < 0))
			{
				EntityesAngle[i] += M_PI;
			}
			else if ((RECords.x < 0))
			{
				EntityesAngle[i] += M_PI;
			}
			else if (EntityesAngle[i] < 0)
			{
				EntityesAngle[i] += M_PI * 2;
			}

		}

		curRenderingAngle = playerCameraAngle - PLAYER_VIEVING_ANGLE / 2;
		rendreAngleInc = PLAYER_VIEVING_ANGLE / pixelsWight;
		for (int i = 0; i < pixelsWight; i++)
		{
			for (int j = 0; j < entityesCount; j++)
			{
				if (DistanceBeforeWalls[i] > DistanceBeforeEntitys[j])
				{
					if (curRenderingAngle < 0)
					{
						curRenderingAngle += M_PI * 2;
					}
					double angleDif = fabs(EntityesAngle[j] - curRenderingAngle);
					BOOL wasNormalized = 0;
					if (angleDif > M_PI + M_PI_2)
					{
						angleDif -= M_PI * 2;
						wasNormalized = 1;
					}
					if (fabs(angleDif) < M_PI_2)
					{
						double offset = DistanceBeforeEntitys[j] * tan(fabs(angleDif));
						if (offset < GetEntityRadius(j))
						{

							double distance = sqrt(DistanceBeforeEntitys[j] * DistanceBeforeEntitys[j] + offset * offset);
							double hight = GetEntityHight(j) / distance / cos(playerCameraAngle - curRenderingAngle);
							if (wasNormalized)
							{
								if (fabs(EntityesAngle[j] - curRenderingAngle) - M_PI * 2 > 0)
								{
									offset = GetEntityRadius(j) + offset;
								}
								else
								{
									offset = GetEntityRadius(j) - offset;
									
								}
							}
							else
							{
								if ((EntityesAngle[j] - curRenderingAngle > 0))
								{
									offset = GetEntityRadius(j) - offset;
								}
								else
								{
									offset = GetEntityRadius(j) + offset;
								}
							}

							RenderEntityColumn((DWORD*)lpPixels, i, hight * GetResY(), GetEntytyTexture(j), offset / (GetEntityRadius(j) * 2));
						}
					}
				}
			}
			curRenderingAngle += rendreAngleInc;
		}

		//Конец рисования в lpPixels сущностей 

		//Освобождение памяти
		free(DistanceBeforeWalls);
		free(DistanceBeforeEntitys);
		free(EntityesAngle);
		DrawArmTextures((DWORD*)lpPixels, GetPlayerArmTexture());
		DrawHud((DWORD*)lpPixels);
	}

	return lpPixels;
}
