#include <Windows.h>

#include "Engine.h"
#include "Resolution.h"

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			KeyPressed(wParam);
			break;

		case WM_KEYUP:
			KeyReleased(wParam);
			break;

		case WM_MOUSEMOVE:
			MouseMoved(hWnd);
			break;

		case WM_TIMER:
			Think(hWnd);
			break;

		case WM_PAINT:
			Redraw(hWnd);
			break;

		case WM_LBUTTONDOWN:
			LeftMouseBottonClicked();
			break;

		case WM_LBUTTONUP:
			LeftMouseButtonRelised();
			break;

		case WM_SETCURSOR:
			SetCursor(NULL);
			return TRUE;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG msg;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = MyWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MyWindowClass";
	wcex.hIconSm = 0;
	RegisterClassEx(&wcex);

	SetResX(1152);
	SetResY(864);

	hWnd = CreateWindowEx(0, L"MyWindowClass", L"MBG", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, GetResX(), GetResY(), 0, 0, hInstance, NULL);

	SetTimer(hWnd, NULL, 1/240, NULL);

	EngineInit(hInstance);

	while (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
	}

	return msg.wParam;
}