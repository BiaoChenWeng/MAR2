
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


void reconstruir(string const& word, int i, int j, vector<vector<int>>& almacen, string& sol) {

	if (i == j) {
		return sol.push_back(word[i]);
	}
	else if (i < j) {
		int i_ = i, j_ = j;
		char x;
		if (word[i] == word[j]) {
			x = word[i];
			i_++;
			j_--;

		}
		else {
			if (almacen[i + 1][j] < almacen[i][j - 1]) {
				x = word[i];
				i_++;
			}
			else {
				x = word[j];
				j_--;
			}
		}
		sol.push_back(x);
		reconstruir(word, i_ , j_, almacen, sol);
		sol.push_back(x);
	}

}


int descendente(string const& word, int i, int j, vector<vector<int>>& almacen) {
	if (i == j || i > j) {
		return almacen[i][j] = 0;
	}
	else if (almacen[i][j] != -1) {
		return almacen[i][j];
	}
	else {
		if (word[i] == word[j]) {
			almacen[i][j] = descendente(word, i + 1, j - 1, almacen);
		}
		else {
			almacen[i][j] = min(descendente(word, i + 1, j, almacen), descendente(word, i, j - 1, almacen)) + 1;
		}

		return almacen[i][j];
	}

}




bool resuelveCaso() {
	string entrada;
	cin >> entrada;
	if (!cin)
		return false;
	vector<vector<int>>almacen(entrada.size(), vector<int>(entrada.size(), -1));
	int solucion = descendente(entrada, 0, entrada.size() - 1, almacen);
	string sol = "";
	reconstruir(entrada, 0, entrada.size() - 1, almacen, sol);

	cout << solucion << " " << sol << "\n";

	return true;
}



