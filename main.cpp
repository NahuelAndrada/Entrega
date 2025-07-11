#include <iostream>
#include "TipoAutoparteManager.h"
#include "EmpresaManager.h"
#include "AutopartesManager.h"
#include "EntregaManager.h"
#include "TipoAutoparte.h"
#include "presentacion.h"
#include "creditos.h"
#include "Backup.h"
#include "Usuario.h"

using namespace std;

void menuInformes();
void mostrarMenuPrincipal();

int main() {

    Usuario usuario;

    if (!usuario.login()) {
        cout << "Saliendo del sistema." << endl;
        return 0;
    }

    EmpresaManager empresas;
    AutopartesManager autopartes;
    EntregasManager entregas;
    TipoAutoparteManager tipoAutopartes;
    creditos menuCreditos;
    Backup backupManager;

    system("cls");

    int opcion;
    do {
        presentacion();
        cout << "Seleccione opcion: ";
        cin  >> opcion;

        system("cls");

        switch (opcion) {
            case 1: empresas.menuEmpresas(usuario.getRol());  break;
            case 2: autopartes.menuAutopartes(usuario.getRol()); break;
            case 3: entregas.MenuEntrega(usuario.getRol());  break;
            case 4: tipoAutopartes.menuTipoAutopartes(usuario.getRol()); break;
            case 5: menuInformes(); break;
            case 6: menuCreditos.mostrarCreditos(); system("pause"); break;
            case 7: backupManager.mostrarSubmenuBackup(); break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n"; system("pause"); break;
        }

        if(opcion != 0) system("cls");

    } while (opcion != 0);

    return 0;
}

void menuInformes() {
    int opcion;
    EntregasManager manager;
    do {
        system("cls");

        cout << "#######################################" << endl;
        cout << "              MENU INFORMES     " <<endl;
        cout << "#######################################" << endl;
        cout <<endl;

        cout << "1 - Ranking de autopartes con mayores entregas" << endl;
        cout << "2 - Informe de autopartes con stock bajo" << endl;
        cout << "3 - Ranking de empresas (mayor cantidad de entregas)" << endl;
        cout << "4 - Ranking de empresas (mayor importe acumulado en entregas)" << endl;
        cout << "5 - Informe de entregas mensuales de una empresa" << endl;
        cout << "6 - Informe de tipo de autopartes activas utilizadas en las autopartes activas" << endl;
        cout << "7 - Informe Mostrar entregas por empresa" << endl;
        cout << "8 - Informe Mostrar entregas por rango de fechas" << endl;
        cout << "9 - Mostrar entregas por nombre de empresa" << endl;
        cout << "10 - Mostrar entregas por nombre de autoparte" << endl;
        cout << "11 - Mostrar cantidad de entregas por nombre de empresa" << endl;
        cout << "12 - Mostrar cantidad de entregas por nombre de autoparte" << endl;
        cout << "13 - Pruebas" << endl;
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
            case 7: {
                manager.entregasPorEmpresa();
                system("pause");
                break;
            }
            case 8: {
                manager.entregasPorFecha();
                system("pause");
                break;
            }
             case 9:{
                manager.entregasPorNombreEmpresa();
                system("pause");
                break;
            }
            case 10:{
                manager.entregasPorNombreAutoparte();
                system("pause");
                break;
            }
            case 11:{
                manager.cantidadEntregasPorNombreEmpresa();
                system("pause");
                break;
            }
            case 12:{
                manager.cantidadEntregasPorNombreAutoparte();
                system("pause");
                break;
            }
            case 13:{
                EmpresaManager em;
                em.empresasQueRecibieronEntregasEnFecha();
                system("pause");
                break;
            }
            case 0:
                break;
            default:
                cout << "Opcion invalida\n";
                system("pause");
        }
    } while (opcion != 0);
}


