#include "globals.h"

LPCTSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCTSTR g_lpszAplicationTitle = TEXT("Главное окно приложения. Програмист <Поляк А.>");
LPCTSTR g_lpszDestroyMessage = TEXT("Поступило сообщение WM_DESTROY, из обработчика которого\
	и выполнен данный вывод. Сообщение поступило в связи с разрушение мокна приложения");

HINSTANCE g_hInst = NULL;
HBRUSH hbr = CreateSolidBrush(RGB(0, 255, 0));

HWND hButtonSave = NULL;
HWND hButtonAdd = NULL;
HWND hButtonExit = NULL;
HWND hEdit = NULL;
HWND hListBox = NULL;