#ifndef AUTOPARTESMANAGER_H_INCLUDED
#define AUTOPARTESMANAGER_H_INCLUDED

class AutopartesManager {
public:
    void cargarAutoparte();
    void listarAutoparteActivas();
    void listarAutoparteInactivas();
    void buscarAutopartePorNumero();
    void buscarAutopartePorNombre();
    void modificarAutoparte();
    void eliminarAutoparte();
}    ;

#endif
