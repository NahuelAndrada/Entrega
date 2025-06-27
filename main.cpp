#include <iostream>
#include "TipoAutoparteManager.h"
#include "EmpresaManager.h"
#include "AutopartesManager.h"
#include "EntregaManager.h"
#include "TipoAutoparte.h"

using namespace std;

void menuTipos(TipoAutoparteManager&);
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
            case 4: menuTipos(tipoAutopartes); break;
            case 5: menuInformes(); break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n"; system("pause");
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
        cout << "--- INFORMES ---" << endl;

        cout << endl;
        cout << "1 - Ranking de autopartes con mayores entregas" << endl;
        cout << "2 - Ranking de empresas (mayor cantidad de entregas)" << endl;
        cout << "3 - Ranking de empresas (mayor importe acumulado en entregas)" << endl;
        cout << "4 - Informe de entregas mensuales de una empresa" << endl;
        cout << "0 - Volver al menu principal" << endl;
        cout << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion){
            case 1:{
                EntregasManager em;
                em.rankingAutopartes();
                system("pause");
                break;
            }
            case 2:{
                EmpresaManager em;
                em.informeEmpresasConMasEntregas();
                system("pause");
                break;
            }
            case 3:{
                EmpresaManager em;
                em.informeEmpresasConMasImporte();
                system("pause");
                break;
            }
            case 4:{
                EmpresaManager em;
                em.informedeEntregasMensualesPorAnio();
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
    cout << "Alumnos: " << endl;
    cout << "- Alumno1" << endl;
    cout << "- Alumno2" << endl;
    cout << "- Alumno3" << endl;
    cout << "- Alumno4" << endl;
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
