
#include <iostream>
#include "TipoAutoparteManager.h"
#include "EmpresaManager.h"
#include "AutopartesManager.h"
#include "EntregaManager.h"
#include "TipoAutoparte.h"

using namespace std;

void menuEmpresas(EmpresaManager& em);
void menuAutopartes(AutopartesManager& am);
void menuEntregas(EntregasManager& en);
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
            case 1: menuEmpresas(empresas);  break;
            case 2: menuAutopartes(autopartes); break;
            case 3: menuEntregas(entregas);  break;
            case 4: menuTipos(tipoAutopartes); break;
            case 5: menuInformes(); break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}

// ---------- SUBMENUS ----------
void menuEmpresas(EmpresaManager& em) {
    int op;
    do {
        cout << "\n--- EMPRESAS ---\n";
        cout << "1. Alta\n2. Listar\n3. Buscar por CUIT\n4. Baja\n0. Volver\n";
        cin  >> op;
        switch (op) {
            case 1: em.cargarEmpresa();           break;
            case 2: em.listarEmpresasActivas();           break;
            case 3: {string c; cout<<"CUIT:";cin>>c; em.buscarEmpresaPorCUIT(c);} break;
            case 4: {string c; cout<<"CUIT:";cin>>c; em.dardebajarEmpresa(c);}      break;
            case 0: break;
            default: cout<<"Opcion invalida.\n";
        }
    } while (op!=0);
}

    void menuAutopartes(AutopartesManager& am) {
    int op;
    do {
        cout << "\n--- AUTOPARTES ---\n";
        cout << "1. Alta\n2. Modificar autoparte\n3. Buscar autoparte por ID\n4. Buscar autoparte por nombre\n5. Listar autoparte activa\n6. Listar autoparte inactiva\n7. Eliminar autoparte\n0. Volver\n";
        cin >> op;
        switch (op) {
            case 1:
                am.cargarAutoparte();
                break;
            case 2:
                am.modificarAutoparte();
                break;
            case 3:
                am.buscarAutopartePorNumero();
                break;
            case 4:
                am.buscarAutopartePorNombre();
                break;
            case 5:
                am.listarAutoparteActivas();
                break;
            case 6:
                am.listarAutoparteInactivas();
                break;
            case 7:
                am.eliminarAutoparte();
                break;
            case 0:
                cout << "Fin del programa." << endl;
                break;
            default:
                cout<<"Opcion invalida.\n";
                break;
        }
        cout << endl;
        system("pause");
        system("cls");

    } while (op!=0);
}

void menuEntregas(EntregasManager& en) {
    int op;
    do {
        cout << "\n--- ENTREGAS ---\n";
        cout << "1. Cargar\n2. Listar activas\n3. Buscar por ID\n";
        cout << "4. Por empresa\n5. Por rango de fechas\n";
        cout << "6. Eliminar por ID\n7. Modificar por ID\n0. Volver\n";
        cin >> op;
        switch (op) {
            case 1: en.cargar();         break;
            case 2: en.listar();         break;
            case 3: {int id;cout<<"ID:";cin>>id;en.buscarPorId(id);}        break;
            case 4: {string c;cout<<"CUIT:";cin>>c;en.entregasPorEmpresa(c);}break;
            case 5: {
                Fecha d,h; int dd,mm,aa;
                cout<<"Desde (d m a): ";cin>>dd>>mm>>aa;
                d.setDia(dd);d.setMes(mm);d.setAnio(aa);
                cout<<"Hasta (d m a): ";cin>>dd>>mm>>aa;
                h.setDia(dd);h.setMes(mm);h.setAnio(aa);
                en.entregasPorFecha(d,h);
            } break;
            case 6: {int id;cout<<"ID:";cin>>id;en.eliminarPorId(id);} break;
            //case 7: {int id;cout<<"ID:";cin>>id;en.|(id);} break;
            case 0: break;
            default: cout<<"Opcion invalida.\n";
        }
    } while (op!=0);
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
