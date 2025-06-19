#ifndef ARCHIVOAUTOPARTES_H_INCLUDED
#define ARCHIVOAUTOPARTES_H_INCLUDED

#include "Autoparte.h"

class ArchivoAutopartes {
private:
    char _nombreArchivo[100];

public:
    ArchivoAutopartes(const char* nombre = "autopartes.dat");

    Autoparte leer(int pos);
    bool guardar(Autoparte reg);
    bool modificar(int pos, Autoparte reg);
    int contar();

    int buscarPorNumero(int numero);
    int buscarPorNombre(const char* nombre);
};

#endif
