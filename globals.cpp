#include "globals.h"

LPCTSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCTSTR g_lpszAplicationTitle = TEXT("������� ���� ����������. ���������� <����� �.>");
LPCTSTR g_lpszDestroyMessage = TEXT("��������� ��������� WM_DESTROY, �� ����������� ��������\
	� �������� ������ �����. ��������� ��������� � ����� � ���������� ����� ����������");

HINSTANCE g_hInst = NULL;
HBRUSH hbr = CreateSolidBrush(RGB(0, 255, 0));

HWND hButtonSave = NULL;
HWND hButtonAdd = NULL;
HWND hButtonExit = NULL;
HWND hEdit = NULL;
HWND hListBox = NULL;