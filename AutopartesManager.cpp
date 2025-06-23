#include "AutopartesManager.h"
#include "Autoparte.h"
#include "TipoAutoparte.h"
#include "ArchivoAutopartes.h"
#include "ArchivoTipoAutoparte.h"
#include <iostream>
#include <string>
using namespace std;

void AutopartesManager::cargar() {
    Autoparte reg;
    int numero, tipo, stock;
    std::string nombre;
    bool activo = true;

    cout << "=== CARGAR NUEVA AUTOPARTE ===" << endl;

    cout << "Numero de autoparte: ";
    cin >> numero;

    if (numero <= 0) {
        cout << "Error: El numero de autoparte debe ser mayor que cero." << endl;
        return;
    }

    ArchivoAutopartes arch;
    if (arch.buscarPorNumero(numero) >= 0) {
        cout << "Ya existe una autoparte con ese numero." << endl;
        return;
    }
    cin.ignore();
    cout << "Nombre de autoparte: ";
    getline(cin, nombre);

    cout << "Tipo de autoparte: ";
    cin >> tipo;
    ArchivoTipoAutoparte archivoTipo;
    if (archivoTipo.buscarPorNumero(tipo) < 0) {
        cout << "Error: Tipo de autoparte no valido (no existe en el archivo)." << endl;
        return;
    }

    cout << "Stock inicial: ";
    cin >> stock;
    if (stock < 0) {
        cout << "Error: El stock no puede ser negativo." << endl;
        return;
    }

    reg.setNumero(numero);
    reg.setNombre(nombre);
    reg.setTipo(tipo);
    reg.setStock(stock);
    reg.setActivo(activo);

    if (arch.guardar(reg)){
        cout << "Autoparte guardada con exito.\n";
    }else{
        cout << "Error al guardar.\n";
    }
}

void AutopartesManager::listar() {
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

void AutopartesManager::buscarPorNumero() {
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
            cout << "La autoparte encontrada está dada de baja (inactiva)." << endl;
        }
    } else {
        cout << "Autoparte no encontrada." << endl;
    }
}

void AutopartesManager::buscarPorNombre() {
    std::string nombre;
    cin.ignore();
    cout << "Ingrese nombre: ";
    getline(cin, nombre);
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNombre(nombre.c_str());
    if (pos >= 0) arch.leer(pos).mostrar();
    else cout << "No encontrado.\n";
}

void AutopartesManager::modificar() {
    int numero;
    cout << "Ingrese numero a modificar: ";
    cin >> numero;
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "No encontrado.\n";
        return;
    }

    Autoparte reg = arch.leer(pos);
    std::string nuevoNombre;
    int nuevoStock, nuevoTipo;

    cin.ignore();
    cout << "Nuevo nombre: ";
    getline(cin, nuevoNombre);
    cout << "Nuevo tipo: ";
    cin >> nuevoTipo;
    cout << "Nuevo stock: ";
    cin >> nuevoStock;

    reg.setNombre(nuevoNombre);
    reg.setTipo(nuevoTipo);
    reg.setStock(nuevoStock);

    if (arch.modificar(pos, reg)) {
        cout << "Modificado.\n";
    } else {
        cout << "Error al modificar.\n";
    }
}

void AutopartesManager::eliminar() {
    int numero;
    cout << "Ingrese numero a eliminar: ";
    cin >> numero;
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "No encontrado.\n";
        return;
    }
    Autoparte reg = arch.leer(pos);
    reg.setActivo(false);
    if (arch.modificar(pos, reg)) cout << "Eliminado logicamente.\n";
    else cout << "Error.\n";
}

void AutopartesManager::modificarStock() {
    int numero;
    cout << "Ingrese numero de autoparte: ";
    cin >> numero;
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "No encontrado.\n";
        return;
    }

    Autoparte reg = arch.leer(pos);
    cout << "Stock actual: " << reg.getStock() << endl;

    char opcion;
    cout << "Desea (S)umar o (R)estar stock? ";
    cin >> opcion;

    int cantidad;
    cout << "Cantidad: ";
    cin >> cantidad;

    if (cantidad <= 0) {
        cout << "La cantidad debe ser positiva.\n";
        return;
    }

    int nuevoStock = reg.getStock();

    if (opcion == 'S' || opcion == 's') {
        nuevoStock += cantidad;
    } else if (opcion == 'R' || opcion == 'r') {
        if (cantidad > reg.getStock()) {
            cout << "Error: no puede restar más de lo que hay en stock.\n";
            return;
        }
        nuevoStock -= cantidad;
    } else {
        cout << "Opcion invalida. Debe ser S o R.\n";
        return;
    }

    reg.setStock(nuevoStock);

    if (arch.modificar(pos, reg)) cout << "Stock actualizado correctamente.\n";
    else cout << "Error al actualizar el stock.\n";
}
