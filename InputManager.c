#include "InputManager.h"

#include "Resolution.h"

typedef struct _UserInput
{
	BOOL movingForward;
	BOOL movingLeft;
	BOOL movingRight;
	BOOL movingBack;
	BOOL firing;
	BOOL action;
	int cameraRotationAngle;
	int rechoisedWeapon;
} UserInput;

UserInput userInput;

void InitInputManager()
{
	userInput.cameraRotationAngle = 0;
	userInput.movingForward = FALSE;
	userInput.movingBack = FALSE;
	userInput.movingLeft = FALSE;
	userInput.movingRight = FALSE;
	userInput.rechoisedWeapon = -1;
	userInput.action = FALSE;
}

void MoveForwardButtonPresed()
{
	userInput.movingForward = TRUE;
}

void MoveForwardButtonReleased()
{
	userInput.movingForward = FALSE;
}

void MoveLeftButtonPresed()
{
	userInput.movingLeft = TRUE;
}

void MoveLeftButtonReleased()
{
	userInput.movingLeft = FALSE;
}

void MoveRightButtonPresed()
{
	userInput.movingRight = TRUE;
}

void MoveRightButtonReleased()
{
	userInput.movingRight = FALSE;
}

void MoveBackButtonPresed()
{
	userInput.movingBack = TRUE;
}

void MoveBackButtonReleased()
{
	userInput.movingBack = FALSE;
}

void SetXOffsetMouseMove(HWND hWnd)
{
	POINT mouseCords;
	GetCursorPos(&mouseCords);
	ScreenToClient(hWnd, &mouseCords);
	userInput.cameraRotationAngle += mouseCords.x - GetResX() / 2;
	mouseCords.x = GetResX() / 2;
	mouseCords.y = GetResY() / 2;
	ClientToScreen(hWnd, &mouseCords);
	SetCursorPos(mouseCords.x, mouseCords.y);
}

void ClearCameraXOffset()
{
	userInput.cameraRotationAngle = 0;
}

BOOL IsMoveForwardButtonPresed()
{
	return userInput.movingForward;
}

BOOL IsMoveLeftButtonPresed()
{
	return userInput.movingLeft;
}

BOOL IsMoveRightButtonPresed()
{
	return userInput.movingRight;
}

BOOL IsMoveBackButtonPresed()
{
	return userInput.movingBack;
}

int GetCameraXOffset()
{
	return userInput.cameraRotationAngle;
}

void StartFiring()
{
	userInput.firing = TRUE;
}

void StopFiring()
{
	userInput.firing = FALSE;
}

BOOL IsFiring()
{
	return userInput.firing;
}

void SetWeaponRechoise(int weapon)
{
	userInput.rechoisedWeapon = weapon;
}

int GetWeaponRechoise()
{
	return userInput.rechoisedWeapon;
}

void ClearWeaponRechoise()
{
	userInput.rechoisedWeapon = -1;
}

BOOL IsActionKeyPresed()
{
	return userInput.action;
}

void ActionKeyPresed()
{
	userInput.action = TRUE;
}

void ActionKeyReleased()
{
	userInput.action = FALSE;
}
