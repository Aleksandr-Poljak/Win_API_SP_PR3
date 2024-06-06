#include <windows.h>
#include <windowsx.h>
#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include "wndProcFuncs.h" 
#include "globals.h"

//�������� ������� ���������
LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd; // ����
	g_hInst = hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = Pr2_WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_POINTER));
	wc.hbrBackground = hbr;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, TEXT("������ ����������� ����"), 
			TEXT("������!"), MB_OK | MB_ICONERROR);
		return false;
	}

	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	hWnd = CreateWindowExW(NULL, g_lpszClassName,
		g_lpszAplicationTitle,
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		200, // X ��������� (X)
		200, // Y ��������� (Y)
		450, // ������ (nWidth)
		450, // ������ (nHeight)
		NULL,
		hMenu,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("���� �� �������!"),
			TEXT("������ ��� �������� ����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		{
			if (!TranslateAccelerator(hWnd, hAccel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	return msg.wParam;

}


LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {
		
		HANDLE_MSG(hWnd, WM_DESTROY, wndProc_OnDestroy);
		HANDLE_MSG(hWnd, WM_MENUSELECT, wndProc_OnMenuSelect);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, wndProc_OnLButtonDown);
		HANDLE_MSG(hWnd, WM_RBUTTONDOWN, wndProc_OnRButtonDown);
		HANDLE_MSG(hWnd, WM_CONTEXTMENU, wndProc_OnContextMenu);
		HANDLE_MSG(hWnd, WM_PAINT, wndProc_OnPaint);
		HANDLE_MSG(hWnd, WM_CREATE, wndProc_OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, wndProc_OnCommand);
		
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return false;
}
