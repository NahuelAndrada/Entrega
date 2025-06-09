#ifndef AUTOPARTESMANAGER_H
#define AUTOPARTESMANAGER_H

class AutopartesManager {
public:
    void Menu();
    void CargarAutoparteNueva();
    void DarDeBajaAutoparte(int numero);
    void DarDeAltaAutoparte(int numero);
    void ModificarAutoparte(int numero);
    int BuscarAutopartePorNumero(int numero);
    int BuscarAutopartePorNombre(const char* nombre);
    void ListarAutopartes();
    void ListarAutopartesActivas();
    void ListarAutopartesInactivas();
    void AumentarStockAutoparte();
    void Existe();
};

#endif
