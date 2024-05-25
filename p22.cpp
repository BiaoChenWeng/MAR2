//"Biao Chen Weng, Germán Bravo Sánchez Grupo 54"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include<algorithm>
#include<vector>
#include<queue>
#include <climits>

using namespace std;

/*
//RESTRICCIONES EXPLICITAS
Sabemos que siempre existe solución al problema porque la suma de capacidad de todos los hospitales es menor a numero de pacientes
Sabemos que la distancia entre hospital y paciente es solo la distancia de ida o bien vuelta
El numero de paciente y hospitales es menor o igual que 100 


//RESTRICCIONES IMPLICITAS
La k nunca supera al numero de paciente 
No se queda en un bucle infinito el codigo , porque siempre aumentamos k en cada iteración .
El numero de veces que usamos un hospital como mucho es su capacidad. 
Un paciente no puede ir a 2 hospitales.


//DESCRIPCION DEL ESPACIO DE SOLUCIONES
Tenemos un arbol de buscada con factor de ramificacion el numero de hospitales
Una altura de pacientes 
por lo tanto el arbol de busqueda tiene un coste de O(hospitales ^pacientes) es decir coste exponencia, en el peor de los casos es peor que vueltas atras por la cola de prioridad.
Ya que visitas todos los nodos y tiene un coste de nlog n siendo n el tamaño de la cola , extra. Pero en el caso medio el coste es mejor que el exponencia de vueltas atras
Una cota maxima de coste de espacio es en la cola de prioridad siendo como cota superior es O(hospitales ^pacientes) , que nunca podrá superar.  

//COTAS OPTIMISTAS (IMPLEMENTA SOLO UNA)

Sumatorio de la distancia minima cada paciente a cada hospital *2 (ida y vuelta) 
Tiene coste costante el acceso O(1) y coste O(hospital*pacientes) en su calculo

//COTAS PESIMISTAS (IMPLEMENTA SOLO UNA SI ES POSIBLE USARLAS)

Sumatorio de la distancia maxima de cada paciente a cada hospital *2 (ida y vuelta)
Tiene coste costante el acceso O(1) y coste O(hospital*pacientes) en su calculo, tiene el mismo coste , porque calculamos los dos a la vez


MEJORA
Inicializamos en una solucion válida, para podar más el árbol de busqueda. Aprovechando el calculo de los coste .
Si lo hiciera aparte, tendría coste O(n) siendo n el numero de pacientes 

*/
struct Nodo {
	int coste_optimo;
	int coste_actual;
	int coste_pesimo;
	int k;
	vector<int >visit;

	Nodo(vector<int >v, int k ,int ca, int co,int cp):visit(v),k(k),coste_optimo(co),coste_actual(ca), coste_pesimo(cp){
	}
	bool operator <(const Nodo& other) const{
		return this->coste_optimo > other.coste_optimo;
	}
};

//int cont = 0;



int ambulancias(int pacientes, int hospitales, vector<int> const& capacidades, vector<vector<int>> const& distancias)
{
	int ans = 0;
	vector<int>coste_optimo(pacientes+1,INT_MAX);
	vector<int>coste_pesimo(pacientes + 1, 0);
	coste_optimo[pacientes] = 0;
	int hospital_select = 0;
	int cant_usado = 0;
	for (int i = pacientes-1; i >= 0; i--) {
		for (int j = 0; j < hospitales; j++) {
			coste_optimo[i] = min(coste_optimo[i], distancias[i][j]*2);
			coste_pesimo[i] = max(coste_pesimo[i], distancias[i][j]*2);
		}
		coste_optimo[i] += coste_optimo[i + 1];
		coste_pesimo[i] += coste_pesimo[i + 1];

		ans += distancias[i][hospital_select] * 2;
		cant_usado++;
		if (cant_usado == capacidades[hospital_select]) {
			hospital_select++;
			cant_usado = 0;
		}
	}

	int k, ca, co, cp;
	
	int limite=ans;
	priority_queue<Nodo>q;
	q.push(Nodo(capacidades, -1, 0, coste_optimo[0], coste_pesimo[0]));
	while (!q.empty() && q.top().coste_optimo <= limite) {
		Nodo aux = q.top();
		q.pop();
		for (int i = 0; i < hospitales; i++)
		{
			if (aux.visit[i] != 0) {
				aux.visit[i]--;
				k = aux.k + 1;
				ca = aux.coste_actual + distancias[k][i]*2;
				co = ca + coste_optimo[k + 1];
				cp = ca + coste_pesimo[k + 1];

				if (co < ans) {
					if (k == pacientes - 1) {
						limite = ans = ca;
					}
					else {
						q.push(Nodo(aux.visit, k, ca, co, cp));
						if (cp < limite) {
							cp = limite;
						}
					}
				}
				aux.visit[i]++;
			}
		}
	}

	return ans;
	//Implementar RP
}



void resuelveCaso() {
	//cont = 0;
	int m, n;
	std::cin >> n >> m;//n pacientes, m hospitales
	std::vector<vector<int>> distancias(n, vector<int>(m));
	std::vector<int> capacidades(m);

	//Lectura de las capacidades de los hospitales
	for (int h = 0; h < m; h++) { std::cin >> capacidades[h]; }

	//Lectura de las distancias de pacientes a hospitales
	//si hay un paciente al menos hay un hospital con cama para el
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			std::cin >> distancias[i][j];

		}

	int mejorDistancia = ambulancias(n, m, capacidades, distancias);

	cout << mejorDistancia << "\n";
	//cout << cont << "\n";
}





int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}