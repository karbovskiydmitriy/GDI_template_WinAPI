#include <Windows.h>

#define CAPTION L"WinAPI program template"
#define MAIN_CLASS_NAME L"MainClass"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);
void Draw();