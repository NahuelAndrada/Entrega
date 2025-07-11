#ifndef AUTOPARTE_H_INCLUDED
#define AUTOPARTE_H_INCLUDED
#include<string>
using namespace std;

class Autoparte {
private:
    int _numero;
    char _nombre[50];
    int _tipo;
    int _stock;
    bool _activo;

public:
    Autoparte();
    Autoparte(int numero, const std::string nombre, int tipo, int stock, bool activo);

    void setNumero(int numero);
    void setNombre(const std::string nombre);
    void setTipo(int tipo);
    void setStock(int stock);
    void setActivo(bool activo);

    int getNumero();
    std::string getNombre();
    int getTipo();
    int getStock();
    bool getActivo();

    std::string getDescripcionTipo();
    void mostrar();
};

#endif
