#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

// Introduce más librerías si son necesarias
using namespace std;

const vector<vector<char>>TABLA_MULT = { {'b','b','a'},{'c','b','a'},{'a','c','c'} };



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
	bool explorado;
	bool letra_esta[3] ;

	tDatos():explorado(false){
		for (int i = 0; i < 3; i++) {
			letra_esta[i] = false;
		}
	}

};


void conseguir_letras(vector<vector<tDatos>>& almacen,int i , int j ,int k ) {

	for (int l = 0; l < TABLA_MULT.size(); l++) {// si la letra a, b o c esta mira si se puede combinar con algunos de la columna
		if (!almacen[i][k].letra_esta[l])
			continue;
		for (int m = 0; m < TABLA_MULT[0].size(); m++) {
			if (almacen[k + 1][j].letra_esta[m]) {
				almacen[i][j].letra_esta[TABLA_MULT[l][m] - 'a'] = true;
			}
		}
	}


}

void ascendente(string const& palabra, vector<vector<tDatos>>& almacen) {
	int n = palabra.size();
	for (int d = 1; d < n; d++) {
		for (int i = 0; i < n - d; i++) {
			int j = d + i;
			for (int k = i ; k < j; k++) {
				conseguir_letras(almacen, i, j, k);
			}
		}
	}



}

void descendente(string const& palabra, vector<vector<tDatos>>& almacen,int i ,int j) {
	tDatos& it = almacen[i][j];

	if (!it.explorado) {
		if (i + 1 == j)
			it.letra_esta[TABLA_MULT[palabra[i]-'a'][palabra[j]-'a']-'a'] = true;
		else {
			for (int k = i; k < j; k++) {
				descendente(palabra, almacen, i, k);
				descendente(palabra, almacen, k + 1, j);
				conseguir_letras(almacen, i, j, k);
			}
		}
		it.explorado = true;
	}



}




bool resuelveCaso() {
	string entrada;
	cin >> entrada;
	if (!cin)
		return false;
	vector<vector<tDatos>>almacen(entrada.size(), vector<tDatos>(entrada.size()));
	for (int i = 0; i < entrada.size(); i++) {
		almacen[i][i].explorado = true;
		almacen[i][i].letra_esta[entrada[i] - 'a'] = true;
	}

	//ascendente(entrada, almacen);
	descendente(entrada, almacen, 0, entrada.size() - 1);

	if (almacen[0][entrada.size() - 1].letra_esta[0]) {
		cout << "SI\n";

	}
	else {
		cout << "NO\n";
	}


	return true;
}