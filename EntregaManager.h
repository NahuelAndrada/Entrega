#ifndef ENTREGAMANAGER_H_INCLUDED
#define ENTREGAMANAGER_H_INCLUDED
#include "Entrega.h"
#include "EntregaArchivo.h"
#include <string>

class EntregasManager {
public:
    void cargar(std::string rol);
    void listar();
    void buscarPorId();
    void entregasPorEmpresa();
    void entregasPorFecha();
    void eliminarPorId(std::string rol);
    void reactivarentrega(std::string rol);
    void MenuEntrega(std::string rol);
    void modificarentregaporid(std::string rol);
    void entregasPorNombreEmpresa();
    void entregasPorNombreAutoparte();
    void cantidadEntregasPorNombreEmpresa();
    void cantidadEntregasPorNombreAutoparte();
    void prueba();
};



#endif // ENTREGAMANAGER_H_INCLUDED
