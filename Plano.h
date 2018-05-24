#ifndef PLANO_H_
#define PLANO_H_

#include <vector>
#include "Punto.h"

using namespace std;

class Plano {
public:

	Plano(size_t id, Punto p) : _idPlano(id) {
		for (size_t i = 0; i < p.totalValues(); i++) {
			_valoresCentrales.push_back(p.getValue(i));
		}
		_puntos.push_back(p);
	}

	void anadirPunto(Punto p) { _puntos.push_back(p); }
	bool quitarPunto(size_t id) {
		bool encontrado = false;
		for (auto cit = _puntos.cbegin(); cit != _puntos.cend() && !encontrado; cit++) {
			if (cit->getID() == id) {
				_puntos.erase(cit);
				encontrado = true;
			}
		}
		return encontrado;
	}

	float getValorCentral(size_t idx) const { return _valoresCentrales[idx]; }
	void setValorCentral(size_t idx, float x) { _valoresCentrales[idx] = x; }
	size_t getPuntosTotales() const { return _puntos.size(); }
	size_t getIDPlano() { return _idPlano; }



private:
	int _idPlano;
	vector<float> _valoresCentrales;
	vector<Punto> _puntos;

};
#endif // !PLANO_H_

