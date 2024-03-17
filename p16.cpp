#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
// Introduce más librerías si son necesarias
using namespace std;
void resuelveCaso();

// como representar la solucion 


int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::ofstream out("datos.out");
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}

struct Nodo {
	int coste_actual;
	int coste_optimo;
	int coste_pesimo;
	int k;
	vector<int>visit;
	
	Nodo(int tam,int ca=0, int co=INT_MAX, int cp=0, int _k=-1) :coste_actual(ca), coste_optimo(co), coste_pesimo(cp), k(_k), visit(tam,0) {

	}
	Nodo(int ca, int co, int cp, int _k, vector<int>v) :coste_actual(ca), coste_optimo(co), coste_pesimo(cp), k(_k), visit(v) {

	}

	bool operator<(const Nodo other)const {
		if (coste_optimo != other.coste_optimo)
			return coste_optimo > other.coste_optimo;
		return k < other.k;
	}

};

int coste_min_optimo_pesimo(vector<vector<int>>const &datos) {
	int n=datos.size();
	if (n == 0)
		return 0;
	int num_prod = datos[0].size();
	// k es numero de productos 
	int ans = 0;
	vector<int>coste_pesimo(num_prod+1,0);
	vector<int>coste_optimo(num_prod+1,INT_MAX);
	coste_optimo[num_prod] = 0;
	
	for (int i = num_prod - 1; i >= 0; i--) {
		for (int j = datos.size() - 1; j >= 0; j--) {
			coste_optimo[i] = min(coste_optimo[i], datos[j][i]);
			coste_pesimo[i] = max(coste_pesimo[i], datos[j][i]);
		}
		coste_optimo[i] += coste_optimo[i + 1];
		coste_pesimo[i] += coste_pesimo[i + 1];
		ans += datos[i%n][i];
	}
	
	
	priority_queue<Nodo>q;
	q.push(Nodo(n, 0, coste_optimo[0], coste_pesimo[0],-1));
	int limite = ans;
	int k, ca, co, cp;
	while (!q.empty() && q.top().coste_optimo <= limite) {
		Nodo aux = q.top();
		q.pop();
		for (int i = 0; i < n; i++) {
			if (aux.visit[i] != 3) {
				k = aux.k + 1;
				ca = aux.coste_actual + datos[i][k];
				co = ca + coste_optimo[k+1];
				cp = ca + coste_pesimo[k+1];
				if (ans > co) {
					if (k == num_prod- 1) {
						ans = limite = ca;
					}
					else {
						aux.visit[i]++;
						q.push(Nodo(ca, co, cp, k, aux.visit));
						aux.visit[i]--;
						limite = min(limite, cp);
					}
				}
			}
		}

	}

	return ans;
}


// configuración, y escribiendo la respuesta
void resuelveCaso() {
	int nsuper, mproductos;
	cin >> nsuper >> mproductos;
	
	vector<vector<int>>datos(nsuper, vector<int>(mproductos));

	

	for (int i = 0; i < nsuper; i++) {
		for (int j = 0; j < mproductos;j++) {
			cin >> datos[i][j];
		}
			
	}
	int ans = coste_min_optimo_pesimo(datos);
	cout << ans<<"\n";
}
