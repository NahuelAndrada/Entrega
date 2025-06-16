#include "Autoparte.h"
#include <cstring>
#include <sstream>
#include <ioStream>
using namespace std;

    Autoparte::Autoparte(){
        _numeroAutoparte = 0;
        strcpy(_nombre, "");
        TipoAutoparte _Tipo;
        _stock = 0;
        _activo = true;
    }

    Autoparte::Autoparte(int numeroAutoparte,const char* nombre,TipoAutoparte tipo,int stock, bool activo){
        _numeroAutoparte = numeroAutoparte;
        strcpy(_nombre, nombre);
        _tipo = tipo;
        _stock = stock;
        _activo = activo;
    }

    void Autoparte::setNumeroAutoparte(int numero){
        _numeroAutoparte=numero;
    }
    void Autoparte::setNombre(const char* nombre){
        strcpy(_nombre,nombre);
    }
    void Autoparte::setTipo(TipoAutoparte tipo){
        _tipo=tipo;
    }
    void Autoparte::setStock(int stock){
        _stock=stock;
    }
    void Autoparte::setActivo(bool activo){
        _activo=activo;
    }

    int Autoparte::getNumeroAutoparte(){
        return _numeroAutoparte;
    }
    const char* Autoparte::getNombreAutoparte(){
        return _nombre;
    }
    TipoAutoparte Autoparte::getTipo(){
        return _tipo;
    }
    int Autoparte::getStock(){
        return _stock;
    }
    bool Autoparte::getActivo(){
        return _activo;
    }

    void Autoparte::mostrar() {
    cout << "ID: " << _numeroAutoparte
         << " - Nombre: " << _nombre
         << " - Tipo: " << _tipo.getNombre()
         << " - Stock: " << _stock
         << " - Activo: " << (_activo ? "Si" : "No")
         << endl;
    }

