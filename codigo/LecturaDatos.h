#ifndef LECTURADATOS_H_
#define LECTURADATOS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class LecturaDatos {
public:

	LecturaDatos(string rutaFichero) : _rutaFichero(rutaFichero) {}

	bool leerFichero() {
		_datos.clear();

		ifstream lectura;
		lectura.open(_rutaFichero);

		string linea;

		if (!lectura.is_open())
			return false;

		while (!lectura.eof()) {
			getline(lectura, linea);
			_datos.push_back(linea);
		}

		return true;
	}

	vector<string> vectorDatos() {
		return _datos;
	}

	vector<vector<double>> matrizDatos() {
		vector<vector<double>> v;
		for (auto it = _datos.begin(); it != _datos.end(); it++) {
			vector<string> vs = split(*it, ',');
			vector<double> vf;
			for (auto it2 = vs.begin(); it2 != vs.end(); it2++) {
				vf.push_back(parseDouble(*it2));
			}
			v.push_back(vf);
		}
		return v;
	}

private:

	vector<string> split(string linea, char pattern) {
		vector<string> v;
		string palabra = "";
		for (size_t i = 0; i < linea.size(); i++) {
			if (linea[i] != pattern)
				palabra.push_back(linea[i]);
			else {
				v.push_back(palabra);
				palabra = "";
			}
		}
		v.push_back(palabra);
		return v;
	}

	double parseDouble(string x) { return strtod(x.c_str(), 0); }

	string _rutaFichero;
	vector<string> _datos;
};

#endif // !LECTURADATOS_H_
