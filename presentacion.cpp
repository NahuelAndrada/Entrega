#include <iostream>
#include "TipoAutoparteManager.h"
#include "EmpresaManager.h"
#include "AutopartesManager.h"
#include "EntregaManager.h"
#include "TipoAutoparte.h"

using namespace std;

void presentacion(){


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

    cout << "========= MENU PRINCIPAL =========" << endl;
    cout << endl;
    cout << "1. Gestion de Empresas" << endl;
    cout << "2. Gestion de Autopartes" << endl;
    cout << "3. Gestion de Entregas" << endl;
    cout << "4. Gestion de Tipo autopartes" << endl;
    cout << "5. Consulta de Informes" << endl;
    cout << "6. Ver Creditos" << endl;
    cout << "7. Hacer Backup" << endl;
    cout << "0. Salir" << endl;
    cout << endl;
}
