#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include "sp_pr3.h"

//Прототип
LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

// Имя класса окна
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class"); 
// Заголовок окна
LPCTSTR g_lpszAplicationTitle = TEXT("Главное окно приложения. Програмист <Поляк А.>");
// Выводится в сообщении о закрытии окна
LPCTSTR g_lpszDestroyMessage = TEXT("Поступило сообщение WM_DESTROY, из обработчика которого\
	и выполнен данный вывод. Сообщение поступило в связи с разрушение мокна приложения");
//Глобальная переменная для хранения дискриптера приложения.
HINSTANCE g_hInst;
HBRUSH hbr = CreateSolidBrush(RGB(0, 255, 0)); //Цвет фона

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;
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
		MessageBox(NULL, TEXT("Ошибка регистрации окна"), 
			TEXT("Ошибка!"), MB_OK | MB_ICONERROR);
		return false;
	}

	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	hWnd = CreateWindowExW(NULL, g_lpszClassName,
		g_lpszAplicationTitle,
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		200, // X положение (X)
		200, // Y положение (Y)
		450, // Ширина (nWidth)
		450, // Высота (nHeight)
		NULL,
		hMenu,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"),
			TEXT("Ошибка при создании окна"), MB_OK | MB_ICONERROR);
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

	HDC hdc; // Дескриптор контекста устройства.

	LPCTSTR lpszMessage = TEXT("Обработка сообщения WM_LBUTTONDOWN,\n которое посылается \
				в окно при щелчке левой кнопки мыши");
	TCHAR messageFormat[200];
	wsprintf(messageFormat, lpszMessage);

	int xPos; 
	int yPos;
	RECT rt; 

	PAINTSTRUCT ps;
	TCHAR messageWM_PAINT[200];
	wsprintf(messageWM_PAINT, TEXT("Обработка сообщения WM_PAINT."));

	static HWND hButtonSave; // Кнопка в буфер
	static HWND hButtonAdd; // Кнопка в список
	static HWND hButtonExit; // кнопка Выход
	static HWND hEdit; //Редактор
	static HWND hListBox; // Список

	static TCHAR pszTextBuff[500];

	#define IDC_BTN_SAVE 150
	#define IDC_BTN_ADD 151
	#define IDC_EDIT1 152
	#define IDC_LISTBOX 153


	switch (msg) {
		case WM_DESTROY:
			MessageBox(NULL, g_lpszDestroyMessage, TEXT("Окно закрыто"), MB_OK);
			PostQuitMessage(5);
			break;

		
		case WM_MENUSELECT:
		{
			HDC hdc1;
			TCHAR Buf[100];
			HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
			int size = LoadString(hInst, LOWORD(wParam), Buf, 100);
			hdc1 = GetDC(hWnd);
			RECT rc;
			GetClientRect(hWnd, &rc);

			// Очищаем область вывода текста
			RECT clearRect = { rc.left + 10, rc.bottom - 30, rc.right, rc.bottom };
			FillRect(hdc1, &clearRect, hbr);

			// Выводим новый текст
			TextOut(hdc1, rc.left + 10, rc.bottom - 30, Buf, lstrlen(Buf));

			ReleaseDC(hWnd, hdc1);
			memset(Buf, 0, 100);
			break;
		}

		// Вывод сообщения при  клике левой кнопкой мыши по координатам мыши
		case WM_LBUTTONDOWN:
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
			rt = { xPos, yPos, xPos + 200, yPos + 50 };
			hdc = GetDC(hWnd);
			DrawText(hdc, messageFormat, lstrlen(messageFormat), &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
			ReleaseDC(hWnd, hdc);
			break;

		case WM_RBUTTONDOWN:
		{
			SendMessage(hWnd, WM_CONTEXTMENU, wParam, lParam);
			break;
		}

		case WM_CONTEXTMENU:
		{	
			// получаем позицию курсора
			POINT pt;
			GetCursorPos(&pt);
			// Создаем плавающее меню
			HMENU contextMenu = CreatePopupMenu();
			AppendMenu(contextMenu, MF_STRING, IDM_EDIT_SELECT, TEXT("Выделить"));
			AppendMenu(contextMenu, MF_STRING, IDM_EDIT_COPY, TEXT("Копировать"));

			// получаем информацию о пунктах Копировать, Выделить основного меню.
			MENUITEMINFO hMenuSelectInfo = { sizeof(MENUITEMINFO) };
			MENUITEMINFO hMenuCopyInfo = { sizeof(MENUITEMINFO) };
			hMenuSelectInfo.fMask = MIIM_STATE;
			hMenuCopyInfo.fMask = MIIM_STATE;;
			GetMenuItemInfo(GetMenu(hWnd), IDM_EDIT_SELECT,false, &hMenuSelectInfo);
			GetMenuItemInfo(GetMenu(hWnd), IDM_EDIT_COPY, false, &hMenuCopyInfo);
			
			
			//Меняем статус плавающего меню.					
			EnableMenuItem(contextMenu, IDM_EDIT_SELECT, hMenuSelectInfo.fState);
			EnableMenuItem(contextMenu, IDM_EDIT_COPY, hMenuCopyInfo.fState);
			
			// Отображаем плавающее меню
			TrackPopupMenu(contextMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,
				pt.x,pt.y,
				0, hWnd, NULL);
			
			DestroyMenu(contextMenu);
			break;
		}


		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, 20, 100, messageWM_PAINT, lstrlen(messageWM_PAINT));
			EndPaint(hWnd, &ps);
			break;
		
		case WM_CREATE:
		{
			MessageBox(hWnd,
				TEXT("Выполняется обработка WM_CREATE"), TEXT("Обработка WM_CREATE")
				, MB_OK);

			hEdit = CreateWindowEx(0L, _T("Edit"), _T("Редактор"),
				WS_CHILD | WS_BORDER | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
				20, 50, 160, 40, hWnd,
				(HMENU)IDC_EDIT1,
				g_hInst, NULL);
			if (hEdit == 0) return -1;

			hListBox = CreateWindowEx(0L, _T("ListBox"), _T("Список"),
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				200, 50, 160, 180, hWnd,
				(HMENU)IDC_LISTBOX, g_hInst, NULL);
			if (hListBox == 0) return -1;

			hButtonSave = CreateWindowEx(0L, _T("Button"), _T("В буфер"),
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				20, 240, 80, 24, hWnd,
				(HMENU)IDC_BTN_SAVE, g_hInst, NULL);
			if (hButtonSave == 0) return -1;

			hButtonAdd = CreateWindowEx(0L, _T("Button"), _T("В список"),
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				120, 240, 80, 24, hWnd,
				(HMENU)IDC_BTN_ADD, g_hInst, NULL);
			if (hButtonAdd == 0) return -1;

			hButtonExit = CreateWindowEx(0L, _T("Button"), _T("Выход"),
				WS_CHILD | WS_BORDER | WS_VISIBLE, 220, 240, 80, 24, hWnd,
				(HMENU)IDCANCEL, g_hInst, NULL);
			if (hButtonExit == 0) return -1;

			#define IDM_FILE_CLOSE 1234
			HMENU hMenuBar = GetMenu(hWnd);
			HMENU hFileMenu = GetSubMenu(hMenuBar, 0);
			InsertMenu(hFileMenu, 2, MF_BYPOSITION | MF_STRING, IDM_FILE_CLOSE, TEXT("Закрыть документ"));

			return 0;
			break;
		}

		case WM_COMMAND:
			int wmId, wmEvent;
			wmEvent = HIWORD(wParam); // Код события
			wmId = LOWORD(wParam); // Идентификатор команды меню или горячей клавиши

			switch (wmId) {
			case IDC_BTN_SAVE: {
				int cch = SendMessage(hEdit, WM_GETTEXT, (WPARAM)500, (LPARAM)pszTextBuff);
				if (cch == 0)
				{
					MessageBox(hWnd, _T("Введите текст"), _T("Читаем Edit"), MB_OK);
				}
				else
				{
					TCHAR Buff1[500] = { 0 };
					SYSTEMTIME st;
					GetSystemTime(&st);
					wsprintf(Buff1, TEXT("Время : %d ч %d мин %d сек\n"), st.wHour, st.wMinute, st.wSecond);
					lstrcat(Buff1, __TEXT("Текст в памяти: "));
					lstrcat(Buff1, pszTextBuff);
					MessageBox(hWnd, Buff1, TEXT("Содержимое буфера"), MB_OK);
					break;
				}

			}

			case IDC_BTN_ADD: {
				int ind = SendMessage(hListBox, LB_ADDSTRING, (WPARAM)0, (LPARAM)pszTextBuff);
				if (ind == LB_ERR)
					MessageBox(hWnd, TEXT("Ошибка в списке"), TEXT(""), MB_OK);
				break;
			}

			case IDCANCEL:
				DestroyWindow(hWnd);
				break;

			case IDM_FILE_OPEN:
				MessageBox(hWnd, _T("Выбран пукт ''"), _T("Меню Файл"), MB_OK);
				break;

			case IDM_FILE_NEW:
			{
				MessageBox(hWnd, _T("Выбран пукт 'Создать'"), _T("Меню Файл"), MB_OK);
				HMENU hMenu = GetMenu(hWnd);
				EnableMenuItem(hMenu, IDM_EDIT_SELECT, MF_ENABLED);
				break;
			}

			case IDM_FILE_EXIT:
				MessageBox(hWnd, _T("Выбран пукт 'Выход'"), _T("Меню Файл"), MB_OK);
				DestroyWindow(hWnd);
				break;

			case IDM_EDIT_SELECT:
			{
				MessageBox(hWnd, _T("Выбран пукт 'Выделить' "), _T("Меню Правка"), MB_OK);
				HMENU hMenu = GetMenu(hWnd);
				EnableMenuItem(hMenu, IDM_EDIT_COPY, MF_ENABLED);
				break;
			}

			case IDM_EDIT_CUT:
				MessageBox(hWnd, _T("Выбран пукт 'Вырезеать'"), _T("Меню Правка"), MB_OK);
				break;

			case IDM_EDIT_COPY:
				MessageBox(hWnd, _T("Выбран пукт 'Копировать'"), _T("Меню Правка"), MB_OK);
				break;

			case IDM_EDIT_INSERT:
				MessageBox(hWnd, _T("Выбран пукт 'Вставить'"), _T("Меню Правка"), MB_OK);
				break;

			case IDM_REF_HELP:
				MessageBox(hWnd, _T("Выбран пукт 'Помощь'"), _T("Меню Справка"), MB_OK);
				break;

			case IDM_REF_ABOUT:
				MessageBox(hWnd, _T("Выбран пукт 'О программе'"), _T("Меню Справка"), MB_OK);
				break;

			case IDA_ACCELERAT_R:
				MessageBox(hWnd, _T("Нажата горячая клавиша 'R'"), _T("R"), MB_OK);
				break;

			case IDA_ACCELERAT_T:
				MessageBox(hWnd, _T("Нажата горячая клавиша 'T'"), _T("T"), MB_OK);
				break;
			
			case IDM_FILE_CLOSE:
			{
					MessageBox(hWnd, _T("Выбран пукт 'Закрыть документ'"), _T("Меню Файл"), MB_OK);
					HMENU hMenu = GetMenu(hWnd);
					EnableMenuItem(hMenu, IDM_EDIT_COPY, MF_DISABLED);
					EnableMenuItem(hMenu, IDM_EDIT_SELECT, MF_DISABLED);
					EnableMenuItem(hMenu, IDM_EDIT_CUT, MF_DISABLED);
					EnableMenuItem(hMenu, IDM_EDIT_INSERT, MF_DISABLED);
			}

			default:
				/*TCHAR str[100] ;
				wsprintf(str,TEXT("Команда с идентификатором %d не реализована"), wmId);
				MessageBox(hWnd, str, _T("Неизвестно"), MB_OK);*/
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return false;
}
