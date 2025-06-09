#include "ArchivoAutopartes.h"
#include <fstream>

ArchivoAutopartes::ArchivoAutopartes() {
    strcpy(nombreArchivo,"autopartes.dat");
}

ArchivoAutopartes::ArchivoAutopartes(const char* nombre) {
    strcpy(nombreArchivo, nombre);
}

Autoparte ArchivoAutopartes::LeerUna(int pos) {
    Autoparte reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * sizeof(Autoparte), SEEK_SET);
    fread(&reg, sizeof(Autoparte), 1, p);
    fclose(p);
    return reg;
}

/*int ArchivoAutopartes::LeerMuchas(Autoparte* vec, int cantidad) {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;

    int leidos = fread(vec, sizeof(Autoparte), cantidad, p);
    fclose(p);
    return leidos;
}*/

bool ArchivoAutopartes::Guardar(Autoparte reg) {
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;

    bool ok = fwrite(&reg, sizeof(Autoparte), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoAutopartes::Modificar(Autoparte reg, int pos) {
    FILE *p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * sizeof(Autoparte), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Autoparte), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoAutopartes::Eliminar(int pos) {
    Autoparte reg = LeerUna(pos);
    reg.setActivo(false);
    return Modificar(reg, pos);
}

int ArchivoAutopartes::CantidadAutopartes() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int tam = ftell(p);
    fclose(p);

    return tam / sizeof(Autoparte);
}

int ArchivoAutopartes::BuscarPosicion(int numero) {
    int cantidad = CantidadAutopartes();
    for (int i = 0; i < cantidad; i++) {
        Autoparte reg = LeerUna(i);
        if (reg.getNumeroAutoparte() == numero) {
            return i;
        }
    }
    return -1;
}

bool ArchivoAutopartes::Existe(int numero) {
    int pos = BuscarPosicion(numero);
    if(pos==-1){
        return false;
    }

    Autoparte reg = LeerUna(pos);
    return reg.getActivo();
}
