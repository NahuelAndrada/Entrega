#ifndef ARCHIVOAUTOPARTES_H_INCLUDED
#define ARCHIVOAUTOPARTES_H_INCLUDED

#include "Autoparte.h"
#include <string>

class ArchivoAutopartes {
private:
    std::string _nombreArchivo;

public:
    ArchivoAutopartes(std::string nombreArchivo="autopartes.dat");

    Autoparte leer(int pos);
    bool guardar(Autoparte reg);
    bool modificar(int pos, Autoparte reg);
    int contar();

    int buscarPorNumero(int numero);
    int buscarPorNombre(const char* nombre);
};

#endif
