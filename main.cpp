#include <iostream>
#include "TipoAutoparte.h"
#include "EmpresaManager.h"
#include "AutopartesManager.h"
#include "EntregaManager.h"

using namespace std;

void menuEmpresas(EmpresaManager& em);
void menuAutopartes(AutopartesManager& am);
void menuEntregas(EntregasManager& en);

int main() {
    EmpresaManager   empresas;
    AutopartesManager autopartes;
    EntregasManager  entregas;

    int opcion;
    do {
        cout << "\n========= MENU PRINCIPAL =========\n";
        cout << "1. Gestion de Empresas\n";
        cout << "2. Gestion de Autopartes\n";
        cout << "3. Gestion de Entregas\n";
        cout << "0. Salir\n";
        cout << "Seleccione opcion: ";
        cin  >> opcion;

        switch (opcion) {
            case 1: menuEmpresas(empresas);  break;
            case 2: menuAutopartes(autopartes); break;
            case 3: menuEntregas(entregas);  break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}

// ---------- SUB‑MENUS ----------
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
        cout << "1. Alta\n2. Listar\n3. Buscar por numero\n4. Baja\n0. Volver\n";
        cin >> op;
        switch (op) {
            case 1: am.CargarAutoparteNueva();             break;
            case 2: am.ListarAutopartesActivas();             break;
            case 3: {int n;cout<<"Numero:";cin>>n;am.BuscarAutopartePorNumero(n);} break;
            case 4: {int n;cout<<"Numero:";cin>>n;am.DarDeBajaAutoparte(n);}        break;
            case 0: break;
            default: cout<<"Opcion invalida.\n";
        }
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
