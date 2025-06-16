#include "AutopartesManager.h"
#include "ArchivoAutopartes.h"
#include "TipoAutoparte.h"
#include "Autoparte.h"
#include <iostream>
#include <cstring>
using namespace std;

void AutopartesManager::Menu() {
    int opcion, numero;
    char nombre[50];

    do {
        cout << "\n=== MENU AUTOPARTES ===\n";
        cout << "1. Cargar autoparte nueva\n";
        cout << "2. Dar de baja autoparte\n";
        cout << "3. Dar de alta autoparte\n";
        cout << "4. Modificar autoparte\n";
        cout << "5. Buscar autoparte por numero\n";
        cout << "6. Buscar autoparte por nombre\n";
        cout << "7. Listar todas las autopartes\n";
        cout << "8. Listar autopartes activas\n";
        cout << "9. Listar autopartes inactivas\n";
        cout << "10. Aumentar stock de autoparte existente" << endl;
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                CargarAutoparteNueva();
                break;
            case 2:
                cout << "Ingrese numero de autoparte a dar de baja: ";
                cin >> numero;
                DarDeBajaAutoparte(numero);
                break;
            case 3:
                cout << "Ingrese numero de autoparte a dar de alta: ";
                cin >> numero;
                DarDeAltaAutoparte(numero);
                break;
            case 4:
                cout << "Ingrese numero de autoparte a modificar: ";
                cin >> numero;
                ModificarAutoparte(numero);
                break;
            case 5:
                cout << "Ingrese numero de autoparte a buscar: ";
                cin >> numero;
                BuscarAutopartePorNumero(numero);
                break;
            case 6:
                cout << "Ingrese nombre de autoparte a buscar: ";
                cin.ignore();
                cin.getline(nombre, 50);
                BuscarAutopartePorNombre(nombre);
                break;
            case 7:
                ListarAutopartes();
                break;
            case 8:
                ListarAutopartesActivas();
                break;
            case 9:
                ListarAutopartesInactivas();
                break;
            case 10:
                AumentarStockAutoparte();
                break;
            case 0:
                cout << "Saliendo del menu de autopartes..." << endl;
                break;
            default:
                cout << "Opción invalida." << endl;
        }

    } while (opcion != 0);
}

void AutopartesManager::CargarAutoparteNueva(){
    int numero,tipoNumero,stock;
    bool activo;
    char nombre[50], nombreTipo[50];

    cout << "=== CARGA DE NUEVA AUTOPARTE ===" << endl;

    cout << "Ingrese numero de autoparte: ";
    cin >> numero;

    ArchivoAutopartes archivo("autopartes.dat");
    if (archivo.Existe(numero)) {
        cout << "Ya existe una autoparte con ese numero. No se puede cargar.\n";
        return;
    }

    cout << "Ingrese nombre de la autoparte: ";
    cin.ignore();
    cin.getline(nombre, 50);

    cout << "Ingrese tipo (1: motor, 2: carroceria, 3: chasis, 4: interior): ";
    cin >> tipoNumero;

    cout << "Ingrese nombre del tipo: ";
    cin.ignore();
    cin.getline(nombreTipo, 50);

    cout << "Ingrese stock: ";
    cin >> stock;

    cout << "¿Esta activa? (1: si, 0: no): ";
    cin >> activo;

    TipoAutoparte tipoAutoparte(tipoNumero, nombreTipo);

    Autoparte nueva(numero,nombre,tipoAutoparte,stock,activo);

    if (archivo.Guardar(nueva)) {
        cout << "Autoparte guardada exitosamente.\n";
    } else {
        cout << "Error al guardar la autoparte.\n";
    }
}

void AutopartesManager::DarDeBajaAutoparte(int numero) {
    ArchivoAutopartes archivo("autopartes.dat");
    Autoparte reg;

    int pos = archivo.BuscarPosicion(numero);
    if(pos==-1){
        cout << "No se encontró una autoparte activa con ese numero.\n";
        return;
    }

    reg=archivo.LeerUna(pos);

    if (!reg.getActivo()) {
        cout << "La autoparte ya esta dada de baja." << endl;
        return;
    }

    reg.setActivo(false);

    if (archivo.Modificar(reg, pos)) {
        cout << "Autoparte dada de baja exitosamente.\n";
    } else {
        cout << "Error al dar de baja la autoparte.\n";
    }


}
void AutopartesManager::DarDeAltaAutoparte(int numero) {
    ArchivoAutopartes archivo;
    Autoparte reg;

    int pos = archivo.BuscarPosicion(numero);
    if (pos == -1) {
        cout << "Autoparte no encontrada." << endl;
        return;
    }

    reg = archivo.LeerUna(pos);

    if (reg.getActivo()) {
        cout << "La autoparte ya esta activa." << endl;
        return;
    }

    reg.setActivo(true);

    if (archivo.Modificar(reg, pos)) {
        cout << "Autoparte dada de alta exitosamente." << endl;
    } else {
        cout << "Error al modificar la autoparte." << endl;
    }
}

void AutopartesManager::ModificarAutoparte(int numero){

    ArchivoAutopartes archivo("autopartes.dat");

    int pos = archivo.BuscarPosicion(numero);

       if (pos == -1) {
        cout << "Autoparte no encontrada." << endl;
        return;
    }

    Autoparte reg = archivo.LeerUna(pos);

    if (!reg.getActivo()) {
        cout << "La autoparte esta inactiva. No se puede modificar." << endl;
        return;
    }

    char nuevoNombre[50];
    int nuevoStock;
    int nuevoTipo;

    cout << "Nombre actual: " << reg.getNombreAutoparte() << endl;
    cout << "Ingrese nuevo nombre: ";
    cin.ignore();
    cin.getline(nuevoNombre, 50);

    cout << "Stock actual: " << reg.getStock() << endl;
    cout << "Ingrese nuevo stock: ";
    cin >> nuevoStock;

    cout << "Tipo actual: " << reg.getTipo().getIdTipo() << endl;
    cout << "Ingrese nuevo tipo (1-Motor, 2-Carroceria, 3-Chasis, 4-Interior): ";
    cin >> nuevoTipo;

    TipoAutoparte tipo;
    tipo.setIdTipo(nuevoTipo);

    reg.setNombre(nuevoNombre);
    reg.setStock(nuevoStock);
    reg.setTipo(tipo);

    if (archivo.Modificar(reg, pos)) {
        cout << "Autoparte modificada correctamente." << endl;
    } else {
        cout << "Error al modificar la autoparte." << endl;
    }
}

int AutopartesManager::BuscarAutopartePorNumero(int numero){

    ArchivoAutopartes archivo("autopartes.dat");

    int pos = archivo.BuscarPosicion(numero);

    if (pos == -1) {
        cout << "Autoparte no encontrada." << endl;
        return -1;
    }

    Autoparte reg = archivo.LeerUna(pos);

    if (!reg.getActivo()) {
        cout << "La autoparte esta dada de baja (inactiva)." << endl;
        return -1;
    }

    cout << "\n=== Datos de la Autoparte ===" << endl;
    cout << "Numero: " << reg.getNumeroAutoparte() << endl;
    cout << "Nombre: " << reg.getNombreAutoparte() << endl;
    cout << "Tipo: " << reg.getTipo().getIdTipo()<<" - " << reg.getTipo().getNombre()<<endl;
    cout << "Stock: " << reg.getStock() << endl;
    cout << "Estado: Activa" << endl;

    return pos;

}

int AutopartesManager::BuscarAutopartePorNombre(const char* nombre){
    ArchivoAutopartes archivo("autopartes.dat");
     int cantidad = archivo.CantidadAutopartes();

    for (int i = 0; i < cantidad; i++) {
        Autoparte reg = archivo.LeerUna(i);

        if (reg.getActivo() && strcmp(reg.getNombreAutoparte(), nombre) == 0) {
            cout << "\n=== Datos de la Autoparte ===" << endl;
            cout << "Numero: " << reg.getNumeroAutoparte() << endl;
            cout << "Nombre: " << reg.getNombreAutoparte() << endl;
            cout << "Tipo: " << reg.getTipo().getIdTipo() << " - " << reg.getTipo().getNombre() << endl;
            cout << "Stock: " << reg.getStock() << endl;
            cout << "Estado: Activa" << endl;
            return i;
        }
    }

    cout << "Autoparte no encontrada." << endl;
    return -1;
}
void AutopartesManager::ListarAutopartes(){
    ArchivoAutopartes archivo("autopartes.dat");
    int cantidad = archivo.CantidadAutopartes();

    cout << "\n=== LISTADO DE TODAS LAS AUTOPARTES ===" << endl;

    for (int i = 0; i < cantidad; i++) {
        Autoparte reg = archivo.LeerUna(i);

        cout << "\nNumero: " << reg.getNumeroAutoparte() << endl;
        cout << "Nombre: " << reg.getNombreAutoparte() << endl;
        cout << "Tipo: " << reg.getTipo().getIdTipo()<<" - " << reg.getTipo().getNombre() << endl;
        cout << "Stock: " << reg.getStock() << endl;
        cout << "Estado: " << (reg.getActivo() ? "Activa" : "Inactiva") << endl;
    }
}

void AutopartesManager::ListarAutopartesActivas(){
ArchivoAutopartes archivo("autopartes.dat");
    int cantidad = archivo.CantidadAutopartes();

    cout << "\n=== LISTADO DE AUTOPARTES ACTIVAS ===" << endl;

    for (int i = 0; i < cantidad; i++) {
        Autoparte reg = archivo.LeerUna(i);

        if (reg.getActivo()) {
            cout << "\nNumero: " << reg.getNumeroAutoparte() << endl;
            cout << "Nombre: " << reg.getNombreAutoparte() << endl;
            cout << "Tipo: " << reg.getTipo().getIdTipo() << " - " << reg.getTipo().getNombre() << endl;
            cout << "Stock: " << reg.getStock() << endl;
        }
    }
}

void AutopartesManager::ListarAutopartesInactivas(){
    ArchivoAutopartes archivo("autopartes.dat");
    int cantidad = archivo.CantidadAutopartes();

    cout << "\n=== LISTADO DE AUTOPARTES INACTIVAS ===" << endl;

    for (int i = 0; i < cantidad; i++) {
        Autoparte reg = archivo.LeerUna(i);

        if (!reg.getActivo()) {
            cout << "\nNumero: " << reg.getNumeroAutoparte() << endl;
            cout << "Nombre: " << reg.getNombreAutoparte() << endl;
            cout << "Tipo: " << reg.getTipo().getIdTipo() << " - " << reg.getTipo().getNombre() << endl;
            cout << "Stock: " << reg.getStock() << endl;
        }
    }
}

void AutopartesManager::AumentarStockAutoparte() {
    int numero, cantidad;
    cout << "Ingrese numero de autoparte: ";
    cin >> numero;

    ArchivoAutopartes archivo("autopartes.dat");
    int pos = archivo.BuscarPosicion(numero);

    if (pos == -1) {
        cout << "No se encontro una autoparte activa con ese numero.\n";
        return;
    }

    Autoparte reg = archivo.LeerUna(pos);

    if (!reg.getActivo()) {
        cout << "La autoparte esta dada de baja. No se puede modificar el stock.\n";
        return;
    }

    cout << "Stock actual: " << reg.getStock() << endl;
    cout << "Ingrese cantidad a agregar: ";
    cin >> cantidad;

    reg.setStock(reg.getStock() + cantidad);

    if (archivo.Modificar(reg, pos)) {
        cout << "Stock actualizado exitosamente.\n";
    } else {
        cout << "Error al actualizar el stock.\n";
    }
}
