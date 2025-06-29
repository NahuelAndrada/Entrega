#include <iostream>
#include "TipoAutoparteManager.h"
#include "EmpresaManager.h"
#include "AutopartesManager.h"
#include "EntregaManager.h"
#include "TipoAutoparte.h"

using namespace std;

void menuInformes();
void menuPrincipal();
void presentacion();

int main() {
    EmpresaManager   empresas;
    AutopartesManager autopartes;
    EntregasManager  entregas;
    TipoAutoparteManager tipoAutopartes;

    int opcion;
    do {
        system("cls");

        presentacion();
        menuPrincipal();

        cout << "Seleccione opcion: ";
        cin  >> opcion;

        system("cls");

        switch (opcion) {
            case 1: empresas.menuEmpresas();  break;
            case 2: autopartes.menuAutopartes(); break;
            case 3: entregas.MenuEntrega();  break;
            case 4: tipoAutopartes.menuTipoAutopartes(); break;
            case 5: menuInformes(); break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n"; system("pause");
        }
    } while (opcion != 0);

    return 0;
}
void menuInformes() {
    int opcion;
    do {
        system("cls");
        cout << "--- INFORMES ---" << endl;

        cout << endl;
        cout << "1 - Ranking de autopartes con mayores entregas" << endl;
        cout << "2 - Informe de autopartes con stock bajo" << endl;
        cout << "3 - Ranking de empresas (mayor cantidad de entregas)" << endl;
        cout << "4 - Ranking de empresas (mayor importe acumulado en entregas)" << endl;
        cout << "5 - Informe de entregas mensuales de una empresa" << endl;
        cout << "6 - Informe de tipo de autopartes activas utilizadas en las autopartes activas" << endl;
        cout << "0 - Volver al menu principal" << endl;
        cout << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion){
            case 1:{
                AutopartesManager am;
                am.rankingAutopartes();
                system("pause");
                break;
            }
            case 2:{
                AutopartesManager am;
                am.informeStockBajo();
                system("pause");
                break;
            }
            case 3:{
                EmpresaManager em;
                em.informeEmpresasConMasEntregas();
                system("pause");
                break;
            }
            case 4:{
                EmpresaManager em;
                em.informeEmpresasConMasImporte();
                system("pause");
                break;
            }
            case 5:{
                EmpresaManager em;
                em.informedeEntregasMensualesPorAnio();
                system("pause");
                break;
            }
            case 6:{
                TipoAutoparteManager tipoMa;
                tipoMa.InformeCantidadDeTiposAutopartesUtilizadas();
                system("pause");
                break;
            }
            case 0:
                break;
            default:
                cout << "Opción invalida\n";
                system("pause");
        }
    } while (opcion != 0);
}
void presentacion(){


    cout << endl;
    cout << "   |                     ##     ##  #    #  ##    # ####     ####                            |   " << endl;
    cout << "   |                     # #   # #  #    #  # #   # #   #   #    #                           |   " << endl;
    cout << "   |                     #  ###  #  #    #  #  #  # #    # #      #                          |   " << endl;
    cout << "   |                     #   #   #  #    #  #   # # #   #   #    #                           |   " << endl;
    cout << "   |                     #       #   ####   #    ## ####     ####                            |   " << endl;
    cout << "   |                                                                                         |   " << endl;
    cout << "   |      ###     #    #  #########   ####    ####    ###    ####  ######### #### #######    |   " << endl;
    cout << "   |    ##   ##   #    #      #      #    #   #   # ##   ##  #   #     #     #    #          |   " << endl;
    cout << "   |    #######   #    #      #     #      #  ####  #######  ####      #     #### #######    |   " << endl;
    cout << "   |    #     #   #    #      #      #    #   #     #     #  #  #      #     #          #    |   " << endl;
    cout << "   |    #     #    ####       #       ####    #     #     #  #   #     #     #### #######    |   " << endl;
    cout << endl;

    cout << endl;
    cout << "####################################" << endl;
    cout << "  Universidad Tecnologica Nacional" << endl;
    cout << "####################################" << endl;
    cout << endl;
    cout << "- Tecnicatura Universitaria en Programacion" << endl;
    cout << "- Trabajo Practico Integral" << endl;
    cout << endl;
    cout << "> Materia: Programacion 2" << endl;
    cout << "> Profesor: Daniel Kloster" << endl;
    cout << endl;
    cout << "Alumnos:" << endl;
    cout << "- Franco Dario Fioravanti" << endl;
    cout << "- Gabriel Agustin Fernandez Alcaraz" << endl;
    cout << "- Nicolas Ezequiel Strozzi" << endl;
    cout << "- Nahuel Emiliano Andrada" << endl;
    cout << endl;
}
void menuPrincipal(){
    cout << "========= MENU PRINCIPAL =========" << endl;
    cout << endl;
    cout << "1. Gestion de Empresas" << endl;
    cout << "2. Gestion de Autopartes" << endl;
    cout << "3. Gestion de Entregas" << endl;
    cout << "4. Gestion de Tipo autopartes" << endl;
    cout << "5. Consulta de Informes" << endl;
    cout << "0. Salir" << endl;
    cout << endl;
}
