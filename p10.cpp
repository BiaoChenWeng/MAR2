
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>
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

/*
vector<pelicula>

hora(i) = tiempo_pelicula(i) si cabe
			max()


*/

/*
el problema en almacen[i] significa que desde el 00:00 hasta el i
has visto tanto tiempo en minutos, si i por ejemplo es 16:00 en min , 
entonces desde las 0 hasta la 16 ha visto x tiempo, y para las 16:01
suponiendo que no ha visto ninguna nueva pelicula , será x también 

*/
void ascendente(vector<int>&almacen, vector<pair<int, int>>const& tiempo) {
	// tiempo.first comienzo , tiempo.second duracion

	for (int i = 0; i < tiempo.size(); i++) {
		int ini= tiempo[i].first;
		int fin=ini+tiempo[i].second;

		for (int j = almacen.size()-1; j >= fin +10 ; j--) {// si ha terminado la pelicula y paso 10 min entonces significa que en el momento j ha visto esa cantidad de tiempo
			almacen[j] = max(almacen[j], almacen[ini]+tiempo[i].second);
			// no cojo la pelicula , o cojo la pelicula , miro si ante de inicalizar la pelicula cual era el maximo de tiempo que consegui + el tiempo que me pasare mirando la peli
		}
		


	}

}






bool resuelveCaso() {

	int entrada;
	cin >> entrada;
	if (entrada==0)
		return false;
	vector<pair<int,int>>v(entrada);
	int h, m,d;
	char espacio;
	for (int i = 0; i < entrada; i++) {
		cin >> h >> espacio >> m>>d;
		v[i] = { h*60 + m, d };
	}
	sort(v.begin(), v.end());
	vector<int>almacen(60 * 24 +11,0);

	//int ans = descendente(almacen, v, 0, 0);
	ascendente(almacen, v);
	cout << almacen[almacen.size()-1] << "\n";

	return true;
}



