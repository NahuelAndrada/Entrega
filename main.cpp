
#include <iostream>
#include "TipoAutoparteManager.h"
#include "EmpresaManager.h"
#include "AutopartesManager.h"
#include "EntregaManager.h"
#include "TipoAutoparte.h"

using namespace std;

void menuTipos(TipoAutoparteManager&);
void menuInformes();

int main() {
    EmpresaManager   empresas;
    AutopartesManager autopartes;
    EntregasManager  entregas;
    TipoAutoparteManager tipoAutopartes;

    int opcion;
    do {
        system("cls");
        cout << "\n========= MENU PRINCIPAL =========\n";
        cout << "1. Gestion de Empresas\n";
        cout << "2. Gestion de Autopartes\n";
        cout << "3. Gestion de Entregas\n";
        cout << "4. Gestion de Tipo autopartes\n";
        cout << "5. Informes\n";
        cout << "0. Salir\n";
        cout << "Seleccione opcion: ";
        cin  >> opcion;

        switch (opcion) {
            case 1: empresas.menuEmpresas();  break;
            case 2: autopartes.menuAutopartes(); break;
            case 3: entregas.MenuEntrega();  break;
            case 4: menuTipos(tipoAutopartes); break;
            case 5: menuInformes(); break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}

void menuTipos(TipoAutoparteManager& tm) {
    int op;
    do {
        cout << "\n--- TIPOS DE AUTOPARTES ---\n";
        cout << "1. Alta\n";
        cout << "2. Modificar\n";
        cout << "3. Buscar por ID\n";
        cout << "4. Listar activos\n";
        cout << "5. Listar inactivos\n";
        cout << "6. Eliminar\n";
        cout << "0. Volver\n";
        cin >> op;

        switch (op) {
            case 1: tm.cargar(); break;
            case 2: tm.modificar(); break;
            case 3: tm.buscarPorID(); break;
            case 4: tm.listar(); break;
            case 5: tm.listarInactivos(); break;
            case 6: tm.eliminar(); break;
            case 0: break;
            default: cout << "Opci¢n inv lida.\n";
        }

        system("pause");
        system("cls");
    } while (op != 0);
}

void menuInformes() {
    int opcion;
    do {
        system("cls");
        cout << "--- INFORMES ---\n";
        cout << "1 - Ranking de autopartes mas entregadas\n";
        cout << "0 - Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                EntregasManager em;
                em.rankingAutopartes();
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
