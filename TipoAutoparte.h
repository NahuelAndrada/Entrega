#ifndef TIPOAUTOPARTE_H_INCLUDED
#define TIPOAUTOPARTE_H_INCLUDED

class TipoAutoparte {
private:
    int _numero;
    char _nombre[50];

public:
    TipoAutoparte();
    TipoAutoparte(int numero);
    TipoAutoparte(int numero, const char* nombre);

    void setTipo(int numero, const char* nombre);

    void setNumero(int numero);
    void setNombre(const char* nombre);
    void setNombre(int numero, const char* nombre);

    int getNumero() const;
    const char* getNombre() const;
};

#endif
