
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
	vector<vector<int>>ady;// coste y valor
public:
	tGrafo(int v = 0) :V(v), A(0), ady(v) {}

	void ponArista(int v, int w) {
		if (v < 0 || v >= V || w < 0 || w >= V)
			throw std::domain_error("Vertice inexistente");
		++A;
		ady[v].push_back({ w });
		ady[w].push_back({ v });

	}
	vector<int> const& getAdy(int v) const {
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





void Floyd(vector<vector<int>>&almacen) {
	int V = almacen.size();

	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (almacen[i][k] != INT_MAX && almacen[k][j] != INT_MAX) {
					almacen[i][j] = min(almacen[i][j], almacen[i][k] + almacen[k][j]);
				}
				
			}
			
		}
	}



}



bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	int arista;
	cin >> arista;
	tGrafo grafo(entrada);
	unordered_map<string, int>m;
	string a, b;
	int count=0;
	for (int i = 0; i < arista; i++) {
		cin >> a >> b;
		auto it = m.insert({a,count});
		if (it.second)
			count++;
		auto it2 = m.insert({ b,count });
		if (it2.second)
			count++;
		grafo.ponArista(m[a], m[b]);
	}


	vector<vector<int>>almacen(entrada,vector<int>(entrada,INT_MAX));
	for (int i = 0; i < entrada; i++) {
		for (auto x : grafo.getAdy(i)) {

			almacen[i][x] = 1;
		}
		almacen[i][i] = 0;
	}
	Floyd( almacen);

	bool ans = true;
	int sep=0;
	for (int i = 0; i < entrada; i++) {
		for (int j = 0; j < entrada; j++) {
			if (almacen[i][j] == INT_MAX) {
				ans = false;
				break;
			}
			sep = max(sep, almacen[i][j]);
		}
	}

	if (ans)
		cout << sep << "\n";
	else
		cout << "DESCONECTADA\n";

	return true;
}



