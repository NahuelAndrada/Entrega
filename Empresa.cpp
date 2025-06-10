#include "Empresa.h"

#include "string"  //Para usar el std::string
#include "cstring" //Para usar el strcopy

//Constructores
Empresa::Empresa(){
    strcpy(_CUIT, "");
    strcpy(_Nombre, "");
    strcpy(_Responsable, "");
    strcpy(_Telefono, "");
    strcpy(_Email, "");
    strcpy(_Direccion, "");
    _Activo = true;
}

Empresa::Empresa(std::string CUIT, std::string Nombre, std::string Responsable, std::string Telefono, std::string Email, std::string Direccion, bool Activo){
    strcpy(_CUIT, CUIT.c_str());
    strcpy(_Nombre, Nombre.c_str());
    strcpy(_Responsable, Responsable.c_str());
    strcpy(_Telefono, Telefono.c_str());
    strcpy(_Email, Email.c_str());
    strcpy(_Direccion, Direccion.c_str());
    _Activo = Activo;
}

//Getters
std::string Empresa::get_CUIT(){
    return _CUIT;
}

std::string Empresa::get_Nombre(){
    return _Nombre;
}

std::string Empresa::get_Responsable(){
    return _Responsable;
}

std::string Empresa::get_Telefono(){
    return _Telefono;
}

std::string Empresa::get_Email(){
    return _Email;
}

std::string Empresa::get_Direccion(){
    return _Direccion;
}

bool Empresa::get_Activo(){
    return _Activo;
}

//Setters
bool Empresa::set_CUIT(std::string CUIT){
    //Control de longitud para el vector:
    if(CUIT.length() >= sizeof _CUIT){
        return false;
    }
    strcpy(_CUIT, CUIT.c_str());
    return true;
}

bool Empresa::set_Nombre(std::string Nombre){
    //Control de longitud para el vector:
    if(Nombre.length() >= sizeof _Nombre){
        return false;
    }
    strcpy(_Nombre, Nombre.c_str());
    return true;
}

bool Empresa::set_Responsable(std::string Responsable){
    //Control de longitud para el vector:
    if(Responsable.length() >= sizeof _Responsable){
        return false;
    }
    strcpy(_Responsable, Responsable.c_str());
    return true;
}

bool Empresa::set_Telefono(std::string Telefono){
    //Control de longitud para el vector:
    if(Telefono.length() >= sizeof _Telefono){
        return false;
    }
    strcpy(_Telefono, Telefono.c_str());
    return true;
}

bool Empresa::set_Email(std::string Email){
    //Control de longitud para el vector:
    if(Email.length() >= sizeof _Email){
        return false;
    }
    strcpy(_Email, Email.c_str());
    return true;
}

bool Empresa::set_Direccion(std::string Direccion){
    //Control de longitud para el vector:
    if(Direccion.length() >= sizeof _Direccion){
        return false;
    }
    strcpy(_Direccion, Direccion.c_str());
    return true;
}

bool Empresa::set_Activo(bool Activo){
    _Activo = Activo;
    return true;
}

std::string Empresa::toCSV(){
    std::string str = std::string(_CUIT) + "," +
                      std::string(_Nombre) + "," +
                      std::string(_Responsable) + "," +
                      std::string(_Telefono) + "," +
                      std::string(_Email) + "," +
                      std::string(_Direccion);
    return str;
}
