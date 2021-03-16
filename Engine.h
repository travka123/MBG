#pragma once

#include <Windows.h>

void Think(HWND hWnd);
void KeyPressed(WPARAM keyCode);
void KeyReleased(WPARAM keyCode);
void LeftMouseBottonClicked();
void LeftMouseButtonRelised();
void Redraw(HWND hWnd);
void MouseMoved(HWND hWnd);
void EngineInit(HINSTANCE hInstance);
