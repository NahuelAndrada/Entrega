#ifndef AUTOPARTESMANAGER_H_INCLUDED
#define AUTOPARTESMANAGER_H_INCLUDED

class AutopartesManager {
public:
    void cargar();
    void listar();
    void buscarPorNumero();
    void buscarPorNombre();
    void modificar();
    void eliminar();
    void modificarStock();
};

#endif
