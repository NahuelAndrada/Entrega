#include "AutopartesManager.h"
#include "Autoparte.h"
#include "TipoAutoparte.h"
#include "ArchivoAutopartes.h"
#include <iostream>
#include <string>
using namespace std;

void AutopartesManager::cargar() {
    Autoparte reg;
    int numero, tipo, stock;
    std::string nombre;
    bool activo = true;

    cout << "Numero de autoparte: ";
    cin >> numero;
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
    cout << "Stock: ";
    cin >> stock;

    reg.setNumero(numero);
    reg.setNombre(nombre);
    reg.setTipo(tipo);
    reg.setStock(stock);
    reg.setActivo(activo);

    if (arch.guardar(reg)) cout << "Autoparte guardada con exito.\n";
    else cout << "Error al guardar.\n";
}

void AutopartesManager::listar() {
    ArchivoAutopartes arch;
    int total = arch.contar();
    for (int i = 0; i < total; i++) {
        Autoparte reg = arch.leer(i);
        if (reg.getActivo()) reg.mostrar();
    }
}

void AutopartesManager::buscarPorNumero() {
    int numero;
    cout << "Ingrese numero: ";
    cin >> numero;
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos >= 0) arch.leer(pos).mostrar();
    else cout << "No encontrado.\n";
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
