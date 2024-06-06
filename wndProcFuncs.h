#ifndef WND_PROC_FUNCS_H
#define WND_PROC_FUNCS_H

#include <windows.h>

/// <summary>
/// Функция обработки WM_DESTROY.
/// Вызывается HANDLE_MSG при закрыти приложения.
/// </summary>
void wndProc_OnDestroy(HWND hwnd);

/// <summary>
/// Функция обработки WM_MENUSELECT. 
/// Вызывается HANDLE_MSG при отображении подсказки меню.
/// </summary>
void wndProc_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags);


/// <summary>
/// Функция обработки WM_LBUTTONDOWN. 
/// Вызывается HANDLE_MSG при клике левой кнопкой мыши по координатам мыши.Выводит текст.
/// </summary>
void wndProc_OnLButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/// <summary>
/// Функция обработки WM_RBUTTONDOWN. 
/// Вызывается HANDLE_MSG при клике правой кнопкой мыши по координатам мыши.
///  Вызывает контекстное меню по координатам мыши
/// </summary>
void wndProc_OnRButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/// <summary>
/// Функция обработки WM_CONTEXTMENU. 
/// Вызывается HANDLE_MSG при создании плавающего меню. Динамичски создает контекстное меню.
/// </summary>
void wndProc_OnContextMenu(HWND hWnd, HWND hwndContext, UINT xPos, UINT yPos);

/// <summary>
/// Функция обработки WM_PAINT.
/// Функция рисует в окне текст согласно условию.
/// </summary>
void wndProc_OnPaint(HWND hWnd);

/// <summary>
/// Функция обработки WM_CREATE.
/// Функция создает элементы окна.
/// </summary>
bool wndProc_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);

/// <summary>
/// Функция обработки WM_CREATE WM_COMMAND. Обработка команд.
/// </summary>
void wndProc_OnCommand(HWND hWnd, int wmId, HWND hwndCtl, UINT codeNotify);

#endif // WND_PROC_FUNCS_H