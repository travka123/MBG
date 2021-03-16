#pragma once

#include <Windows.h>

void RendringInit(HINSTANCE hInstance);
BYTE* GetFrameBits();
BITMAPINFO GetBitmapInfo(PAINTSTRUCT *ps);