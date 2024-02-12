#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

// Introduce más librerías si son necesarias
using namespace std;
using lli = long long int;

const lli MAX_VALUE =LLONG_MAX;
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



void ascendente(vector<int>const& pot, vector<int>const& coste,int pmax) {
	vector<vector<lli>>almacen(pot.size()+1, vector<int>(pmax+1, MAX_VALUE));
	for (int j = 0; j < pot.size() + 1; j++) {
		almacen[j][0] = 0;
	}
	int coger;
	int no_coger;
	for (int i = 1; i < coste.size()+1; i++) {
		for (int j = 1; j < pmax + 1; j++) {
			if (j >= pot[i - 1] && almacen[i][j-pot[i-1]!= MAX_VALUE]) {
				almacen[i][j] = min(almacen[i - 1][j], almacen[i][j - pot[i - 1] + coste[i - 1]);
			}
			else {
				almacen[i][j] = almacen[i - 1][j];
			}
		}
	}



}

lli descendente(vector<lli>&almacen,vector<int>const &pot, vector<int>const &coste,int k) {
	if (k <= 0)
		return MAX_VALUE;
	else if (almacen[k] != MAX_VALUE)
		return almacen[k];
	else {
		lli coste_min=MAX_VALUE;
		for (int i = 0; i < pot.size(); i++) {
			if (k == pot[i] && almacen[k] > coste[i])
				almacen[k] = coste[i];
			else {
				coste_min = descendente(almacen, pot, coste, k - pot[i]);
				if (coste_min != MAX_VALUE && almacen[k] > coste_min + coste[i]) {
					almacen[k] = coste_min + coste[i];
				}
			}
		}
		return almacen[k];
	}
}

void descendente_sol(int pmin, int pmax, vector<int>const& pot, vector<int>const& coste) {
	vector<lli>almacen(pmax + 1, MAX_VALUE);
	lli aux;
	for (int i = pmin; i <= pmax; i++) {
		if (almacen[i] == MAX_VALUE)
			descendente(almacen, potencia, coste, i);
		if (ans.first > almacen[i]) {
			ans.first = almacen[i];
			ans.second = i;
		}
	}


	//auto ans = ascendente(almacen, potencia, coste, pmin);
	if (ans.first != MAX_VALUE)
		cout << ans.first << " " << ans.second << "\n";
	else
		cout << "IMPOSIBLE\n";
}


bool resuelveCaso() {
	int entrada;
	int pmax, pmin;
	cin >> entrada>>pmax>>pmin;
	if (!cin)
		return false;
	
	// coste potencia
	vector<int>potencia(entrada);
	vector<int>coste(entrada);
	for (int& k : potencia)
		cin >> k;
	for (int& k : coste)
		cin >> k;
	pair<lli, int>ans = {MAX_VALUE,-1};


	
	return true;
}