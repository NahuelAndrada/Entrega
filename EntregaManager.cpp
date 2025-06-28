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
    int posAutoparte = archivoAutoparte.buscarPorNumero(numeroAutoparte);

    if (posAutoparte < 0) {
    cout << "Error: la autoparte no existe." << endl;
    return;


}
    reg.setNumeroAutoparte(numeroAutoparte);

    cout << "CUIT de la empresa: ";
    cin >> cuit;
    EmpresaManager archivoEmpresas;
    if (archivoEmpresas.buscarEmpresaPorCUIT(cuit) < 0) {
    cout << "Error: la empresa no está registrada." << endl;
    return;
}

    reg.setCuitEmpresa(cuit);

    cout << "Fecha de entrega:" << endl;
    int dia, mes, anio;
    int fin;
    bool validar;
    do{

    cout << "  Dia: "; cin >> dia;
    validar= fecha.DiaValido(dia);
        if(dia==0){
        dia=-1;
    }
    while(validar==false){
        cout<<"el dia no es valido, por favor vuelva a ingresar un dia o aprete 0 para volver al menu"<<endl;
        cout << "  Dia: ";
        cin>>dia;
        validar= fecha.DiaValido(dia);
        if(dia==0){
        return;}
    }

    cout << "  Mes: "; cin >> mes;
    validar=fecha.MesValido(mes);
    if (mes==0){
        mes=-1;
    }
    while(validar==false){
        cout<<"el mes no es valido, por favor vuelva a ingresar un mes o aprete 0 para volver al menu"<<endl;
        cout << "  Mes: ";
        cin>>mes;
        validar= fecha.MesValido(mes);
        if(mes==0){
        return;}
    }

    cout << "  Anio: "; cin >> anio;
    validar=fecha.AnioValido(anio);
    if (anio==0){
        anio=-1;
    }
    while(validar==false){
        cout<<"el anio no es valido, por favor vuelva a ingresar un anio o aprete 0 para volver al menu"<<endl;
        cin>>anio;
        validar= fecha.AnioValido(anio);
        if(anio==0){
        return;}
    }

    validar=fecha.Validarfecha(dia,mes,anio);
    if (!validar){
    cout << "La fecha completa no es válida (por ejemplo, 30/2). Apriete 0 para volver al menu o cualquier otro numero para volver a ingresar otra fecha"<<endl;
    cin>>fin;
    if(fin==0)return;
}
    }while(!validar);

    fecha.setDia(dia);
    fecha.setMes(mes);
    fecha.setAnio(anio);
    reg.setFechaEntrega(fecha);


    cout << "Cantidad de unidades: ";
    cin >> cantidad;
    Autoparte autoParte = archivoAutoparte.leer(posAutoparte);

	if (cantidad <= 0) {
       cout << "Error: la cantidad debe ser mayor a 0." << endl;
        return;
}

      if (autoParte.getStock() < cantidad) {
       cout << "Error: no hay suficiente stock disponible." << endl;
       cout << "Stock actual: " << autoParte.getStock() << endl;
     return;
}
    cout<<"el stock inicial era: "<<autoParte.getStock()<<endl;;
	int nuevoStock = autoParte.getStock() - cantidad;
	autoParte.setStock(nuevoStock);
    cout<<"el stock actual es: "<<nuevoStock<<endl;
    reg.setCantidadUnidades(cantidad);


    cout << "Importe total: ";
    cin >> importe;
    reg.setImporte(importe);

    reg.setActivo(true);
    if (!archivoAutoparte.modificar(posAutoparte, autoParte)) {
    cout << "Error al actualizar el stock de la autoparte." << endl;
    return;
}


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
        cout << "La entrega está dada de baja." << endl;
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
            cout << "Número autoparte: " << reg.getNumeroAutoparte() << endl;
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
    ArchivoAutopartes archivoautoparte;
    Autoparte autoparte;

    int pos = archivo.buscar(id);

    if (pos < 0) {
        cout << "Error: No se encontró una entrega con ese ID." << endl;
        return;
    }

    Entrega reg = archivo.leer(pos);

    if (!reg.getActivo()) {
        cout << "La entrega ya está dada de baja." << endl;
        return;
    }

    int numeroAutoparte = reg.getNumeroAutoparte();
    int cantidadDevuelta = reg.getCantidadUnidades();

    int posauto= archivoautoparte.buscarPorNumero(numeroAutoparte);
    if(posauto<0){
        cout<< "error: no se encontro la autoparte asociada para devolver stock. "<< endl;
        return;
    }
    autoparte= archivoautoparte.leer(posauto);
    cout<<"el stock inicial es de: "<<autoparte.getStock()<<endl;
    cout<<"la cantidad de entrega de este id fue de: "<< reg.getCantidadUnidades()<<endl;
    int nuevostock= autoparte.getStock()+cantidadDevuelta;
    autoparte.setStock(nuevostock);
    cout<<"stock actualizado es de: "<<nuevostock<<endl;

    reg.setActivo(false);

    if (archivo.guardar(reg, pos)) {
        cout << "Entrega eliminada correctamente (dada de baja)." << endl;
    } else {
        cout << "Error al intentar eliminar la entrega." << endl;
    }

    if (!archivoautoparte.modificar(posauto, autoparte)) {
    cout << "Error al devolver el stock de la autoparte." << endl;
    return;
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
        cout << "Seleccione una opción: ";
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
            cout << "Día: ";
            cin >> dd;
            cout << "Mes: ";
            cin >> md;
            cout << "Año: ";
            cin >> ad;
            desde.setDia(dd); desde.setMes(md); desde.setAnio(ad);

            cout << "Fecha HASTA:" << endl;
            cout << "Día: "; cin >> dh;
            cout << "Mes: "; cin >> mh;
            cout << "Año: "; cin >> ah;
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
            cout << "Opcion inválida." << endl;
        }

    } while (opcion != 0);
}



void EntregasManager::rankingAutopartes() {
    const int MAX_AUTOPARTES = 100;
    int ids[MAX_AUTOPARTES];            // Almacena los ID de autopartes
    int cantidades[MAX_AUTOPARTES];     // Acumula cantidad entregada por ID
    int totalIDs = 0;

    EntregaArchivo archEnt;
    int cantidadReg = archEnt.getCantidadRegistros();  // Metodo correcto del archivo

    for (int i = 0; i < cantidadReg; i++) {
        Entrega reg = archEnt.leer(i);
        if (!reg.getActivo()) continue;

        int id = reg.getNumeroAutoparte();
        int cant = reg.getCantidadUnidades();

        // Buscar si ya esta ese ID en el vector
        int pos = -1;
        for (int j = 0; j < totalIDs; j++) {
            if (ids[j] == id) {
                pos = j;
                break;
            }
        }

        if (pos >= 0) {
            cantidades[pos] += cant;
        } else {
            ids[totalIDs] = id;
            cantidades[totalIDs] = cant;
            totalIDs++;
        }
    }

    // Ordenar por cantidad de mayor a menor (burbuja)
    for (int i = 0; i < totalIDs - 1; i++) {
        for (int j = i + 1; j < totalIDs; j++) {
            if (cantidades[j] > cantidades[i]) {

                int tempCant = cantidades[i];
                cantidades[i] = cantidades[j];
                cantidades[j] = tempCant;

                int tempId = ids[i];
                ids[i] = ids[j];
                ids[j] = tempId;
            }
        }
    }

    // Mostrar resultados
    ArchivoAutopartes archAuto;
    cout << "\n--- RANKING DE AUTOPARTES MAS ENTREGADAS ---\n";
    for (int i = 0; i < totalIDs; i++) {
        int pos = archAuto.buscarPorNumero(ids[i]);
        if (pos >= 0) {
            Autoparte reg = archAuto.leer(pos);
            cout << i + 1 << ". " << reg.getNombre() << " (ID: " << ids[i] << ") - Total entregado: " << cantidades[i] << endl;
        } else {
            cout << i + 1 << ". " << "ID desconocido (" << ids[i] << ") - Total entregado: " << cantidades[i] << endl;
        }
    }
}

