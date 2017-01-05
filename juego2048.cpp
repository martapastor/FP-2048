#include "juego2048.h"

void inicializa (tTablero tablero) {
	for (int f = 0; f < DIM; f++) {
		for (int c = 0; c < DIM; c++) tablero[f][c] = 1;
	}

	int fila, columna;
	fila = rand() % DIM;
	columna = rand() % DIM;
	tablero[fila][columna] = 2;

	nuevaFicha(tablero);
}

void nuevaFicha (tTablero tablero) {
	int fila, columna;
	fila = rand() % DIM;
	columna = rand() % DIM;

	int prob = rand() % PROBABILIDAD;

	while (tablero[fila][columna] != 1) {
		fila = rand() % DIM;
		columna = rand() % DIM;
	}

	if (prob < PROBABILIDAD) tablero[fila][columna] = 2;
	else tablero[fila][columna] = 4;
}

int log2 (int num) {
	int exponente = 0;

	while (num > 1) {
		num = num/2;
		exponente++;	
	}

	return exponente;
}

void visualiza (const tTablero tablero, int puntos, int totalPuntos) {
	cout << "Jugadas: " << puntos << "  Total: " << totalPuntos << "  Meta: " << META << endl;

	bordeSuperior();

	for (int fila = 0; fila < DIM; fila++) {
		visualiza (tablero, fila);
		if (fila < DIM - 1) bordeInter();
	}
	
	bordeInferior();
}

void visualiza (const tTablero tablero, int fila) {
	backgroundTextAtt(0);
	for (int i = 0; i < 3; i++) {
		cout << char(179);
		for (int columna = 0; columna < DIM; columna++) {
			if (tablero[fila][columna] == 1) cout << "      ";
			else {
				backgroundTextAtt(log2(tablero[fila][columna]));
				if (i == 1) cout << setw(5) << tablero[fila][columna] << " ";
				else cout << "      ";
				backgroundTextAtt(0);
			}
			cout << char(179);
		}
		cout << endl;
	}
}

void bordeSuperior() {
	backgroundTextAtt(0);
	cout << char(218);
	for (int i = 1; i < DIM; i++) {
		cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(194);
	}
	cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(191) << endl;
}

void bordeInferior() {
	backgroundTextAtt(0);
	cout << char(192);
	for (int i = 1; i < DIM; i++) {
		cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(193);
	}
	cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(217) << endl;
}

void bordeInter() {
	backgroundTextAtt(0);
	cout << char(195);
	for (int i = 1; i < DIM; i++) {
		cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(197);
	}
	cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(180) << endl;	
}

bool carga (tTablero tablero, int &puntos) {
	bool cargaRealizada;
	string archivo;
	ifstream partida;
	cout << "Introduce el nombre del archivo que deseas cargar: ";
	cin >> archivo;

	partida.open(archivo);

	if (!partida.is_open()) {
		inicializa(tablero);
		puntos = 0;
		cargaRealizada = false;
	}
	else {
		int nuevaMeta, nuevaDim;
		partida >> nuevaMeta;
		partida >> nuevaDim;

		if (nuevaMeta == META && nuevaDim == DIM) {
			for (int f = 0; f < DIM; f++) { //f = fila
				for(int c = 0; c < DIM; c++) { //c = columna
					partida >> tablero[f][c];
				}
			}
			partida >> puntos;
			cargaRealizada = true;
		}
		else inicializa(tablero);
	}
	partida.close();

	return cargaRealizada;
}

void guarda (const tTablero tablero, int puntos) {
	string archivo;
	cout << "Introduce el nombre con el que quieres guardar tu partida: ";
	cin >> archivo;

	ofstream partida;
	partida.open(archivo);

	if (!partida.is_open()) cout << "Error: no ha podido guardarse su partida.";

	else {
		partida << META << '\t' << DIM << endl;
		for (int f = 0; f < DIM; f++) { //f = fila
			for(int c = 0; c < DIM; c++) { //c = columna
				partida << tablero[f][c] << endl;
			}
		}
	}
	partida << puntos;

	partida.close();
}

tOpcion menu() {
	tOpcion opcion;
	cout << "Usa las flechas (ESC para salir)..." << endl;

	int tecla = getKey();
	
	while (tecla != TE_Salir && tecla != TE_Arriba && tecla != TE_Abajo && tecla != TE_Derecha && tecla != TE_Izquierda)
		tecla = getKey();

	if (tecla == TE_Salir) opcion = OP_Salir;
	else if (tecla == TE_Arriba) opcion = OP_Arriba;
	else if (tecla == TE_Abajo) opcion = OP_Abajo;
	else if (tecla == TE_Derecha) opcion = OP_Derecha;
	else if (tecla == TE_Izquierda) opcion = OP_Izquierda;

	return opcion;
}

bool mueveFichas (tTablero tablero, tDireccion direccion) { //IMPORTANTE: HACER QUE SOLO APAREZCA NÚMERO ALEATORIO SI mueveFichas == true
	bool movimientoRealizado = false;
	bool encontrado;

	tCoord ini, incr;
	for(int ind = 0; ind < DIM; ind++) {
		obtenerCoordMov (direccion, ind, ini, incr);
		for (int f = ini.x, c = ini.y; f < DIM && f >= 0 && c < DIM && c >= 0; f += incr.x, c += incr.y) {
			encontrado = false;
			if (tablero[f][c] == 1) {
				for(int ff = f + incr.x, cc = c + incr.y; ff < DIM && ff >= 0 && cc < DIM && cc >= 0 && !encontrado; ff += incr.x, cc += incr.y) {
					if (tablero[ff][cc] != 1) {
						encontrado = true;
						movimientoRealizado = true;
						tablero[f][c] = tablero[ff][cc];
						tablero[ff][cc] = 1;
					}
				}
			}
		}
	}

	return movimientoRealizado;
}

void obtenerCoordMov (tDireccion dir, int ind, tCoord &ini, tCoord &incr) {
	if (dir == Arriba) {
		ini.x = 0;
		ini.y = ind;
		incr.x = 1;
		incr.y = 0;
	}

	else if (dir == Abajo) {
		ini.x = DIM - 1;
		ini.y = ind;
		incr.x = -1,
		incr.y = 0;
	}

	else if (dir == Derecha) {
		ini.x = ind;
		ini.y = DIM - 1;
		incr.x = 0;
		incr.y = -1;
	}

	else if (dir == Izquierda) {
		ini.x = ind;
		ini.y = 0;
		incr.x = 0;
		incr.y = 1;
	}	
}

int mayor(const tTablero tablero) {
	int numMayor = 0;
	for (int f = 0; f < DIM; f++) {
		for (int c = 0; c < DIM; c++)
			if (numMayor < tablero[f][c]) numMayor = tablero[f][c];
	}
	return numMayor;
}

bool lleno (const tTablero tablero) {
	bool tableroLleno = true;
	for (int f = 0; f < DIM; f++) {
		for (int c = 0; c < DIM; c++)
			if (tablero[f][c] == 1) tableroLleno = false;
	}
	return tableroLleno;
}

tResultado mueveFichas (tTablero tablero, tDireccion direccion, int &puntos, int &total) {
	tResultado resultado = Jugando;
	tCoord ini, incr;

	int maximo, ff, cc;
	puntos = 0;

	for (int ind = 0; ind < DIM; ind++) {
		maximo = 1; 
		obtenerCoordMov (direccion, ind, ini, incr);
		ff = ini.x; cc = ini.y; //ff y cc corresponden a las coordenadas de la nueva celda distinta de tablero[f][c], y así sucesivamente: fff, ccc...

		for (int f = ini.x, c = ini.y; f < DIM && f >= 0 && c < DIM && c >= 0; f += incr.x, c += incr.y) {
			if (tablero[f][c] == maximo && maximo != 1) {
				tablero[ff][cc] = 2 * maximo;
				tablero[f][c] = 1;
				puntos += 2 * maximo;
				ff = f; cc = c; maximo = 1; f -= incr.x; c -= incr.y;
			}

			else {
				maximo = tablero[f][c];
				ff = f; cc = c;
			}
			mueveFichas (tablero, direccion);
		}
	}

	total += puntos;

	if (mayor(tablero) >= META) resultado = Gana;
	if(lleno(tablero) && !sumaProximas(tablero)) resultado = Pierde;
	
	return resultado;
}

bool sumaProximas (const tTablero tablero) {
	bool suma = false;

	int cont;
	for (int f = 0; f < DIM; f++) {
		cont = 0;
		for (int c = 1; c < DIM; c++) {
			if (tablero[f][cont] == tablero[f][c]) suma = true;
			else cont++;
		}
	}

	for(int c = 0; c < DIM; c++) {
		cont = 0;
		for (int f = 1; f < DIM; f++) {
			if (tablero[cont][c] == tablero[f][c]) suma = true;
			else cont++;
		}
	}

	return suma;
}
