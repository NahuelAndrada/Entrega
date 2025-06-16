#ifndef ARCHIVOTIPOAUTOPARTE_H
#define ARCHIVOTIPOAUTOPARTE_H
#include "TipoAutoparteManager.h"
#include "TipoAutoparte.h"
#include <string>
class ArchivoTipoAutoparte {
private:
    std::string _nombreArchivo;

public:
    ArchivoTipoAutoparte();
    ArchivoTipoAutoparte(std::string nombre);

    TipoAutoparte leerUno(int pos);
    bool guardar(TipoAutoparte reg);
    bool modificar(TipoAutoparte reg, int pos);
    bool eliminar(int pos);
    int cantidad();
    void listarActivos();
};

#endif
