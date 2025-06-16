#ifndef TIPOAUTOPARTE_H_INCLUDED
#define TIPOAUTOPARTE_H_INCLUDED
#include <string>

class TipoAutoparte {
private:
    int _Tipo;
    char _nombre[50];
    bool _activo;

public:
    TipoAutoparte();
    TipoAutoparte(int Tipo, std::string nombre);


    // SETTERS
    void setIdTipo(int id);
    void setNombre(std::string nombre);
    void setActivo(bool activo);

    // GETTERS
    int getIdTipo() const;
    const char* getNombre() const;
    bool getActivo() const;
};

#endif // TIPOAUTOPARTE_H_INCLUDED
