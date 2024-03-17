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

void ascendente(vector<vector<lli>>& almacen,  vector<pair<int, int>>const& monedas) {
	
	lli minimo;
	for (int i = 1; i < almacen.size() ; i++)
		for (int j = 1; j < almacen[0].size() ; ++j) {
			minimo = MAX_VALUE;
			for (int k = 0; k <= monedas[i - 1].second && (k * monedas[i - 1].first)<=j; k++) {// numero de veces que uso la moneda i
		
				if(almacen[i-1][j - monedas[i - 1].first * k]!=MAX_VALUE)
					minimo = min(minimo, k + almacen[i-1][j - monedas[i - 1].first * k]);
			}
			almacen[i][j] = minimo;
		}


}
// esto no funciona 
lli descendente(vector<vector<lli>>& almacen, int i, int j, vector<pair<int, int>>const& monedas, int k) {
	if (i <= 0 || j < 0 || monedas[i - 1].second < k) {
		return MAX_VALUE;
	}
	else if (almacen[i][j] != MAX_VALUE) {
		return almacen[i][j];
	}
	else {

		

		lli coger = descendente(almacen, i, j - monedas[i - 1].first, monedas, k + 1);
		lli no_coger = descendente(almacen, i - 1, j, monedas, 0);
		if (coger == MAX_VALUE)
			almacen[i][j] = no_coger;
		else {

			almacen[i][j] = min(coger + 1, no_coger);
		}
		return almacen[i][j];
	}


}


bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	vector<pair<int, int>>monedas(entrada);// valor, cantidad
	for (int i = 0; i < entrada; i++) {
		cin >> monedas[i].first;
	}
	for (int i = 0; i < entrada; i++) {
		cin >> monedas[i].second;
	}
	int obj;
	cin >> obj;
	vector<vector<lli>>almacen(entrada + 1, vector<lli>(obj + 1, MAX_VALUE));
	for (auto& x : almacen)
		x[0] = 0;
	
	//vector<lli>almacen(obj + 1, MAX_VALUE);
	
	//almacen[0] = 0;
	lli ans;
	ascendente(almacen, monedas);
	ans = almacen[entrada ][obj];
	//ans = descendente(almacen, entrada-1, obj, monedas, 0);

	if (ans == MAX_VALUE)
		cout << "NO\n";
	else
		cout << "SI " << ans << "\n";

	return true;
}