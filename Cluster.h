#ifndef CLUSTER_H_
#define CLUSTER_H_

#include <vector>
#include "Punto.h"

using namespace std;

class Cluster {
public:

private:
	int _idCluster;
	vector<float> _valoresCentrales;
	vector<Punto> _puntos;

};
#endif // !CLUSTER_H_

