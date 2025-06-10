#pragma once
#include <string>

class EmpresaManager{

    private:

    public:
        void menuEmpresas();
        void imprimirMenu(bool limpiar);

        void cargarEmpresa();
        void mostrarCantidadEmpresas();

        void listarEmpresasActivas();
        void listarEmpresasInactivas();

        int  buscarEmpresaPorCUIT(std::string in_CUIT); //devuelve la posicion
        void buscarPorParametroEspecifico();

        void modificarEmpresaPorCUIT();
        void dardebajarEmpresa();
        void dardebajarEmpresa(std::string in_CUIT);
        void dardealtaEmpresa(std::string in_CUIT);
};
