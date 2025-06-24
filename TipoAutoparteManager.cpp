#include "TipoAutoparteManager.h"
#include "ArchivoTipoAutoparte.h"
#include "TipoAutoparte.h"
#include <iostream>
using namespace std;

void TipoAutoparteManager::cargar() {
    int numero;
    string nombre;
    char opcion;
    ArchivoTipoAutoparte archivo;

    while (true) {
        cout << "Numero tipo autoparte: ";
        cin >> numero;

        int pos = archivo.buscarPorNumero(numero);
        if (pos != -1) {
            TipoAutoparte existente = archivo.leer(pos);
            if (existente.getActivo()) {
                cout << "Ya existe un tipo de autoparte activo con ese numero." << endl;
            } else {
                cout << "Ese n£mero pertenece a un tipo de autoparte que est  inactivo." << endl;

                do {
                    cout << "¨Desea reactivarlo? (S/N): ";
                    cin >> opcion;
                    opcion = toupper(opcion);
                    if (opcion != 'S' && opcion != 'N') {
                        cout << "Opcion invalida. Escriba 'S' para si o 'N' para no." << endl;
                    }
                } while (opcion != 'S' && opcion != 'N');

                if (opcion == 'S') {
                    existente.setActivo(true);
                    if (archivo.modificar(pos, existente)) {
                        cout << "Tipo de autoparte reactivado correctamente." << endl;
                    } else {
                        cout << "Error al reactivar tipo de autoparte." << endl;
                    }
                    return;
                } else {
                    continue;
                }
            }

            do {
                cout << "Desea ingresar otro numero? (S/N): ";
                cin >> opcion;
                opcion = toupper(opcion);
                if (opcion != 'S' && opcion != 'N') {
                    cout << "Opcion invalida. Escriba 'S' para si o 'N' para no." << endl;
                }
            } while (opcion != 'S' && opcion != 'N');

            if (opcion == 'N') return;
            else continue;
        }

        break;
    }

    cin.ignore();
    cout << "Nombre tipo autoparte: ";
    getline(cin, nombre);

    TipoAutoparte reg(numero, nombre);
    if (archivo.guardar(reg)) cout << "Guardado con exito." << endl;
    else cout << "Error al guardar." << endl;
}

void TipoAutoparteManager::listar() {
    ArchivoTipoAutoparte archivo;
    int total = archivo.contar();
    bool hayActivos = false;

    cout << "=== LISTADO DE TIPOS DE AUTOPARTE ACTIVOS ===\n";

    for (int i = 0; i < total; i++) {
        TipoAutoparte reg = archivo.leer(i);
        if (reg.getActivo()) {
            hayActivos = true;
            cout << "ID: " << reg.getNumero() << " - Nombre: " << reg.getNombre() << endl;
        }
    }

    if (!hayActivos) {
        cout << "No hay tipos de autoparte activos registrados." << endl;
    }
}

void TipoAutoparteManager::listarInactivos() {
    ArchivoTipoAutoparte archivo;
    int total = archivo.contar();
    bool hayInactivos = false;

    cout << "=== LISTADO DE TIPOS DE AUTOPARTE INACTIVOS ===\n";

    for (int i = 0; i < total; i++) {
        TipoAutoparte reg = archivo.leer(i);
        if (!reg.getActivo()) {
            hayInactivos = true;
            cout << "ID: " << reg.getNumero() << " - Nombre: " << reg.getNombre() << endl;
        }
    }

    if (!hayInactivos) {
        cout << "No hay tipos de autoparte inactivos registrados." << endl;
    }
}

void TipoAutoparteManager::buscarPorID() {
    ArchivoTipoAutoparte archivo;
    int numero;
    char opcion;

    while (true) {
        cout << "Ingrese el ID del tipo de autoparte a buscar: ";
        cin >> numero;

        int pos = archivo.buscarPorNumero(numero);
        if (pos == -1) {
            cout << "Tipo de autoparte no encontrado." << endl;

            do {
                cout << "Desea intentar con otro ID? (S/N): ";
                cin >> opcion;
                opcion = toupper(opcion);
                if (opcion != 'S' && opcion != 'N') {
                    cout << "Opcion invalida. Escriba 'S' para si o 'N' para no." << endl;
                }
            } while (opcion != 'S' && opcion != 'N');

            if (opcion == 'N') return;
        } else {
            TipoAutoparte tipo = archivo.leer(pos);
            tipo.mostrar();
            return;
        }
    }
}

void TipoAutoparteManager::modificar() {
    ArchivoTipoAutoparte archivo;
    int id;
    cout << "Ingrese el ID del tipo de autoparte a modificar: ";
    cin >> id;

    int pos = archivo.buscarPorNumero(id);
    if (pos == -1) {
        cout << "Tipo de autoparte no encontrado.\n";
        return;
    }

    TipoAutoparte tipo = archivo.leer(pos);

    cin.ignore();
    string nuevoNombre;
    cout << "Nombre actual: " << tipo.getNombre() << "\n";
    cout << "Ingrese el nuevo nombre: ";
    getline(cin, nuevoNombre);
    tipo.setNombre(nuevoNombre);

    bool estado;
    cout << "Estado actual (1 = activo, 0 = inactivo): " << tipo.getActivo() << "\n";
    cout << "Desea modificar el estado? (1 = activo, 0 = inactivo): ";
    cin >> estado;
    tipo.setActivo(estado);

    if (archivo.modificar(pos, tipo)) {
        cout << "Tipo de autoparte modificado correctamente.\n";
    } else {
        cout << "Error al modificar tipo de autoparte.\n";
    }
}

void TipoAutoparteManager::eliminar() {
    int numero;
    cout << "Numero de tipo de autoparte a eliminar: ";
    cin >> numero;

    ArchivoTipoAutoparte archivo;
    int total = archivo.contar();

    for (int i = 0; i < total; i++) {
        TipoAutoparte reg = archivo.leer(i);
        if (reg.getNumero() == numero && reg.getActivo()) {
            reg.setActivo(false);
            if (archivo.modificar(i, reg)) {
                cout << "Tipo de autoparte dado de baja (inactivo)." << endl;
            } else {
                cout << "Error al modificar." << endl;
            }
            return;
        }
    }

    cout << "Tipo de autoparte no encontrado o ya inactivo." << endl;
}
