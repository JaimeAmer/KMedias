#ifndef PUNTO_H_
#define PUNTO_H_

#include <string>
#include <vector>

using namespace std;

class Punto {
public:
	Punto(int idPunto, vector<float> values, string nombre) : _idPunto(idPunto), _idCluster(-1), _nombre(nombre), _values(values) {}

	int getID() { return _idPunto; }
	int setCluster(int id) { _idCluster = id; }
	int getCluster() { return _idCluster; }
	int getValue(size_t idx) { return _values[idx]; }
	int totalValues() { return _values.size(); }
	void addValue(float value) { _values.push_back(value); }
	string getNombre() { return _nombre; }

private:

	int _idPunto;
	int _idCluster;
	vector<float> _values;
	string _nombre;
};

#endif // !PUNTO_H_
