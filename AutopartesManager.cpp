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
    Autoparte reg;
    int numero, tipo, stock;
    std::string nombre;
    bool activo = true;

    cout << "=== CARGAR NUEVA AUTOPARTE ===" << endl;

    ArchivoAutopartes arch;

    // Validación del número
    while (true) {
        cout << "Numero de autoparte: ";
        cin >> numero;
        if (numero <= 0) {
            cout << "Error: El numero debe ser mayor que cero." << endl;
            continue;
        }

        int pos = arch.buscarPorNumero(numero);
        if (pos >= 0) {
            Autoparte existente = arch.leer(pos);
            if (existente.getActivo()) {
                cout << "Ya existe una autoparte ACTIVA con ese numero." << endl;
                return;
            } else {
                char opcion;
                cout << "Ya existe una autoparte INACTIVA con ese numero. ¿Desea reactivarla? (s/n): ";
                cin >> opcion;
                if (opcion == 's' || opcion == 'S') {
                    existente.setActivo(true);
                    if (arch.modificar(pos, existente)) {
                        cout << "Autoparte reactivada correctamente." << endl;
                    } else {
                        cout << "Error al reactivar la autoparte." << endl;
                    }
                }
                return;
            }
        }
        break;
    }
    cin.ignore();
    // Validar nombre
    while (true) {
        cout << "Nombre de autoparte: ";
        getline(cin, nombre);
        if (nombre.length() >= 50) {
            cout << "Error: El nombre no puede superar los 49 caracteres." << endl;
        } else {
            break;
        }
    }

    // Validar tipo
    ArchivoTipoAutoparte archivoTipo;
    int totalTipos = archivoTipo.contar();
    while (true) {
        cout << "--- TIPOS DE AUTOPARTE DISPONIBLES ---" << endl;
        for (int i = 0; i < totalTipos; i++) {
            TipoAutoparte tipoAux = archivoTipo.leer(i);
            if (tipoAux.getActivo()) {
                tipoAux.mostrar();
            }
        }

        cout << "Tipo de autoparte (ingrese el numero correspondiente): ";
        cin >> tipo;
        if (archivoTipo.buscarPorNumero(tipo) < 0) {
            cout << "Error: Tipo de autoparte no valido." << endl;
        } else {
            break;
        }
    }
    // Validar stock
    while (true) {
        cout << "Stock inicial: ";
        cin >> stock;
        if (stock < 0) {
            cout << "Error: El stock no puede ser negativo." << endl;
        } else {
            break;
        }
    }

    reg.setNumero(numero);
    reg.setNombre(nombre);
    reg.setTipo(tipo);
    reg.setStock(stock);
    reg.setActivo(activo);

    if (arch.guardar(reg)) {
        cout << "Autoparte guardada con exito." << endl;
    } else {
        cout << "Error al guardar la autoparte." << endl;
    }
}

void AutopartesManager::listarAutoparteActivas() {
    ArchivoAutopartes arch;
    int total = arch.contar();
    bool hayActivas = false;

    cout << "=== LISTADO DE AUTOPARTES ACTIVAS ===\n";

    for (int i = 0; i < total; i++) {
        Autoparte reg = arch.leer(i);
        if (reg.getActivo()){
            hayActivas=true;
            reg.mostrar();
        }
    }
    if(!hayActivas){
        cout << "No hay autopartes activas registradas." << endl;
    }
}

void AutopartesManager::listarAutoparteInactivas() {
    ArchivoAutopartes arch;
    int cantidad = arch.contar();
    bool hayInactivas = false;

    cout << "=== LISTADO DE AUTOPARTES INACTIVAS ===" << endl;

    for (int i = 0; i < cantidad; i++) {
        Autoparte reg = arch.leer(i);
        if (!reg.getActivo()) {
            reg.mostrar();
            hayInactivas = true;
        }
    }

    if (!hayInactivas) {
        cout << "No hay autopartes inactivas registradas." << endl;
    }
}

void AutopartesManager::buscarAutopartePorNumero() {
    int numero;
    cout << "Ingrese el numero de autoparte a buscar: ";
    cin >> numero;

    if (numero <= 0) {
        cout << "Error: El numero de autoparte debe ser mayor que cero." << endl;
        return;
    }

     ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);

    if (pos >= 0) {
        Autoparte reg = arch.leer(pos);
        if (reg.getActivo()) {
            cout << "=== AUTOPARTE ENCONTRADA ===" << endl;
            reg.mostrar();
        } else {
            cout << "La autoparte encontrada esta dada de baja (inactiva)." << endl;
        }
    } else {
        cout << "Autoparte no encontrada." << endl;
    }
}

void AutopartesManager::buscarAutopartePorNombre() {
    std::string nombre;
    cin.ignore();
    cout << "Ingrese el nombre de la autoparte a buscar: ";
    getline(cin, nombre);

    ArchivoAutopartes arch;
    int total = arch.contar();
    bool encontrada = false;

    for (int i = 0; i < total; i++) {
        Autoparte reg = arch.leer(i);
        if (reg.getActivo() && reg.getNombre() == nombre) {
            cout << "=== AUTOPARTE ENCONTRADA ===" << endl;
            reg.mostrar();
            encontrada = true;
            break;
        }
    }

    if (!encontrada) {
        cout << "Autoparte no encontrada." << endl;
    }
}


void AutopartesManager::modificarAutoparte() {
    system("cls");
    int numero;
    cout << "Ingrese el numero de la autoparte a modificar: ";
    cin >> numero;

    if (numero <= 0) {
        cout << "Numero invalido." << endl;
        return;
    }

    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "Autoparte no encontrada." << endl;
        return;
    }

    Autoparte reg = arch.leer(pos);
    if (!reg.getActivo()) {
        cout << "La autoparte esta dada de baja. No se puede modificar." << endl;
        return;
    }

    int opcion;
    do {
        system("cls");
        cout << "\n--- MENU DE MODIFICACION ---" << endl;
        cout << "1. Modificar nombre" << endl;
        cout << "2. Modificar tipo de autoparte" << endl;
        cout << "3. Modificar stock" << endl;
        cout << "4. Cambiar estado (activo/inactivo)" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cin.ignore();
                string nuevoNombre;
                while (true) {
                    cout << "Nuevo nombre: ";
                    getline(cin, nuevoNombre);
                    if (nuevoNombre.length() >= 50) {
                        cout << "Error: El nombre no puede superar los 49 caracteres." << endl;
                    } else {
                        break;
                    }
                }
                reg.setNombre(nuevoNombre);
                break;
            }
            case 2: {
                ArchivoTipoAutoparte archivoTipo;
                int totalTipos = archivoTipo.contar();
                int nuevoTipo;
                while (true) {
                    cout << "--- TIPOS DISPONIBLES ---" << endl;
                    for (int i = 0; i < totalTipos; i++) {
                        TipoAutoparte tipoAux = archivoTipo.leer(i);
                        if (tipoAux.getActivo()) {
                            tipoAux.mostrar();
                        }
                    }
                    cout << "Ingrese el numero del nuevo tipo: ";
                    cin >> nuevoTipo;
                    if (archivoTipo.buscarPorNumero(nuevoTipo) < 0) {
                        cout << "Error: Tipo no valido." << endl;
                    } else {
                        break;
                    }
                }
                reg.setTipo(nuevoTipo);
                break;
            }
            case 3: {
                int nuevoStock;
                while (true) {
                    cout << "Nuevo stock: ";
                    cin >> nuevoStock;
                    if (nuevoStock < 0) {
                        cout << "Error: El stock no puede ser negativo." << endl;
                    } else {
                        break;
                    }
                }
                reg.setStock(nuevoStock);
                break;
            }
            case 4: {
                char respuesta;
                if (reg.getActivo()) {
                    cout << "Actualmente la autoparte esta ACTIVA." << endl;
                } else {
                    cout << "Actualmente la autoparte esta INACTIVA." << endl;
                }
                cout << "Desea cambiar su estado? (s/n): ";
                cin >> respuesta;
                if (respuesta == 's' || respuesta == 'S') {
                    reg.setActivo(!reg.getActivo());
                } else {
                    cout << "Estado no modificado." << endl;
                }
                break;
            }
            case 0:
                cout << "Saliendo del menu de modificacion." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }

        // Guardar después de cualquier cambio válido
        if (opcion >= 1 && opcion <= 4) {
            if (arch.modificar(pos, reg)) {
                cout << "Modificacion realizada correctamente." << endl;
            } else {
                cout << "Error al guardar los cambios." << endl;
            }
        }

    } while (opcion != 0);
}


void AutopartesManager::eliminarAutoparte() {
    int numero;
    cout << "Ingrese el numero de la autoparte a eliminar: ";
    cin >> numero;

    if (numero <= 0) {
        cout << "Numero invalido." << endl;
        return;
    }

    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "Autoparte no encontrada." << endl;
        return;
    }

    Autoparte reg = arch.leer(pos);
    if (!reg.getActivo()) {
        cout << "La autoparte ya estaba dada de baja." << endl;
        return;
    }

    reg.setActivo(false);
    if (arch.modificar(pos,reg)) {
        cout << "Autoparte dada de baja correctamente." << endl;
    } else {
        cout << "Error al dar de baja la autoparte." << endl;
    }
}



