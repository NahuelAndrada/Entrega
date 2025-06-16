#ifndef TIPOAUTOPARTEMANAGER_H
#define TIPOAUTOPARTEMANAGER_H

class TipoAutoparteManager {
public:
    void Menu();
    void Cargar();
    void Eliminar(int numero);
    void Modificar(int numero);
    int BuscarPorNumero(int numero);
    void Listar();
};

#endif
