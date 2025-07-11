#pragma once
#include <string>


class Fecha{
    private:
    int _dia, _mes, _anio;

    public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia();
    int getMes();
    int getAnio();
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    std::string toString();
    bool DiaValido(int dia);
    bool MesValido(int Mes);
    bool AnioValido(int Anio);
    bool Validarfecha(int dia, int mes, int anio);
};
