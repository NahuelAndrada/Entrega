#ifndef TIPOAUTOPARTEMANAGER_H_INCLUDED
#define TIPOAUTOPARTEMANAGER_H_INCLUDED
#include <string>

class TipoAutoparteManager {
public:
    void cargar(std::string rol);
    void listar();
    void listarInactivos();
    void buscarPorID();
    void modificar(std::string rol);
    void eliminar(std::string rol);
    void menuTipoAutopartes(std::string rol);
    void InformeCantidadDeTiposAutopartesUtilizadas();
};

#endif
