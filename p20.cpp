#include<iostream>
#include"Matriz.h"
#include <fstream>
using namespace std;


//Plantea y explica la recurrencia
//Definicion
//Llamada inicial
//Caso/s base
//Casos recursivos

/*
Caso base almacen(0,0)=1
caso recursivo 
	almacen(i,j) =  sumatorio (0,i) + sumatorio(0,j) si en la posicion tablero[i'][j']=salto, si la suma de salto+ i  
	salto = tablero[i][j] // siendo salto+i o salto +j este en lo limite de la matriz

	alamacen(i, j) = sumatorio(de 0 hasta i)( almacen(i'+salto, j) + sumatorio(0,j)almacen(i, j' + salto))

	siendo 0<=i'<i y 0<=j'<j o dicho de otro manera el sumatorio de todas casillas de la izquierda y de arriba que puedan alcanzarte con un salto.


Llamada inicial (0,0) ya que empezamos desde la primera posicion de la matriz 

Explicación:
	El problema se resuelve desde la casilla 0,0 (inicial ) , el objetivo es llegar a la ultima casilla (n-1,m-1) siendo n el tamaño de las filas del tablero y m el número de columnas del tablero
	
	mirando la recurrencia , en el caso base , el unico movimiento que tenemos al inicio es estar en la posicion inicial, por lo tanto un 1 . 
	En los siguientes casos , tenemos el sumatorio de todos los movimientos que con un salto te lleve a la casilla deseada , sumandole el 
	numero de camino que va desde la casilla inicial a ese . 



*/




long long int numCaminos(Matriz<int> const& tablero, int N, int M) {

	//Resuelve el problema utilizando programacion dinamica ITERATIVA

	//Analiza justificadamente el coste en tiempo y espacio
	/*
	Coste en tiempo O(n*m) siendo n el tamaño de las filas del tablero y m el número de columnas del tablero 
	
	Coste en espacio O(n*m) siendo n el tamaño de las filas del tablero y m el número de columnas del tablero 
	Esto lo vemos en la matriz de almacen, que es donde guardamos los datos de iteracion.
	
	
	
	*/


	vector<vector<int>>almacen(tablero.numfils(), vector<int>(tablero.numcols(), 0));
	almacen[0][0] = 1;
	int salto;
	for (int i = 0; i < tablero.numfils(); i++)
	{
		for (int j = 0; j < tablero.numcols(); j++) {
			salto= tablero[i][j];
			if (tablero.posCorrecta(i+salto, j)) {
				almacen[i + salto][j]+= almacen[i][j];
			}
			if (tablero.posCorrecta(i, j+salto)) {
				almacen[i][j+salto]+=almacen[i][j];
			}
		}
	}

	return almacen[tablero.numfils() - 1][tablero.numcols() - 1];
}


bool resuelveCaso() {
	int N, M;
	cin >> N >> M;
	if (!cin) {
		return false;
	}
	else {
		Matriz<int> tablero(N, M);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
				cin >> tablero[i][j];
		}

		cout << numCaminos(tablero, N, M) << '\n';
		return true;
	}
}



int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}