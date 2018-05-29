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

	KMedias(vector<vector<double>> muestras) {

		cout << termcolor::blue << "          Bienvenido al Algoritmo K-Medias" << endl;
		cout << termcolor::red << "----------------------------------------------------" << termcolor::reset << endl << endl;

		for (size_t i = 0; i < _NMUESTRAS; i++) {
			for (size_t j = 0; j < _DIMENSION; j++) {
				_muestras[i][j] = muestras[i][j];
			}
		}
		ejecutar();
	}

private:

	void ejecutar() {

		size_t numIteracion = 0;
		
		cout << termcolor::yellow << "Iteracion #" << numIteracion << ":" << endl << endl;
		cout << termcolor::cyan << "Centros Iniciales: " << termcolor::reset << endl;
		mostrarCentros();

		while (!parar()) {

			//rellenar_grados_pertenencia
			for (size_t i = 0; i < _NMUESTRAS; i++) {
				for (size_t j = 0; j < _NCLASES; j++) {
					_pert[i][j] = calcularP(i, j);
				}
			}

			arraycpy(_v1Anterior, _v1Actual);
			arraycpy(_v2Anterior, _v2Actual);

			arraycpy(_v1Actual, calcularV1().data());
			arraycpy(_v2Actual, calcularV2().data());

			cout << termcolor::yellow << "Iteracion #" << ++numIteracion << ":" << endl << endl;
			cout << termcolor::cyan << "Nuevos Centros: " << termcolor::reset << endl;
			mostrarCentros();
		}

		double punto1[] = { 5.1, 3.5, 1.4, 0.2 };
		double punto2[] = { 6.9, 3.1, 4.9, 1.5 };
		double punto3[] = { 5.0, 3.4, 1.5, 0.2 };

		cout << endl;
		pertenenciaClase(punto1, 4);
		pertenenciaClase(punto2, 4);
		pertenenciaClase(punto3, 4);

	}

	double calcularP(int nMuestra, int nClase) {
		double muestra[] = { _muestras[nMuestra][0], _muestras[nMuestra][1], _muestras[nMuestra][2], _muestras[nMuestra][3] };
		double distanciaAClase1 = calcularDistancia(_v1Actual, muestra);
		double distanciaAClase2 = calcularDistancia(_v2Actual, muestra);

		double num = 0.0f;
		double den = 0.0f;
		if (nClase == 0) {
			num = pow(1 / distanciaAClase1, 1 / (_B - 1));
			den = pow(1 / distanciaAClase1, 1 / (_B - 1)) + pow(1 / distanciaAClase2, 1 / (_B - 1));
		}
		else {
			num = pow(1 / distanciaAClase2, 1 / (_B - 1));
			den = pow(1 / distanciaAClase1, 1 / (_B - 1)) + pow(1 / distanciaAClase2, 1 / (_B - 1));
		}

		return num/den;
	}

	double calcularDistancia(double *x, double *y) {
		double distancia = 0.0f;

		for (size_t i = 0; i < _DIMENSION; i++) {
			distancia += pow((x[i] - y[i]), 2);
		}

		return distancia;
	}

	vector<double> calcularV1() {
		vector<double> nuevoCentro(_DIMENSION);

		double den = 0.0;

		for (size_t i = 0; i < _NMUESTRAS; i++)
			den += pow(calcularP(i, 0), _B);

		vector<double> num(_DIMENSION);
		vector<double> xj(_DIMENSION);
		for (size_t i = 0; i < _NMUESTRAS; i++) {
			for (size_t j = 0; j < _DIMENSION; j++) {
				xj[j] = _muestras[i][j];
				num[j] += pow(_pert[i][0], _B)*xj[j];
			}
		}
		
		for (size_t i = 0; i < _DIMENSION; i++)
			nuevoCentro[i] = num[i] / den;

		return nuevoCentro;
	}

	vector<double> calcularV2() {
		vector<double> nuevoCentro(_DIMENSION);

		double den = 0.0;

		for (size_t i = 0; i < _NMUESTRAS; i++)
			den += pow(calcularP(i, 1), _B);

		vector<double> num(_DIMENSION);
		vector<double> xj(_DIMENSION);
		for (size_t i = 0; i < _NMUESTRAS; i++) {
			for (size_t j = 0; j < _DIMENSION; j++) {
				xj[j] = _muestras[i][j];
				num[j] += pow(_pert[i][1], _B)*xj[j];
			}
		}

		for (size_t i = 0; i < _DIMENSION; i++)
			nuevoCentro[i] = num[i] / den;

		return nuevoCentro;
	}

		void mostrarCentros() {
		cout	<< termcolor::red << "V1: " << termcolor::reset << fixed << setprecision(3) << _v1Actual[0] << ", " << _v1Actual[1] << ", " << _v1Actual[2] << ", " << _v1Actual[3] << endl
				<< termcolor::red << "V2: " << termcolor::reset << fixed << setprecision(3) << _v2Actual[0] << ", " << _v2Actual[1] << ", " << _v2Actual[2] << ", " << _v2Actual[3] << endl
				<< endl;
	}


	bool parar() {
		double distancia1 = calcularDistancia(_v1Actual, _v1Anterior);
		double distancia2 = calcularDistancia(_v2Actual, _v2Anterior);

		cout	<< termcolor::green << "Distancias: " << termcolor::reset << endl
				<< termcolor::red <<  "Dist. 1: " << termcolor::reset << fixed << setprecision(3) << distancia1 << endl
				<< termcolor::red << "Dist. 2: " << termcolor::reset << fixed << setprecision(3) << distancia2 << endl
				<< "----------------------------------------------------" << endl;

		return distancia1 < _TOLERANCIA && distancia2 < _TOLERANCIA;
	}

	void pertenenciaClase(double *punto, size_t lenght) {
		cout << termcolor::red << "El punto: " << termcolor::reset << punto[0];
		for (size_t i = 1; i < lenght; i++) {
			cout << ", " << punto[i];
		}

		if (calcularDistancia(_v1Actual, punto) < calcularDistancia(_v2Actual, punto))
			cout << " pertenece a la clase " << termcolor::magenta << "Iris-Setosa" << termcolor::reset << endl;
		else cout << " pertenece a la clase " << termcolor::cyan << "Iris-Versicolor" << termcolor::reset << endl;
	}

	void arraycpy(double *dst, double *src) {
		for (size_t i = 0; i < _DIMENSION; i++) {
			dst[i] = src[i];
		}
	}

	const size_t _DIMENSION = 4;
	const size_t _NMUESTRAS = 100;
	const size_t _NCLASES = 2;

	double _muestras[100][4];
	double _pert[100][2];

	const double _TOLERANCIA = 0.01;
	const int _B = 2;

	double _v1Actual[4] = { 4.6, 3.0, 4.0, 0.0 };
	double _v2Actual[4] = { 6.8, 3.4, 4.6, 0.7 };

	double _v1Anterior[4] = { 0.0, 0.0, 0.0, 0.0 };
	double _v2Anterior[4] = { 0.0, 0.0, 0.0, 0.0 };


};

#endif // !KMEDIAS_H_
