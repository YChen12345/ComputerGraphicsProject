#pragma once

#define NOMINMAX
#include <Windows.h>
#include <string>
#include "Mathf.h"

#define WINDOW_GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define WINDOW_GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

class Window
{
public:
	HWND hwnd;
	HINSTANCE hinstance;
	int width;
	int height;
	float invZoom;
	std::string name;
	int keys[256] = { 0 };
	int mousex;
	int mousey;
	int mouseButtons[3] = { 0 };
	int mouseWheel;
	bool useMouseClip;
	Vec2 dir;
	void updateMouse(int x, int y)
	{
		mousex = x;
		mousey = y;
	}
	void processMessages();
	void create(int window_width, int window_height, const std::string window_name, float zoom = 1.0f, bool window_fullscreen = false, int window_x = 0, int window_y = 0);
	void checkInput()
	{
		if (useMouseClip)
		{
			clipMouseToWindow();
		}
		IssueKeyUp();
		processMessages();
	}
	int keyPressed(int key)
	{
		return keys[key];
	}
	bool GetKeyDown(int key) {
		if (keyPressed(key) == 1) {
			return true;
		}
		return false;
	}
	bool GetKey(int key) {
		if (keyPressed(key) > 0&& keyPressed(key) <3) {
			return true;
		}
		return false;
	}
	bool GetKeyUp(int key) {
		if (keyPressed(key) == 3) {
			return true;
		}
		return false;
	}
	bool GetMouseButtonDown(int key)
	{
		if (mouseButtons[key] == 1) {
			return true;
		}
		return false;
	}
	bool GetMouseButton(int key)
	{
		if (mouseButtons[key] >0 && mouseButtons[key] < 3) {
			return true;
		}
		return false;
	}
	bool GetMouseButtonUp(int key)
	{
		if (mouseButtons[key] == 3) {
			return true;
		}
		return false;
	}
	int getMouseInWindowX()
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p);
		RECT rect;
		GetClientRect(hwnd, &rect);
		p.x = p.x - rect.left;
		p.x = p.x * invZoom;
		return p.x;
	}
	int getMouseInWindowY()
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p);
		RECT rect;
		GetClientRect(hwnd, &rect);
		p.y = p.y - rect.top;
		p.y = p.y * invZoom;
		return p.y;
	}
	void clipMouseToWindow()
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		POINT ul;
		ul.x = rect.left;
		ul.y = rect.top;
		POINT lr;
		lr.x = rect.right;
		lr.y = rect.bottom;
		MapWindowPoints(hwnd, nullptr, &ul, 1);
		MapWindowPoints(hwnd, nullptr, &lr, 1);
		rect.left = ul.x;
		rect.top = ul.y;
		rect.right = lr.x;
		rect.bottom = lr.y;
		ClipCursor(&rect);
	}
	void IssueKeyUp() {
		for (int i = 0; i < 256; i++) {
			if (keys[i] == 3) {
				keys[i] = 0;
			}
			if (keys[i] == 1) {
				keys[i] = 2;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (mouseButtons[i] == 3) {
				mouseButtons[i] = 0;
			}
			if (mouseButtons[i] == 1) {
				mouseButtons[i] = 2;
			}
		}
	}
	void SetMousePos(int x, int y) {
		SetCursorPos(x, y);
	}
	void MouseInWindowLoop()
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		Vec2 origin((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
		Vec2 mousePos(mousex, mousey);
		dir = direction(origin,mousePos)*distance(origin, mousePos);
		SetCursorPos(origin.x, origin.y);
	}
	Vec2 MouseMove() {
		return dir;
	}
	void SetFullscreen() {
		static WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
		static BOOL g_bFullscreen = FALSE;

		if (!g_bFullscreen) {
			GetWindowPlacement(hwnd, &g_wpPrev);

			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			SetWindowLongPtr(hwnd, GWL_STYLE,
				WS_POPUP | WS_VISIBLE);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, screenWidth, screenHeight,
				SWP_FRAMECHANGED | SWP_SHOWWINDOW);

			g_bFullscreen = TRUE;
		}
		else {
			SetWindowLongPtr(hwnd, GWL_STYLE,
				WS_OVERLAPPEDWINDOW | WS_VISIBLE);
			SetWindowPlacement(hwnd, &g_wpPrev);

			g_bFullscreen = FALSE;
		}
	}
	void SetDisplayFullscreen(int width, int height, int bitsPerPixel) {
		DEVMODE dm = { 0 };
		dm.dmSize = sizeof(dm);
		dm.dmPelsWidth = width;
		dm.dmPelsHeight = height;
		dm.dmBitsPerPel = bitsPerPixel;
		dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
	}

	void RestoreDisplay() {
		ChangeDisplaySettings(NULL, 0);
	}
	void MouseCursor(bool a) {
		if (a) {
			while (ShowCursor(TRUE) < 0);
		}
		else
		{
			while (ShowCursor(FALSE) >= 0);
		}
	}
	~Window()
	{
		ShowCursor(true);
		ClipCursor(NULL);
	}
};
