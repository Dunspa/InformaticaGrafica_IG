// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: luz.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz{
protected:
   Tupla4f posicion;
   GLenum id;
   Tupla4f colorAmbiente;
   Tupla4f colorDifuso;
   Tupla4f colorEspecular;
   bool activada;

public:
   void activar();
};

#endif
