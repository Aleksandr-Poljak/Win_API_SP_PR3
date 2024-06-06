#include "wndProcFuncs.h"
#include "globals.h"
#include "resource.h"

// �������� ������� ��������� � ����������� �����.

void wndProc_OnDestroy(HWND hwnd)
{
    MessageBox(NULL, g_lpszDestroyMessage, TEXT("���� �������"), MB_OK);
    PostQuitMessage(5);
}


void wndProc_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
{
    HDC hdc1;
    TCHAR Buf[100];
    HINSTANCE hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
    int size = LoadString(hInst, item, Buf, 100);
    hdc1 = GetDC(hwnd);
    RECT rc;
    GetClientRect(hwnd, &rc);

    // ������� ������� ������ ������
    RECT clearRect = { rc.left + 10, rc.bottom - 30, rc.right, rc.bottom };
    FillRect(hdc1, &clearRect, hbr);

    // ������� ����� �����
    TextOut(hdc1, rc.left + 10, rc.bottom - 30, Buf, lstrlen(Buf));

    ReleaseDC(hwnd, hdc1);
    memset(Buf, 0, 100);
}


void wndProc_OnLButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    LPCTSTR lpszMessage = TEXT("��������� ��������� WM_LBUTTONDOWN,\n ������� ���������� \
				� ���� ��� ������ ����� ������ ����");
    TCHAR messageFormat[200];
    wsprintf(messageFormat, lpszMessage);

    RECT rt = { x, y, x + 200, y + 50 };
    HDC hdc = GetDC(hWnd);
    DrawText(hdc, messageFormat, lstrlen(messageFormat), &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
    ReleaseDC(hWnd, hdc);

}

void wndProc_OnRButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) 
{
    SendMessage(hWnd, WM_CONTEXTMENU, x, y);
}

void wndProc_OnContextMenu(HWND hWnd, HWND hwndContext, UINT xPos, UINT yPos) 
{
	// �������� ������� �������
	POINT pt;
	GetCursorPos(&pt);
	// ������� ��������� ����
	HMENU contextMenu = CreatePopupMenu();
	AppendMenu(contextMenu, MF_STRING, IDM_EDIT_SELECT, TEXT("��������"));
	AppendMenu(contextMenu, MF_STRING, IDM_EDIT_COPY, TEXT("����������"));

	// �������� ���������� � ������� ����������, �������� ��������� ����.
	MENUITEMINFO hMenuSelectInfo = { sizeof(MENUITEMINFO) };
	MENUITEMINFO hMenuCopyInfo = { sizeof(MENUITEMINFO) };
	hMenuSelectInfo.fMask = MIIM_STATE;
	hMenuCopyInfo.fMask = MIIM_STATE;;
	GetMenuItemInfo(GetMenu(hWnd), IDM_EDIT_SELECT, false, &hMenuSelectInfo);
	GetMenuItemInfo(GetMenu(hWnd), IDM_EDIT_COPY, false, &hMenuCopyInfo);


	//������ ������ ���������� ����.					
	EnableMenuItem(contextMenu, IDM_EDIT_SELECT, hMenuSelectInfo.fState);
	EnableMenuItem(contextMenu, IDM_EDIT_COPY, hMenuCopyInfo.fState);

	// ���������� ��������� ����
	TrackPopupMenu(contextMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,
		pt.x, pt.y,
		0, hWnd, NULL);

	DestroyMenu(contextMenu);

}

void wndProc_OnPaint(HWND hWnd) 
{
	PAINTSTRUCT ps;
	TCHAR messageWM_PAINT[200];
	wsprintf(messageWM_PAINT, TEXT("��������� ��������� WM_PAINT."));

	HDC hdc = BeginPaint(hWnd, &ps);
	TextOut(hdc, 20, 100, messageWM_PAINT, lstrlen(messageWM_PAINT));
	EndPaint(hWnd, &ps);
}

bool wndProc_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct) 
{
	
	MessageBox(hWnd,
		TEXT("����������� ��������� WM_CREATE"), TEXT("��������� WM_CREATE")
		, MB_OK);

	hEdit = CreateWindowEx(0L, _T("Edit"), _T("��������"),
		WS_CHILD | WS_BORDER | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
		20, 50, 160, 40, hWnd,
		(HMENU)IDC_EDIT1,
		g_hInst, NULL);
	if (hEdit == 0) return false;

	hListBox = CreateWindowEx(0L, _T("ListBox"), _T("������"),
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		200, 50, 160, 180, hWnd,
		(HMENU)IDC_LISTBOX, g_hInst, NULL);
	if (hListBox == 0) return false;

	hButtonSave = CreateWindowEx(0L, _T("Button"), _T("� �����"),
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		20, 240, 80, 24, hWnd,
		(HMENU)IDC_BTN_SAVE, g_hInst, NULL);
	if (hButtonSave == 0) return false;

	hButtonAdd = CreateWindowEx(0L, _T("Button"), _T("� ������"),
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		120, 240, 80, 24, hWnd,
		(HMENU)IDC_BTN_ADD, g_hInst, NULL);
	if (hButtonAdd == 0) return false;

	hButtonExit = CreateWindowEx(0L, _T("Button"), _T("�����"),
		WS_CHILD | WS_BORDER | WS_VISIBLE, 220, 240, 80, 24, hWnd,
		(HMENU)IDCANCEL, g_hInst, NULL);
	if (hButtonExit == 0) return false;


	HMENU hMenuBar = GetMenu(hWnd);
	HMENU hFileMenu = GetSubMenu(hMenuBar, 0);

	InsertMenu(hFileMenu, 2, MF_BYPOSITION | MF_STRING, IDM_FILE_CLOSE, TEXT("������� ��������"));

	return true;
}

TCHAR pszTextBuff[500] = { 0 };
void wndProc_OnCommand(HWND hWnd, int wmId, HWND hwndCtl, UINT codeNotify)
{
	
	switch (wmId) {

	case IDC_BTN_SAVE: {
		int cch = SendMessage(hEdit, WM_GETTEXT, (WPARAM)500, (LPARAM)pszTextBuff);
		if (cch == 0)
		{
			MessageBox(hWnd, _T("������� �����"), _T("������ Edit"), MB_OK);
		}
		else
		{
			TCHAR Buff1[500] = { 0 };
			SYSTEMTIME st;
			GetSystemTime(&st);
			wsprintf(Buff1, TEXT("����� : %d � %d ��� %d ���\n"), st.wHour, st.wMinute, st.wSecond);
			lstrcat(Buff1, __TEXT("����� � ������: "));
			lstrcat(Buff1, pszTextBuff);
			MessageBox(hWnd, Buff1, TEXT("���������� ������"), MB_OK);
			break;
		}

	}

	case IDC_BTN_ADD: {
		int ind = SendMessage(hListBox, LB_ADDSTRING, (WPARAM)0, (LPARAM)pszTextBuff);
		if (ind == LB_ERR)
			MessageBox(hWnd, TEXT("������ � ������"), TEXT(""), MB_OK);
		break;
	}

	case IDCANCEL:
		DestroyWindow(hWnd);
		break;

	case IDM_FILE_OPEN:
		MessageBox(hWnd, _T("������ ���� ''"), _T("���� ����"), MB_OK);
		break;

	case IDM_FILE_NEW:
	{
		MessageBox(hWnd, _T("������ ���� '�������'"), _T("���� ����"), MB_OK);
		HMENU hMenu = GetMenu(hWnd);
		EnableMenuItem(hMenu, IDM_EDIT_SELECT, MF_ENABLED);
		break;
	}

	case IDM_FILE_EXIT:
		MessageBox(hWnd, _T("������ ���� '�����'"), _T("���� ����"), MB_OK);
		DestroyWindow(hWnd);
		break;

	case IDM_EDIT_SELECT:
	{
		MessageBox(hWnd, _T("������ ���� '��������' "), _T("���� ������"), MB_OK);
		HMENU hMenu = GetMenu(hWnd);
		EnableMenuItem(hMenu, IDM_EDIT_COPY, MF_ENABLED);
		break;
	}

	case IDM_EDIT_CUT:
		MessageBox(hWnd, _T("������ ���� '���������'"), _T("���� ������"), MB_OK);
		break;

	case IDM_EDIT_COPY:
		MessageBox(hWnd, _T("������ ���� '����������'"), _T("���� ������"), MB_OK);
		break;

	case IDM_EDIT_INSERT:
		MessageBox(hWnd, _T("������ ���� '��������'"), _T("���� ������"), MB_OK);
		break;

	case IDM_REF_HELP:
		MessageBox(hWnd, _T("������ ���� '������'"), _T("���� �������"), MB_OK);
		break;

	case IDM_REF_ABOUT:
		MessageBox(hWnd, _T("������ ���� '� ���������'"), _T("���� �������"), MB_OK);
		break;

	case IDA_ACCELERAT_R:
		MessageBox(hWnd, _T("������ ������� ������� 'R'"), _T("R"), MB_OK);
		break;

	case IDA_ACCELERAT_T:
		MessageBox(hWnd, _T("������ ������� ������� 'T'"), _T("T"), MB_OK);
		break;

	case IDM_FILE_CLOSE:
	{
		MessageBox(hWnd, _T("������ ���� '������� ��������'"), _T("���� ����"), MB_OK);
		HMENU hMenu = GetMenu(hWnd);
		EnableMenuItem(hMenu, IDM_EDIT_COPY, MF_DISABLED);
		EnableMenuItem(hMenu, IDM_EDIT_SELECT, MF_DISABLED);
		EnableMenuItem(hMenu, IDM_EDIT_CUT, MF_DISABLED);
		EnableMenuItem(hMenu, IDM_EDIT_INSERT, MF_DISABLED);
		break;
	}

	default:
		/*TCHAR str[100] ;
		wsprintf(str,TEXT("������� � ��������������� %d �� �����������"), wmId);
		MessageBox(hWnd, str, _T("����������"), MB_OK);*/
		DefWindowProc(hWnd, WM_COMMAND, MAKEWPARAM(wmId, codeNotify), (LPARAM)hwndCtl);
	}

}