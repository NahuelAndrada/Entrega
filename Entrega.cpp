#include "Entrega.h"
#include <iostream>
#include <cstring>
    using namespace std;

    Entrega::Entrega() {
    _identrega = 0;
    _NumeroAutoparte = 0;
    strcpy(_cuitEmpresa, "");
    _fechaEntrega = Fecha();
    _CantidadUnidades = 0;
    _importe = 0.0f;
    _activo = true;
    }

    Entrega::Entrega(int IdEntrega, int numeroAutoparte, std::string cuitEmpresa,Fecha FechaEntrega, int cantidadUnidades, float importe) {
    setIdEntrega(IdEntrega);
    setNumeroAutoparte(numeroAutoparte);
    setCuitEmpresa(cuitEmpresa);
    setFechaEntrega(FechaEntrega);
    setCantidadUnidades(cantidadUnidades);
    setImporte(importe);
}

// GETTERS
int Entrega::getIdEntrega() {
    return _identrega;
}

int Entrega::getNumeroAutoparte() {
    return _NumeroAutoparte;
}

std::string Entrega::getCuitEmpresa() {
    return std::string(_cuitEmpresa);
}

Fecha Entrega::getFechaEntrega() {
    return _fechaEntrega;
}

int Entrega::getCantidadUnidades() {
    return _CantidadUnidades;
}

float Entrega::getImporte() {
    return _importe;
}
bool Entrega::getActivo() {
    return _activo;
}

// SETTERS
void Entrega::setIdEntrega(int IdEntrega) {
    _identrega = IdEntrega;
}

void Entrega::setNumeroAutoparte(int numeroAutoparte) {
    _NumeroAutoparte = numeroAutoparte;
}

void Entrega::setCuitEmpresa(std::string cuitEmpresa) {
    strcpy(_cuitEmpresa, cuitEmpresa.c_str());
}

void Entrega::setFechaEntrega(Fecha fechaEntrega) {
    _fechaEntrega = fechaEntrega;
}

void Entrega::setCantidadUnidades(int cantidadUnidades) {
    _CantidadUnidades = cantidadUnidades;
}

void Entrega::setImporte(float importe) {
    _importe = importe;
}
void Entrega::setActivo(bool activo) {
    _activo = activo;
}

void Entrega::mostrar() {
    std::cout << "ID entrega: " << getIdEntrega() << std::endl;
    std::cout << "CUIT empresa: " << getCuitEmpresa() << std::endl;
    std::cout << "ID autoparte: " << getNumeroAutoparte() << std::endl;
    std::cout << "Fecha: " << getFechaEntrega().toString() << std::endl;
    std::cout << "Cantidad: " << getCantidadUnidades() << std::endl;
    std::cout << "Importe: $" << getImporte() << std::endl;

    if (getActivo()) {
        std::cout << "Estado: Activa" << std::endl;
    } else {
        std::cout << "Estado: Inactiva" << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
}
