
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
// Introduce más librerías si son necesarias
using namespace std;

using lli = long long int;
const lli MAX_VALUE = LLONG_MAX;

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




lli descendente(vector<vector<lli>>& almacen, vector<lli>const& puntuacion, int i, int j) {
	if (i < 1 || j < 0) {
		return MAX_VALUE;
	}
	else if (almacen[i][j] != MAX_VALUE) {
		return almacen[i][j];
	}
	else {
		lli aux = descendente(almacen, puntuacion, i, j - puntuacion[i - 1]);
		lli ant = descendente(almacen, puntuacion, i - 1, j);
		if (aux == MAX_VALUE)
			almacen[i][j] = ant;
		else {
			almacen[i][j] = min(ant, aux + 1);
		}

		return almacen[i][j];
	}
}


void ascendente(vector<vector<lli>>& almacen, vector<lli>const& puntuacion) {

	for (int i = 1; i < almacen.size(); i++) {
		for (int j = 1; j < almacen[0].size(); j++) {
			if (puntuacion[i - 1] > j || almacen[i][j - puntuacion[i - 1]] == MAX_VALUE) {
				almacen[i][j] = almacen[i - 1][j];
			}
			else {
				almacen[i][j] = min(almacen[i - 1][j], 1 + almacen[i][j - puntuacion[i - 1]]);
			}
		}
	}
}


bool resuelveCaso() {
	int entrada;
	int sector;
	cin >> entrada >> sector;
	if (!std::cin)  // fin de la entrada
		return false;

	vector<vector<lli>>almacen(sector + 1, vector<lli>(entrada + 1, MAX_VALUE));

	for (int i = 0; i < almacen.size(); i++) {
		almacen[i][0] = 0;
	}
	vector<lli>puntuacion(sector);
	for (int i = 0; i < sector; i++) {
		cin >> puntuacion[i];
	}
	descendente(almacen, puntuacion, sector, entrada);
	//ascendente(almacen, puntuacion);

	if (almacen[sector][entrada] == MAX_VALUE) {
		cout << "Imposible\n";
	}
	else {
		cout << almacen[sector][entrada] << ":";
		pair<int, int>aux = { sector,entrada };
		while (aux.second > 0) {
			if (puntuacion[aux.first - 1] <= aux.second && almacen[aux.first][aux.second] != almacen[aux.first - 1][aux.second]) {
				aux.second -= puntuacion[aux.first - 1];
				cout << " " << puntuacion[aux.first - 1];
			}
			else {
				aux.first--;
			}




		}
		cout << "\n";
	}



	return true;
}



