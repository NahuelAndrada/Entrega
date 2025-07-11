#ifndef ARCHIVOTIPOAUTOPARTE_H_INCLUDED
#define ARCHIVOTIPOAUTOPARTE_H_INCLUDED

#include "TipoAutoparte.h"
#include <string>

class ArchivoTipoAutoparte {
private:
    std::string _nombreArchivo;

public:
    ArchivoTipoAutoparte(std::string nombreArchivo = "tipoautoparte.dat");

    TipoAutoparte leer(int pos);
    bool guardar(TipoAutoparte reg);
    bool modificar(int pos, TipoAutoparte reg);
    int contar();
    int buscarPorNumero(int numero);
};

#endif
