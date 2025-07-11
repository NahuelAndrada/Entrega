#pragma once
#include <string> //Para usar el std::string

class Empresa{

    private:
        char _CUIT[15];
        char _Nombre[50];
        char _Responsable[50];
        char _Telefono[20];
        char _Email[50];
        char _Direccion[100];
        bool _Activo;

    public:

        //Constructores
        Empresa();
        Empresa(
                std::string CUIT,
                std::string Nombre,
                std::string Responsable,
                std::string Telefono,
                std::string Email,
                std::string Direccion,
                bool Activo
        );

        //Getters
        std::string get_CUIT();
        std::string get_Nombre();
        std::string get_Responsable();
        std::string get_Telefono();
        std::string get_Email();
        std::string get_Direccion();
        bool get_Activo();

        //Setters
        void set_CUIT(std::string CUIT);
        void set_Nombre(std::string Nombre);
        void set_Responsable(std::string Responsable);
        void set_Telefono(std::string Telefono);
        void set_Email(std::string Email);
        void set_Direccion(std::string Direccion);
        void set_Activo(bool Activo);

        //Otros
        std::string toCSV();
};
