#ifndef ENTREGAMANAGER_H_INCLUDED
#define ENTREGAMANAGER_H_INCLUDED
#include "Entrega.h"
#include <string>

class EntregasManager {
public:
    void cargar();
    void listar();
    void buscarPorId(int id);
    void entregasPorEmpresa(std::string cuit);
    void entregasPorFecha(Fecha desde, Fecha hasta);
    void eliminarPorId(int id);
    void MenuEntrega();
};



#endif // ENTREGAMANAGER_H_INCLUDED
