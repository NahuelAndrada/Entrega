#include "ArchivoTipoAutoparte.h"
#include <cstdio>

ArchivoTipoAutoparte::ArchivoTipoAutoparte() {
    _nombreArchivo= "tipo_autopartes.dat";
}

ArchivoTipoAutoparte::ArchivoTipoAutoparte(std::string nombreArchivo){
  _nombreArchivo = nombreArchivo;
}

TipoAutoparte ArchivoTipoAutoparte::leerUno(int pos) {
    TipoAutoparte reg;
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return reg;

    fseek(pFile, pos * sizeof(TipoAutoparte), SEEK_SET);
    fread(&reg, sizeof(TipoAutoparte), 1, pFile);
    fclose(pFile);
    return reg;
}

bool ArchivoTipoAutoparte::guardar(TipoAutoparte reg) {
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return false;

    bool ok = fwrite(&reg, sizeof(TipoAutoparte), 1, pFile);
    fclose(pFile);
    return ok;
}

bool ArchivoTipoAutoparte::modificar(TipoAutoparte reg, int pos) {
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb+");
    if (pFile == nullptr) return false;


    fseek(pFile, pos * sizeof(TipoAutoparte), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(TipoAutoparte), 1, pFile);
    fclose(pFile);
    return ok;
}

bool ArchivoTipoAutoparte::eliminar(int pos) {
    TipoAutoparte reg = leerUno(pos);
    reg.setActivo(false);
    return modificar(reg, pos);
}

int ArchivoTipoAutoparte::cantidad() {
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return 0;

    fseek(pFile, 0, SEEK_END);
    int tam = ftell(pFile);
    fclose(pFile);

    return tam / sizeof(TipoAutoparte);
}

void ArchivoTipoAutoparte::listarActivos() {
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    TipoAutoparte reg;
    TipoAutoparteManager prueba;
    while (fread(&reg, sizeof(TipoAutoparte), 1, pFile)) {
        if (reg.getActivo()) {
            prueba.Listar();
        }
    }
    fclose(pFile);
}
