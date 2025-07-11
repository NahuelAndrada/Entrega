#ifndef TIPOAUTOPARTE_H_INCLUDED
#define TIPOAUTOPARTE_H_INCLUDED

#include <string>

class TipoAutoparte {
private:
    int _numero;
    char _nombre[50];
    bool _activo;

public:
    TipoAutoparte();
    TipoAutoparte(int numero, std::string nombre, bool activo = true);

    void setNumero(int numero);
    void setNombre(const std::string nombre);
    void setActivo(bool activo);

    int getNumero();
    std::string getNombre();
    bool getActivo();

    void mostrar();
};

#endif
