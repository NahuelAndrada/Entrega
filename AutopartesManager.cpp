#include <iostream>
#include <string>

#include "AutopartesManager.h"
#include "TipoAutoparteManager.h"

#include "Autoparte.h"
#include "TipoAutoparte.h"

#include "ArchivoAutopartes.h"
#include "ArchivoTipoAutoparte.h"
#include "EntregaArchivo.h"

#include "Usuario.h"


using namespace std;

void AutopartesManager::cargarAutoparte(string rol) {
    if (rol != "admin") {
        cout << "No tiene permisos para cargar autopartes." << endl;
        return;
    }
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

    if (nombre.length() == 0) {
    cout << "El nombre no puede estar vacio." << endl;
    return;
    }
    if (nombre.length() >= 30) {
        cout << "Nombre demasiado largo." << endl;
        return;
    }

    ArchivoTipoAutoparte archTipo;
    TipoAutoparteManager managerTipo;

    int tipo;

    managerTipo.listar();

    cout << "Ingrese numero de tipo de autoparte: ";
    cin >> tipo;
    if (archTipo.buscarPorNumero(tipo) < 0) {
        cout << "Tipo invalido, revise la existencia de ese tipo de autoparte." << endl;
        cout << endl;
        return;
    }

    int stock;
    cout << "Ingrese stock inicial: ";
    cin >> stock;
    if (stock < 0) {
        cout << "Stock invalido." << endl;;
        return;
    }

    Autoparte reg(numero, nombre, tipo, stock, true);

    if (arch.guardar(reg)) {
        cout << "Autoparte guardada con exito.\n";
    } else {
        cout << "Error al guardar la autoparte.\n";
    }
}

void AutopartesManager::modificarAutoparte(string rol) {
    if (rol != "admin") {
        cout << "No tiene permisos para modificar autopartes." << endl;
        return;
    }
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
                if (nuevoNombre.length() == 0) {
                    cout << "El nombre no puede estar vacío." << endl;
                    return;
                }
                if (nuevoNombre.length() >= 30) {
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
                    cout << "Stock invalido. No puede ser negativo.\n";
                } else {
                    reg.setStock(nuevoStock);
                }
                break;
            }
            case 4: {
                system("cls");
                cout << "--- CAMBIAR ESTADO DE AUTOPARTE ---" << endl;

                if (reg.getActivo()) {
                    cout << "La autoparte esta actualmente ACTIVA." << endl;
                } else {
                    cout << "La autoparte esta actualmente INACTIVA." << endl;
                }

                char opc;
                cout << "Desea cambiar el estado? (s/n): ";
                cin >> opc;

                if (opc == 's' || opc == 'S') {
                    reg.setActivo(!reg.getActivo());
                    arch.modificar(pos, reg);

                    cout << "Estado modificado correctamente. Nuevo estado -> ";
                    if (reg.getActivo()) {
                        cout << "Activo" << endl;
                    } else {
                        cout << "Inactivo" << endl;
                    }
                } else {
                cout << "Operacion cancelada por el usuario." << endl;
                }

                system("pause");
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
void AutopartesManager::eliminarAutoparte(string rol) {
    if (rol != "admin") {
        cout << "No tiene permisos para eliminar autopartes." << endl;
        return;
    }
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
void AutopartesManager::menuAutopartes(std::string rol) {
    int opcion;
    do {
        system("cls");
        cout << "=== MENU AUTOPARTES ===\n\n";
        cout << "1. Cargar autoparte\n";
        cout << "2. Modificar autoparte\n";
        cout << "3. Eliminar autoparte\n";
        cout << "4. Buscar autoparte por numero\n";
        cout << "5. Buscar autoparte por nombre\n";
        cout << "6. Listar autopartes activas\n";
        cout << "7. Listar autopartes inactivas\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarAutoparte(rol);
                break;
            case 2:
                modificarAutoparte(rol);
                break;
            case 3:
                eliminarAutoparte(rol);
                break;
            case 4:
                buscarAutopartePorNumero();
                break;
            case 5:
                buscarAutopartePorNombre();
                break;
            case 6:
                listarAutoparteActivas();
                break;
            case 7:
                listarAutoparteInactivas();
                break;
            case 0:
                cout << "Volviendo al menu anterior...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
        system("pause");
    } while (opcion != 0);
}
void AutopartesManager::rankingAutopartes() {

    system("cls");
    cout << "--- RANKING DE AUTOPARTES MAS ENTREGADAS ---" << endl;
    cout << endl;

    ArchivoAutopartes archAutoparte;
    EntregaArchivo archEntrega;

    Autoparte regAutoparte;
    Entrega regEntrega;

    int int_CantidadAutopartesTotales = archAutoparte.contar();
    int int_CantidadEntregasTotales = archEntrega.getCantidadRegistros();

    int limite;
    cout << "Cuantas autopartes desea ver en el ranking?: ";
    cin >> limite;

    if(int_CantidadAutopartesTotales == 0){
        cout << "No se encontraron autopartes registradas." << endl;
        cout << endl;
        return;
    }

    int* vectorAutopartes = new int[int_CantidadAutopartesTotales]{};
    int* vectorEntregasAu = new int[int_CantidadAutopartesTotales]{};

    for(int i = 0; i < int_CantidadAutopartesTotales; i++){
        regAutoparte = archAutoparte.leer(i);
        if(regAutoparte.getActivo()){
            vectorAutopartes[i] = regAutoparte.getNumero();
        }
    }

    //AHORA RECORRO CADA ENTREGA Y VOY GUARDANDO
    for(int k = 0; k < int_CantidadEntregasTotales; k++){
        regEntrega = archEntrega.leer(k);
        if(regEntrega.getActivo()){
            //Busco en el vector de entregas los que coincidan con su numero de autoparte
            for(int l = 0; l < int_CantidadAutopartesTotales; l++){
                if(regEntrega.getNumeroAutoparte() == vectorAutopartes[l]){
                    vectorEntregasAu[l] += regEntrega.getCantidadUnidades();
                }
            }
        }
    }

    int tempAutoparteNum;
    int tempAutoparteCan;

    //Ordeno resultados con el metodo de ordenamiento burbuja
    for(int i = 0; i < int_CantidadAutopartesTotales; i++){
        for(int j = i+1; j < int_CantidadAutopartesTotales; j++){

            if(vectorEntregasAu[j]>vectorEntregasAu[i]){

                tempAutoparteNum = vectorAutopartes[i];
                tempAutoparteCan = vectorEntregasAu[i];

                vectorAutopartes[i] = vectorAutopartes[j];
                vectorEntregasAu[i] = vectorEntregasAu[j];

                vectorAutopartes[j] = tempAutoparteNum;
                vectorEntregasAu[j] = tempAutoparteCan;
            }
        }
    }

    for(int m = 0; m < int_CantidadAutopartesTotales; m++){
        if(vectorAutopartes[m]>0){
            int pos = archAutoparte.buscarPorNumero(vectorAutopartes[m]);
            Autoparte reg = archAutoparte.leer(pos);
            string nombre = reg.getNombre();
            cout << "Autoparte: "<<nombre<<" ID: " << vectorAutopartes[m] << " | " << " Cantidad entregas: " << vectorEntregasAu[m] << endl;
        }
    }

    delete[] vectorAutopartes;
    delete[] vectorEntregasAu;
    cout << endl;

}

void AutopartesManager::informeStockBajo() {

    ArchivoAutopartes arch;
    int CantidadMaxima;

    system("cls");
    cout << "--- AUTOPARTES CON STOCK BAJO ---" << endl;
    cout << endl;

    int total = arch.contar();

    if(total==0){
        cout << "No se encontraron autopartes registradas." << endl;
        cout << endl;
        return;
    }


    cout << "Ingrese la cantidad maxima de stock a buscar: ";

    cin >> CantidadMaxima;
    cin.ignore();

    for(int i = 0; i < total; i++) {
        Autoparte reg = arch.leer(i);
        if(reg.getActivo() && reg.getStock() <= CantidadMaxima) {
            cout << "ID: " << reg.getNumero()
                 << " - Nombre: " << reg.getNombre()
                 << " - Stock: " << reg.getStock() << "\n";
        }
    }
}

void AutopartesManager::autopartesActivasSinEntrega(){

    ArchivoAutopartes archAuto;
    EntregaArchivo archEnt;
    Autoparte regAut;
    Entrega regEnt;

    int cantidadAutoActivas=archAuto.contar();

    int* vecAutoActivas=new int[cantidadAutoActivas]{};
    int cantActivas=0;

    for(int i=0;i<cantidadAutoActivas;i++){
        regAut=archAuto.leer(i);
        if(regAut.getActivo()){
            vecAutoActivas[i]=regAut.getNumero();
            cantActivas++;
        }
    }
    bool* entregadas= new bool[cantActivas]{};
    int cantEntregas=archEnt.getCantidadRegistros();
    for(int i=0;i<cantEntregas;i++){
        regEnt=archEnt.leer(i);
        int idEntregado=regEnt.getNumeroAutoparte();
        for(int j=0;j<cantActivas;j++){
            if(vecAutoActivas[j]==idEntregado){
                entregadas[j]=true;
                break;
            }

        }
    }
    for(int m=0;m<cantActivas;m++){
            if(!entregadas[m]){
                int pos = archAuto.buscarPorNumero(vecAutoActivas[m]);
                if (pos != -1){
                regAut = archAuto.leer(pos);
                cout << "La autoparte \"" << regAut.getNombre()<< "\" (ID: " << vecAutoActivas[m]<< ") no se entregó nunca." << endl;
                }
            }

        }
    delete[] vecAutoActivas;
    delete[] entregadas;

    cout << endl;
}

void AutopartesManager::listarAutopartesConUnidadesMayoresA(){

    system("cls");

    ArchivoAutopartes archAut;
    Autoparte regAut;

    EntregaArchivo archEnt;
    Entrega regEnt;

    int cantidad=0;

    cout<<"Ingrese la cantidad minima de autopartes: "<<endl;
    cin>>cantidad;

    int cantidadEntregas=archEnt.getCantidadRegistros();
    int cantidadAutopartes=archAut.contar();

    int* vecSumaUnidades = new int[cantidadAutopartes]{};

    for(int i=0;i<cantidadEntregas;i++){
        regEnt=archEnt.leer(i);
        if(regEnt.getActivo()){
            int idAutoparte=regEnt.getNumeroAutoparte();
            vecSumaUnidades[idAutoparte]+=regEnt.getCantidadUnidades();
        }
    }
    for(int i=0;i<cantidadAutopartes;i++){
        regAut=archAut.leer(i);
        if(regAut.getActivo()){
            int idAutoparte=regAut.getNumero();
            if(vecSumaUnidades[idAutoparte]>cantidad){
                cout << "Autoparte: " << regAut.getNombre()<< " (ID: " << idAutoparte<< ") - Unidades entregadas: " << vecSumaUnidades[idAutoparte] << endl;
            }
        }
    }
    delete[] vecSumaUnidades;
}
