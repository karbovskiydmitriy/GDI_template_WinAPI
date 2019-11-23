#include "Template.h"

const DWORD windowStyle = WS_OVERLAPPEDWINDOW;
RECT clientRect = {0, 0, 800, 600};
HDC hdcBack;
HBITMAP hbmBack;
#define caption L"WinAPI program template"
#define mainClassName L"MainClass"

WNDCLASSEXW WndClassEx = {sizeof(WNDCLASSEX), 0, (WNDPROC)WindowProc, 0, 0, (HINSTANCE)0, (HICON)0, (HCURSOR)0, (HBRUSH)0, (LPCWSTR)0, (LPCWSTR)mainClassName, 0};

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	MSG msg;
	RECT R;

	R = clientRect;
	AdjustWindowRectEx(&R, windowStyle, FALSE, 0);
	WndClassEx.hInstance = hInstance;
	WndClassEx.hCursor = LoadCursorW((HINSTANCE)0, IDC_ARROW);
	RegisterClassEx(&WndClassEx);
	CreateWindowExW(0, mainClassName, caption, windowStyle, 0, 0, R.right, R.bottom, (HWND)0, (HMENU)0, hInstance, (LPVOID)0);

	while (GetMessageW(&msg, (HWND)0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;

}

LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	HDC hdc;
	PAINTSTRUCT ps;

	switch(uMsg) {
	case WM_CREATE:
		ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);
		hdc = GetDC((HWND)0);
		hdcBack = CreateCompatibleDC(hdc);
		hbmBack = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		SelectObject(hdcBack, hbmBack);
		ReleaseDC((HWND)0, hdc);
		return 0;
	case WM_SIZE:
		GetClientRect(hWnd, &clientRect);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		Draw();
		BeginPaint(hWnd, &ps);
		BitBlt(ps.hdc, 0, 0, clientRect.right, clientRect.bottom, hdcBack, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		InvalidateRect(hWnd, (RECT *)NULL, FALSE);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}

void Draw()
{	

	FillRect(hdcBack, &clientRect, (HBRUSH)0);
	Rectangle(hdcBack, clientRect.left + 40, clientRect.top + 40, clientRect.right - 40, clientRect.bottom - 40);

}
