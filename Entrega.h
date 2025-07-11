#ifndef ENTREGA_H_INCLUDED
#define ENTREGA_H_INCLUDED
#include "Fecha.h"
#include <string>

    class Entrega {
    private:

        int _identrega;
        int _NumeroAutoparte;
        char _cuitEmpresa[15];
        Fecha _fechaEntrega;
        int _CantidadUnidades;
        float _importe;
        bool _activo;

    public:
        Entrega();
        Entrega(int IdEntrega, int numeroAutoparte, std::string cuitEmpresa,
                Fecha FechaEntrega, int cantidadUnidades, float importe);

        int getIdEntrega();
        int getNumeroAutoparte();
        std::string getCuitEmpresa();
        Fecha getFechaEntrega();
        int getCantidadUnidades();
        float getImporte();
        bool getActivo();

        void setIdEntrega(int IdEntrega);
        void setNumeroAutoparte(int numeroAutoparte);
        void setCuitEmpresa(std::string cuitEmpresa);
        void setFechaEntrega(Fecha fechaEntrega);
        void setCantidadUnidades(int cantidadUnidades);
        void setImporte(float importe);
        void setActivo(bool activo);

        void mostrar();

};


#endif // ENTREGAMANAGER_H_INCLUDED
