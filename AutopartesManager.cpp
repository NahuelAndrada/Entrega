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

    ArchivoTipoAutoparte archivoTipo;
    int totalTipos = archivoTipo.contar();
    cout << "--- TIPOS DE AUTOPARTE DISPONIBLES ---" << endl;
    for (int i = 0; i < totalTipos; i++) {
        TipoAutoparte tipoAux = archivoTipo.leer(i);
        if (tipoAux.getActivo()) {
            tipoAux.mostrar();
        }
    }
    cout << "Tipo de autoparte (ingrese el número correspondiente): ";
    cin >> tipo;
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


void AutopartesManager::modificar() {
    int numero;
    cout << "Ingrese el numero de la autoparte a modificar: ";
    cin >> numero;

    if (numero <= 0) {
        cout << "Error: Numero invalido." << endl;
        return;
    }

    ArchivoAutopartes arch;
    int pos = arch.buscarPorNumero(numero);
    if (pos < 0) {
        cout << "No existe una autoparte con ese numero." << endl;
        return;
    }

    Autoparte reg = arch.leer(pos);
    if (!reg.getActivo()) {
        cout << "La autoparte está dada de baja." << endl;
        return;
    }

    string nuevoNombre;
    int nuevoTipo, nuevoStock;

    cin.ignore();
    cout << "Nuevo nombre: ";
    getline(cin, nuevoNombre);

    ArchivoTipoAutoparte archivoTipo;
    int totalTipos = archivoTipo.contar();
    cout << "--- TIPOS DE AUTOPARTE DISPONIBLES ---" << endl;
    for (int i = 0; i < totalTipos; i++) {
        TipoAutoparte tipoAux = archivoTipo.leer(i);
        if (tipoAux.getActivo()) {
            tipoAux.mostrar();
        }
    }

    cout << "Nuevo tipo (ingrese el número correspondiente): ";
    cin >> nuevoTipo;
    if (archivoTipo.buscarPorNumero(nuevoTipo) < 0) {
        cout << "Tipo no valido." << endl;
        return;
    }

    cout << "Nuevo stock: ";
    cin >> nuevoStock;
    if (nuevoStock < 0) {
        cout << "Stock invalido." << endl;
        return;
    }

    reg.setNombre(nuevoNombre);
    reg.setTipo(nuevoTipo);
    reg.setStock(nuevoStock);

    if (arch.modificar(pos,reg)) {
        cout << "Autoparte modificada." << endl;
    } else {
        cout << "No se pudo modificar." << endl;
    }
}


void AutopartesManager::eliminar() {
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


void AutopartesManager::modificarStock() {
    int numero;
    cout << "Ingrese el numero de la autoparte para modificar el stock: ";
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
        cout << "La autoparte está dada de baja." << endl;
        return;
    }

    int diferencia;
    cout << "Ingrese la cantidad a sumar o restar al stock actual (puede ser negativa): ";
    cin >> diferencia;

    int stockActual = reg.getStock();
    int nuevoStock = stockActual + diferencia;

    if (nuevoStock < 0) {
        cout << "Error: El resultado del stock no puede ser negativo." << endl;
        return;
    }

    reg.setStock(nuevoStock);
    if (arch.modificar(pos,reg)) {
        cout << "Stock actualizado correctamente. Nuevo stock: " << nuevoStock << endl;
    } else {
        cout << "Error al actualizar el stock." << endl;
    }
}
