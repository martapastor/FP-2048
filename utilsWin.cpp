#include "utilsWin.h"

void clearConsole() {
	system("cls");
}

void backgroundTextAtt(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (color << 4));
}

void fontConsole (bool console) { 
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.FontWeight = 400; //¿Anchura de campo = 4?
	if (console) {
		cfi.nFont = 1;
		cfi.dwFontSize.X = 12; cfi.dwFontSize.Y = 20;
		cfi.FontFamily = 54;
		wcscpy_s(cfi.FaceName, L"Lucida Console"); //Consola
	}
	else {
		cfi.nFont = 8;
		cfi.dwFontSize.X = 12; cfi.dwFontSize.Y = 16;
		cfi.FontFamily = 48;
		wcscpy_s(cfi.FaceName, L"Terminal"); //Mapa de bits
	} 
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
}

int getKey() {
	int key;
	INPUT_RECORD record; DWORD num;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	do {
		ReadConsoleInput(hStdIn, &record, 1, &num);
	} while (record.EventType != KEY_EVENT);

	if (record.Event.KeyEvent.uChar.AsciiChar == 0) {  //Teclas especiales
		ReadConsoleInput(hStdIn, &record, 1, &num);  //Leer otro
		key = record.Event.KeyEvent.wVirtualKeyCode;
	}
	else key = record.Event.KeyEvent.uChar.AsciiChar;

	return key;
}

void cpConsoleOut (int cp) {
	SetConsoleOutputCP(cp);
}

/*
void cambiarFuente(int num) {
	backgroundTextAtt(0);
	cpConsoleOut (num);

	if (num == 850) fontConsole (false);
	else if (num == 1252) fontConsole (true);
}
*/
