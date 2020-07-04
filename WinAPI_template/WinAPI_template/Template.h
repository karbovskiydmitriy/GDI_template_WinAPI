#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

#include <Windows.h>

#define CAPTION "WinAPI program template"
#define MAIN_CLASS_NAME "TemplateClass"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Draw();

#endif // __TEMPLATE_H__