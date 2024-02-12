
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
// num de oro
lli descendente(vector<pair<int,int>>const& cofres, vector<vector<lli>>& almacen, int i, int j) {

	if (i <0 || j <0) {
		return -1;
	}
	else if (almacen[i][j]!=-1) {
		return almacen[i][j];
	}
	else {
		lli no_coger = descendente(cofres, almacen, i - 1, j);
		lli coger = descendente(cofres, almacen, i - 1, j - (3 * cofres[i - 1].first));
		
		if (coger==-1) {
			almacen[i][j] = no_coger;
		}
		else {
			
			coger += cofres[i - 1].second;
			almacen[i][j] = max(coger, no_coger);
		}
		return almacen[i][j];
	}
}

void ascendente(vector<pair<int, int>>const& cofres, vector<vector<lli>>& almacen) {
	int coger;
	int no_coger;

	for (int i = 1; i < almacen.size(); i++) {
		for (int j = 1; j < almacen[0].size(); j++) {
			if (j < 3 * cofres[i-1].first) {
				almacen[i][j] = almacen[i - 1][j];
			}
			else {
				almacen[i][j] = max(almacen[i - 1][j], almacen[i - 1][j-3*cofres[i-1].first]+ cofres[i-1].second);
			}
		}
	}




}

bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	int numC;
	cin >> numC;
	vector<pair<int, int>>cofres(numC);// profundidad y valor
	for (auto &x : cofres) {
		cin >> x.first >> x.second;
	}

	vector<vector<lli>>almacen(numC + 1, vector<lli>(entrada + 1, -1 ));

	for (lli& x : almacen[0])
		x = 0;
	for (auto &x : almacen) {
		x[0] = 0;
	}
	//descendente(cofres, almacen, numC, entrada);
	ascendente(cofres, almacen);
	int i = numC;
	int j = entrada;
	vector<int>sol;
	while (i>0 && j>0 ) {
		if (almacen[i][j]!= almacen[i-1][j]) {
			j -= 3 * cofres[i - 1].first;
			sol.push_back(i-1);
		}
		i--;
	}
	cout << almacen[numC][entrada]<< "\n" << sol.size()<< "\n";

	for (int i = sol.size() - 1; i >= 0; i--) {
		cout << cofres[sol[i]].first << " " << cofres[sol[i]].second << "\n";
	}



	cout << "---\n";

	return true;
}



