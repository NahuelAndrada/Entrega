
#ifndef ARCHIVOAUTOPARTES_H_INCLUDED
#define ARCHIVOAUTOPARTES_H_INCLUDED

#include "Autoparte.h"
#include <cstring>
#include <cstdio>

class ArchivoAutopartes {
private:
    char nombreArchivo[30];

public:
    ArchivoAutopartes();
    ArchivoAutopartes(const char* nombre);

    Autoparte LeerUna(int pos);
    bool Guardar(Autoparte reg);
    bool Modificar(Autoparte reg, int pos);
    bool Eliminar(int pos);
    int CantidadAutopartes();
    bool Existe(int numero);
    int BuscarPosicion(int numero);
};

#endif
