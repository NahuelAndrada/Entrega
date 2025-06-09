#include "TipoAutoparte.h"
#include <cstring>

TipoAutoparte::TipoAutoparte(){
    _numero = 0;
    strcpy(_nombre, "");
}

TipoAutoparte::TipoAutoparte(int numero) {
    _numero = numero;
    strcpy(_nombre, "");
}

TipoAutoparte::TipoAutoparte(int numero, const char* nombre){
    _numero = numero;
    strcpy(_nombre, nombre);
}

void TipoAutoparte::setNumero(int numero){
    _numero = numero;
}

void TipoAutoparte::setNombre(const char* nombre){
    strcpy(_nombre, nombre);
}

void TipoAutoparte::setTipo(int numero, const char* nombre) {
    _numero = numero;
    strcpy(_nombre, nombre);
}

int TipoAutoparte::getNumero() const{
    return _numero;
}

const char* TipoAutoparte::getNombre() const{
    return _nombre;
}
