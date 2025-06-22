#include <iostream>
#include <string>

#include "Empresa.h"
#include "ArchivoEmpresa.h"
#include "EmpresaManager.h"

void EmpresaManager::cargarEmpresa(){

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "            CARGAR EMPRESA" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    Empresa datosEmpresa; //Crear objeto vacio

    //#################################
    //Variables para reactivar empresa:
    Empresa registro;
    int pos;
    std::string opcion;
    //#################################

    ArchivoEmpresa archEmpresa;

    std::string in_CUIT, in_Nombre, in_Responsable, in_Telefono, in_Email, in_Direccion;
    bool status;

    status = false;

    while(!status){
        std::cout << "Ingrese CUIT (max 14 car.): ";
        getline(std::cin, in_CUIT);

        if(in_CUIT.length() >= 15){
            std::cout << "Error: el CUIT es demasiado largo, recuerde que puede tener hasta 14 caracteres.";
            return;
        }

        std::cout << "Ingrese nombre (max 49 car.): ";
        getline(std::cin, in_Nombre);

        if(in_Nombre.length() >= 50){
            std::cout << "Error: el nombre es demasiado largo, recuerde que puede tener hasta 49 caracteres.";
            return;
        }

        std::cout << "Ingrese responsable (max 49 car.): ";
        getline(std::cin, in_Responsable);

        if(in_Responsable.length() >= 50){
            std::cout << "Error: el responsable es demasiado largo, recuerde que puede tener hasta 49 caracteres.";
            return;
        }

        std::cout << "Ingrese telefono (max 19 car.): ";
        getline(std::cin, in_Telefono);

        if(in_Telefono.length() >= 20){
            std::cout << "Error: el telefono es demasiado largo, recuerde que puede tener hasta 19 caracteres.";
            return;
        }

        std::cout << "Ingrese email (max 49 car.): ";
        getline(std::cin, in_Email);

        if(in_Email.length() >= 50){
            std::cout << "Error: el email es demasiado largo, recuerde que puede tener hasta 49 caracteres.";
            return;
        }

        std::cout << "Ingrese direccion (max 99 car.): ";
        getline(std::cin, in_Direccion);

        if(in_Direccion.length() >= 100){
            std::cout << "Error: la direccion es demasiado larga, recuerde que puede tener hasta 99 caracteres.";
            return;
        }

        datosEmpresa.set_CUIT(in_CUIT);
        datosEmpresa.set_Nombre(in_Nombre);
        datosEmpresa.set_Responsable(in_Responsable);
        datosEmpresa.set_Telefono(in_Telefono);
        datosEmpresa.set_Email(in_Email);
        datosEmpresa.set_Direccion(in_Direccion);
        datosEmpresa.set_Activo(true);

        pos = buscarEmpresaPorCUIT(datosEmpresa.get_CUIT());
        if(pos>=0){
            registro = archEmpresa.leerEmpresa(pos);
            if(registro.get_Activo()){
                system("cls");
                std::cout << std::endl;
                std::cout << ">> No se pudo cargar la empresa porque ya existe un registro con este CUIT.";
                std::cout << std::endl;
            }else{
                system("cls");
                std::cout << std::endl;
                std::cout << ">> La empresa que intentaste cargar se encuentra actualmente inactiva, te gustaria reactivarla? (S/N): ";
                std::cout << std::endl;
                getline(std::cin,opcion);
                while(opcion != "S" && opcion != "N"){
                    std::cout << ">> Opcion equivocada, escriba S para SI o N para NO." << std::endl;
                    std::cout << ">> Te gustaria reactivar la empresa " << in_CUIT << "? (S/N): ";
                    getline(std::cin,opcion);
                }
                if(opcion == "S"){
                    dardealtaEmpresa(in_CUIT);
                }
            }
            status = true;
        }else{
            status = true;
            archEmpresa.guardarEmpresa(datosEmpresa);
            std::cout << "Registro cargado con exito." << std::endl;
        }
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
               std::cout << ">> " << registro.toCSV() << std::endl;
               contador++;
            }
        }
    }
    if(contador==0 && cantidadRegistros != 0){
        std::cout << ">> No se encontraron empresas activas para mostrar." << std::endl;
    }
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
               std::cout << ">> " << registro.toCSV() << std::endl;
               contador++;
            }
        }
    }
    if(contador==0 && cantidadRegistros != 0){
        std::cout << ">> No se encontraron empresas inactivas para mostrar." << std::endl;
    }
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
            std::cout << "No se encontraron registros." << std::endl;
            std::cout << std::endl;
        }else{
            std::cout << std::endl;
            std::cout << "RESULTADOS: " << std::endl;
            for(int i=0;i<cantidadRegistro;i++){
                registro = archEmpresa.leerEmpresa(i);

                switch(in_opcion){
                    case 1:
                        if(in_Parametro == registro.get_CUIT()){
                            std::cout << i+1 << ") " << registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 2:
                        if(in_Parametro == registro.get_Nombre()){
                            std::cout << i+1 << ") " <<  registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 3:
                        if(in_Parametro == registro.get_Responsable()){
                            std::cout << i+1 << ") " <<  registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 4:
                        if(in_Parametro == registro.get_Telefono()){
                            std::cout << i+1 << ") " <<  registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 5:
                        if(in_Parametro == registro.get_Email()){
                            std::cout << i+1 << ") " <<  registro.toCSV() << std::endl;
                            resultados++;
                        }
                        break;
                    case 6:
                        if(in_Parametro == registro.get_Direccion()){
                            std::cout << i+1 << ") " <<  registro.toCSV() << std::endl;
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
}
void EmpresaManager::modificarEmpresaPorCUIT(){

    system("cls");

    std::cout << "#######################################" << std::endl;
    std::cout << "         MODIFICAR EMPRESAS     " << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    int in_opcion;
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
        std::cout << ">> Empresa encontrada (" << posicionEmpresa << "): " << registro.toCSV() << std::endl;
        std::cout << "Que dato te gustaria modificar?" << std::endl;
        std::cout << std::endl;
        std::cout << "1) Nombre" << std::endl;
        std::cout << "2) Responsable" << std::endl;
        std::cout << "3) Tel" << std::endl;
        std::cout << "4) Mail" << std::endl;
        std::cout << "5) Direccion" << std::endl;
        std::cout << std::endl;
        std::cout << "Ingrese la opcion deseada (1 - 5):";

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
        }else{
            std::cout << "Opcion equivocada, debe ser del 1 al 5." << std::endl;
        }
    }
}
void EmpresaManager::dardebajarEmpresa(){

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
}
void EmpresaManager::dardebajarEmpresa(std::string in_CUIT){

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
}
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
void EmpresaManager::menuEmpresas(){

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
                cargarEmpresa();

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
                dardebajarEmpresa();

                std::cout << std::endl;
                imprimirMenu(false);

                break;
             case 6:

                std::cout << std::endl;
                modificarEmpresaPorCUIT();

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
}
void EmpresaManager::imprimirMenu(bool limpiar){

    if(limpiar){
        system("cls");
    }

    std::cout << "#######################################" << std::endl;
    std::cout << "             MENU EMPRESAS" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Cargar una empresa nueva." << std::endl;
    std::cout << "2. Listar empresas dadas de ALTA." << std::endl;
    std::cout << "3. Listar empresas dadas de BAJA." << std::endl;
    std::cout << "4. Consultar cantidad de empresas totales." << std::endl;
    std::cout << "5. Dar de BAJA una empresa cargada." << std::endl;
    std::cout << "6. Modificar los datos de una empresa." << std::endl;
    std::cout << "7. Buscar empresas." << std::endl;
    std::cout << std::endl;
}
