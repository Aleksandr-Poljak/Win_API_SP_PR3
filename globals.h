#ifndef GLOBALS_H
#define GLOBALS_H

#include <tchar.h>
#include <Windows.h>

// Объявление глобальных переменных

extern LPCTSTR g_lpszClassName; // Имя класса окна
extern LPCTSTR g_lpszAplicationTitle; // Заголовок окна
extern LPCTSTR g_lpszDestroyMessage; //Сообщение о закрытии окна

//Глобальная переменная для хранения дискриптера приложения.
extern HINSTANCE g_hInst;

//Цвет фона
extern HBRUSH hbr;

extern HWND hButtonSave; // Кнопка в буфер
extern HWND hButtonAdd; // Кнопка в список
extern HWND hButtonExit; // кнопка Выход
extern HWND hEdit; //Редактор
extern HWND hListBox; // Список

#endif // GLOBALS_H
