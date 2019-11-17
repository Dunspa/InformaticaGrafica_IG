// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: material.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material{
public:
   Material();
   Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo);
   void aplicar();

private:
   Tupla4f difuso;
   Tupla4f especular;
   Tupla4f ambiente;
   float brillo;
};

#endif
