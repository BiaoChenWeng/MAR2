
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <unordered_map>
// Introduce más librerías si son necesarias
using namespace std;
class tGrafo {
	int V;
	int A;
	vector<vector<pair<int, int>>>ady;// coste y valor
public:
	tGrafo(int v = 0) :V(v), A(0), ady(v) {}

	void ponArista(int v, int w, int coste) {
		if (v < 0 || v >= V || w < 0 || w >= V)
			throw std::domain_error("Vertice inexistente");
		++A;
		ady[v].push_back({ coste,w });
		ady[w].push_back({ coste,v });

	}
	vector<pair<int, int>> const& getAdy(int v) const {
		if (v < 0 || v >= V)
			throw std::domain_error("Vertice inexistente");
		return ady[v];
	}
	int getA()const {
		return A;
	}
	int getV()const {
		return V;
	}
};

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


void reconstruir(string const& a, string const& b, int ia, int ib, vector<vector<int>>const& almacen, string& sol) {

	if (ia < a.size() && ib < b.size()) {
		if (almacen[ia][ib] == 0)
			return;
		int i = ia;
		int j = ib;

		if (a[ia] == b[ib]) {
			sol.push_back(a[ia]);
			i++;
			j++;
			
		}
		else {
			if (ia + 1 < a.size() && ib+1 < b.size()) {
				if (almacen[ia][ib + 1] > almacen[ia + 1][ib]) {
					j++;
				}
				else {
					i++;
				}
			}
			else {
				if (ia + 1 == a.size()) {
					j++;
				}
				else {
					i++;
				}
			}
			
		}
		reconstruir(a, b, i, j, almacen, sol);
	}



}


int descendente(string const& a, string const& b, int ia, int ib, vector<vector<int>>& almacen) {

	if (ia >= a.size() || ib >= b.size()) {
		return 0;
	}
	else if (almacen[ia][ib] != -1) {
		return almacen[ia][ib];
	}
	else {
		if (a[ia] == b[ib]) {
			almacen[ia][ib] = 1 + descendente(a, b, ia + 1, ib + 1, almacen);
		}
		else {
			almacen[ia][ib] = max(descendente(a, b, ia + 1, ib, almacen), descendente(a, b, ia, ib + 1, almacen));
		}
		return almacen[ia][ib];
	}


}




bool resuelveCaso() {
	string a, b;
	cin >> a >> b;
	if (!cin)
		return false;

	vector<vector<int>>almacen(a.size(), vector<int>(b.size(), -1));
	descendente(a, b, 0, 0,almacen);
	string ans;
	reconstruir(a, b, 0, 0, almacen, ans);
	cout << ans << "\n";
	return true;
}



