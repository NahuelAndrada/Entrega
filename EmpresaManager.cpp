#include <iostream>
#include <string>

#include "Empresa.h"
#include "ArchivoEmpresa.h"
#include "EmpresaManager.h"

//Los siguientes includes se usan para los informes
#include "EntregaArchivo.h"
#include "Entrega.h"
#include "Fecha.h"

using namespace std;

void EmpresaManager::cargarEmpresa(std::string rol){

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "            CARGAR EMPRESA" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    Empresa datosEmpresa; //Crear objeto vacio

    //################################# Variables para reactivar empresa
    Empresa registro;
    int pos;
    std::string opcion;
    //#################################

    ArchivoEmpresa archEmpresa;

    std::string in_CUIT, in_Nombre, in_Responsable, in_Telefono, in_Email, in_Direccion;

    std::cout << "Ingrese CUIT (max 14 car.): ";
    getline(std::cin, in_CUIT);

    if(in_CUIT.length() >= 15){
        std::cout << "Error: el CUIT es demasiado largo, recuerde que puede tener hasta 14 caracteres." << std::endl;
        return;
    }

    pos = buscarEmpresaPorCUIT(in_CUIT);
    if(pos>=0){
        registro = archEmpresa.leerEmpresa(pos);
        if(registro.get_Activo()){
            system("cls");
            std::cout << std::endl;
            std::cout << ">> No se pudo cargar la empresa porque ya existe un registro con este CUIT.";
            std::cout << std::endl;
            return;
        }else{
            system("cls");
            std::cout << std::endl;
            std::cout << ">> La empresa que intentaste cargar ya existe pero se encuentra inactiva, te gustaria reactivarla? (S/N): ";
            getline(std::cin,opcion);
            while(opcion != "S" && opcion != "N" && opcion != "s" && opcion != "n"){
                std::cout << ">> Opcion equivocada, escriba S para SI o N para NO." << std::endl;
                std::cout << ">> Te gustaria reactivar la empresa " << in_CUIT << "? (S/N): ";
                getline(std::cin,opcion);
            }
            if(opcion == "S" || opcion == "s"){
                dardealtaEmpresa(in_CUIT);
                system("pause");
            }
            return;
        }
    }

    std::cout << "Ingrese nombre (max 49 car.): ";
    getline(std::cin, in_Nombre);

    if(in_Nombre.length() >= 50){
        std::cout << "Error: el nombre es demasiado largo, recuerde que puede tener hasta 49 caracteres." << std::endl;
        return;
    }

    std::cout << "Ingrese responsable (max 49 car.): ";
    getline(std::cin, in_Responsable);

    if(in_Responsable.length() >= 50){
        std::cout << "Error: el responsable es demasiado largo, recuerde que puede tener hasta 49 caracteres." << std::endl;
        return;
    }

    std::cout << "Ingrese telefono (max 19 car.): ";
    getline(std::cin, in_Telefono);

    if(in_Telefono.length() >= 20){
        std::cout << "Error: el telefono es demasiado largo, recuerde que puede tener hasta 19 caracteres." << std::endl;
        return;
    }

    std::cout << "Ingrese email (max 49 car.): ";
    getline(std::cin, in_Email);

    if(in_Email.length() >= 50){
        std::cout << "Error: el email es demasiado largo, recuerde que puede tener hasta 49 caracteres." << std::endl;
        return;
    }

    std::cout << "Ingrese direccion (max 99 car.): ";
    getline(std::cin, in_Direccion);

    if(in_Direccion.length() >= 100){
        std::cout << "Error: la direccion es demasiado larga, recuerde que puede tener hasta 99 caracteres." << std::endl;
        return;
    }

    datosEmpresa.set_CUIT(in_CUIT);
    datosEmpresa.set_Nombre(in_Nombre);
    datosEmpresa.set_Responsable(in_Responsable);
    datosEmpresa.set_Telefono(in_Telefono);
    datosEmpresa.set_Email(in_Email);
    datosEmpresa.set_Direccion(in_Direccion);
    datosEmpresa.set_Activo(true);

    if(archEmpresa.guardarEmpresa(datosEmpresa)){
        std::cout << ">> Empresa cargada con exito." << std::endl;
    }else{
        std::cout << ">> Error al cargar la empresa." << std::endl;
    }

}

void EmpresaManager::mostrarCantidadEmpresas(){

    system("cls");

    ArchivoEmpresa archEmpresa;

    int cantidadRegistros = archEmpresa.get_CantidadRegistros();
    std::cout << ">> Cantidad de empresas (activas e inactivas): " << cantidadRegistros << "." << std::endl;
}

void EmpresaManager::listarEmpresasActivas(){

    system("cls");

    ArchivoEmpresa archEmpresa;
    Empresa registro;

    int cantidadRegistros = archEmpresa.get_CantidadRegistros();
    int contador = 0;

    std::cout << "Registro de empresas activas: " << std::endl;

    if(cantidadRegistros == 0){
        std::cout << ">> No se encontraron empresas en los registros." << std::endl;
    }else{
        for(int i=0;i<cantidadRegistros; i++){
            registro = archEmpresa.leerEmpresa(i);
            if(registro.get_Activo()){
               std::cout << std::endl;
               std::cout << ">> CUIT: " << registro.get_CUIT() << std::endl;
               std::cout << ">> Nombre: " << registro.get_Nombre() << std::endl;
               std::cout << ">> Direccion: " << registro.get_Direccion() << std::endl;
               std::cout << ">> Responsable: " << registro.get_Responsable() << std::endl;
               std::cout << ">> Email: " << registro.get_Email() << std::endl;
               std::cout << ">> Telefono: " << registro.get_Telefono() << std::endl;
               std::cout << "____________________" << std::endl;
               contador++;
            }
        }
    }
    if(contador==0 && cantidadRegistros != 0){
        std::cout << ">> No se encontraron empresas activas para mostrar." << std::endl;
    }
    system("pause");
    system("cls");
}

void EmpresaManager::listarEmpresasInactivas(){

    system("cls");

    ArchivoEmpresa archEmpresa;
    Empresa registro;

    int cantidadRegistros = archEmpresa.get_CantidadRegistros();
    int contador = 0;

    std::cout << "Registro de empresas inactivas: " << std::endl;

    if(cantidadRegistros == 0){
        std::cout << ">> No se encontraron empresas en los registros." << std::endl;
    }else{
        for(int i=0;i<cantidadRegistros; i++){
            registro = archEmpresa.leerEmpresa(i);
            if(!registro.get_Activo()){
               std::cout << std::endl;
               std::cout << ">> CUIT: " << registro.get_CUIT() << std::endl;
               std::cout << ">> Nombre: " << registro.get_Nombre() << std::endl;
               std::cout << ">> Direccion: " << registro.get_Direccion() << std::endl;
               std::cout << ">> Responsable: " << registro.get_Responsable() << std::endl;
               std::cout << ">> Email: " << registro.get_Email() << std::endl;
               std::cout << ">> Telefono: " << registro.get_Telefono() << std::endl;
               std::cout << "____________________" << std::endl;
               contador++;
            }
        }
    }
    if(contador==0 && cantidadRegistros != 0){
        std::cout << ">> No se encontraron empresas inactivas para mostrar." << std::endl;
    }
    system("pause");
    system("cls");
}

int  EmpresaManager::buscarEmpresaPorCUIT(std::string in_CUIT){

    ArchivoEmpresa archEmpresa;
    Empresa registro;

    int cantidadRegistros = archEmpresa.get_CantidadRegistros();

    for(int i=0; i < cantidadRegistros; i++){
        registro = archEmpresa.leerEmpresa(i);
        if(registro.get_CUIT() == in_CUIT){
            return i;
        }
    }
    return -1;
}

void EmpresaManager::buscarPorParametroEspecifico(){

    system("cls");
    int in_opcion;

    std::cout << "#######################################" << std::endl;
    std::cout << "     MENU DE BUSQUEDA DE EMPRESAS     " << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;
    std::cout << "Por que parametro te gustaria buscar?" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Buscar por CUIT." << std::endl;
    std::cout << "2. Buscar por nombre." << std::endl;
    std::cout << "3. Buscar por responsable." << std::endl;
    std::cout << "4. Buscar por numero de telefono." << std::endl;
    std::cout << "5. Buscar por correo electronico." << std::endl;
    std::cout << "6. Buscar por direccion." << std::endl;
    std::cout << std::endl;
    std::cout << "Ingrese el numero de la opcion deseada (0 para cancelar): ";

    std::cin >> in_opcion;
    std::cin.ignore();

    system("cls");
    std::cout << std::endl;

    switch(in_opcion){
        case 1:
            std::cout << "Ingrese el CUIT a buscar: ";
            break;
        case 2:
            std::cout << "Ingrese el nombre a buscar: ";
            break;
        case 3:
            std::cout << "Ingrese el responsable a buscar: ";
            break;
        case 4:
            std::cout << "Ingrese el telefono a buscar: ";
            break;
        case 5:
            std::cout << "Ingrese el correo a buscar: ";
            break;
        case 6:
            std::cout << "Ingrese la direccion a buscar: ";
            break;
        case 0:
            break;
        default:
            std::cout << "Opcion equivocada, debe ser un numero entre 1 y 6.";
            std::cout << std::endl;
            break;
    }

    std::string in_Parametro;

    if(in_opcion>0 && in_opcion<7){

        getline(std::cin, in_Parametro);
        system("cls");

        ArchivoEmpresa archEmpresa;
        Empresa registro;

        int resultados = 0;

        int cantidadRegistro = archEmpresa.get_CantidadRegistros();

        if(cantidadRegistro == 0){
            std::cout << std::endl;
            std::cout << "No se encontraron empresas registradas." << std::endl;
            return;
        }else{
            std::cout << std::endl;
            std::cout << "RESULTADOS: " << std::endl;
            for(int i=0;i<cantidadRegistro;i++){
                registro = archEmpresa.leerEmpresa(i);

                switch(in_opcion){
                    case 1:
                        if(in_Parametro == registro.get_CUIT()){
                            std::cout << i+1 << ") "<<endl << registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 2:
                        if(in_Parametro == registro.get_Nombre()){
                            std::cout << i+1 << ") "<<endl<<  registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 3:
                        if(in_Parametro == registro.get_Responsable()){
                            std::cout << i+1 << ") "<<endl <<  registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 4:
                        if(in_Parametro == registro.get_Telefono()){
                            std::cout << i+1 << ") "<<endl <<  registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 5:
                        if(in_Parametro == registro.get_Email()){
                            std::cout << i+1 << ") "<<endl <<  registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 6:
                        if(in_Parametro == registro.get_Direccion()){
                            std::cout << i+1 << ") "<<endl <<  registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if(resultados == 0){
            std::cout << "No se encontraron resultados con ese parametro." << std::endl;
        }
    }
    system("pause");
}
void EmpresaManager::modificarEmpresaPorCUIT(std::string rol){

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "         MODIFICAR EMPRESAS     " << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    int in_opcion = 1; //inicializado en 1 para que entre al bucle while
    bool error = false;

    std::string in_CUIT;
    std::string in_Dato;

    std::cout << "Ingrese el CUIT de la empresa: ";
    getline(std::cin,in_CUIT);

    ArchivoEmpresa archEmpresa;

    int posicionEmpresa = buscarEmpresaPorCUIT(in_CUIT);

    if(posicionEmpresa == -1){
        std::cout << std::endl;
        std::cout << ">> No se encontro ninguna empresa con ese CUIT.";
        std::cout << std::endl;
    }else{
        Empresa registro = archEmpresa.leerEmpresa(posicionEmpresa);
        std::cout << std::endl;
        std::cout << ">> Empresa encontrada:" << std::endl;
        std::cout << std::endl;
        std::cout << "- CUIT: " << registro.get_CUIT() << std::endl;
        std::cout << "- Nombre: " << registro.get_Nombre() << std::endl;
        std::cout << "- Direccion: " << registro.get_Direccion() << std::endl;
        std::cout << "- Responsable: " << registro.get_Responsable() << std::endl;
        std::cout << "- Email: " << registro.get_Email() << std::endl;
        std::cout << "- Telefono: " << registro.get_Telefono() << std::endl;
        std::cout << std::endl;
        std::cout << "Que dato te gustaria modificar?" << std::endl;
        std::cout << std::endl;
        std::cout << "1) Nombre" << std::endl;
        std::cout << "2) Responsable" << std::endl;
        std::cout << "3) Tel" << std::endl;
        std::cout << "4) Mail" << std::endl;
        std::cout << "5) Direccion" << std::endl;
        std::cout << std::endl;

        while(in_opcion != 0){

            std::cout << "Ingrese la opcion deseada (0 para cancelar):";
            std::cin >> in_opcion;
            std::cin.ignore();

            if(in_opcion>0 && in_opcion < 6){
                std::cout << "Ingrese el dato nuevo: ";
                getline(std::cin,in_Dato);

                system("cls");

                switch(in_opcion){
                    case 1:
                        if(in_Dato.length() > 50 || in_Dato.length() <= 0){
                            std::cout << "Error al cambiar el nombre (caracteres maximos aceptados: 49)." << std::endl;
                            error = true;
                        }else{
                            registro.set_Nombre(in_Dato);
                        }
                        break;
                    case 2:
                        if(in_Dato.length() > 50 || in_Dato.length() <= 0){
                            std::cout << "Error al cambiar el responsable (caracteres maximos aceptados: 49).." << std::endl;
                            error = true;
                        }else{
                            registro.set_Responsable(in_Dato);
                        }
                        break;
                    case 3:
                        if(in_Dato.length() > 20 || in_Dato.length() <= 0){
                            std::cout << "Error al cambiar el telefono (caracteres maximos aceptados: 19).." << std::endl;
                            error = true;
                        }else{
                            registro.set_Telefono(in_Dato);
                        }
                        break;
                    case 4:
                        if(in_Dato.length() > 50 || in_Dato.length() <= 0){
                            std::cout << "Error al cambiar el email (caracteres maximos aceptados: 49).." << std::endl;
                            error = true;
                        }else{
                            registro.set_Email(in_Dato);
                        }
                        break;
                    case 5:
                        if(in_Dato.length() > 100 || in_Dato.length() <= 0){
                            std::cout << "Error al cambiar la direccion (caracteres maximos aceptados: 99).." << std::endl;
                            error = true;
                        }else{
                            registro.set_Direccion(in_Dato);
                        }
                        break;
                    default:
                        break;
                }
                if(!error && archEmpresa.guardarEmpresa(registro,posicionEmpresa)){
                    std::cout << ">> Empresa modificada correctamente." << std::endl;
                }else{
                    std::cout << ">> No se pudieron modificar los datos de la empresa." << std::endl;
                    std::cout << std::endl;
                }
                in_opcion = 0; //para salir del bucle while
            }else{
                if(in_opcion != 0){
                    std::cout << "Opcion equivocada, debe ser del 1 al 5." << std::endl;
                }else{
                    system("cls");
                }
            }
        }
    }
    system("pause");
    system("cls");
}
void EmpresaManager::dardebajarEmpresa(std::string rol){

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "        MENU DE BAJA DE EMPRESA" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    std::string in_CUIT;

    std::cout << "Ingresar el CUIT de la empresa: ";
    getline(std::cin,in_CUIT);

    ArchivoEmpresa archEmpresa;

    int posicionEmpresa = buscarEmpresaPorCUIT(in_CUIT);
    if(posicionEmpresa == -1){
        std::cout << std::endl;
        std::cout << ">> No se encontro ninguna empresa con ese CUIT.";
        std::cout << std::endl;
    }else{
        Empresa registro = archEmpresa.leerEmpresa(posicionEmpresa);
        if(registro.get_Activo()){
            registro.set_Activo(false);
            archEmpresa.guardarEmpresa(registro,posicionEmpresa);
            std::cout << std::endl;
            std::cout << ">> Empresa dada de baja con exito." << std::endl;
            std::cout << std::endl;
        }else{
            std::cout << std::endl;
            std::cout << ">> La empresa ya se encuentra dada de baja." << std::endl;
            std::cout << std::endl;
        }
    }
    system("pause");
    system("cls");
}
/*void EmpresaManager::dardebajarEmpresa(std::string in_CUIT){

    ArchivoEmpresa archEmpresa;

    int posicionEmpresa = buscarEmpresaPorCUIT(in_CUIT);
    if(posicionEmpresa == -1){
        std::cout << "No se encontro ninguna empresa con ese CUIT.";
    }else{
        Empresa registro = archEmpresa.leerEmpresa(posicionEmpresa);
        if(registro.get_Activo()){
            registro.set_Activo(false);
            archEmpresa.guardarEmpresa(registro,posicionEmpresa);
            std::cout << "Empresa dada de baja con exito." << std::endl;
        }else{
            std::cout << "La empresa ya se encuentra dada de baja." << std::endl;
        }
    }
}*/
void EmpresaManager::dardealtaEmpresa(std::string in_CUIT){

    ArchivoEmpresa archEmpresa;

    int posicionEmpresa = buscarEmpresaPorCUIT(in_CUIT);
    if(posicionEmpresa == -1){
        std::cout << ">> No se encontro ninguna empresa con ese CUIT.";
    }else{
        Empresa registro = archEmpresa.leerEmpresa(posicionEmpresa);
        if(!registro.get_Activo()){
            registro.set_Activo(true);
            archEmpresa.guardarEmpresa(registro,posicionEmpresa);
            std::cout << ">> Empresa dada de alta con exito." << std::endl;
        }else{
            std::cout << ">> La empresa ya se encontraba dada de alta." << std::endl;
        }
    }
}
void EmpresaManager::menuEmpresas(std::string rol){

    int in_opcion = 0;
    imprimirMenu(true);

    do{
        std::cout << "Ingrese la opcion que desee (0 para cancelar): ";
        std::cin >> in_opcion;
        std::cin.ignore();

        if(in_opcion != 0){
            if(in_opcion < 0 || in_opcion > 8){
                std::cout << "Opcion invalida, vuelva a intentarlo." << std::endl;
            }else{
                switch(in_opcion){
                 case 1:
                    std::cout << std::endl;
                    cargarEmpresa(rol);
                    std::cout << std::endl;
                    imprimirMenu(false);
                    break;
                 case 2:
                    std::cout << std::endl;
                    listarEmpresasActivas();
                    std::cout << std::endl;
                    imprimirMenu(false);
                    break;
                 case 3:
                    std::cout << std::endl;
                    listarEmpresasInactivas();
                    std::cout << std::endl;
                    imprimirMenu(false);
                    break;
                 case 4:
                    std::cout << std::endl;
                    mostrarCantidadEmpresas();
                    std::cout << std::endl;
                    imprimirMenu(false);
                    break;
                 case 5:
                    std::cout << std::endl;
                    dardebajarEmpresa(rol);
                    std::cout << std::endl;
                    imprimirMenu(false);
                    break;
                 case 6:
                    std::cout << std::endl;
                    modificarEmpresaPorCUIT(rol);
                    std::cout << std::endl;
                    imprimirMenu(false);
                    break;
                 case 7:
                    std::cout << std::endl;
                    buscarPorParametroEspecifico();
                    std::cout << std::endl;
                    imprimirMenu(false);
                    break;
                 default:
                    break;
                }
            }
        }
    }while(in_opcion != 0);
    system("cls");
}
void EmpresaManager::imprimirMenu(bool limpiar){

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "             MENU EMPRESAS" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Cargar una empresa nueva." << std::endl;
    std::cout << "2. Listar empresas dadas de ALTA." << std::endl;
    std::cout << "3. Listar empresas dadas de BAJA." << std::endl;
    std::cout << "4. Consultar cantidad de empresas totales." << std::endl;
    std::cout << "5. Dar de BAJA una empresa cargada por CUIT." << std::endl;
    std::cout << "6. Modificar los datos de una empresa." << std::endl;
    std::cout << "7. Buscar empresas." << std::endl;
    std::cout << std::endl;
}
void EmpresaManager::informeEmpresasConMasEntregas(){

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "Empresas con mayor cantidad de entregas" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    EntregaArchivo archEntrega;
    ArchivoEmpresa archEmpresa;

    Entrega regEntrega;
    Empresa regEmpresa;

    std::string CUIT;
    int totalCUITs = 0;

    int cantidadEntregas = archEntrega.getCantidadRegistros();

    if(cantidadEntregas==0){
        std::cout << ">> No se encontraron entregas registradas en este momento." << std::endl;
        std::cout << std::endl;
        return;
    }

    //Vec que guarda los CUITs de las empresas encontradas.
    std::string* EmpresaCUIT = new std::string[cantidadEntregas];
    //Vec que guarda y acumula las entregas de las empresas encontradas.
    int* EmpresaENTREGAS = new int[cantidadEntregas]{};

    for(int i = 0; i < cantidadEntregas; i++){

        regEntrega = archEntrega.leer(i);
        if(!regEntrega.getActivo()) continue; //En caso de que no este activa la entrega se saltea.

        CUIT = regEntrega.getCuitEmpresa();
        int pos = -1;

        //Busco el CUIT en el vector de CUITs que cree mas arriba
        for(int j = 0; j < totalCUITs; j++){
            if(EmpresaCUIT[j]==CUIT){
                pos = j;
                break;
            }
        }

        //Si lo encontro incremento el contador de entregas
        //Si no lo encontro (else) guardo el CUIT y seteo su contador de entregas en 1.
        if(pos>=0){
            EmpresaENTREGAS[pos] += 1;
        }else{
            EmpresaCUIT[totalCUITs] = CUIT;
            EmpresaENTREGAS[totalCUITs] = 1;
            totalCUITs++;
        }

    }

    std::string tempCUIT;
    int tempEntregas;

    //Ordeno resultados con el metodo de ordenamiento burbuja
    for(int i = 0; i < totalCUITs; i++){
        for(int j = i+1; j < totalCUITs; j++){
            if(EmpresaENTREGAS[j]>EmpresaENTREGAS[i]){

                tempCUIT = EmpresaCUIT[i];
                tempEntregas = EmpresaENTREGAS[i];

                EmpresaCUIT[i] = EmpresaCUIT[j];
                EmpresaENTREGAS[i] = EmpresaENTREGAS[j];

                EmpresaCUIT[j] = tempCUIT;
                EmpresaENTREGAS[j] = tempEntregas;
            }
        }
    }

    std::string nombreEmpresa;
    int posEmpresa;

    //Imprimo los resultados
    for(int i=0; i < totalCUITs; i++){

        //Busco el nombre de la empresa en el archivo empresas.
        posEmpresa = buscarEmpresaPorCUIT(EmpresaCUIT[i]);
        if(posEmpresa>=0){
            regEmpresa = archEmpresa.leerEmpresa(posEmpresa);
            nombreEmpresa = regEmpresa.get_Nombre();
        }else{
            nombreEmpresa = "Nombre no encontrado en los registros de empresas.";
        }

        std::cout << i+1 << ") " << "Empresa " << EmpresaCUIT[i] << " (" << nombreEmpresa << ")" << std::endl;
        std::cout << ">> Cantidad de entregas: " << EmpresaENTREGAS[i] << std::endl;
        std::cout << std::endl;
    }

    delete[] EmpresaCUIT;
    delete[] EmpresaENTREGAS;

}
void EmpresaManager::informeEmpresasConMasImporte(){

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "Empresas con mayor importe acumulado en sus entregas" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    EntregaArchivo archEntrega;
    ArchivoEmpresa archEmpresa;

    Entrega regEntrega;
    Empresa regEmpresa;

    std::string CUIT;
    float Importe;

    int totalCUITs = 0;

    int cantidadEntregas = archEntrega.getCantidadRegistros();

    if(cantidadEntregas==0){
        std::cout << ">> No se encontraron entregas registradas en este momento." << std::endl;
        std::cout << std::endl;
        return;
    }

    //Vec que guarda los CUITs de las empresas encontradas.
    std::string* EmpresaCUIT = new std::string[cantidadEntregas];
    //Vec que guarda y acumula las entregas de las empresas encontradas.
    float* EmpresaIMPORTEACUM = new float[cantidadEntregas]{};

    for(int i = 0; i < cantidadEntregas; i++){

        regEntrega = archEntrega.leer(i);
        if(!regEntrega.getActivo()) continue; //En caso de que no este activa la entrega se saltea.

        CUIT = regEntrega.getCuitEmpresa();
        Importe = regEntrega.getImporte();

        int pos = -1;

        //Busco el CUIT en el vector de CUITs que cree mas arriba
        for(int j = 0; j < totalCUITs; j++){
            if(EmpresaCUIT[j]==CUIT){
                pos = j;
                break;
            }
        }

        //Si lo encontro incremento el acumulador con su importe
        //Si no lo encontro (else) guardo el CUIT y seteo acumulador con el importe
        if(pos>=0){
            EmpresaIMPORTEACUM[pos] += Importe;
        }else{
            EmpresaCUIT[totalCUITs] = CUIT;
            EmpresaIMPORTEACUM[totalCUITs] = Importe;
            totalCUITs++;
        }

    }

    std::string tempCUIT;
    float tempImporteAcum;

    //Ordeno resultados con el metodo de ordenamiento burbuja
    for(int i = 0; i < totalCUITs; i++){
        for(int j = i+1; j < totalCUITs; j++){
            if(EmpresaIMPORTEACUM[j]>EmpresaIMPORTEACUM[i]){

                tempCUIT = EmpresaCUIT[i];
                tempImporteAcum = EmpresaIMPORTEACUM[i];

                EmpresaCUIT[i] = EmpresaCUIT[j];
                EmpresaIMPORTEACUM[i] = EmpresaIMPORTEACUM[j];

                EmpresaCUIT[j] = tempCUIT;
                EmpresaIMPORTEACUM[j] = tempImporteAcum;
            }
        }
    }

    std::string nombreEmpresa;
    int posEmpresa;

    //Imprimo los resultados
    for(int i=0; i < totalCUITs; i++){

        //Busco el nombre de la empresa en el archivo empresas.
        posEmpresa = buscarEmpresaPorCUIT(EmpresaCUIT[i]);
        if(posEmpresa>=0){
            regEmpresa = archEmpresa.leerEmpresa(posEmpresa);
            nombreEmpresa = regEmpresa.get_Nombre();
        }else{
            nombreEmpresa = "Nombre no encontrado en los registros de empresas.";
        }

        std::cout << i+1 << ") " << "Empresa " << EmpresaCUIT[i] << " (" << nombreEmpresa << ")" << std::endl;
        std::cout << ">> Importe acumulado: $" << EmpresaIMPORTEACUM[i] << std::endl;
        std::cout << std::endl;
    }

    delete[] EmpresaCUIT;
    delete[] EmpresaIMPORTEACUM;

}
void EmpresaManager::informedeEntregasMensualesPorAnio(){

    ArchivoEmpresa archEmpresa;
    EntregaArchivo archEntrega;

    Empresa regEmpresa;
    Entrega regEntrega;
    Fecha fecha;

    const int meses = 12;
    int entregasMensuales[meses]{0};
    int cantidadEntregasAnualesTotales = 0;

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "Informe de entregas mensuales" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    if(archEmpresa.get_CantidadRegistros() == 0){
        std::cout << "No se encontraron empresas registradas." << std::endl;
        std::cout << std::endl;
        return;
    };

    std::string in_CUITEmpresa;
    std::string str_NombreEmpresa;
    int in_posEmpresa;
    int in_anio;
    int cantidadEntregasTotales;

    cantidadEntregasTotales = archEntrega.getCantidadRegistros();

    std::cout << "Ingrese el CUIT de la empresa que desea buscar: ";
    getline(std::cin, in_CUITEmpresa);

    in_posEmpresa = buscarEmpresaPorCUIT(in_CUITEmpresa);

    if(cantidadEntregasTotales == 0){
        std::cout << "No hay entregas registradas en este momento." << std::endl;
        std::cout << std::endl;
        return;
    }

    if(in_posEmpresa>=0){

        std::cout << "Ingrese el anio que desea controlar: ";
        std::cin >> in_anio;
        std::cin.ignore();

        //Buscar y extraer el nombre de la empresa
        regEmpresa = archEmpresa.leerEmpresa(in_posEmpresa);
        str_NombreEmpresa = regEmpresa.get_Nombre();

        //Recorro cada entrega
        for(int i = 0; i < cantidadEntregasTotales; i++){
            regEntrega = archEntrega.leer(i);

            //Saltear las entregas inactivas
            if(!regEntrega.getActivo()) continue;

            //Controlo que el cuit sea el mismo
            if(regEntrega.getCuitEmpresa() == in_CUITEmpresa){

                //Extraigo fecha de la entrega
                fecha = regEntrega.getFechaEntrega();
                if(fecha.getAnio() == in_anio && (fecha.getMes() >= 1 && fecha.getMes() <= 12)){
                    entregasMensuales[fecha.getMes()-1] += 1;
                    cantidadEntregasAnualesTotales++;
                }

            }
        }

        system("cls");
        std::cout << "#######################################" << std::endl;
        std::cout << "Informe de entregas mensuales" << std::endl;
        std::cout << "#######################################" << std::endl;
        std::cout << std::endl;
        std::cout << "> CUIT: " << in_CUITEmpresa << std::endl;
        std::cout << "> Nombre empresa: " << str_NombreEmpresa << std::endl;
        std::cout << "> Entregas totales en el anio: " << cantidadEntregasAnualesTotales << std::endl;
        std::cout << std::endl;

        for(int j = 0; j < 12; j++){
            if(j <= 8){
                std::cout << "Mes 0" << j+1 << " - ";
            }else{
                std::cout << "Mes " << j+1 << " - ";
            }
            std::cout << "Cantidad de entregas encontradas: " << entregasMensuales[j] << std::endl;
        }
        std::cout << std::endl;
    }else{
        std::cout << "No se encontro la empresa, revise que el CUIT sea el correcto." << std::endl;
        std::cout << std::endl;
    }
}

void EmpresaManager::empresasSinEntregas(){

    system("cls");

    ArchivoEmpresa archEmp;
    Empresa regEmp;

    int cantidadEmpresas = archEmp.get_CantidadRegistros();
    string* vecEmpresasActivas = new string[cantidadEmpresas];
    bool* entregadas = new bool[cantidadEmpresas]{}; // inicializa en false
    int cantActivas = 0;

    for(int i = 0; i < cantidadEmpresas; i++){
        regEmp = archEmp.leerEmpresa(i);
        if(regEmp.get_Activo()){
            vecEmpresasActivas[cantActivas] = regEmp.get_CUIT();
            cantActivas++;
        }
    }

    EntregaArchivo archEnt;
    Entrega regEnt;

    int cantEntregas = archEnt.getCantidadRegistros();

    for(int i = 0; i < cantEntregas; i++){
        regEnt = archEnt.leer(i);
        string CUITEntregado = regEnt.getCuitEmpresa();
        for(int j = 0; j < cantActivas; j++){
            if(vecEmpresasActivas[j] == CUITEntregado){
                entregadas[j] = true;
                break;
            }
        }
    }

    for(int m = 0; m < cantActivas; m++){
        if(!entregadas[m]){
            int pos = buscarEmpresaPorCUIT(vecEmpresasActivas[m]);
            if(pos != -1) {
                regEmp = archEmp.leerEmpresa(pos);
                cout << "La empresa \"" << regEmp.get_Nombre() << "\" (CUIT: " << regEmp.get_CUIT() << ") no recibio entregas." << endl;
            }
        }
    }

    delete[] vecEmpresasActivas;
    delete[] entregadas;
}

void EmpresaManager::empresasQueRecibieronEntregasEnFecha(){
    system("cls");
    int diaBuscar,mesBuscar,anioBuscar;
    bool encontrado=false;

    cout<<"Ingrese la fecha a buscar: "<<endl;
    cout<<"Ingrese el dia: "<<endl;
    cin>>diaBuscar;
    cout<<"Ingrese el mes: "<<endl;
    cin>>mesBuscar;
    cout<<"Ingrese el año: "<<endl;
    cin>>anioBuscar;

    ArchivoEmpresa archEmp;
    Empresa regEmp;
    EntregaArchivo archEnt;
    Entrega regEnt;

    int cantidadEntregas=archEnt.getCantidadRegistros();
    for(int i=0;i<cantidadEntregas;i++){
        regEnt=archEnt.leer(i);
        Fecha fecha=regEnt.getFechaEntrega();
        if(fecha.getDia()==diaBuscar&&fecha.getMes()==mesBuscar&&fecha.getAnio()==anioBuscar){
            encontrado=true;
            string cuitEncontrado=regEnt.getCuitEmpresa();
            int cantidadEmpresas=archEmp.get_CantidadRegistros();
            for(int j=0;j<cantidadEmpresas;j++){
                regEmp=archEmp.leerEmpresa(j);
                if(regEmp.get_CUIT()==cuitEncontrado){
                    cout<<"En esa fecha se entrego a la empresa: "<<regEmp.get_Nombre()<<endl;
                }
            }
        }
    }
    if (!encontrado) {
    cout << "No se encontraron entregas en esa fecha." << endl;
}
 }
