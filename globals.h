#ifndef GLOBALS_H
#define GLOBALS_H

#include <tchar.h>
#include <Windows.h>

// ���������� ���������� ����������

extern LPCTSTR g_lpszClassName; // ��� ������ ����
extern LPCTSTR g_lpszAplicationTitle; // ��������� ����
extern LPCTSTR g_lpszDestroyMessage; //��������� � �������� ����

//���������� ���������� ��� �������� ����������� ����������.
extern HINSTANCE g_hInst;

//���� ����
extern HBRUSH hbr;

extern HWND hButtonSave; // ������ � �����
extern HWND hButtonAdd; // ������ � ������
extern HWND hButtonExit; // ������ �����
extern HWND hEdit; //��������
extern HWND hListBox; // ������

#endif // GLOBALS_H
