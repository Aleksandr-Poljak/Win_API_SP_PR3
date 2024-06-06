#ifndef WND_PROC_FUNCS_H
#define WND_PROC_FUNCS_H

#include <windows.h>

/// <summary>
/// ������� ��������� WM_DESTROY.
/// ���������� HANDLE_MSG ��� ������� ����������.
/// </summary>
void wndProc_OnDestroy(HWND hwnd);

/// <summary>
/// ������� ��������� WM_MENUSELECT. 
/// ���������� HANDLE_MSG ��� ����������� ��������� ����.
/// </summary>
void wndProc_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags);


/// <summary>
/// ������� ��������� WM_LBUTTONDOWN. 
/// ���������� HANDLE_MSG ��� ����� ����� ������� ���� �� ����������� ����.������� �����.
/// </summary>
void wndProc_OnLButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/// <summary>
/// ������� ��������� WM_RBUTTONDOWN. 
/// ���������� HANDLE_MSG ��� ����� ������ ������� ���� �� ����������� ����.
///  �������� ����������� ���� �� ����������� ����
/// </summary>
void wndProc_OnRButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/// <summary>
/// ������� ��������� WM_CONTEXTMENU. 
/// ���������� HANDLE_MSG ��� �������� ���������� ����. ���������� ������� ����������� ����.
/// </summary>
void wndProc_OnContextMenu(HWND hWnd, HWND hwndContext, UINT xPos, UINT yPos);

/// <summary>
/// ������� ��������� WM_PAINT.
/// ������� ������ � ���� ����� �������� �������.
/// </summary>
void wndProc_OnPaint(HWND hWnd);

/// <summary>
/// ������� ��������� WM_CREATE.
/// ������� ������� �������� ����.
/// </summary>
bool wndProc_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);

/// <summary>
/// ������� ��������� WM_CREATE WM_COMMAND. ��������� ������.
/// </summary>
void wndProc_OnCommand(HWND hWnd, int wmId, HWND hwndCtl, UINT codeNotify);

#endif // WND_PROC_FUNCS_H