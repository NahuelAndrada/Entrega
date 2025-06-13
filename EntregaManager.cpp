#include <iostream>
#include "EntregaManager.h"

#include "EntregaArchivo.h"
#include "ArchivoAutopartes.h"
#include "EmpresaManager.h"

using namespace std;

void EntregasManager::cargar() {
    Entrega reg;
    EntregaArchivo archivo;
    int id, numeroAutoparte, cantidad;
    float importe;
    string cuit;
    Fecha fecha;

    cout << "=== CARGAR NUEVA ENTREGA ===" << endl;

    cout << "ID de entrega: ";
    cin >> id;
    if (id <= 0) {
    cout << "Error: el ID debe ser mayor a 0." << endl;
    return;
}

    if (archivo.buscar(id) >= 0) {
       cout << "Error: el ID de entrega ya existe." << endl;
        return;
}


    reg.setIdEntrega(id);

    cout << "Numero de autoparte: ";
    cin >> numeroAutoparte;
    ArchivoAutopartes archivoAutoparte;
    int posAutoparte = archivoAutoparte.BuscarPosicion(numeroAutoparte);

    if (posAutoparte < 0) {
    cout << "Error: la autoparte no existe." << endl;
    return;


}
    reg.setNumeroAutoparte(numeroAutoparte);

    cout << "CUIT de la empresa: ";
    cin >> cuit;
    EmpresaManager archivoEmpresas;
    if (archivoEmpresas.buscarEmpresaPorCUIT(cuit) < 0) {
    cout << "Error: la empresa no est� registrada." << endl;
    return;
}

    reg.setCuitEmpresa(cuit);

    cout << "Fecha de entrega:" << endl;
    int dia, mes, anio;
    cout << "  Dia: "; cin >> dia;
    cout << "  Mes: "; cin >> mes;
    cout << "  Anio: "; cin >> anio;
    fecha.setDia(dia);
    fecha.setMes(mes);
    fecha.setAnio(anio);
    reg.setFechaEntrega(fecha);

    cout << "Cantidad de unidades: ";
    cin >> cantidad;
    Autoparte autoParte = archivoAutoparte.LeerUna(posAutoparte);

	if (cantidad <= 0) {
       cout << "Error: la cantidad debe ser mayor a 0." << endl;
        return;
}

      if (autoParte.getStock() < cantidad) {
       cout << "Error: no hay suficiente stock disponible." << endl;
       cout << "Stock actual: " << autoParte.getStock() << endl;
     return;
}

	int nuevoStock = autoParte.getStock() - cantidad;
	autoParte.setStock(nuevoStock);
	if (!archivoAutoparte.Modificar(autoParte, posAutoparte)) {
    cout << "Error al actualizar el stock de la autoparte." << endl;
    return;
}

    cout << "Importe total: ";
    cin >> importe;
    reg.setImporte(importe);

    reg.setActivo(true);

    // Guardar en archivo
    EntregaArchivo archi;
    if (archi.guardar(reg)) {
        cout << "Entrega guardada correctamente." << endl;
    } else {
        cout << "Error al guardar la entrega." << endl;
    }
}
void EntregasManager::listar() {
    EntregaArchivo archivo;
    int total = archivo.getCantidadRegistros();
    bool hayActivos = false;

    cout << "=== LISTADO DE ENTREGAS ACTIVAS ===" << endl;

    for (int i = 0; i < total; i++) {
        Entrega reg = archivo.leer(i);

        if (reg.getActivo()) {
            hayActivos = true;

            cout << "ID entrega: " << reg.getIdEntrega() << endl;
            cout << "Numero de autoparte: " << reg.getNumeroAutoparte() << endl;
            cout << "CUIT empresa: " << reg.getCuitEmpresa() << endl;

            Fecha f = reg.getFechaEntrega();
            cout << "Fecha de entrega: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;

            cout << "Cantidad de unidades: " << reg.getCantidadUnidades() << endl;
            cout << "Importe: $" << reg.getImporte() << endl;

            cout << "--------------------------" << endl;
        }
    }

    if (!hayActivos) {
        cout << "No hay entregas activas registradas." << endl;
    }
}
void EntregasManager::buscarPorId(int id) {
    EntregaArchivo archivo;
    int pos = archivo.buscar(id);

    if (pos < 0) {
        cout << "Entrega no encontrada." << endl;
        return;
    }

    Entrega reg = archivo.leer(pos);

    if (!reg.getActivo()) {
        cout << "La entrega est� dada de baja." << endl;
        return;
    }

    cout << "=== ENTREGA ENCONTRADA ===" << endl;
    cout << "ID entrega: " << reg.getIdEntrega() << endl;
    cout << "Numero de autoparte: " << reg.getNumeroAutoparte() << endl;
    cout << "CUIT empresa: " << reg.getCuitEmpresa() << endl;

    Fecha f = reg.getFechaEntrega();
    cout << "Fecha de entrega: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;

    cout << "Cantidad de unidades: " << reg.getCantidadUnidades() << endl;
    cout << "Importe: $" << reg.getImporte() << endl;
}
void EntregasManager::entregasPorEmpresa(std::string cuit) {
    EntregaArchivo archivo;
    int total = archivo.getCantidadRegistros();
    bool hayCoincidencias = false;
    float TotalEmpresa=0;

    cout << "=== ENTREGAS PARA EMPRESA: " << cuit << " ===" << endl;

    for (int i = 0; i < total; i++) {
        Entrega reg = archivo.leer(i);

        if (reg.getActivo() && reg.getCuitEmpresa() == cuit) {
            hayCoincidencias = true;

            cout << "ID entrega: " << reg.getIdEntrega() << endl;
            cout << "Numero de autoparte: " << reg.getNumeroAutoparte() << endl;

            Fecha f = reg.getFechaEntrega();
            cout << "Fecha de entrega: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;

            cout << "Cantidad de unidades: " << reg.getCantidadUnidades() << endl;
            cout << "Importe: $" << reg.getImporte() << endl;

            cout << "--------------------------" << endl;
            TotalEmpresa+=reg.getImporte();
        }
    }

    if (!hayCoincidencias) {
        cout << "No se encontraron entregas activas para esa empresa." << endl;
    }
    else{
        cout<<"El CUIT: "<<cuit<< " se le facturo por un total de: $ "<<TotalEmpresa<<endl;
    }
}
void EntregasManager::entregasPorFecha(Fecha desde, Fecha hasta) {
    EntregaArchivo archivo;
    int total = archivo.getCantidadRegistros();
    bool hayCoincidencias = false;
    float sumaImporte = 0;

    cout << "=== ENTREGAS ENTRE "
         << desde.getDia() << "/" << desde.getMes() << "/" << desde.getAnio()
         << " Y "
         << hasta.getDia() << "/" << hasta.getMes() << "/" << hasta.getAnio()
         << " ===" << endl;

    // Convertir fechas a formato entero AAAAMMDD
    int fechaDesde = desde.getAnio() * 10000 + desde.getMes() * 100 + desde.getDia();
    int fechaHasta = hasta.getAnio() * 10000 + hasta.getMes() * 100 + hasta.getDia();

    for (int i = 0; i < total; i++) {
        Entrega reg = archivo.leer(i);

        int fechaEntrega = reg.getFechaEntrega().getAnio() * 10000 + reg.getFechaEntrega().getMes() * 100 + reg.getFechaEntrega().getDia();

        if (reg.getActivo()&&fechaEntrega >= fechaDesde && fechaEntrega <= fechaHasta) {
            hayCoincidencias = true;
            sumaImporte += reg.getImporte();

            cout << "ID entrega: " << reg.getIdEntrega() << endl;
            cout << "CUIT empresa: " << reg.getCuitEmpresa() << endl;
            cout << "N�mero autoparte: " << reg.getNumeroAutoparte() << endl;
            cout << "Fecha: " << reg.getFechaEntrega().getDia() << "/" << reg.getFechaEntrega().getMes() << "/" << reg.getFechaEntrega().getAnio() << endl;
            cout << "Cantidad unidades: " << reg.getCantidadUnidades() << endl;
            cout << "Importe: $" << reg.getImporte() << endl;
            cout << "--------------------------" << endl;
        }
    }

    if (!hayCoincidencias) {
        cout << "No se encontraron entregas en ese rango de fechas." << endl;
    } else {
        cout << "TOTAL FACTURADO EN EL RANGO: $" << sumaImporte << endl;
    }
}
void EntregasManager::eliminarPorId(int id) {
    EntregaArchivo archivo;
    int pos = archivo.buscar(id);

    if (pos < 0) {
        cout << "Error: No se encontr� una entrega con ese ID." << endl;
        return;
    }

    Entrega reg = archivo.leer(pos);

    if (!reg.getActivo()) {
        cout << "La entrega ya est� dada de baja." << endl;
        return;
    }

    reg.setActivo(false);

    if (archivo.guardar(reg, pos)) {
        cout << "Entrega eliminada correctamente (dada de baja)." << endl;
    } else {
        cout << "Error al intentar eliminar la entrega." << endl;
    }
}
void EntregasManager::MenuEntrega(){
    EntregasManager manager;
    int opcion;

    do {
        cout << "=== MENU DE GESTION DE ENTREGAS ===" << endl;
        cout << "1. Cargar nueva entrega" << endl;
        cout << "2. Listar entregas activas" << endl;
        cout << "3. Buscar entrega por ID" << endl;
        cout << "4. Mostrar entregas por empresa" << endl;
        cout << "5. Mostrar entregas por rango de fechas" << endl;
        cout << "6. Eliminar entrega por ID" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            manager.cargar();
            break;
        case 2:
            manager.listar();
            break;
        case 3: {
            int id;
            cout << "Ingrese ID de la entrega: ";
            cin >> id;
            manager.buscarPorId(id);
            break;
        }
        case 4: {
            string cuit;
            cout << "Ingrese CUIT de la empresa: ";
            cin >> cuit;
            manager.entregasPorEmpresa(cuit);
            break;
        }
        case 5: {
            Fecha desde, hasta;
            int dd, md, ad, dh, mh, ah;

            cout << "Fecha DESDE:" << endl;
            cout << "D�a: ";
            cin >> dd;
            cout << "Mes: ";
            cin >> md;
            cout << "A�o: ";
            cin >> ad;
            desde.setDia(dd); desde.setMes(md); desde.setAnio(ad);

            cout << "Fecha HASTA:" << endl;
            cout << "D�a: "; cin >> dh;
            cout << "Mes: "; cin >> mh;
            cout << "A�o: "; cin >> ah;
            hasta.setDia(dh); hasta.setMes(mh); hasta.setAnio(ah);

            manager.entregasPorFecha(desde, hasta);
            break;
        }
        case 6: {
            int id;
            cout << "Ingrese ID de entrega a eliminar: ";
            cin >> id;
            manager.eliminarPorId(id);
            break;
        }
        case 0:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion inv�lida." << endl;
        }

    } while (opcion != 0);
}



