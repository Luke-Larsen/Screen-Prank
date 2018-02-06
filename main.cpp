#include <Windows.h>

int ScreenWidth, ScreenHeight;
int Interval = 100;

LRESULT CALLBACK melter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE:
	{
		HDC Desktop = GetDC(HWND_DESKTOP);
		HDC Window = GetDC(hWnd);
		BitBlt(Window, 0, 0, ScreenWidth, ScreenHeight, Desktop, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, Window);
		ReleaseDC(HWND_DESKTOP, Desktop);
		SetTimer(hWnd, 0, Interval, 0);
		ShowWindow(hWnd, SW_SHOW);
		break;
	}
	case WM_PAINT: {
		ValidateRect(hWnd, 0);
		break;
	}
	case WM_TIMER: {
		HDC Window = GetDC(hWnd);
		int X = (rand() % ScreenWidth) - (150 / 2);
		int Y = (rand() % 15);
		int Width = (rand() % 150);
		BitBlt(Window, X, Y, Width, ScreenHeight, Window, X, 0, SRCCOPY);
		ReleaseDC(hWnd, Window);
		break;
	}
	case WM_DESTROY: {
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		
	}
	return 0;			 
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
int APIENTRY WinMain(HINSTANCE Inst, HINSTANCE Prev, LPSTR cmd, int showcmd) {
	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	WNDCLASS wndClass = { 0, melter,0,0,Inst,0,LoadCursor(0,IDC_ARROW),0,0,"ScreenMelter"};
	if (RegisterClass(&wndClass)) {
		HWND hWnd = CreateWindowExA(WS_EX_TOPMOST, "ScreenMelter", 0, WS_POPUP, 0, 0, ScreenWidth, ScreenHeight, HWND_DESKTOP, 0, Inst, 0);
		if (hWnd) {
			srand(GetTickCount());
			MSG msg = { 0 };
			while (msg.message != WM_QUIT) {
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
}