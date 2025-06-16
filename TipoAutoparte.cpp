#include "TipoAutoparte.h"
#include <iostream>
#include <cstring>
    using namespace std;


TipoAutoparte::TipoAutoparte() {
     _Tipo = 0;
     strcpy(_nombre,"");
    _activo = true;
}

TipoAutoparte::TipoAutoparte(int Tipo, std::string nombre){
    setIdTipo(Tipo);
    setNombre(nombre);
}

void TipoAutoparte::setIdTipo(int id) {
    _Tipo = id;
}

void TipoAutoparte::setNombre(std::string nombre) {
     strcpy(_nombre, nombre.c_str());
}

void TipoAutoparte::setActivo(bool activo) {
    _activo = activo;
}

int TipoAutoparte::getIdTipo() const {
    return _Tipo;
}

const char* TipoAutoparte::getNombre() const {
    return _nombre;
}

bool TipoAutoparte::getActivo() const {
    return _activo;
}
