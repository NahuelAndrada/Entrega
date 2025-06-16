#ifndef ARCHIVOTIPOAUTOPARTE_H
#define ARCHIVOTIPOAUTOPARTE_H

#include "TipoAutoparte.h"

class ArchivoTipoAutoparte {
private:
    char nombreArchivo[30];

public:
    ArchivoTipoAutoparte();
    ArchivoTipoAutoparte(const char* nombre);

    TipoAutoparte leerUno(int pos);
    bool guardar(TipoAutoparte reg);
    bool modificar(TipoAutoparte reg, int pos);
    bool eliminar(int pos);
    int cantidad();
    void listarActivos();
};

#endif
