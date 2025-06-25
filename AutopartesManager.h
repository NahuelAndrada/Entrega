#ifndef AUTOPARTESMANAGER_H_INCLUDED
#define AUTOPARTESMANAGER_H_INCLUDED

class AutopartesManager {
public:
    void cargarAutoparte();
    void modificarAutoparte();
    void listarAutoparteActivas();
    void listarAutoparteInactivas();
    void buscarAutopartePorNumero();
    void buscarAutopartePorNombre();
    void eliminarAutoparte();
    void menuAutopartes();
}    ;

#endif
