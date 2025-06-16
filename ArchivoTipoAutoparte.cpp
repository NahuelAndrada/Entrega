#include "ArchivoTipoAutoparte.h"
#include <cstdio>

ArchivoTipoAutoparte::ArchivoTipoAutoparte() {
    strcpy(nombreArchivo, "tipo_autopartes.dat");
}

ArchivoTipoAutoparte::ArchivoTipoAutoparte(const char* nombre) {
    strcpy(nombreArchivo, nombre);
}

TipoAutoparte ArchivoTipoAutoparte::leerUno(int pos) {
    TipoAutoparte reg;
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * sizeof(TipoAutoparte), SEEK_SET);
    fread(&reg, sizeof(TipoAutoparte), 1, p);
    fclose(p);
    return reg;
}

bool ArchivoTipoAutoparte::guardar(TipoAutoparte reg) {
    FILE* p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;

    bool ok = fwrite(&reg, sizeof(TipoAutoparte), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoTipoAutoparte::modificar(TipoAutoparte reg, int pos) {
    FILE* p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * sizeof(TipoAutoparte), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(TipoAutoparte), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoTipoAutoparte::eliminar(int pos) {
    TipoAutoparte reg = leerUno(pos);
    reg.setActivo(false);
    return modificar(reg, pos);
}

int ArchivoTipoAutoparte::cantidad() {
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int tam = ftell(p);
    fclose(p);

    return tam / sizeof(TipoAutoparte);
}

void ArchivoTipoAutoparte::listarActivos() {
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    TipoAutoparte reg;
    while (fread(&reg, sizeof(TipoAutoparte), 1, p)) {
        if (reg.getActivo()) {
            reg.mostrar();
        }
    }
    fclose(p);
}
