#include "Engine.h"

#include "GameLogic.h"
#include "Rendring.h"
#include "InputManager.h"
#include "Resolution.h"
#include "Weapons.h"

void Think(HWND hWnd)
{
	ProcessInput();
	InvalidateRect(hWnd, NULL, FALSE);
}

void Redraw(HWND hWnd)
{
	PAINTSTRUCT ps;
	BeginPaint(hWnd, &ps);

	HDC hMemDC = CreateCompatibleDC(ps.hdc);
	HBITMAP hScreen;
	HBITMAP oldBmp;
	hScreen = CreateCompatibleBitmap(ps.hdc, GetResX(), GetResY());
	oldBmp = (HBITMAP)SelectObject(hMemDC, hScreen);

	BITMAPINFO MyBMInfo = { 0 };
	MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);

	//Получение информации о битмапе
	if (0 == GetDIBits(hMemDC, hScreen, 0, 0, NULL, &MyBMInfo, DIB_RGB_COLORS))
	{
		return;
	}

	//Настройка представления битмапа
	MyBMInfo.bmiHeader.biBitCount = 32;
	MyBMInfo.bmiHeader.biCompression = BI_RGB;
	MyBMInfo.bmiHeader.biHeight = abs(MyBMInfo.bmiHeader.biHeight);

	BYTE* lpPixels = GetFrameBits();

	if (0 == SetDIBits(hMemDC, hScreen, 0, GetResY(), lpPixels, &MyBMInfo, DIB_RGB_COLORS))
	{
		return;
	}
	BitBlt(ps.hdc, 0, 0, GetResX(), GetResY(), hMemDC, 0, 0, SRCCOPY);

	free(lpPixels);
	SelectObject(hMemDC, oldBmp);
	DeleteObject(hScreen);
	DeleteDC(hMemDC);

	EndPaint(hWnd, &ps);
}

void MouseMoved(HWND hWnd)
{
	SetXOffsetMouseMove(hWnd);
}

void EngineInit(HINSTANCE hInstance)
{
	RendringInit(hInstance);
	GameLogicInit();
}

void KeyPressed(WPARAM keyCode)
{
	switch (keyCode)
	{
		case VK_UP:
		case 0x57:
			MoveForwardButtonPresed();
			break;

		case VK_LEFT:
		case 0x41:
			MoveLeftButtonPresed();
			break;

		case VK_RIGHT:
		case 0x44:
			MoveRightButtonPresed();
			break;

		case VK_DOWN:
		case 0x53:
			MoveBackButtonPresed();
			break;

		case 0x31:
			SetWeaponRechoise(WEAPON_PISTOL);
			break;

		case 0x32:
			SetWeaponRechoise(WEAPON_SHOTGUN);
			break;

		case 0x45:
			ActionKeyPresed();
			break;

		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
	}
}

void KeyReleased(WPARAM keyCode)
{
	switch (keyCode)
	{
		case VK_UP:
		case 0x57:
			MoveForwardButtonReleased();
			break;

		case VK_LEFT:
		case 0x41:
			MoveLeftButtonReleased();
			break;

		case VK_RIGHT:
		case 0x44:
			MoveRightButtonReleased();
			break;

		case VK_DOWN:
		case 0x53:
			MoveBackButtonReleased();
			break;

		case 0x45:
			ActionKeyReleased();
			break;
	}
}

void LeftMouseBottonClicked()
{
	StartFiring();
}

void LeftMouseButtonRelised()
{
	StopFiring();
}


