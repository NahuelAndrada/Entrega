#include "AutopartesManager.h"
#include "Autoparte.h"
#include "ArchivoAutopartes.h"
#include <iostream>
using namespace std;

void AutopartesManager::cargar() {
    Autoparte reg;
    int numero, tipo, stock;
    char nombre[50];
    bool activo = true;

    cout << "Numero: "; cin >> numero;
    ArchivoAutopartes arch;
    if (arch.buscarPorNumero(numero) >= 0) {
        cout << "Ya existe una autoparte con ese numero." << endl;
        return;
    }

    cout << "Nombre: "; cin.ignore(); cin.getline(nombre, 50);
    cout << "Tipo: "; cin >> tipo;
    cout << "Stock: "; cin >> stock;

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
    cout << "Ingrese numero: "; cin >> numero;
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos >= 0) arch.leer(pos).mostrar();
    else cout << "No encontrado.\n";
}

void AutopartesManager::buscarPorNombre() {
    char nombre[50];
    cout << "Ingrese nombre: "; cin.ignore(); cin.getline(nombre, 50);
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNombre(nombre);
    if (pos >= 0) arch.leer(pos).mostrar();
    else cout << "No encontrado.\n";
}

void AutopartesManager::modificar() {
    int numero;
    cout << "Ingrese numero a modificar: "; cin >> numero;
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "No encontrado.\n"; return;
    }
    Autoparte reg = arch.leer(pos);
    int nuevoStock;
    cout << "Nuevo stock: "; cin >> nuevoStock;
    reg.setStock(nuevoStock);
    if (arch.modificar(pos, reg)) cout << "Modificado.\n";
    else cout << "Error al modificar.\n";
}

void AutopartesManager::eliminar() {
    int numero;
    cout << "Ingrese numero a eliminar: "; cin >> numero;
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "No encontrado.\n"; return;
    }
    Autoparte reg = arch.leer(pos);
    reg.setActivo(false);
    if (arch.modificar(pos, reg)) cout << "Eliminado logicamente.\n";
    else cout << "Error.\n";
}

void AutopartesManager::modificarStock() {
    int numero;
    cout << "Numero: "; cin >> numero;
    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "No encontrado.\n"; return;
    }
    Autoparte reg = arch.leer(pos);
    int extra;
    cout << "Cantidad a sumar: "; cin >> extra;
    reg.setStock(reg.getStock() + extra);
    if (arch.modificar(pos, reg)) cout << "Stock actualizado.\n";
    else cout << "Error.\n";
}
