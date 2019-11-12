// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: luzdireccional.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz{
protected:
   float alpha;
   float beta;

public:
   // Inicializar la fuente de luz
   LuzDireccional(const Tupla3f & orientacion, GLenum idLuzOpenGL, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular);

   // Cambiar ángulo
   void variarAnguloAlpha(float incremento);
   void variarAnguloBeta(float incremento);
};

#endif
