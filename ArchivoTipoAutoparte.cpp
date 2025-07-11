#include "ArchivoTipoAutoparte.h"
#include <cstdio>

ArchivoTipoAutoparte::ArchivoTipoAutoparte(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

TipoAutoparte ArchivoTipoAutoparte::leer(int pos) {
    TipoAutoparte reg;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(TipoAutoparte), SEEK_SET);
    fread(&reg, sizeof(TipoAutoparte), 1, p);
    fclose(p);
    return reg;
}

bool ArchivoTipoAutoparte::guardar(TipoAutoparte reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == nullptr) return false;
    bool ok = fwrite(&reg, sizeof(TipoAutoparte), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoTipoAutoparte::modificar(int pos, TipoAutoparte reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(TipoAutoparte), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(TipoAutoparte), 1, p);
    fclose(p);
    return ok;
}

int ArchivoTipoAutoparte::contar() {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes/sizeof(TipoAutoparte);
}

int ArchivoTipoAutoparte::buscarPorNumero(int numero) {
    TipoAutoparte reg;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;
    int pos = 0;
    while (fread(&reg, sizeof(TipoAutoparte), 1, p)) {
        if (reg.getNumero() == numero) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
