#include <iostream>
#include <string>
#include "LecturaDatos.h"
#include "KMedias.h"

using namespace std;

int main(int argc, char **argv) {

	string rutaFichero = "Iris2Clases.txt";

	if (argc == 2) {
		rutaFichero = argv[1];
	}

	LecturaDatos ld(rutaFichero);
	ld.leerFichero();
	
	if (ld.leerFichero()) {
		KMedias km(ld.matrizDatos());
		cout << endl;
	}
	else cout << "ERROR DE LECTURA. El fichero no existe o la ruta esta mal especificada." << endl;
	
	system("pause");
	return 0;
}