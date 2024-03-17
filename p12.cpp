
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


void comer_gordo(pair<int,int>&a , vector<int>const & v) {// el gordo coge siempre el mayor de los dos
	if (v[a.first] > v[a.second]) {
		a.first++;
	}
	else {
		a.second--;
	}
}

int descendente(vector<vector<int>>& almacen, int i, int j,vector<int>const & datos) {
	if (i > j)// no queda cubos
		return 0;
	else if (i == j) {// queda un solo cubo 
		return almacen[i][j] = datos[i];
	}	
	else if(almacen[i][j]!=-1) {// memoria dinamica
		return almacen[i][j];
	}
	else {// en el enunciado nos asegura que no existen 2 cubos con el mismo valor
		pair<int, int> v_izq {i + 1, j};
		pair<int, int> v_der = {i,j-1};
		comer_gordo(v_izq, datos);
		comer_gordo(v_der, datos);

		int izq=descendente(almacen,v_izq.first,v_izq.second,datos)+datos[i];
		int der = descendente(almacen, v_der.first, v_der.second, datos)+datos[j];
		return almacen[i][j] = max(izq, der);
	}

}



bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (entrada==0)
		return false;

	vector<int>v(entrada);

	for (int& x : v)
		cin >> x;
	vector<vector<int>>almacen(entrada, vector<int>(entrada, -1));

	int ans = descendente(almacen, 0, entrada-1, v);
	cout << ans << "\n";
	return true;
}