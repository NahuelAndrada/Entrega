#ifndef AUTOPARTE_H_INCLUDED
#define AUTOPARTE_H_INCLUDED

class Autoparte {
private:
    int _numero;
    char _nombre[50];
    int _tipo;
    int _stock;
    bool _activo;

public:
    Autoparte();
    Autoparte(int numero, const char* nombre, int tipo, int stock, bool activo);

    void setNumero(int numero);
    void setNombre(const char* nombre);
    void setTipo(int tipo);
    void setStock(int stock);
    void setActivo(bool activo);

    int getNumero();
    const char* getNombre();
    int getTipo();
    int getStock();
    bool getActivo();

    void mostrar();
};

#endif
