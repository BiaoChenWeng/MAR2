#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>
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
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		resuelveCaso();
	}
	

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;

}
struct Nodo {
	vector<bool>visit;
	vector<int>asiento_de;
	int coste_actual;
	int coste_optimo;
	int _k;

	Nodo(int nMesa=0,int nPersona=0,int k=-1, int ca=0, int co=INT_MAX) :visit(nMesa, false),asiento_de(nPersona,-1), _k(k), coste_actual(ca), coste_optimo(co) {

	}
	Nodo(vector<bool>const &v,vector<int>const & a, int k = -1, int ca = 0, int co=INT_MAX) :visit(v),asiento_de(a), _k(k), coste_actual(ca), coste_optimo(co){}
	bool operator<(Nodo const &other)const {
		return coste_optimo < other.coste_optimo;
	}
};



int sentarse(vector<vector<bool>>const &relacion,const vector<vector<double>>&distancia) {
	if (relacion.size() > distancia.size())// hay más persona que asiento no es válido
		return -1;
	int ans = -1;// no es valido y no se pueden sentar todos
	
	vector<int>v(relacion.size()+1,0);

	for (int i = relacion.size()-1; i >=0; i--) {
		for (int j = i - 1; j >=0; j--) {
			if(relacion[j][i])
				v[i]++;

		}
		v[i] += v[i + 1];
	}

	int k, ca, co;
	priority_queue<Nodo>q;
	q.push(Nodo(distancia.size(),relacion.size(),-1,0,v[0]));

	while (!q.empty() && q.top().coste_optimo > ans) {
		Nodo aux = q.top();
		q.pop();

		for (int i = 0; i < distancia.size(); i++) {
			if (!aux.visit[i]) {
				bool valido = true;
				k = aux._k+1;
				aux.visit[i] = true;
				aux.asiento_de[k] = i;
				ca = 0;
				for (int j = 0; j < k &&valido; j++) {
					if (!relacion[k][j] && distancia[aux.asiento_de[j]][i] < 2) {
						valido = false;
					}
					else if (relacion[k][j] && distancia[aux.asiento_de[j]][i] <2) {
						ca++;
					}
				}
				ca += aux.coste_actual;
				co = ca + v[k + 1];

				if (valido && co>ans) {
					if (k == relacion.size() - 1) {
						ans = ca;
					}
					else {
						q.push(Nodo(aux.visit,aux.asiento_de, k,ca,co));
					}

				}
				//aux.asiento_de[k] = -1;
				aux.visit[i] = false;

			}


		}

	}


	return ans;
}


// coste optimo puede ser numero de aciento que están cerca o numero de persona que estan relacionadas 



void resuelveCaso() {
	int nPlazas, mComensal;
	cin >> nPlazas >> mComensal;

	vector<vector<bool>>relacion(mComensal,vector<bool>(mComensal, false));
	vector<vector<double>>distancia(nPlazas,vector<double>(nPlazas,0));

	for (int i = 0; i < nPlazas; i++) {
		for (auto& x : distancia[i])
			cin >> x;
	}
	int a;
	for (int i = 0; i < mComensal; i++) {
		for (int j = 0; j < mComensal; j++) {
			cin >> a;
			relacion[i][j] = a==1;
		}
	}

	int ans=sentarse(relacion,distancia);
	if (ans == -1)
		cout << "CANCELA\n";
	else {
		cout << "PAREJAS " << ans << "\n";
	}
	
}