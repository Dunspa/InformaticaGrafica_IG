// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: lienzo.h
// Declaraciones de clase Lienzo, un plano sobre el que poner texturas planas
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef LIENZO_H_INCLUDED
#define LIENZO_H_INCLUDED

#include "aux.h"
#include "malla.h"

class Lienzo : public Malla3D{
private:
   float lado;

public:
   Lienzo(float l = 1);
};

#endif
