#ifndef AUTOPARTE_H_INCLUDED
#define AUTOPARTE_H_INCLUDED

#include "TipoAutoparte.h"
using namespace std;

class Autoparte{
    private:
    int _numeroAutoparte;
    char _nombre[50];
    TipoAutoparte _tipo;
    int _stock;
    bool _activo;

    public:
    Autoparte();
    Autoparte(int numeroAutoparte,const char* nombre,TipoAutoparte tipo,int stock, bool activo);

    int getNumeroAutoparte();
    const char* getNombreAutoparte();
    TipoAutoparte getTipo();
    int getStock();
    bool getActivo();

    void setNumeroAutoparte(int numero);
    void setNombre(const char* nombre);
    void setTipo(TipoAutoparte tipo);
    void setStock(int stock);
    void setActivo(bool activo);

    void mostrar();

};

#endif // AUTOPARTE_H_INCLUDED
