#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

// Introduce más librerías si son necesarias
using namespace std;
void resuelveCaso();


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
	for (int i = 0; i < numCasos; i++) {
		resuelveCaso();
	}
	//while(resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}

// numero maximo de basura limpiada , numero de playas limpiada
struct Result {
	int numero_basura;
	int numero_playa_limpia;
	
	Result() :numero_basura(0), numero_playa_limpia(0) {}
	Result(int b, int p) :numero_basura(b), numero_playa_limpia(p) {}

	bool operator<(Result const& other)const {
		return this->numero_basura < other.numero_basura;
	}

	bool valido(int const &numero_minimo)const {
		return numero_playa_limpia >= numero_minimo;
	}

};
struct Nodo {
	vector<int>visit;
	Result coste_actual;
	Result coste_optimo;
	Result coste_pesimo;
	int _k;// persona en la que estoy 

	
	Nodo(vector<int>const& v, Result ca, Result co, Result cp, int k) :_k(k), visit(v), coste_actual(ca), coste_optimo(co), coste_pesimo(cp) {}
	Nodo():visit(0),coste_actual(Result()), coste_optimo(Result()), coste_pesimo(Result()), _k(0) {}
	bool operator<(Nodo const& other)const {
		return coste_optimo < other.coste_optimo;
	}
};

int num_playa_posible(int a, int b , int max_p) {
	if (b == 0) {
		return max_p;
	}
	return min(max_p, a / b);
}


Result limpiar_playa(const vector<vector<int>>& datos, vector<int>const& playas, const int& minimo_p) {

	int num_playa_total = playas.size();
	int playa_max = 1;
	int playa_min = INT_MAX;
	int playa_limpias = 0;
	int basura_total = 0;
	vector<int>estimacion_optima(datos.size() + 1, 0);
	vector<int>estimacion_pesima(datos.size() + 1, INT_MAX);
	estimacion_pesima[datos.size()] = 0;
	for (int i = playas.size() - 1; i >= 0; i--) {
		if (playas[i] == 0) {
			playa_limpias++;
		}
		else {
			basura_total += playas[i];
			playa_max = max(playa_max, playas[i]);// cogemos la playa con el mayor numero de basura
			playa_min = min(playa_min, playas[i]);// minimo 

		}
	}
	for (int i = datos.size() - 1; i >= 0; i--) {
		for (int j = datos[0].size() - 1; j >= 0; j--) {
			estimacion_optima[i] = max(estimacion_optima[i], datos[i][j]);
			estimacion_pesima[i] = min(estimacion_pesima[i], datos[i][j]);
		}
		estimacion_optima[i] += estimacion_optima[i + 1];// cada persona coge la playa con su mejor rendimiento
		estimacion_pesima[i] += estimacion_pesima[i + 1];
	}
	Result ans = { 0,playa_limpias };
	Result limite = ans;
	Result ca, co, cp;
	int k = -1;
	ca = ans;
	cp = { min(estimacion_pesima[0],basura_total),num_playa_posible(estimacion_pesima[0],playa_max,num_playa_total) + playa_limpias };// coste pesimo, suponemos que todo coge la minima cantidad de basura, todas la playas tiene el peor coste imaginable
	co = { estimacion_optima[0],num_playa_posible(estimacion_optima[0],playa_min,num_playa_total) + playa_limpias };
	priority_queue<Nodo>q;
	q.push(Nodo(playas, ca, co, cp, k));
	while (!q.empty() && q.top().coste_optimo.valido(minimo_p) && q.top().coste_optimo.numero_basura >= limite.numero_basura) {
		Nodo aux = q.top();
		q.pop();

		for (int i = 0; i < playas.size(); i++) {// recorrer las playas
			if (aux.visit[i] > 0) {
				k = aux._k + 1;
				ca = aux.coste_actual;
				ca.numero_basura += min(datos[k][i], aux.visit[i]);
				aux.visit[i] -= datos[k][i];// lo restamos para que sea mas sencillo despues sumar

				ca.numero_playa_limpia += (aux.visit[i] > 0) ? 0 : 1;// si es 0 o menor hay una playa limpia extra
				cp.numero_basura = min(estimacion_pesima[k + 1] + ca.numero_basura, basura_total);
				cp.numero_playa_limpia = num_playa_posible(cp.numero_basura, playa_max, num_playa_total) + playa_limpias;


				co.numero_basura = estimacion_optima[k + 1] + ca.numero_basura;
				co.numero_playa_limpia = num_playa_posible(co.numero_basura, playa_min, num_playa_total) + playa_limpias;

				if (co.valido(minimo_p) && ans.numero_basura < co.numero_basura) {
					if (k == datos.size() - 1) {
						if (ca.valido(minimo_p))
							limite = ans = ca;
					}
					else {
						q.push(Nodo(aux.visit, ca, co, cp, k));
						if (cp.valido(minimo_p) && cp.numero_basura > limite.numero_basura) {
							limite = cp;
						}
					}
				}
				aux.visit[i] += datos[k][i];
			}
		}
		// la persona k no hace nada
		k = aux._k + 1;
		ca = aux.coste_actual;

		cp.numero_basura = min(estimacion_pesima[k + 1] + ca.numero_basura, basura_total);
		cp.numero_playa_limpia = num_playa_posible(cp.numero_basura, playa_max, num_playa_total) + playa_limpias;
		co.numero_basura = estimacion_optima[k + 1] + ca.numero_basura;
		co.numero_playa_limpia = num_playa_posible(co.numero_basura, playa_min, num_playa_total) + playa_limpias;

		if (co.valido(minimo_p) && ans.numero_basura < co.numero_basura) {
			if (k == datos.size() - 1) {
				if (ca.valido(minimo_p))
					limite = ans = ca;
			}
			else {
				q.push(Nodo(aux.visit, ca, co, cp, k));
				if (cp.valido(minimo_p) && cp.numero_basura > limite.numero_basura) {
					limite = cp;
				}
			}
		}
	}
	return ans;

}

void resuelveCaso() {
	int npersona, mplayas, minimo_limpio;
	cin >> npersona >> mplayas >> minimo_limpio;
	vector<int>playas(mplayas);
	for (auto& x : playas)
		cin >> x;
	vector<vector<int>>datos(npersona, vector<int>(mplayas));
	for (int i = 0; i < npersona; i++) {
		for (auto& x : datos[i]) {
			cin >> x;
		}
	}
	Result ans;
	ans = limpiar_playa(datos, playas, minimo_limpio);
	if (ans.valido(minimo_limpio)) {
		cout << ans.numero_basura << " " << ans.numero_playa_limpia << "\n";
	}
	else {
		cout << "IMPOSIBLE\n";
	}
}
