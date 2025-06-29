#include "EntregaArchivo.h"

EntregaArchivo::EntregaArchivo(){
  _nombreArchivo = "Entregas.dat";
}
EntregaArchivo::EntregaArchivo(std::string nombreArchivo){
  _nombreArchivo = nombreArchivo;
}
bool EntregaArchivo::guardar(Entrega registro){
  FILE *pFile;
  bool result;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if(pFile == nullptr){
    return false;
  }

  result = fwrite(&registro, sizeof(Entrega), 1, pFile);

  fclose(pFile);

  return result;
}
bool EntregaArchivo::guardar(Entrega registro, int posicion){

   FILE *pFile;
   bool result;

   pFile = fopen(_nombreArchivo.c_str(), "rb+");

   if (pFile == nullptr){
      return false;
   }

   fseek(pFile, posicion * sizeof(Entrega) , SEEK_SET);
   result = fwrite(&registro, sizeof(Entrega), 1, pFile);

   fclose(pFile);

   return result;

}
int EntregaArchivo::getCantidadRegistros(){
  int total, cantidad;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return 0;
  }
    // file  byte  desde
  fseek(pFile, 0, SEEK_END);

  total = ftell(pFile);

  cantidad = total / sizeof(Entrega);

  fclose(pFile);

  return cantidad;
}
Entrega EntregaArchivo::leer(int pos){
  FILE *pFile;
  Entrega reg;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return reg;
  }

  fseek(pFile, sizeof(Entrega) * pos, SEEK_SET);

  fread(&reg, sizeof(Entrega), 1, pFile);

  fclose(pFile);

  return reg;
}
int EntregaArchivo::buscar(int idEntrega){
   FILE *pFile;
   Entrega reg;
   int posicion = 0;

   pFile = fopen(_nombreArchivo.c_str(), "rb");

   if (pFile == nullptr){
      return -2;
   }

   while(fread(&reg, sizeof(Entrega), 1, pFile) == 1){
      if (reg.getIdEntrega() == idEntrega){
         fclose(pFile);
         return posicion;
      }
      posicion++;
   }

   fclose(pFile);
   return -1;
}
