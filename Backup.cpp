#include <iostream>
#include <cstdio>
#include <cstring>
#include "Backup.h"

using namespace std;

bool Backup::realizarBackup(const string& origen, const string& destino) {
    FILE* archivoOriginal = fopen(origen.c_str(), "rb");
    if (archivoOriginal == nullptr) {
        cout << "No se pudo abrir el archivo de origen: " << origen << endl;
        return false;
    }

    FILE* archivoCopia = fopen(destino.c_str(), "wb");
    if (archivoCopia == nullptr) {
        cout << "No se pudo crear el archivo de destino: " << destino << endl;
        fclose(archivoOriginal);
        return false;
    }

    char byte;
    while (fread(&byte, 1, 1, archivoOriginal) == 1) {
        fwrite(&byte, 1, 1, archivoCopia);
    }

    fclose(archivoOriginal);
    fclose(archivoCopia);

    cout << "Backup creado: " << destino << endl;
    return true;
}

void Backup::hacerBackupIndividual() {
    system("cls");
    int opcion;
    cout << "--- BACKUP INDIVIDUAL ---" << endl;
    cout << "1. Empresas" << endl;
    cout << "2. Autopartes" << endl;
    cout << "3. Entregas" << endl;
    cout << "4. TipoAutopartes" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        realizarBackup("empresas.dat", "backup_empresas.bkp");
    }
    else if (opcion == 2) {
        realizarBackup("autopartes.dat", "backup_autopartes.bkp");
    }
    else if (opcion == 3) {
        realizarBackup("entregas.dat", "backup_entregas.bkp");
    }
    else if (opcion == 4) {
        realizarBackup("tipo_autopartes.dat", "backup_tipo_autopartes.bkp");
    }
    else {
        cout << "Opcion invalida." << endl;
    }
    system("pause");
}

void Backup::hacerBackupCompleto() {
    system("cls");
    realizarBackup("empresas.dat", "backup_empresas.bkp");
    realizarBackup("autopartes.dat", "backup_autopartes.bkp");
    realizarBackup("entregas.dat", "backup_entregas.bkp");
    realizarBackup("tipo_autopartes.dat", "backup_tipo_autopartes.bkp");
    cout << "Backup completo realizado." << endl;
    system("pause");
}

void Backup::mostrarSubmenuBackup() {
    system("cls");
    int opcion;
    cout << "--- MENU DE BACKUP ---" << endl;
    cout << "1. Backup Individual" << endl;
    cout << "2. Backup Completo" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        hacerBackupIndividual();
    }
    else if (opcion == 2) {
        hacerBackupCompleto();
    }
    else {
        cout << "Opcion invalida." << endl;
        system("pause");
    }
}
