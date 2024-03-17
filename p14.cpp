
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <queue>
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


struct Nodo {
	vector<bool>disponibles;
	int ult_trabajador;
	int coste_real;
	int coste_optimo;
	int coste_pesimista;
	Nodo(int tam):disponibles(tam,true),coste_real(0),ult_trabajador(-1),coste_optimo(0),coste_pesimista(INT_MAX){

	}

	bool operator<(Nodo const other) const {
		if(this->coste_optimo != other.coste_optimo)
			return this->coste_optimo > other.coste_optimo;
		return ult_trabajador < other.ult_trabajador;
	}
};





int repartir_trabajo(vector<vector<int>>const & datos) {
	int n = datos.size();
	priority_queue<Nodo>q;
	int ans=0;
	vector<int>coste_pesimo(n+1,0);
	vector<int>coste_optimo(n+1, INT_MAX);
	coste_optimo[n] = 0;
	for (int i = n-1; i >=0; i--) {// i trabajador
		for (int j = 0; j < datos.size(); j++) {//j tareas
			coste_optimo[i] = min(coste_optimo[i], datos[i][j]);
			coste_pesimo[i] = max(coste_pesimo[i], datos[i][j]);
		}
		coste_pesimo[i] += coste_pesimo[i + 1];
		coste_optimo[i] += coste_optimo[i + 1];
		ans += datos[i][i];
	}
	
	q.push(Nodo(n));
	int limite= ans;
	while (!q.empty() && limite > q.top().coste_optimo) {
		Nodo aux = q.top();
		q.pop();
		
		
		for (int i = 0; i < n; i++) {
			if (aux.disponibles[i]) {
				Nodo hijo(aux);
				hijo.disponibles[i] = false;
				hijo.ult_trabajador++;
				hijo.coste_real += datos[hijo.ult_trabajador][i];
				hijo.coste_optimo = hijo.coste_real+coste_optimo[hijo.ult_trabajador+1];
				hijo.coste_pesimista = hijo.coste_real+coste_pesimo[hijo.ult_trabajador+1];

				if (hijo.coste_optimo < ans) {
					if (hijo.ult_trabajador == n - 1) {
						ans = limite = hijo.coste_real;
					}
					else {
						q.push(hijo);
						limite = min(limite, hijo.coste_pesimista);
					}
				}
			}
		}
	}

	return ans;
}


bool resuelveCaso() {

	int entrada;
	cin >> entrada;
	if (entrada==0)
		return false;

	
	
	vector<vector<int>>v(entrada,vector<int>(entrada));

	
	
	for (int i = 0; i < entrada;i++) {
		for (int j = 0; j < entrada;j++) {
			cin >> v[i][j];
			
			
		}
			
	}

	int ans = repartir_trabajo(v);
	cout << ans<< "\n";
	return true;
}



