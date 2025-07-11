#ifndef USUARIO_H
#define USUARIO_H
#pragma once

#include <string>

class Usuario {
private:
    std::string _rol;

public:
    bool login();
    std::string getRol();
};

#endif

