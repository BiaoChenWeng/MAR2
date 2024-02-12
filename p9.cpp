
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
// Introduce más librerías si son necesarias
using namespace std;


bool resuelveCaso();
int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	/*std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf())*/;
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}


int descendente(vector<vector<int>>& almacen, vector<int>const& cortes,int i ,int j ) {
	if (j - i < 2) {
		return almacen[i][j] = 0;
	}
	else if(almacen[i][j]!= -1) {
		return almacen[i][j];
	}
	else {
		int izq;
		int der;
		int minimo = INT_MAX;
		for (int k = i + 1; k < j; k++) {
			minimo = min(minimo, descendente(almacen, cortes, i, k) + descendente(almacen, cortes, k, j));
		}

		return almacen[i][j] = minimo + 2 * (cortes[j] - cortes[i]);

	}
}

void ascendente(vector<vector<int>>& matriz,vector<int>const &cortes) {
	int n = matriz.size();
	for (int d = 2; d < n ; d++) {
		for (int i = 0; i < n - d; i++) {
			int j = d + i;
			int minimo = INT_MAX;
			for (int k = i+1; k < j; k++) {
				minimo = min(minimo, matriz[i][k] + matriz[k][j]);
			}
			matriz[i][j] = minimo + 2 * (cortes[j]-cortes[i]);
		}

	}

}


bool resuelveCaso() {
	int entrada, num_corte;
	cin >> entrada >> num_corte;
	if (entrada == 0 && num_corte == 0)
		return false;
	vector<int>cortes(num_corte + 2, 0);
	for (int i = 0; i < num_corte; i++)
		cin >> cortes[i + 1];
	cortes[num_corte + 1] = entrada;
	
	vector<vector<int>>matriz(num_corte + 2, vector<int>(num_corte + 2, -1));// matriz inicial de descendente
	descendente(matriz, cortes, 0, num_corte + 1);
	//vector<vector<int>>matriz(num_corte + 2, vector<int>(num_corte + 2, 0)); // esto es la matriz inicial de ascendente
	//ascendente(matriz, cortes);
	cout << matriz[0][num_corte + 1]<<"\n";

	


	return true;
}