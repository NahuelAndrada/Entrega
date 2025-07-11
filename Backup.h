#ifndef BACKUP_H
#define BACKUP_H

#include <string>

class Backup {
public:
    bool realizarBackup(const std::string& origen, const std::string& destino);
    void hacerBackupIndividual();
    void hacerBackupCompleto();
    void mostrarSubmenuBackup();
};

#endif // BACKUP_H

