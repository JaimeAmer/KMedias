#ifndef KMEDIAS_H_
#define KMEDIAS_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include "termcolor.hpp"

using namespace std;

class KMedias {
public:

	KMedias(vector<vector<string>> muestras) : _muestras(muestras) {}

private:

	void ejecutar() {
		size_t numIteracion = 0;

		cout << "Iteracion #" << numIteracion;
		cout << "Centros Iniciales: ";

	}

	vector<vector<string>> _muestras;
};

#endif // !KMEDIAS_H_
