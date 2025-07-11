#include "Fecha.h"

Fecha::Fecha(){
    _dia = 0;
    _mes = 0;
    _anio = 0;
}

Fecha::Fecha(int dia, int mes, int anio){
    _dia = dia;
    _mes = mes;
    _anio = anio;
}

int Fecha::getDia(){
    return _dia;
}

int Fecha::getMes(){
    return _mes;
}

int Fecha::getAnio(){
    return _anio;
}

void Fecha::setDia(int dia){
    _dia = dia;
}

void Fecha::setMes(int mes){
    _mes = mes;
}

void Fecha::setAnio(int anio){
    _anio = anio;
}

std::string Fecha::toString(){
    return std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio);
}

bool Fecha::DiaValido(int dia){
        if(dia<1||dia>31){
        return false;}
        return true;
}
bool Fecha::MesValido(int mes){
        if (mes < 1 || mes > 12) return false;
        return true;
}
bool Fecha::AnioValido(int anio){
    if (anio < 1900 || anio > 2026) return false;

    return true;
}
bool Fecha::Validarfecha(int dia, int mes, int anio){

    if (anio < 1900 || mes < 1 || mes > 12 || dia < 1) return false;

    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        diasPorMes[1] = 29;
    }

    if (dia>diasPorMes[mes-1])return false;

    return true;
}
