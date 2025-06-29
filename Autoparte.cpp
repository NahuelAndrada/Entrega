#include "Autoparte.h"
#include "TipoAutoparte.h"
#include "ArchivoAutopartes.h"
#include"ArchivoTipoAutoparte.h"
#include <iostream>
#include <cstring>
using namespace std;

Autoparte::Autoparte() {
    _numero=0;
    strcpy(_nombre,"");
    _tipo=0;
    _stock=0;
    _activo=true;
}

Autoparte::Autoparte(int numero, const std::string nombre, int tipo, int stock, bool activo) {
    setNumero(numero);
    setNombre(nombre);
    setTipo(tipo);
    setStock(stock);
    setActivo(activo);
}

void Autoparte::setNumero(int numero){
    _numero = numero;
}
void Autoparte::setNombre(std::string nombre){
    strcpy(_nombre, nombre.c_str());
}
void Autoparte::setTipo(int tipo){
    _tipo = tipo;
}
void Autoparte::setStock(int stock){
    _stock = stock;

}
void Autoparte::setActivo(bool activo){
    _activo = activo;
}

int Autoparte::getNumero(){
    return _numero;
}
std::string Autoparte::getNombre(){
    return std::string(_nombre);
}
int Autoparte::getTipo(){
    return _tipo;
}
int Autoparte::getStock(){
    return _stock;
}
bool Autoparte::getActivo(){
    return _activo;
}

std::string Autoparte::getDescripcionTipo() {
    ArchivoTipoAutoparte archivo;
    int pos = archivo.buscarPorNumero(_tipo);
    if (pos >= 0) {
        TipoAutoparte tipo = archivo.leer(pos);
        return tipo.getNombre();
    }
    return "(tipo no encontrado)";
}

void Autoparte::mostrar() {
    cout << "Numero: " << _numero << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Tipo: " << _tipo << " (" << getDescripcionTipo() << ")" << endl;

    cout << "Stock: " << _stock << endl;
    if (getActivo()) {
        cout << "Activo: Si" << endl;
    } else {
        cout << "Activo: No" << endl;
    }
    cout << "---------------------" << endl;
}
