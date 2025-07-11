#pragma once
#include <string> //Para usar el std::string
#include "Empresa.h"

class ArchivoEmpresa{

    private:
        std::string _nombreArchivo;

    public:
        ArchivoEmpresa();
        int get_CantidadRegistros();
        bool guardarEmpresa(Empresa registro);
        bool guardarEmpresa(Empresa registro, int posicion);
        Empresa leerEmpresa(int posicion);

};
