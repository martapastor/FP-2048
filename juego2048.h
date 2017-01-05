#ifndef JUEGO2048_H
#define JUEGO2048 _H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "utilsWin.h"
using namespace std;

const int DIM = 4;
const int META = 2048; //Puede ser cualquier múltiplo de 2 hasta 2048
const int PROBABILIDAD = 95;

typedef int tTablero[DIM][DIM]; //Array bidimensional de DIMxDIM enteros

typedef enum {Gana, Pierde, Jugando} tResultado;

typedef enum {Arriba, Abajo, Derecha, Izquierda} tDireccion;

typedef enum {OP_Salir, OP_Arriba, OP_Abajo, OP_Derecha, OP_Izquierda} tOpcion;

typedef struct {
	int x;
	int y;
} tCoord;

void inicializa (tTablero tablero);
void nuevaFicha (tTablero tablero);
int log2 (int num);
void visualiza (const tTablero tablero, int puntos, int totalPuntos);
void visualiza (const tTablero tablero, int fila);
void bordeSuperior();
void bordeInferior();
void bordeInter();
bool carga (tTablero tablero, int &puntos);
void guarda (const tTablero tablero, int puntos);
tOpcion menu();
bool mueveFichas (tTablero tablero, tDireccion direccion);
void obtenerCoordMov (tDireccion dir, int ind, tCoord &ini, tCoord &incr);
int mayor(const tTablero tablero);
bool lleno (const tTablero tablero);
tResultado mueveFichas (tTablero tablero, tDireccion direccion, int &puntos, int &total);
bool sumaProximas (const tTablero tablero);

#endif 