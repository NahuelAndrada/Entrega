#include <iostream>
#include <string>
#include "Usuario.h"

using namespace std;

bool Usuario::login() {
    system("cls");
    string usuario, contrasenia;

    cout << endl;
    cout << "   |                     ##     ##  #    #  ##    # ####     ####                            |   " << endl;
    cout << "   |                     # #   # #  #    #  # #   # #   #   #    #                           |   " << endl;
    cout << "   |                     #  ###  #  #    #  #  #  # #    # #      #                          |   " << endl;
    cout << "   |                     #   #   #  #    #  #   # # #   #   #    #                           |   " << endl;
    cout << "   |                     #       #   ####   #    ## ####     ####                            |   " << endl;
    cout << "   |                                                                                         |   " << endl;
    cout << "   |      ###     #    #  #########   ####    ####    ###    ####  ######### #### #######    |   " << endl;
    cout << "   |    ##   ##   #    #      #      #    #   #   # ##   ##  #   #     #     #    #          |   " << endl;
    cout << "   |    #######   #    #      #     #      #  ####  #######  ####      #     #### #######    |   " << endl;
    cout << "   |    #     #   #    #      #      #    #   #     #     #  #  #      #     #          #    |   " << endl;
    cout << "   |    #     #    ####       #       ####    #     #     #  #   #     #     #### #######    |   " << endl;
    cout << endl;

    cout << "=== INICIO DE SESION ===" << endl;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contrasena: ";
    cin >> contrasenia;

    if (usuario == "admin" && contrasenia == "admin123") {
        _rol = "admin";
        return true;
    }
    else if (usuario == "user" && contrasenia == "user123") {
        _rol = "usuario";
        return true;
    }
    else {
        cout << "Credenciales incorrectas." << endl;
        return false;
    }
}

string Usuario::getRol() {
    return _rol;
}
