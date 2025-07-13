#include <iostream>
#include "EntregaManager.h"
#include "EntregaArchivo.h"
#include "ArchivoAutopartes.h"
#include "EmpresaManager.h"
#include "ArchivoEmpresa.h"

using namespace std;

void EntregasManager::cargar(std::string rol) {

    if (rol != "admin") {
    cout << "No tiene permisos para realizar esta accion." << endl;
    system("pause");
    return;
    }
    system("cls");

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
       system("pause");
       system("cls");
       return;
}


    reg.setIdEntrega(id);

    cout << "Numero de autoparte: ";
    cin >> numeroAutoparte;

    ArchivoAutopartes archivoAutoparte;
    int posAutoparte = archivoAutoparte.buscarPorNumero(numeroAutoparte);
    Autoparte autoParte = archivoAutoparte.leer(posAutoparte);

    //Control no hay autoparte
    if(posAutoparte < 0) {

            cout << "Error: la autoparte no existe." << endl;
            system("pause");
            system("cls");
            return;

    }

    //Control de autoparte inactiva
    if(!autoParte.getActivo()){
            cout << "Error: la autoparte esta inactiva." << endl;
            system("pause");
            system("cls");
            return;
    }

    reg.setNumeroAutoparte(numeroAutoparte);

    cout << "CUIT de la empresa: ";
    cin >> cuit;
    EmpresaManager archivoEmpresas;
    ArchivoEmpresa archEmpresa;

    Empresa regEmpresa;

    int posEmpresa = archivoEmpresas.buscarEmpresaPorCUIT(cuit);

    if (posEmpresa < 0) {
        cout << "Error: la empresa no está registrada." << endl;
        system("pause");
        system("cls");
        return;
    }

    regEmpresa = archEmpresa.leerEmpresa(posEmpresa);

    if(!regEmpresa.get_Activo()){
        cout << "Error: la empresa no esta activa." << endl;
        system("pause");
        system("cls");
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

    system("cls");

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
    system("pause");
}
void EntregasManager::buscarPorId() {
    system("cls");
    cout << "BUSCAR ENTREGA POR ID" << endl;
    int id;
    cout << "Ingrese ID de entrega: ";
    cin >> id;
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
    system("pause");
}
void EntregasManager::entregasPorEmpresa() {

    system("cls");

    string cuit;
    cout << "Ingrese el CUIT de la empresa: ";
    cin >> ws;
    getline(cin, cuit);

    system("cls");

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
        cout << endl;
    }
    else{
        cout<<"El CUIT: "<<cuit<< " se le facturo por un total de: $ "<<TotalEmpresa<<endl;
        cout<<endl;
    }
}

void EntregasManager::entregasPorFecha() {

    system("cls");

    Fecha desde, hasta;
    int dd, md, ad, dh, mh, ah;

    cout << "Fecha DESDE:" << endl;
    cout << "Dia: "; cin >> dd;
    cout << "Mes: "; cin >> md;
    cout << "Anio: "; cin >> ad;
    desde.setDia(dd); desde.setMes(md); desde.setAnio(ad);

    cout << "Fecha HASTA:" << endl;
    cout << "Dia: "; cin >> dh;
    cout << "Mes: "; cin >> mh;
    cout << "Anio: "; cin >> ah;
    hasta.setDia(dh); hasta.setMes(mh); hasta.setAnio(ah);

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
        cout << endl;
    } else {
        cout << "TOTAL FACTURADO EN EL RANGO: $" << sumaImporte << endl;
        cout << endl;
    }
}

void EntregasManager::eliminarPorId(std::string rol) {
    if (rol != "admin") {
        cout << "No tiene permisos para eliminar entregas." << endl;
        system("pause");
        return;
    }

    system("cls");
    cout << "=== ELIMINAR ENTREGA POR ID ===" << endl;
    int id;
    cout << "Ingrese ID de la entrega: ";
    cin >> id;

    EntregaArchivo archivo;
    ArchivoAutopartes archivoautoparte;
    Autoparte autoparte;

    int pos = archivo.buscar(id);

    if (pos < 0) {
        cout << "Error: No se encontro una entrega con ese ID." << endl;
        system("pause");
        return;
    }

    Entrega reg = archivo.leer(pos);

    if (!reg.getActivo()) {
        cout << "La entrega ya esta dada de baja." << endl;
        system("pause");
        return;
    }

    int numeroAutoparte = reg.getNumeroAutoparte();
    int cantidadDevuelta = reg.getCantidadUnidades();

    int posauto= archivoautoparte.buscarPorNumero(numeroAutoparte);
    if(posauto<0){
        cout<< "error: no se encontro la autoparte asociada para devolver stock. "<< endl;
        system("pause");
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
        system("pause");
    } else {
        cout << "Error al intentar eliminar la entrega." << endl;
        system("pause");
    }

    if (!archivoautoparte.modificar(posauto, autoparte)) {
    cout << "Error al devolver el stock de la autoparte." << endl;
    system("pause");
    return;
    }
}
void EntregasManager::reactivarentrega(std::string rol) {
    if (rol != "admin") {
        cout << "No tiene permisos para reactivar entregas." << endl;
        system("pause");
        return;
    }

    system("cls");
    cout << "=== REACTIVAR ENTREGA ===" << endl;
    int id;
    cout << "Ingrese ID de la entrega: ";
    cin >> id;

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
    system("pause");

}
void EntregasManager::modificarentregaporid(std::string rol){
    if (rol != "admin") {
        cout << "No tiene permisos para modificar entregas." << endl;
        system("pause");
        return;
    }
    system("cls");

    cout << "=== MODIFICAR ENTREGA POR ID ===" << endl;
    int id;
    cout << "Ingrese ID de la entrega: ";
    cin >> id;

    EntregaArchivo Archientrega;
    Entrega RegEntrega;
    ArchivoAutopartes archAutoparte;
    EmpresaManager Empresa;
        cout << "#######################################" << endl;
        cout << "         MODIFICAR EMPRESAS     " <<endl;
        cout << "#######################################" << endl;
        cout <<endl;


    int pos = Archientrega.buscar(id);

    if (pos == -1) {
        cout << "No se encontro ninguna entrega con ese ID." << std::endl;
        return;
    }
    else{
        RegEntrega=Archientrega.leer(pos);
        cout << endl;
        cout << ">> Entrega encontrada ID (" <<RegEntrega.getIdEntrega() << "): " <<endl;
        cout << "Que dato te gustaria modificar?" << std::endl;
        cout << endl;
        cout << "1) NumeroAutoparte: " <<RegEntrega.getNumeroAutoparte()<< endl;
        cout << "2) Cuit Cliente: " <<RegEntrega.getCuitEmpresa()<< endl;
        Fecha f = RegEntrega.getFechaEntrega();
        cout << "3) Fecha: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
        cout << "4) Cantidad Unidades: " <<RegEntrega.getCantidadUnidades()<< endl;
        cout << "5) Importe: "<<RegEntrega.getImporte()<< endl;
        cout << endl;

        int opcion= -1;
        while(opcion != 0){

            cout << endl;
            cout << "Ingrese la opcion deseada (0 para cancelar): ";
            cin >> opcion;


        switch(opcion){
            case 1:{
                int nuevoNumero;
                cout << "Ingrese el nuevo numero de autoparte: ";
                cin >> nuevoNumero;


                int PosAutoParte = archAutoparte.buscarPorNumero(nuevoNumero);

                        if (PosAutoParte == -1) {
                            cout << ">> No existe una autoparte con ese numero." << endl;
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
                    cout << ">> Stock de autoparte a modificar: " << StockAutNuev + unidadesEntregadas << "." << endl;
                    cout << ">> Cantidad de esta entrega: " << unidadesEntregadas << "." << endl;

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
                            cout << endl;
                        } else {
                            cout << ">> Error al guardar la entrega modificada." << endl;
                            cout << endl;
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
                            cout << endl;
                            break;
                        }


                        RegEntrega.setCantidadUnidades(nuevaCantidad);

                        if (Archientrega.guardar(RegEntrega, pos)) {
                            cout << ">> Cantidad de unidades actualizada correctamente." << endl;
                            cout << endl;
                        } else {
                            cout << ">> Error al guardar la entrega modificada." << endl;
                            cout << endl;
                        }

                        break;
                    }
                    case 5: {
                        float nuevoImporte;
                        cout << "Ingrese el nuevo importe de la entrega: $";
                        cin >> nuevoImporte;

                        if (nuevoImporte <= 0) {
                            cout << ">> El importe debe ser mayor a cero." << endl;
                            cout << endl;
                            break;
                        }

                        RegEntrega.setImporte(nuevoImporte);

                        if (Archientrega.guardar(RegEntrega, pos)) {
                            cout << ">> Importe actualizado correctamente." << endl;
                            cout << endl;
                        } else {
                            cout << ">> Error al guardar la entrega modificada." << endl;
                            cout << endl;
                        }

                        break;
                    }
                    default:
                        system("cls");
                        break;

            }
            char continuar;
            cin.ignore();
            cout << "Desea modificar otro campo? (s/n): ";
            cin >> continuar;
            if (continuar != 's' && continuar != 'S') {
                break;
            }
        } //Cierre while
    }
    system("pause");
}
void EntregasManager::MenuEntrega(std::string rol){
    EntregasManager manager;
    int opcion;

    do {
        system("cls");
        cout << "=== MENU DE GESTION DE ENTREGAS ===" << endl;
        cout << "1. Cargar nueva entrega" << endl;
        cout << "2. Listar entregas activas" << endl;
        cout << "3. Buscar entrega por ID" << endl;
        cout << "4. Eliminar entrega por ID" << endl;
        cout << "5. Reactivar entrega por ID" << endl;
        cout << "6. Modificar entrega por ID" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            manager.cargar(rol);
            break;
        case 2:
            manager.listar();
            break;
        case 3: {
            //int id;
            //cout << "Ingrese ID de la entrega: ";
            //cin >> id;
            manager.buscarPorId();
            break;
        }
        case 4: {
            //int id;
            //cout << "Ingrese ID de entrega a eliminar: ";
            //cin >> id;
            manager.eliminarPorId(rol);
            break;
        }
        case 5: {
            //int id;
            //cout << "Ingrese ID de entrega a reactivar: ";
            //cin >> id;
            manager.reactivarentrega(rol);
            break;
        }
        case 6:{
            //int id;
            //cout << "Ingrese ID de entrega a Modificar: ";
            //cin >> id;
            manager.modificarentregaporid(rol);
            break;
        }
        case 0:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
        }

    } while (opcion != 0);
}

void EntregasManager::entregasPorNombreEmpresa(){
    system("cls");
    ArchivoEmpresa archEmp;
    EntregaArchivo archEnt;

    Entrega regEnt;
    Empresa regEmp;

    string nombre,cuitEncontrado;

    cout<<"Ingrese el nommbre de la empresa a buscar:"<<endl;
    cin>>ws;
    getline(cin,nombre);
    int cantidad=archEmp.get_CantidadRegistros();
    for(int i=0;i<cantidad;i++){
        regEmp=archEmp.leerEmpresa(i);
        if(regEmp.get_Nombre()==nombre&&regEmp.get_Activo()){
            cuitEncontrado=regEmp.get_CUIT();
            break;
        }
    }
    if(cuitEncontrado==""){
        cout << "No se encontro ninguna empresa activa con ese nombre." << endl;
        return;
    }
    cantidad=archEnt.getCantidadRegistros();
    for(int i=0;i<cantidad;i++){
        regEnt=archEnt.leer(i);
        if(regEnt.getCuitEmpresa()==cuitEncontrado){
         regEnt.mostrar();
        }
    }
}

void EntregasManager::entregasPorNombreAutoparte(){

    system("cls");

    ArchivoAutopartes archAut;
    EntregaArchivo archEnt;

    Autoparte regAut;
    Entrega regEnt;

    string nombre;
    int IDEncontrado=-1;
    cout<<"Ingrese el nombre de la autoparte a buscar:"<<endl;
    cin>>ws;
    getline(cin,nombre);

    int cantidad=archAut.contar();
    for(int i=0;i<cantidad;i++){
        regAut=archAut.leer(i);
        if(regAut.getNombre()==nombre&&regAut.getActivo()){
            IDEncontrado=regAut.getNumero();
            break;
        }
    }
    if(IDEncontrado==-1){
        cout << "No se encontro ninguna autoparte activa con ese nombre." << endl;
        return;
    }
    cantidad=archEnt.getCantidadRegistros();
    bool encontro=false;
    for(int i=0;i<cantidad;i++){
        regEnt=archEnt.leer(i);
        if(regEnt.getNumeroAutoparte()==IDEncontrado){
            regEnt.mostrar();
            encontro=true;
        }
    }
    if(!encontro){
        cout << "No hay entregas registradas para esa autoparte." << endl;
    }
}

void EntregasManager::cantidadEntregasPorNombreEmpresa(){
    system("cls");
    ArchivoEmpresa archEmp;
    EntregaArchivo archEnt;

    Entrega regEnt;
    Empresa regEmp;

    string nombre,cuitEncontrado;

    cout<<"Ingrese el nommbre de la empresa a buscar:"<<endl;
    cin>>ws;
    getline(cin,nombre);
    int cantidad=archEmp.get_CantidadRegistros();
    for(int i=0;i<cantidad;i++){
        regEmp=archEmp.leerEmpresa(i);
        if(regEmp.get_Nombre()==nombre&&regEmp.get_Activo()){
            cuitEncontrado=regEmp.get_CUIT();
            break;
        }
    }
    if(cuitEncontrado==""){
        cout << "No se encontro ninguna empresa activa con ese nombre." << endl;
        return;
    }
    int contador=0;
    cantidad=archEnt.getCantidadRegistros();
    for(int i=0;i<cantidad;i++){
        regEnt=archEnt.leer(i);
        if(regEnt.getCuitEmpresa()==cuitEncontrado){
            contador++;
        }
    }
    cout<<"La cantidad de entregas realizadas por esa empresa es: "<<contador<<endl;
}

void EntregasManager::cantidadEntregasPorNombreAutoparte(){
    system("cls");

    ArchivoAutopartes archAut;
    EntregaArchivo archEnt;

    Autoparte regAut;
    Entrega regEnt;

    string nombre;
    int IDEncontrado=-1;
    cout<<"Ingrese el nombre de la autoparte a buscar:"<<endl;
    cin>>ws;
    getline(cin,nombre);

    int cantidad=archAut.contar();
    for(int i=0;i<cantidad;i++){
        regAut=archAut.leer(i);
        if(regAut.getNombre()==nombre&&regAut.getActivo()){
            IDEncontrado=regAut.getNumero();
            break;
        }
    }
    if(IDEncontrado==-1){
        cout << "No se encontro ninguna autoparte activa con ese nombre." << endl;
        return;
    }
    cantidad=archEnt.getCantidadRegistros();
    bool encontro=false;
    int contador=0;
    for(int i=0;i<cantidad;i++){
        regEnt=archEnt.leer(i);
        if(regEnt.getNumeroAutoparte()==IDEncontrado){
            contador++;
            encontro=true;
        }
    }
    if(!encontro){
        cout << "No hay entregas registradas para esa autoparte." << endl;
    }
    cout<<"La cantidad de entregas realizadas con esa autoparte es: "<<contador<<endl;
}
