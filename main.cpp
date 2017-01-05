/* Práctica 3 versión 1.0
Juego 2048
Por Marta Pastor Puente y Ángela Martínez Ros */

#include "juego2048.h"
#include "utilsWin.h"
using namespace std;

void pausa();

int main() {
	srand (time(NULL)); //Inicio el generador de números aleatorios
	tTablero tablero;
	tResultado resultado = Jugando;
	int puntos = 0, total = 0;
	//tJuego2048 juego;

	clearConsole();
	fontConsole(true);
	cpConsoleOut(1252);
	backgroundTextAtt(0);

	char opcion;
	bool cargarPartida;
	cout << "¿Quieres cargar una partida? [S/N] : ";
	cin >> opcion;

	while (opcion != 'S' && opcion != 'N') {
		cout << "Error: respuesta no válida. Por favor, introduzca una respuesta correcta: ";
		cin >> opcion;
	}

	if (opcion == 'S') cargarPartida = carga(tablero, puntos);
	else if (opcion == 'N') inicializa(tablero);

	clearConsole();
	cpConsoleOut(850);
	visualiza(tablero, puntos, total); // FALTAN POR VISUALIZAR LOS puntos Y EL total

	tOpcion menuSeleccion = menu();
	bool moverFichas;
	
	while(menuSeleccion != OP_Salir && resultado == Jugando) {
		if (menuSeleccion == OP_Arriba) {
			if (mueveFichas (tablero, Arriba)) {
				resultado = mueveFichas (tablero, Arriba, puntos, total);
				nuevaFicha(tablero);
			}
			else {
				resultado = mueveFichas (tablero, Arriba, puntos, total);
				if (puntos != 0) nuevaFicha(tablero);
			}
		}

		else if (menuSeleccion == OP_Abajo) {
			if(mueveFichas (tablero, Abajo)) {
				resultado = mueveFichas (tablero, Abajo, puntos, total);
				nuevaFicha(tablero);
			}
			else {
				resultado = mueveFichas (tablero, Abajo, puntos, total);
				if (puntos != 0) nuevaFicha(tablero);
			}
		}

		else if (menuSeleccion == OP_Derecha) {
			if(mueveFichas (tablero, Derecha)) {
			resultado = mueveFichas (tablero, Derecha, puntos, total);		
			nuevaFicha(tablero);
			}
			else {
				resultado = mueveFichas (tablero, Derecha, puntos, total);
				if (puntos != 0) nuevaFicha(tablero);
			}
		}

		else if (menuSeleccion == OP_Izquierda) {
			if (mueveFichas (tablero, Izquierda)) {
				resultado = mueveFichas (tablero, Izquierda, puntos, total);		
				nuevaFicha(tablero);
			}
			else {
				resultado = mueveFichas (tablero, Izquierda, puntos, total);
				if (puntos != 0) nuevaFicha(tablero);
			}
		}
		
		clearConsole();
		visualiza (tablero, puntos, total); // FALTAN POR VISUALIZAR LOS puntos Y EL total
		if (resultado == Jugando) menuSeleccion = menu();
	}

	cpConsoleOut(1252);
	if (resultado == Jugando) {
		char opcGuardar;
		cout << "¿Quieres guardar partida? [S/N] : ";
		cin >> opcGuardar;

		while (opcGuardar != 'S' && opcGuardar != 'N') {
			cout << "Error: respuesta no válida. Por favor, introduzca una respuesta correcta: ";
			cin >> opcGuardar;
		}

		if (opcGuardar == 'S') guarda (tablero, puntos);
		else if (opcGuardar == 'N') cout << "\n¡Gracias por jugar!" << endl;
	}
	else if (resultado == Gana) cout << "¡Enhorabuena, has ganado!" << endl;
	else if(resultado == Pierde) cout << "Lo siento, has perdido..." << endl;
	cout << endl;
	
	cout << "¡Hasta pronto!" << endl;
	pausa();

	return 0;
}

void pausa() { 
	cin.clear();
	cin.sync();
	cin.get();
}
