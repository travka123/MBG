#pragma once

#include <Windows.h>

void InitInputManager();

void MoveForwardButtonPresed();
void MoveForwardButtonReleased();

void MoveLeftButtonPresed();
void MoveLeftButtonReleased();

void MoveRightButtonPresed();
void MoveRightButtonReleased();

void MoveBackButtonPresed();
void MoveBackButtonReleased();

void SetXOffsetMouseMove(HWND hWnd);
void ClearCameraXOffset();

BOOL IsMoveForwardButtonPresed();
BOOL IsMoveLeftButtonPresed();
BOOL IsMoveRightButtonPresed();
BOOL IsMoveBackButtonPresed();
int GetCameraXOffset();

void StartFiring();
void StopFiring();
BOOL IsFiring();

void SetWeaponRechoise(int weapon);
int GetWeaponRechoise();
void ClearWeaponRechoise();

BOOL IsActionKeyPresed();
void ActionKeyPresed();
void ActionKeyReleased();
