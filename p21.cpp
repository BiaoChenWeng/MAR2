#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
// Introduce más librerías si son necesarias
using namespace std;
void resuelveCaso();

const int NO_VALIDO = INT_MAX;
int calcular_estimacion_inicial(vector<int>const& cantidad, vector<int>const& precio, int k, int cantidad_deseada, int& ult, int& cantidad_ult);
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
	vector<int>visit;
	
	int coste_actual;

	int coste_optimo;
	int k;
	int masc_deseada;
	int ult_cogido;
	int cant_restante;


	Nodo(vector<int>const& v, int _k, int ca = 0, int co = 0, int m = 0,int u =0 ,int cant=0) :ult_cogido(u),cant_restante(cant),masc_deseada(m), visit(v), coste_actual(ca), coste_optimo(co), k(_k) {

	}

	bool operator<(const Nodo& other) const {
		return this->coste_optimo > other.coste_optimo;
	}
};

int calcular_estimacion(vector<int>const& cantidad, vector<int>const& precio, Nodo const & n,int deseado,int &ult , int &cant_ult) {
	
	int k = n.k + 1;// cogemos la tienda en la que estamos
	int i = ult;// cogemos la ultima tienda donde se compro mascarilla y queda alguna sin comprar
	if (ult == k) {// si la tienda que acabo de comprar es la misma que la ultima, entonces pasamos a la siguiente tienda 
		cant_ult = 0;// pasarlo a 0 hace que pase a la siguiente tienda automaticamente mas adelante 
	}
	if (i== cantidad.size()) {// si no queda tienda
		return NO_VALIDO;
	}

	int ans = n.coste_optimo;
	
	ans -= precio[k] * deseado;// le quitamos la solucion voraz el numero de mascarillas que no consegui comprar
	
	int cant = cant_ult;
	if (cant < deseado) {// si la ultima tienda no tiene suficiente de lo que neceisto
		ans += precio[i++] * cant;// le compramos todos lo que necesitamos
		deseado -= cant;// le restamos la cantidad que me hace falta
		int a = calcular_estimacion_inicial(cantidad, precio, i, deseado, ult, cant_ult);;
		if (a == NO_VALIDO)
			return NO_VALIDO;
		ans += a;

	}
	else {// si la ultima tienda tiene suficiente
		cant_ult -= deseado;// lo compramos 
		ans += precio[i] * deseado;
	}

	return ans;
}

//algoritmo voraz que compra todas las mascarillas de menor precio, y lo reparte con todas las facultad
int calcular_estimacion_inicial(vector<int>const& cantidad, vector<int>const& precio,int k ,int cantidad_deseada,int& ult , int &cantidad_ult) {
	int i = k;
	int ans = 0;
	int cant = cantidad_deseada;
	for (; i < cantidad.size() && cant>=cantidad[i]; i++) {
		ans += cantidad[i] * precio[i];
		cant -= cantidad[i];
	}
	if (i == cantidad.size() && cant != 0) {// si no queda más mascarillas y no queda mas por vender
		return NO_VALIDO;
	}
	ult = i;//ult es la posicion de la ultima tienda de mascarilla
	if (cant != 0 ) {// si aun no compre todo lo que necesito 
		ans += cant * precio[i];// termino la compra
		cantidad_ult = cantidad[i] - cant;// cantidad de mascarilla de esa tienda que le falta por vender 
	
	}
	else {// sabemos que cant == 0 evaluamos si queda aun alguna tienda que venda alguna mascarilla
		cantidad_ult = (++ult <cantidad.size())?cantidad[ult] :0 ;// 
	}

	return ans;

}


int compra(vector<int>const& facultad, vector<int>const& cantidad, vector<int>const& precio) {
	int ans = NO_VALIDO;

	int cantidad_pedida = 0;
	int cant_ult;
	int ult;
	
	for (int i = facultad.size() - 1; i >= 0; i--) {
		cantidad_pedida += facultad[i];
	}

	priority_queue<Nodo>q;
	int ca, co;
	co = calcular_estimacion_inicial(cantidad, precio, 0, cantidad_pedida, ult, cant_ult);
	
	if (co == ans) {// si el coste optimo no es valido
		return ans;
	}
	int k;
	int num;
	q.push(Nodo(facultad, -1, 0, co, cantidad_pedida, ult,cant_ult));
	while (!q.empty() && q.top().coste_optimo < ans) {
		Nodo aux = q.top();
		q.pop();
		// coger 
		for (int i = 0; i < facultad.size(); i++) {
			if (aux.visit[i] > 0) {// si la facultad aun necesita mascarilla
				cantidad_pedida = aux.masc_deseada;
				k = aux.k + 1;
				num = min(aux.visit[i], cantidad[k]);
				aux.visit[i] -= num;
				
				ca = aux.coste_actual + num * precio[k];
				cant_ult = aux.cant_restante;
				ult = aux.ult_cogido;
				if (num != cantidad[k]) {
					// recalcular estimacion
					co = calcular_estimacion(cantidad, precio, aux, min(cantidad[k],cantidad_pedida) - num, ult, cant_ult);
				}
				else {
					co = aux.coste_optimo;
				}
				cantidad_pedida -= num;

				if (co < ans ) {
					if (cantidad_pedida == 0) {
						if (ca < ans) {
							ans = ca;
						}
					}
					else {
						q.push(Nodo(aux.visit, k, ca, co, cantidad_pedida,ult,cant_ult));
					}
				}

				aux.visit[i] += num;
			}
		}

	}

	return ans;
}


void resuelveCaso() {
	int n, m;
	cin >> n >> m;
	vector<int>facultad(n);
	vector<int>cantidad(m);
	vector<int>precio(m);
	for (int& k : facultad) {
		cin >> k;
	}
	for (int& k : cantidad) {
		cin >> k;
	}
	for (int& k : precio) {
		cin >> k;
	}

	int ans = compra(facultad, cantidad, precio);
	if (ans == NO_VALIDO) {
		cout << "NO\n";
	}
	else {
		cout << ans << "\n";
	}

}