#include <Windows.h>
#include <tchar.h>
//#include "sp_pr3.h"

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

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;
	HBRUSH hbr = CreateSolidBrush(RGB(0, 255, 0));
	g_hInst = hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = Pr2_WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = hbr;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, TEXT("Ошибка регистрации окна"), 
			TEXT("Ошибка!"), MB_OK | MB_ICONERROR);
		return false;
	}

	hWnd = CreateWindowEx(NULL, g_lpszClassName,
		g_lpszAplicationTitle,
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		200, // X положение (X)
		200, // Y положение (Y)
		450, // Ширина (nWidth)
		450, // Высота (nHeight)
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"),
			TEXT("Ошибка при создании окна"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
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

		// Вывод сообщения при  клике левой кнопкой мыши по координатам мыши
		case WM_LBUTTONDOWN:
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
			rt = { xPos, yPos, xPos + 200, yPos + 50 };
			hdc = GetDC(hWnd);
			DrawText(hdc, messageFormat, lstrlen(messageFormat), &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
			ReleaseDC(hWnd, hdc);
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, 20, 100, messageWM_PAINT, lstrlen(messageWM_PAINT));
			EndPaint(hWnd, &ps);
			break;
		
		case WM_CREATE:
			MessageBox(hWnd, 
				TEXT("Выполняется обработка WM_CREATE"), TEXT("Обработка WM_CREATE")
				,MB_OK);

			
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
			
			return 0;
			break;

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

			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return false;
}
