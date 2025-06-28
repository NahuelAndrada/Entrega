#ifndef TIPOAUTOPARTEMANAGER_H_INCLUDED
#define TIPOAUTOPARTEMANAGER_H_INCLUDED

class TipoAutoparteManager {
public:
    void cargar();
    void listar();
    void listarInactivos();
    void buscarPorID();
    void modificar();
    void eliminar();
    void menuTipoAutopartes();
    void InformeCantidadDeTiposAutopartesUtilizadas();
};

#endif
