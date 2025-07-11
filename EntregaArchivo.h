#ifndef ENTREGAARCHIVO_H_INCLUDED
#define ENTREGAARCHIVO_H_INCLUDED

#pragma once
#include <string>
#include "Entrega.h"

class EntregaArchivo{
private:
  std::string _nombreArchivo;
public:
  EntregaArchivo();
  EntregaArchivo(std::string nombreArchivo);

  int buscar(int idPedido);
  int buscar(Fecha fecha);
  int buscar(std::string cuit);
  bool guardar(Entrega registro);
  bool guardar(Entrega registro, int posicion);
  int getCantidadRegistros();


  Entrega leer(int pos);
};

#endif // ENTREGAARCHIVO_H_INCLUDED
