#include "Template.h"

const DWORD windowStyle = WS_OVERLAPPEDWINDOW;
int prevTime = 0;
RECT clientRect = {0, 0, 800, 600};
HDC hdcBack;
HBITMAP hbmBack;
const wchar_t *const caption = L"WinAPI program template";
#define mainClassName L"MainClass"

WNDCLASSEXW WndClassEx = {sizeof(WNDCLASSEX), 0, (WNDPROC)WindowProc, 0, 0, 0, 0, 0, 0, 0, (LPCWSTR)mainClassName, 0};

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	MSG msg;
	RECT R;

	R = clientRect;
	AdjustWindowRectEx(&R, WS_OVERLAPPED, 0, 0);
	WndClassEx.hInstance = hInstance;
	WndClassEx.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClassEx(&WndClassEx);
	CreateWindowExW(0, mainClassName, (LPCWSTR)caption, windowStyle, 0, 0, R.right, R.bottom, 0, 0, hInstance, 0);

	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
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
		return 0;
	case WM_SIZE:
		GetClientRect(hWnd, &clientRect);
		DeleteDC(hdcBack);
		DeleteObject(hbmBack);
		hdc = GetDC(0);
		hdcBack = CreateCompatibleDC(hdc);
		hbmBack = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
		SelectObject(hdcBack, hbmBack);
		ReleaseDC(0, hdc);
		InvalidateRect(hWnd, 0, 0);
		return 0;
	case WM_DESTROY:
		ExitProcess(0);
	case WM_PAINT:
		FillRect(hdcBack, &clientRect, 0);
		BeginPaint(hWnd, &ps);
		BitBlt(ps.hdc, 0, 0, clientRect.right, clientRect.bottom, hdcBack, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			PostQuitMessage (0);
			return 0;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}

void Draw()
{	

}
