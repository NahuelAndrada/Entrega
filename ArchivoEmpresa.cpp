#include "ArchivoEmpresa.h"

ArchivoEmpresa::ArchivoEmpresa(){
    _nombreArchivo = "empresas.dat";
}
int ArchivoEmpresa::get_CantidadRegistros(){

    int total, cantidad;
    FILE* pFile;

    pFile = fopen(_nombreArchivo.c_str(), "rb"); //lee (no escribe)

    if(pFile == nullptr){
        return 0;
    }

    fseek(pFile, 0, SEEK_END);
    total = ftell(pFile);
    cantidad = total / sizeof(Empresa);

    fclose(pFile);

    return cantidad;
}
bool ArchivoEmpresa::guardarEmpresa(Empresa registro){

    FILE *pFile;
    bool status;

    pFile = fopen(_nombreArchivo.c_str(),"ab");

    if(pFile == nullptr){
        return false;
    }

    status = fwrite(&registro, sizeof(Empresa), 1, pFile);

    fclose(pFile);
    return status;
}
bool ArchivoEmpresa::guardarEmpresa(Empresa registro, int posicion){

    FILE *pFile;
    bool status;

    pFile = fopen(_nombreArchivo.c_str(),"rb+"); //rb = leer y escribir (sin borrar)

    if(pFile == nullptr){
        return false;
    }

    fseek(pFile, posicion * sizeof(Empresa), SEEK_SET);
    status = fwrite(&registro, sizeof(Empresa), 1, pFile);

    fclose(pFile);
    return status;

}
Empresa ArchivoEmpresa::leerEmpresa(int posicion){

    FILE *pFile;
    Empresa registro;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile == nullptr){
        return registro;
    }

    fseek(pFile, sizeof(Empresa) * posicion, SEEK_SET);
    fread(&registro, sizeof(Empresa), 1, pFile);
    fclose(pFile);

    return registro;

}
