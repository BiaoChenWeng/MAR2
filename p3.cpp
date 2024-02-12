#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include<algorithm>
#include <stack>

// Introduce más librerías si son necesarias
using namespace std;


bool resuelveCaso();

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::ofstream out("datos.out");
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
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

using lli = long long int;
struct tSol {
	lli maximo;
	int pos;
	tSol(lli m = -1, int p = -1) :pos(p), maximo(m) {}

};

lli buscar_max(const vector<vector<int>>& tablero, int i, int j) {
	int ans = tablero[i - 1][j];
	if (j - 1 >= 0 && tablero[i - 1][j - 1] > ans) {
		ans = tablero[i - 1][j - 1];
	}
	if (j + 1 < tablero.size() && tablero[i - 1][j + 1] > ans)
		ans = tablero[i - 1][j + 1];
	return ans;
}

tSol ascendente(vector<vector<int>>& tablero) {
	tSol ans;
	int n = tablero.size();
	for (int i = 1; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			tablero[i][j] += buscar_max(tablero, i, j);
		}
	}

	for (int i = 0; i < n; i++) {
		tablero[n - 1][i] += buscar_max(tablero, n - 1, i);
		if (tablero[n - 1][i] > ans.maximo) {
			ans.maximo = tablero[n - 1][i];
			ans.pos = i + 1;
		}
	}
	return ans;
}

int descendente(const vector<vector<int>>& tablero, vector<vector<int>>& almacen, int i, int j) {
	if (i == 0) {
		return almacen[i][j] = tablero[i][j];
	}
	else if (almacen[i][j] != -1)
		return almacen[i][j];
	else {
		int maximo = almacen[i - 1][j];
		int aux;
		if (maximo == -1)
			maximo = descendente(tablero, almacen, i - 1, j);
		if (j - 1 >= 0) {
			maximo = max(maximo, descendente(tablero, almacen, i - 1, j - 1));
		}
		if (j + 1 < almacen.size()) {
			maximo = max(maximo, descendente(tablero, almacen, i - 1, j + 1));
		}
		return almacen[i][j] = (tablero[i][j] + maximo);
	}

}

bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	vector<vector<int>>tablero(entrada, vector<int>(entrada));
	for (int i = 0; i < entrada; i++) {
		for (int& k : tablero[i]) {
			cin >> k;
		}
	}
	//descendente
	tSol ans;
	int aux;
	vector<vector<int>>almacen(entrada, vector<int>(entrada, -1));

	for (int i = 0; i < entrada; i++) {
		aux = descendente(tablero, almacen, entrada - 1, i);
		if (aux > ans.maximo) {
			ans.maximo = aux;
			ans.pos = i + 1;
		}
	}
	//ascendente
	/* ans = ascendente(tablero);*/
	cout << ans.maximo << " " << ans.pos << "\n";
	return true;
}