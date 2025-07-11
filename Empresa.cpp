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

    set_CUIT(CUIT);
    set_Nombre(Nombre);
    set_Responsable(Responsable);
    set_Telefono(Telefono);
    set_Email(Email);
    set_Direccion(Direccion);
    set_Activo(Activo);
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
void Empresa::set_CUIT(std::string CUIT){
    strcpy(_CUIT, CUIT.c_str());
}
void Empresa::set_Nombre(std::string Nombre){
    strcpy(_Nombre, Nombre.c_str());
}
void Empresa::set_Responsable(std::string Responsable){
    strcpy(_Responsable, Responsable.c_str());
}
void Empresa::set_Telefono(std::string Telefono){
    strcpy(_Telefono, Telefono.c_str());
}
void Empresa::set_Email(std::string Email){
    strcpy(_Email, Email.c_str());
}
void Empresa::set_Direccion(std::string Direccion){
    strcpy(_Direccion, Direccion.c_str());
}
void Empresa::set_Activo(bool Activo){
    _Activo = Activo;
}

std::string Empresa::toCSV() {
    return ">> CUIT: " + std::string(_CUIT) + "\n" +
           ">> Nombre: " + std::string(_Nombre) + "\n" +
           ">> Direccion: " + std::string(_Direccion) + "\n" +
           ">> Responsable: " + std::string(_Responsable) + "\n" +
           ">> Email: " + std::string(_Email) + "\n" +
           ">> Telefono: " + std::string(_Telefono) + "\n" +
           "____________________\n";
}
