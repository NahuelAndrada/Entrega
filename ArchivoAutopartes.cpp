#include "ArchivoAutopartes.h"
#include <cstdio>
#include <cstring>

ArchivoAutopartes::ArchivoAutopartes(std::string nombreArchivo) {
    _nombreArchivo= nombreArchivo;
}

Autoparte ArchivoAutopartes::leer(int pos) {

    Autoparte reg;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
        return reg;
    }
    fseek(p, pos * sizeof(Autoparte), SEEK_SET);
    fread(&reg, sizeof(Autoparte), 1, p);
    fclose(p);
    return reg;

}

bool ArchivoAutopartes::guardar(Autoparte reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == nullptr) return false;
    bool ok = fwrite(&reg, sizeof(Autoparte), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoAutopartes::modificar(int pos, Autoparte reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Autoparte), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Autoparte), 1, p);
    fclose(p);
    return ok;
}

int ArchivoAutopartes::contar() {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Autoparte);
}

int ArchivoAutopartes::buscarPorNumero(int numero) {
    Autoparte reg;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;
    int pos = 0;
    while (fread(&reg, sizeof(Autoparte), 1, p)) {
        if (reg.getNumero() == numero) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int ArchivoAutopartes::buscarPorNombre(const char* nombre) {
    Autoparte reg;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;
    int pos = 0;
    while (fread(&reg, sizeof(Autoparte), 1, p)) {
        if (strcmp(reg.getNombre().c_str(), nombre) == 0) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
