#include "TipoAutoparteManager.h"
#include "ArchivoTipoAutoparte.h"
#include "TipoAutoparte.h"
#include <iostream>
using namespace std;

void TipoAutoparteManager::Cargar() {
    TipoAutoparte reg;
    ArchivoTipoAutoparte archivo;
    archivo.guardar(reg);
    cout << "Tipo de autoparte guardado correctamente." << endl;
}

void TipoAutoparteManager::Eliminar(int numero) {
    ArchivoTipoAutoparte archivo;
    int total = archivo.cantidad();
    for (int i = 0; i < total; i++) {
        TipoAutoparte reg = archivo.leerUno(i);
        if (reg.getIdTipo() == numero && reg.getActivo()) {
            archivo.eliminar(i);
            cout << "Tipo de autoparte eliminado." << endl;
            return;
        }
    }
    cout << "Tipo de autoparte no encontrado o ya eliminado." << endl;
}



int TipoAutoparteManager::BuscarPorNumero(int numero) {
    ArchivoTipoAutoparte archivo;
    int total = archivo.cantidad();
    for (int i = 0; i < total; i++) {
        TipoAutoparte reg = archivo.leerUno(i);
        if (reg.getIdTipo() == numero && reg.getActivo()) {
            return i;
        }
    }
    return -1;
}

void TipoAutoparteManager::Listar() {
    ArchivoTipoAutoparte archivo;
    archivo.listarActivos();
}

void TipoAutoparteManager::Menu() {
    int opcion, numero;

    do {
        cout << "\n=== MENU TIPO DE AUTOPARTES ===" << endl;
        cout << "1. Cargar nuevo tipo" << endl;
        cout << "2. Eliminar tipo" << endl;
        cout << "3. Modificar tipo" << endl;
        cout << "4. Buscar tipo por n�mero" << endl;
        cout << "5. Listar tipos activos" << endl;
        cout << "0. Volver al men� principal" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                Cargar();
                break;
            case 2:
                cout << "Ingrese el n�mero del tipo a eliminar: ";
                cin >> numero;
                Eliminar(numero);
                break;
            case 3:
                break;
            case 4:
                cout << "Ingrese el n�mero del tipo a buscar: ";
                cin >> numero;
                if (BuscarPorNumero(numero) >= 0)
                    cout << "Tipo de autoparte encontrado y activo." << endl;
                else
                    cout << "Tipo de autoparte no encontrado o inactivo." << endl;
                break;
            case 5:
                Listar();
                break;
            case 0:
                cout << "Volviendo al men� principal..." << endl;
                break;
            default:
                cout << "Opci�n inv�lida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);
}
