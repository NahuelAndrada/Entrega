#include "TipoAutoparte.h"
#include <iostream>
#include <cstring>
using namespace std;

TipoAutoparte::TipoAutoparte() {
    numeroTipo = 0;
    strcpy(nombre, "");
    activo = true;
}

void TipoAutoparte::cargar() {
    cout << "Ingrese número de tipo de autoparte: ";
    cin >> numeroTipo;
    cin.ignore();
    cout << "Ingrese nombre del tipo: ";
    cin.getline(nombre, 50);
    activo = true;
}

void TipoAutoparte::mostrar() const {
    cout << "Número de Tipo: " << numeroTipo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Estado: " << (activo ? "Activo" : "Inactivo") << endl;
    cout << "-----------------------------" << endl;
}

int TipoAutoparte::getNumeroTipo() const { return numeroTipo; }
const char* TipoAutoparte::getNombre() const { return nombre; }
bool TipoAutoparte::getActivo() const { return activo; }

void TipoAutoparte::setNumeroTipo(int n) { numeroTipo = n; }

void TipoAutoparte::setNombre(const char* n) {
    strncpy(nombre, n, sizeof(nombre));
    nombre[sizeof(nombre) - 1] = '\0';
}

void TipoAutoparte::setActivo(bool a) { activo = a; }
