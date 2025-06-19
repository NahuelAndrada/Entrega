#include "Autoparte.h"
#include <iostream>
#include <cstring>
using namespace std;

Autoparte::Autoparte() {
    _numero = 0;
    strcpy(_nombre, "");
    _tipo = 0;
    _stock = 0;
    _activo = true;
}

Autoparte::Autoparte(int numero, const char* nombre, int tipo, int stock, bool activo) {
    _numero = numero;
    strcpy(_nombre, nombre);
    _tipo = tipo;
    _stock = stock;
    _activo = activo;
}

void Autoparte::setNumero(int numero) { _numero = numero; }
void Autoparte::setNombre(const char* nombre) { strcpy(_nombre, nombre); }
void Autoparte::setTipo(int tipo) { _tipo = tipo; }
void Autoparte::setStock(int stock) { _stock = stock; }
void Autoparte::setActivo(bool activo) { _activo = activo; }

int Autoparte::getNumero() { return _numero; }
const char* Autoparte::getNombre() { return _nombre; }
int Autoparte::getTipo() { return _tipo; }
int Autoparte::getStock() { return _stock; }
bool Autoparte::getActivo() { return _activo; }

void Autoparte::mostrar() {
    cout << "Numero: " << _numero << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Tipo: " << _tipo << endl;
    cout << "Stock: " << _stock << endl;
    cout << "Activo: " << (_activo ? "Si" : "No") << endl;
    cout << "---------------------" << endl;
}
