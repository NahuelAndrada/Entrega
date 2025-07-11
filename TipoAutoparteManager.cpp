#include "TipoAutoparteManager.h"
#include "ArchivoTipoAutoparte.h"
#include "TipoAutoparte.h"
#include <iostream>
using namespace std;

//Includes utilizados para los informes
#include "ArchivoAutopartes.h"
#include "Autoparte.h"

void TipoAutoparteManager::cargar(string rol) {
    if (rol != "admin") {
        cout << "No tenes permisos para realizar esta accion." << endl;
        system("pause");
        return;
    }
    system("cls");

    int numero;
    string nombre;
    char opcion;
    ArchivoTipoAutoparte archivo;

    ArchivoAutopartes archAutopartes;
    Autoparte regAutoparte;

    int cantidadAutopartes = archAutopartes.contar();

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
                        for(int i = 0; i < cantidadAutopartes; i++){
                            regAutoparte = archAutopartes.leer(i);
                            if(!regAutoparte.getActivo() && regAutoparte.getTipo() == numero){
                                regAutoparte.setActivo(true);
                                archAutopartes.modificar(i,regAutoparte);
                            }
                        }
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

    system("cls");

    ArchivoTipoAutoparte archivo;
    int total = archivo.contar();
    bool hayActivos = false;

    cout << "=== LISTADO DE TIPOS DE AUTOPARTE ACTIVOS ===" << endl;
    cout << endl;

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

    cout << endl;
}
void TipoAutoparteManager::listarInactivos() {

    system("cls");

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
        cout << endl;
        cout << "No hay tipos de autoparte inactivos registrados." << endl;
        cout << endl;
    }
}
void TipoAutoparteManager::buscarPorID() {

    system("cls");

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
void TipoAutoparteManager::modificar(string rol) {
    if (rol != "admin") {
        cout << "No tenes permisos para realizar esta accion." << endl;
        system("pause");
        return;
    }
    system("cls");

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
    int opcion;
    do {
        system("cls");
        cout << "=== MODIFICAR TIPO DE AUTOPARTE ===" << endl;
        cout << "1. Modificar nombre" << endl;
        cout << "2. Cambiar estado (activo/inactivo)" << endl;
        cout << "0. Volver y guardar cambios" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nuevoNombre;
                cout << "Nombre actual: " << tipo.getNombre() << "\n";
                cout << "Ingrese el nuevo nombre: ";
                cin.ignore();
                getline(cin, nuevoNombre);
                tipo.setNombre(nuevoNombre.c_str());
                break;
            }
            case 2: {
                cout << "Estado actual: ";
                if (tipo.getActivo()) {
                    cout << "Activo\n";
                } else {
                    cout << "Inactivo\n";
                }
                bool estado;
                cout << "Desea modificar el estado? (1 = activo, 0 = inactivo): ";
                cin >> estado;
                tipo.setActivo(estado);
                break;
            }
            case 0:
                break;
            default:
                cout << "Opcion invalida." << endl;
                system("pause");
        }
    } while (opcion != 0);

    if (archivo.modificar(pos, tipo)) {
        cout << "Tipo de autoparte modificado correctamente.\n";
    } else {
        cout << "Error al modificar tipo de autoparte.\n";
    }
}
void TipoAutoparteManager::eliminar(string rol) {
    if (rol != "admin") {
        cout << "No tenes permisos para realizar esta accion." << endl;
        system("pause");
        return;
    }
    system("cls");

    int numero;
    cout << "Numero de tipo de autoparte a eliminar: ";
    cin >> numero;

    ArchivoTipoAutoparte archivo;
    int total = archivo.contar();

    //Variables utilizadas para dar de baja las autopartes
    ArchivoAutopartes archAutopartes;
    Autoparte regAutoparte;

    int totalAutopartes = archAutopartes.contar();

    for (int i = 0; i < total; i++) {
        TipoAutoparte reg = archivo.leer(i);
        if (reg.getNumero() == numero && reg.getActivo()) {
            reg.setActivo(false);
            if (archivo.modificar(i, reg)) {
                cout << "Tipo de autoparte (" << reg.getNombre() << ") dado de baja (inactivo)." << endl;
                for(int j = 0; j < totalAutopartes; j++){
                    regAutoparte = archAutopartes.leer(j);
                    if(regAutoparte.getActivo() && regAutoparte.getTipo() == numero){
                        regAutoparte.setActivo(false);
                        archAutopartes.modificar(j,regAutoparte);
                    }
                }
            } else {
                cout << "Error al dar de baja el registro." << endl;
            }
            return;
        }
    }

    cout << "Tipo de autoparte no encontrado o ya inactivo." << endl;
}
void TipoAutoparteManager::menuTipoAutopartes(string rol){
    int op;
    do {

        cout << "#######################################" << endl;
        cout << "          MENU TIPO AUTOPARTES" << endl;
        cout << "#######################################" << endl;
        cout << endl;
        cout << "1. Cargar/dar de alta un tipo de autoparte" << endl;
        cout << "2. Modificar un tipo de autoparte" << endl;
        cout << "3. Buscar un tipo de autoparte por ID" << endl;
        cout << "4. Listar tipos de autopartes dadas de ALTA" << endl;
        cout << "5. Listar tipos de autopartes dadas de BAJA" << endl;
        cout << "6. Dar de baja un tipo de autoparte" << endl;
        cout << "0. Volver al menu anterior" << endl;
        cout << endl;

        cout << "Seleccione una opcion: ";
        cin >> op;

        switch (op) {
            case 1: cargar(rol); break;
            case 2: modificar(rol); break;
            case 3: buscarPorID(); break;
            case 4: listar(); break;
            case 5: listarInactivos(); break;
            case 6: eliminar(rol); break;
            case 0: break;
            default: cout << "Opcion invalida.\n";
        }

        system("pause");
        system("cls");

    } while (op != 0);
}
void TipoAutoparteManager::InformeCantidadDeTiposAutopartesUtilizadas(){

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "Informe de cantidad de tipo de autopartes utilizadas en las autopartes activas" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    //Variables Autopartes
    ArchivoAutopartes archAutopartes;
    Autoparte regAutoparte;

    //Variables TipoAutopartes
    ArchivoTipoAutoparte archTipoAutopartes;
    TipoAutoparte regTipoAutoparte;

    int int_AcumuladorTipoAutopartes;

    int int_CantidadRegistros_Autopartes;
    int int_CantidadRegistros_TipoAutopartes;

    int_CantidadRegistros_Autopartes = archAutopartes.contar();
    int_CantidadRegistros_TipoAutopartes = archTipoAutopartes.contar();

    //Error en caso de que no haya autopartes.
    if(int_CantidadRegistros_Autopartes == 0){
        cout << "No se encontraron autopartes registradas de momento." << endl;
        cout << endl;
        return;
    }

    //Error en caso de que no haya tipo de autopartes
    if(int_CantidadRegistros_TipoAutopartes == 0){
        cout << "No see encontraron tipos de autopartes registradas de momento" << endl;
        cout << endl;
        return;
    }

    //Recorro cada tipo de autoparte
    for(int i = 0; i < int_CantidadRegistros_TipoAutopartes; i++){

        int_AcumuladorTipoAutopartes = 0;
        regTipoAutoparte = archTipoAutopartes.leer(i);

        //Proceso unicamente los tipos de autopartes activos
        if(regTipoAutoparte.getActivo()){

            //Recorro cada autoparte
            for(int j = 0; j < int_CantidadRegistros_Autopartes; j++){

                regAutoparte = archAutopartes.leer(j);

                //Proceso unicamente las autopartes activas y mismo numero de tipoautoparte
                if(regAutoparte.getActivo() && regAutoparte.getTipo() == regTipoAutoparte.getNumero()){
                    int_AcumuladorTipoAutopartes++;
                }
            }

            cout << "> Tipo Autoparte: " << regTipoAutoparte.getNombre();
            cout << " (ID " << regTipoAutoparte.getNumero() << ")" << endl;
            if(int_AcumuladorTipoAutopartes==1){
                cout << "- Utilizado " << int_AcumuladorTipoAutopartes << " vez." << endl;
            }else{
                cout  <<"- Utilizado " << int_AcumuladorTipoAutopartes << " veces." << endl;
            }
            cout << endl;
        }
    }
}
