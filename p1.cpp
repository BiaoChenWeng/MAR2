#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>
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

struct tDatos {
	lli combinacion;
	lli cuerda_min;
	lli coste_min;

	tDatos(lli c = 0, lli lm = MAX_VALUE, lli cm = MAX_VALUE) :combinacion(c), cuerda_min(lm), coste_min(cm) {}
};


tDatos ascendete(vector<pair<lli, lli>>const& cuerdas, vector<tDatos>& almacen) {

	for (int j = 0; j < cuerdas.size(); j++) {
		for (int i = almacen.size()-1; i >= cuerdas[j].first; i--) {

			tDatos& aux = almacen[i - cuerdas[j].first];
			almacen[i].combinacion += aux.combinacion;
			if (aux.cuerda_min !=MAX_VALUE) {
				almacen[i].coste_min = min(aux.coste_min + cuerdas[j].second, almacen[i].coste_min);
				almacen[i].cuerda_min = min(aux.cuerda_min + 1, almacen[i].cuerda_min);
			}

		}
	}
	return almacen[almacen.size() - 1];
}


tDatos descendente(vector<pair<lli, lli>>const& cuerdas, vector<tDatos>& almacen, int k, int valor_inicial) {
	if (k <= 0 || valor_inicial < 0) {
		return { 0,MAX_VALUE ,MAX_VALUE };
	}
	else if (almacen[k].combinacion != 0) {
		return almacen[k];
	}
	else {
		tDatos aux;
		for (int i = valor_inicial; i >= 0; i--) {
			if (cuerdas[i].first == k) {
				aux = { 1,0,0 };
			}
			else
				aux = descendente(cuerdas, almacen, k - cuerdas[i].first, i - 1);
			if (aux.combinacion != 0) {
				almacen[k].combinacion += aux.combinacion;
				if (almacen[k].coste_min > aux.coste_min + cuerdas[i].second) {
					almacen[k].coste_min = aux.coste_min + cuerdas[i].second;
				}
				if (almacen[k].cuerda_min > aux.cuerda_min + 1) {
					almacen[k].cuerda_min = aux.cuerda_min + 1;
				}
			}
		}
		return almacen[k];
	}

}

bool resuelveCaso() {
	int entrada;
	cin >> entrada;

	if (!cin)
		return false;
	int longitud;
	cin >> longitud;
	vector<pair<lli, lli>>cuerdas(entrada);// longitud coste
	vector<tDatos>almacen(longitud + 1);
	almacen[0] = { 1,0,0 };
	for (pair<lli, lli>& k : cuerdas) {
		cin >> k.first >> k.second;
	}
	
	vector<bool>visit(entrada, false);
	//ascendete(cuerdas, almacen);
	descendente(cuerdas, almacen, longitud, cuerdas.size()-1);
	
	if (almacen[longitud].combinacion == 0)
		cout << "NO\n";
	else {
		cout << "SI " << almacen[longitud].combinacion << " " << almacen[longitud].cuerda_min << " " << almacen[longitud].coste_min << "\n";
	}



	return true;
}

