#include <iostream>
#include "EntregaManager.h"
#include "EntregaArchivo.h"
#include "ArchivoAutopartes.h"
#include "EmpresaManager.h"
#include "ArchivoEmpresa.h"

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
void EntregasManager::reactivarentrega(int id) {
    EntregaArchivo archivo;
    ArchivoAutopartes archivoautoparte;
    Autoparte autoparte;
    Entrega reg;

    int pos = archivo.buscar(id);

    if (pos < 0) {
        cout << "Error: No se encontró una entrega con ese ID." << endl;
        return;
    }

     reg = archivo.leer(pos);

    if (reg.getActivo()) {
        cout << "La entrega no esta dada de baja." << endl;
        return;
    }

    int numeroAutoparte = reg.getNumeroAutoparte();
    int cantidadDevuelta = reg.getCantidadUnidades();

    int posauto= archivoautoparte.buscarPorNumero(numeroAutoparte);
    if(posauto<0){
        cout<< "error: no se encontro la autoparte asociada"<< endl;
        return;
    }
    autoparte= archivoautoparte.leer(posauto);
    cout<<"el stock inicial es de: "<<autoparte.getStock()<<endl;
    cout<<"la cantidad de entrega de este id fue de: "<< reg.getCantidadUnidades()<<endl;
    int nuevostock= autoparte.getStock()-cantidadDevuelta;
        if(nuevostock<0){
            cout<<"no se puede reactivar la entrega porque no hay stock necesario"<<endl;
            return;
    }
    autoparte.setStock(nuevostock);
    cout<<"stock actualizado es de: "<<nuevostock<<endl;

    reg.setActivo(true);

    if (archivo.guardar(reg, pos)) {
        cout << "Entrega reactivada correctamente (dada de alta)." << endl;
    } else {
        cout << "Error al intentar reactivar la entrega." << endl;
    }

    if (!archivoautoparte.modificar(posauto, autoparte)) {
    cout << "Error al devolver el stock de la autoparte." << endl;
    return;
}

}
void EntregasManager::modificareentregaporid(){

    system("cls");
    EntregaArchivo Archientrega;
    Entrega RegEntrega;
    ArchivoAutopartes archAutoparte;
    EmpresaManager Empresa;
        cout << "#######################################" << endl;
        cout << "         MODIFICAR EMPRESAS     " <<endl;
        cout << "#######################################" << endl;
        cout <<endl;

        int id;
        cout << "Ingrese el ID de la entrega: ";
        cin >> id;

    int pos = Archientrega.buscar(id);

    if (pos == -1) {
        cout << "No se encontró ninguna entrega con ese ID." << std::endl;
        return;
    }
    else{
        RegEntrega=Archientrega.leer(pos);
        cout << endl;
        cout << ">> Entrega encontrada ID (" <<RegEntrega.getIdEntrega() << "): " <<endl;
        cout << "Que dato te gustaria modificar?" << std::endl;
        cout << endl;
        cout << "1) NumeroAutoparte:     " <<RegEntrega.getNumeroAutoparte()<< endl;
        cout << "2) Cuit Cliente:      " <<RegEntrega.getCuitEmpresa()<< endl;
        Fecha f = RegEntrega.getFechaEntrega();
        cout << "3) Fecha:      " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
        cout << "4) Cantidad Unidades:    " <<RegEntrega.getCantidadUnidades()<< endl;
        cout << "5) Importe:     " <<RegEntrega.getImporte()<< endl;
        cout << endl;

        int opcion= -1;
        while(opcion != 0){

            cout << "\nIngrese la opción deseada (0 para cancelar): ";
            cin >> opcion;


        switch(opcion){
            case 1:{
                int nuevoNumero;
                cout << "Ingrese el nuevo número de autoparte: ";
                cin >> nuevoNumero;


                int PosAutoParte = archAutoparte.buscarPorNumero(nuevoNumero);

                        if (PosAutoParte == -1) {
                            cout << ">> No existe una autoparte con ese número." << endl;
                            break;
                        }

                int numeroAnterior = RegEntrega.getNumeroAutoparte();
                int unidadesEntregadas = RegEntrega.getCantidadUnidades();

                    if (numeroAnterior == nuevoNumero) {
                        cout << ">> El número ingresado es el mismo que el actual." << endl;
                        break;
                        }

                int posAnterior = archAutoparte.buscarPorNumero(numeroAnterior);
                Autoparte autoParteAnterior = archAutoparte.leer(posAnterior);
                Autoparte autoParteNueva = archAutoparte.leer(PosAutoParte);
                int StockAutAnt= autoParteAnterior.getStock()+unidadesEntregadas;
                int StockAutNuev= autoParteNueva.getStock()-unidadesEntregadas;


                autoParteAnterior.setStock(StockAutAnt);
                autoParteNueva.setStock(StockAutNuev);


                if (StockAutNuev < 0) {
                    cout << ">> No hay suficiente stock en la nueva autoparte para realizar el cambio." << endl;
                    cout << ">>Stock de autoparte a modificar: " <<autoParteNueva.getStock()<< endl;
                    cout << ">>cantidad de esta entrega: " <<unidadesEntregadas<< endl;

                        break;
                        }


                    if (!archAutoparte.modificar(posAnterior,autoParteAnterior) || !archAutoparte.modificar(PosAutoParte,autoParteNueva)) {
                    cout << ">> ERROR al actualizar el stock de autopartes." << endl;
                    break;
                        }


                    RegEntrega.setNumeroAutoparte(nuevoNumero);
                    if (Archientrega.guardar(RegEntrega, pos)) {
                    cout << ">> Entrega actualizada correctamente en el archivo." << endl;
                    }
                    else {
                    cout << ">> Error al guardar la entrega modificada." << endl;
                    }
                    break;
            }
                    case 2: {
                        char nuevoCuit[20];
                        cout << "Ingrese el nuevo CUIT de la empresa: ";
                        cin.ignore();
                        cin.getline(nuevoCuit, 20);

                        int posEmpresa = Empresa.buscarEmpresaPorCUIT(nuevoCuit);
                        if (posEmpresa == -1) {
                            cout << ">> No existe una empresa con ese CUIT." << endl;
                            break;
                        }

                        RegEntrega.setCuitEmpresa(nuevoCuit);

                        if (Archientrega.guardar(RegEntrega, pos)) {
                            cout << ">> CUIT de empresa actualizado correctamente en la entrega." << endl;
                        } else {
                            cout << ">> Error al guardar la entrega modificada." << endl;
                        }

                        break;
                    }
                    case 3: {
                        int dia, mes, anio;

                        cout << "Ingrese el nuevo día de entrega: ";
                        cin >> dia;

                        cout << "Ingrese el nuevo mes de entrega: ";
                        cin >> mes;

                        cout << "Ingrese el nuevo año de entrega: ";
                        cin >> anio;

                        Fecha nuevaFecha;
                        if (!nuevaFecha.Validarfecha(dia, mes, anio)) {
                        cout << ">> Fecha inválida. Asegurate de ingresar un día, mes y anio correctos." << endl;
                        break;
                        }


                        nuevaFecha.setDia(dia);
                        nuevaFecha.setMes(mes);
                        nuevaFecha.setAnio(anio);

                        RegEntrega.setFechaEntrega(nuevaFecha);

                        if (Archientrega.guardar(RegEntrega, pos)) {
                            cout << ">> Fecha de entrega actualizada correctamente." << endl;
                        } else {
                            cout << ">> Error al guardar la entrega modificada." << endl;
                        }

                        break;
                    }

                    case 4: {
                        int nuevaCantidad;
                        cout << "Ingrese la nueva cantidad de unidades entregadas: ";
                        cin >> nuevaCantidad;

                        if (nuevaCantidad <= 0) {
                            cout << ">> La cantidad debe ser mayor que cero." << endl;
                            break;
                        }
                        int NumeroAutoparte=RegEntrega.getNumeroAutoparte();
                        int cantidadAnterior = RegEntrega.getCantidadUnidades();
                        int diferencia = nuevaCantidad - cantidadAnterior;
                        int posAutoparte = archAutoparte.buscarPorNumero(NumeroAutoparte);

                        Autoparte Regautoparte = archAutoparte.leer(posAutoparte);
                        int stockActual = Regautoparte.getStock();

                        if (diferencia > 0 && stockActual < diferencia) {
                            cout << ">> No hay suficiente stock para aumentar la cantidad entregada." << endl;
                            cout << ">> Stock actual: " << stockActual << " | Necesario: " << diferencia << endl;
                            break;
                        }


                        Regautoparte.setStock(stockActual - diferencia);
                        if (!archAutoparte.modificar(posAutoparte, Regautoparte)) {
                            cout << ">> Error al actualizar el stock de la autoparte." << endl;
                            break;
                        }


                        RegEntrega.setCantidadUnidades(nuevaCantidad);

                        if (Archientrega.guardar(RegEntrega, pos)) {
                            cout << ">> Cantidad de unidades actualizada correctamente." << endl;
                        } else {
                            cout << ">> Error al guardar la entrega modificada." << endl;
                        }

                        break;
                    }
                    case 5: {
                        float nuevoImporte;
                        cout << "Ingrese el nuevo importe de la entrega: $";
                        cin >> nuevoImporte;

                        if (nuevoImporte <= 0) {
                            cout << ">> El importe debe ser mayor a cero." << endl;
                            break;
                        }

                        RegEntrega.setImporte(nuevoImporte);

                        if (Archientrega.guardar(RegEntrega, pos)) {
                            cout << ">> Importe actualizado correctamente." << endl;
                        } else {
                            cout << ">> Error al guardar la entrega modificada." << endl;
                        }

                        break;
                    }
            }
        }
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
        cout << "7. reactivar entrega por ID" << endl;
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
        case 7: {
            int id;
            cout << "Ingrese ID de entrega a reactivar: ";
            cin >> id;
            manager.reactivarentrega(id);
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

