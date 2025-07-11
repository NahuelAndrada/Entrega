#ifndef AUTOPARTESMANAGER_H_INCLUDED
#define AUTOPARTESMANAGER_H_INCLUDED
using namespace std;

class AutopartesManager {
public:
    void cargarAutoparte(string rol);
    void modificarAutoparte(string rol);
    void listarAutoparteActivas();
    void listarAutoparteInactivas();
    void buscarAutopartePorNumero();
    void buscarAutopartePorNombre();
    void eliminarAutoparte(string rol);
    void menuAutopartes(string rol);
    void rankingAutopartes();
    void informeStockBajo();
    void autopartesActivasSinEntrega();
    void listarAutopartesConUnidadesMayoresA();
};

#endif
