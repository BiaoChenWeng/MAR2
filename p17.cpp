#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>
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
	int tiempo;
	int puntuacion;

	tDatos(int t=0,int p=0):tiempo(t),puntuacion(p){}
	bool operator< (const tDatos &other) const{
		return this->puntuacion * other.tiempo > other.puntuacion * this->tiempo;


		//return ((float)puntuacion / tiempo) > ((float)other.puntuacion / other.tiempo);
	}
};




struct Nodo {
	int k;
	int coste_actual;
	double coste_optimo;
	int disco1_libre;
	int disco2_libre;

	Nodo(int _k=-1 ,int ca=0, double co=INT_MAX,int d1=0,int d2=0):k(_k),coste_actual(ca),coste_optimo(co),disco1_libre(d1),disco2_libre(d2){}


	bool operator <(Nodo const & other) const{
		return coste_optimo < other.coste_optimo;
		//if (coste_optimo != other.coste_optimo)
			
		/*else if (this->k != other.k)
			return this->k < other.k;
		return (disco1_libre + disco2_libre) < (other.disco1_libre + other.disco2_libre);*/
	}
	bool operator==(Nodo const& other)const {
		return false;
	}
};



double calcular_estimacion(int const k,const int &espacio_vacio,vector<tDatos>const &datos) {
	int i = k;
	double ans = 0;
	int espacio_disponible = espacio_vacio;
	for (; i < datos.size() && espacio_disponible>= datos[i].tiempo; i++) {
		ans += datos[i].puntuacion;
		espacio_disponible -= datos[i].tiempo;
	}
	if (i<datos.size() && espacio_disponible != 0) {
		ans += espacio_disponible * ((double)datos[i].puntuacion / datos[i].tiempo);
	}
	return ans;
}

int problema_mochila_binario(vector<tDatos>const & datos,int tiempo) {
	int ans = 0;//valor_inicial(datos,tiempo);
	double estimacion=calcular_estimacion(0,tiempo*2,datos);
	priority_queue<Nodo>q;
	q.push(Nodo(-1, 0, estimacion, tiempo, tiempo));
	int valor,d1,d2;

	while (!q.empty() && q.top().coste_optimo > ans) {
		Nodo aux = q.top();
		q.pop();
		//coger

		d1 = aux.disco1_libre;
		d2 = aux.disco2_libre;
		// meter en la cara1
		if (d1 != d2) {
			if (aux.disco1_libre >= datos[aux.k + 1].tiempo) {
				
				d1 -= datos[aux.k + 1].tiempo;
				valor = datos[aux.k + 1].puntuacion+ aux.coste_actual;
				if (aux.k + 1 == datos.size() - 1) {// ultimo elemento 
					ans = max(ans, valor);
				}
				else {
					
					q.push(Nodo(aux.k + 1, valor, aux.coste_optimo, d1, d2));
				}
				d1 += datos[aux.k + 1].tiempo;
			}
		}
		
		//meter en la cara 2
		if (aux.disco2_libre >= datos[aux.k + 1].tiempo) {

			d2 -= datos[aux.k + 1].tiempo;
			valor = datos[aux.k + 1].puntuacion;
			if (aux.k + 1 == datos.size() - 1) {// ultimo elemento 
				ans = max(ans, valor + aux.coste_actual);
			}
			else {
				
				q.push(Nodo(aux.k + 1, aux.coste_actual + valor, aux.coste_optimo, d1, d2));
			}
			d2 += datos[aux.k + 1].tiempo;
		}


		// no coger

		if (aux.k + 1 == datos.size()-1) {
			ans = max(ans, aux.coste_actual);
		}
		else {
			estimacion = calcular_estimacion(aux.k + 1, d1 + d2, datos)+aux.coste_actual;
			if (estimacion > ans) {
				q.push(Nodo(aux.k + 1, aux.coste_actual, estimacion, d1, d2));
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
	
	int tiempo;
	int t, p;
	cin >> tiempo;
	vector<tDatos>datos;
	for (int i = 0; i < entrada; i++) {
		cin >> t >> p;
		if (tiempo >= t) {
			datos.push_back({ t,p });
		}

	}
	sort(datos.begin(), datos.end());
	int ans = problema_mochila_binario(datos, tiempo);
	cout << ans << "\n";
	return true;
}