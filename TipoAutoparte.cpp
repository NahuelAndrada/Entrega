#include "TipoAutoparte.h"
#include <iostream>
#include <cstring>
using namespace std;

TipoAutoparte::TipoAutoparte() {
    _numero = 0;
    strcpy(_nombre , "");
    _activo = true;
}

TipoAutoparte::TipoAutoparte(int numero, std::string nombre, bool activo) {
    setNumero(numero);
    setNombre(nombre);
    setActivo(activo);
}

void TipoAutoparte::setNumero(int numero){
    _numero = numero;
}

void TipoAutoparte::setNombre(std::string nombre){
    strcpy(_nombre, nombre.c_str());
}

void TipoAutoparte::setActivo(bool activo){
    _activo = activo;
}

int TipoAutoparte::getNumero(){
    return _numero;
}

std::string TipoAutoparte::getNombre(){
    return _nombre;
}

bool TipoAutoparte::getActivo(){
    return _activo;
}

void TipoAutoparte::mostrar() {
   cout << "ID: " << getNumero() << "\n";
   cout << "Nombre: " << getNombre() << "\n";
   cout << "Estado: ";
    if (getActivo()) {
        cout << "Activo\n";
    } else {
        cout << "Inactivo\n";
    }
}
