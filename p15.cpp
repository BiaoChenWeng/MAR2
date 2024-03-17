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
	vector<bool>visit;
	
	Nodo(int tam,int ca=0, int co=INT_MAX, int cp=0, int _k=-1) :coste_actual(ca), coste_optimo(co), coste_pesimo(cp), k(_k), visit(tam,false) {

	}
	Nodo(int ca, int co, int cp, int _k, vector<bool>v) :coste_actual(ca), coste_optimo(co), coste_pesimo(cp), k(_k), visit(v) {

	}

	bool operator<(const Nodo other)const {
		if (coste_optimo != other.coste_optimo)
			return coste_optimo < other.coste_optimo;
		return k < other.k;
	}

};

int maximo_rendimiento(vector<int>const& carros, vector<int>const& caminos, vector<vector<int>>const& eficiencia) {
	int n = carros.size();
	if (n == 0)// si no hay carro devolvemos 0 
		return 0;
	priority_queue<Nodo>q;
	int ans = 0;// la respuesta actual es 0 
	int limite;

	vector<int>coste_pesimo(n + 1, INT_MAX);
	vector<int>coste_optimo(n + 1, 0);
	coste_pesimo[n] = 0;

	for (int i = carros.size() - 1; i >= 0; i--) {

		for (int j = caminos.size() - 1; j >= 0; j--) {
			coste_optimo[i] = max(coste_optimo[i], eficiencia[i][j]);//suponiendo que cada carro puede coger su mejor camino con más rendimiento
			coste_pesimo[i] = min(coste_pesimo[i], eficiencia[i][j]);// suponiendo que cada carro puede coger su peor camino
		}
		coste_optimo[i] += coste_optimo[i + 1];// calculamos la mejor solucion posible si nos queda x cantidada de carro
		coste_pesimo[i] += coste_pesimo[i + 1];// lo mismo con la peor solucion, que en caso de que todos los carros tengan un camino que no puede acceder por su tamaño será 0
		ans += eficiencia[i][i];// creamos una solución posible , en la parte de eficiencia si el carro no cabe el valor de su eficiencia es 0 , como si no se hubiera usado el carro.
	}
	limite = ans;
	
	q.push(Nodo(caminos.size(),0,coste_optimo[0],coste_pesimo[0]));// ponemos el primer nodo ,coste_optimo[0] es el coste optimo suponiendo que cada carro puede usar su camino más eficiente
	int optimo, pesimo,actual,k;
	while (!q.empty() && q.top().coste_optimo>=limite) {
		Nodo aux = q.top();// cogemos, el nodo mas prioritario , sabemos que puede tener solucion 
		q.pop();// eliminamos el nodo 
		
		for (int i = 0;i< caminos.size(); i++) {
			if(!aux.visit[i]) {// si aún no use el camino 
				k = aux.k+1;// decimos que el carro siguiente ha sido usado
				actual = aux.coste_actual+eficiencia[k][i];// su coste actual es el coste conseguido hasta ahora + la eficiencia del carro en el camino i
				optimo=coste_optimo[k+1]+actual;//coste actual + coste optimo sin incluir el carro ya usado
				pesimo=coste_pesimo[k+1]+actual;//lo mismo con el pesimo
				
				if (optimo > ans) {// si es una solucion posible
					if (k== n - 1) {// en este punto el coste optimo , pesimo y actual deben tener el mismo valor
						ans = limite = actual;// cambiamos el limite y la respuesta
					}
					else {// aun no se uso todo los carros
						aux.visit[i] = true;// visitado el camino i 
						q.push(Nodo(actual,optimo,pesimo,k ,aux.visit));// ponemos el hijo en la cola
						limite = max(limite, pesimo);// cambiamos el limite , en caso de que unos de los 
						aux.visit[i] = false;// dejamos el vector de visit como estaba
					}
				}


			}
		}

	}
	return ans;

}


// configuración, y escribiendo la respuesta
void resuelveCaso() {
	int ncarro, mcamino;
	cin >> ncarro >> mcamino;
	vector<int>carros(ncarro);// tam de carros
	vector<int>caminos(mcamino);// tam de caminos
	vector<vector<int>>eficiencia(ncarro, vector<int>(mcamino));

	for (auto& x : carros)
		cin >> x;
	for (auto& x : caminos)
		cin >> x;

	for (int i = 0; i < ncarro; i++) {
		for (int j = 0; j < mcamino;j++) {
			cin >> eficiencia[i][j];
			if (carros[i] > caminos[j]) {
				eficiencia[i][j] = 0;// el carro i no entra al camino j 
			}
		}
			
	}
	int ans = maximo_rendimiento(carros, caminos, eficiencia);
	cout << ans<<"\n";
}
