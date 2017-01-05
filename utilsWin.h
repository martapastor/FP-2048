#ifndef UTILSWIN_H
#define UTILSWIN_H

#include <Windows.h>
using namespace std;

const int TE_Salir = VK_ESCAPE;
const int TE_Arriba = VK_UP;
const int TE_Abajo = VK_DOWN;
const int TE_Derecha = VK_RIGHT;
const int TE_Izquierda = VK_LEFT;

void clearConsole();
void backgroundTextAtt(int color);
void fontConsole (bool console);
int getKey();
void cpConsoleOut (int cp);
//void cambiarFuente(int num);
#endif