#include "AutopartesManager.h"
#include "Autoparte.h"
#include "TipoAutoparte.h"
#include "ArchivoAutopartes.h"
#include "ArchivoTipoAutoparte.h"
#include <iostream>
#include <string>
using namespace std;

void AutopartesManager::cargarAutoparte() {
    system("cls");
    cout << "=== CARGAR AUTOPARTE ===\n" << endl;

    int numero;
    cout << "Ingrese el numero de la autoparte: ";
    cin >> numero;

    if (numero <= 0) {
        cout << "Numero invalido.\n";
        return;
    }

    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos >= 0) {
        Autoparte reg = arch.leer(pos);
        if (reg.getActivo()) {
            cout << "Ya existe una autoparte activa con ese numero.\n";
            return;
        } else {
            char opcion;
            cout << "Existe una autoparte INACTIVA con ese numero. Desea reactivarla? (s/n): ";
            cin >> opcion;
            if (opcion == 's' || opcion == 'S') {
                reg.setActivo(true);
                if (arch.modificar(pos, reg)) {
                    cout << "Autoparte reactivada correctamente.\n";
                } else {
                    cout << "No se pudo reactivar la autoparte.\n";
                }
            }
            return;
        }
    }

    cin.ignore();
    string nombre;
    cout << "Ingrese nombre: ";
    getline(cin, nombre);

    if (nombre.length() >= 50) {
        cout << "Nombre demasiado largo.\n";
        return;
    }

    ArchivoTipoAutoparte archTipo;
    int tipo;
    cout << "Ingrese numero de tipo de autoparte: ";
    cin >> tipo;
    if (archTipo.buscarPorNumero(tipo) < 0) {
        cout << "Tipo invalido.\n";
        return;
    }

    int stock;
    cout << "Ingrese stock inicial: ";
    cin >> stock;
    if (stock < 0) {
        cout << "Stock invalido.\n";
        return;
    }

    Autoparte reg(numero, nombre, tipo, stock, true);

    if (arch.guardar(reg)) {
        cout << "Autoparte guardada con exito.\n";
    } else {
        cout << "Error al guardar la autoparte.\n";
    }
}

void AutopartesManager::modificarAutoparte() {
    system("cls");
    cout << "=== MODIFICAR AUTOPARTE ===\n" << endl;

    int numero;
    cout << "Ingrese el numero de la autoparte a modificar: ";
    cin >> numero;

    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "No existe una autoparte con ese numero.\n";
        return;
    }

    Autoparte reg = arch.leer(pos);

    int opcion;
    do {
        system("cls");
        cout << "=== MODIFICAR AUTOPARTE ===\n\n";
        cout << "1. Modificar nombre\n";
        cout << "2. Modificar tipo\n";
        cout << "3. Modificar stock\n";
        cout << "4. Cambiar estado activo/inactivo\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string nuevoNombre;
                cout << "Nuevo nombre: ";
                getline(cin, nuevoNombre);
                if (nuevoNombre.length() >= 50) {
                    cout << "Nombre demasiado largo.\n";
                } else {
                    reg.setNombre(nuevoNombre);
                }
                break;
            }
            case 2: {
                ArchivoTipoAutoparte archTipo;
                int nuevoTipo;
                cout << "Nuevo tipo de autoparte: ";
                cin >> nuevoTipo;
                if (archTipo.buscarPorNumero(nuevoTipo) < 0) {
                    cout << "Tipo invalido.\n";
                } else {
                    reg.setTipo(nuevoTipo);
                }
                break;
            }
            case 3: {
                int nuevoStock;
                cout << "Nuevo stock: ";
                cin >> nuevoStock;
                if (nuevoStock < 0) {
                    cout << "Stock invalido.\n";
                } else {
                    reg.setStock(nuevoStock);
                }
                break;
            }
            case 4: {
                char act;
                cout << "Desea activar la autoparte? (s/n): ";
                cin >> act;
                reg.setActivo((act == 's' || act == 'S'));
                break;
            }
            case 0:
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    if (arch.modificar(pos, reg)) {
        cout << "Autoparte modificada con exito.\n";
    } else {
        cout << "Error al modificar la autoparte.\n";
    }
}

void AutopartesManager::listarAutoparteActivas() {
    system("cls");
    cout << "=== LISTADO DE AUTOPARTES ACTIVAS ===\n\n";

    ArchivoAutopartes arch;
    int total = arch.contar();
    bool hayActivas = false;

    for (int i = 0; i < total; i++) {
        Autoparte reg = arch.leer(i);
        if (reg.getActivo()) {
            hayActivas = true;
            reg.mostrar();
        }
    }

    if (!hayActivas) {
        cout << "No hay autopartes activas registradas.\n";
    }
}

void AutopartesManager::listarAutoparteInactivas() {
    system("cls");
    cout << "=== LISTADO DE AUTOPARTES INACTIVAS ===\n\n";

    ArchivoAutopartes arch;
    int total = arch.contar();
    bool hayInactivas = false;

    for (int i = 0; i < total; i++) {
        Autoparte reg = arch.leer(i);
        if (!reg.getActivo()) {
            hayInactivas = true;
            reg.mostrar();
        }
    }

    if (!hayInactivas) {
        cout << "No hay autopartes inactivas registradas.\n";
    }
}

void AutopartesManager::buscarAutopartePorNumero() {
    system("cls");
    cout << "=== BUSCAR AUTOPARTE POR NUMERO ===\n\n";

    int numero;
    cout << "Ingrese el numero de autoparte: ";
    cin >> numero;

    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);

    if (pos >= 0) {
        Autoparte reg = arch.leer(pos);
        if (reg.getActivo()) {
            reg.mostrar();
        } else {
            cout << "La autoparte esta INACTIVA.\n";
            char opcion;
            cout << "Desea reactivarla? (s/n): ";
            cin >> opcion;
            if (opcion == 's' || opcion == 'S') {
                reg.setActivo(true);
                if (arch.modificar(pos, reg)) {
                    cout << "Autoparte reactivada correctamente.\n";
                    reg.mostrar();
                } else {
                    cout << "Error al reactivar la autoparte.\n";
                }
            }
        }
    } else {
        cout << "Autoparte no encontrada.\n";
    }
}

void AutopartesManager::buscarAutopartePorNombre() {
    system("cls");
    cout << "=== BUSCAR AUTOPARTE POR NOMBRE ===\n\n";

    string nombre;
    cin.ignore();
    cout << "Ingrese el nombre de la autoparte: ";
    getline(cin, nombre);

    ArchivoAutopartes arch;
    int total = arch.contar();
    bool encontrada = false;

    for (int i = 0; i < total; i++) {
        Autoparte reg = arch.leer(i);
        if (reg.getNombre() == nombre) {
            if (reg.getActivo()) {
                reg.mostrar();
            } else {
                cout << "La autoparte esta inactiva.\n";
                char opc;
                cout << "Desea reactivarla? (s/n): ";
                cin >> opc;
                if (opc == 's' || opc == 'S') {
                    reg.setActivo(true);
                    if (arch.modificar(i, reg)) {
                        cout << "Autoparte reactivada correctamente.\n";
                        reg.mostrar();
                    } else {
                        cout << "Error al reactivar la autoparte.\n";
                    }
                }
            }
            encontrada = true;
            break;
        }
    }

    if (!encontrada) {
        cout << "Autoparte no encontrada.\n";
    }
}

void AutopartesManager::eliminarAutoparte() {
    system("cls");
    cout << "=== ELIMINAR AUTOPARTE ===\n\n";

    int numero;
    cout << "Ingrese el numero de autoparte a eliminar: ";
    cin >> numero;

    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "Autoparte no encontrada.\n";
        return;
    }

    Autoparte reg = arch.leer(pos);
    if (!reg.getActivo()) {
        cout << "La autoparte ya esta dada de baja.\n";
        return;
    }

    reg.setActivo(false);
    if (arch.modificar(pos, reg)) {
        cout << "Autoparte dada de baja correctamente.\n";
    } else {
        cout << "Error al dar de baja la autoparte.\n";
    }
}



