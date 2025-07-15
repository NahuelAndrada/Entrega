#pragma once
#include <string>

class EmpresaManager{

    private:

    public:
        void menuEmpresas(std::string rol);
        void imprimirMenu(bool limpiar);

        void cargarEmpresa(std::string rol);
        void mostrarCantidadEmpresas();

        void listarEmpresasActivas();
        void listarEmpresasInactivas();

        int  buscarEmpresaPorCUIT(std::string in_CUIT); //devuelve la posicion
        void buscarPorParametroEspecifico();

        void modificarEmpresaPorCUIT(std::string rol);
        void dardebajarEmpresa(std::string rol);
        //void dardebajarEmpresa(std::string in_CUIT);
        void dardealtaEmpresa(std::string rol);

        void informeEmpresasConMasEntregas();
        void informeEmpresasConMasImporte();
        void informedeEntregasMensualesPorAnio();
        void informarEntregasPorNombreEmpresa();

        void empresasSinEntregas();
        void empresasQueRecibieronEntregasEnFecha();
};

