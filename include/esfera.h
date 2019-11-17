// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: esfera.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
// Esfera con centro en el origen y radio unidad por defecto
// Es un objeto de revolución que puede girar sobre cualquier eje

class Esfera : public ObjRevolucion{
public:
   Esfera(float r=1.0, int num_instancias=20, int num_vert_perfil=10);

private:
   float radio;
};

#endif
