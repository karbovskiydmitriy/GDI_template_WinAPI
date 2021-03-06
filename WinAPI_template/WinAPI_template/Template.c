#include "Template.h"

const DWORD windowStyle = WS_OVERLAPPEDWINDOW;
RECT clientRect;
HWND hMainWindow;
HDC hdcBack;
HBITMAP hbmBack;

WNDCLASSEX wndClass =
{
	sizeof(WNDCLASSEX), 0, (WNDPROC)WindowProc, 0, 0, (HINSTANCE)0,
		(HICON)0, (HCURSOR)0, (HBRUSH)0, (TCHAR *)NULL, (TCHAR *)MAIN_CLASS_NAME, 0
};

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor((HINSTANCE)0, IDC_ARROW);
	RegisterClassEx(&wndClass);
	hMainWindow = CreateWindowEx(0, MAIN_CLASS_NAME, CAPTION, windowStyle, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, (HWND)0, (HMENU)0, hInstance, (LPVOID)NULL);

	while (GetMessage(&msg, (HWND)0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch(uMsg)
	{
	case WM_CREATE:
		ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);
		hdc = GetDC((HWND)0);
		hdcBack = CreateCompatibleDC(hdc);
		hbmBack = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		SelectObject(hdcBack, hbmBack);
		ReleaseDC((HWND)0, hdc);
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &clientRect);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		Draw();
		BeginPaint(hWnd, &ps);
		BitBlt(ps.hdc, 0, 0, clientRect.right, clientRect.bottom, hdcBack, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		InvalidateRect(hWnd, (RECT *)NULL, FALSE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			break;
		}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

void Draw()
{	
	FillRect(hdcBack, &clientRect, (HBRUSH)0);
	Rectangle(hdcBack, clientRect.left + 40, clientRect.top + 40, clientRect.right - 40, clientRect.bottom - 40);
}