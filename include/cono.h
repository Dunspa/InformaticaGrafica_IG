// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: cono.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
// Cono con centro en el origen y altura unidad por defecto
// Es un objeto de revolución que puede girar sobre cualquier eje

class Cono : public ObjRevolucion{
public:
   Cono(int num_instancias=20, float h=1.0, float r=1.0, char eje_rotacion='Y', bool tapa_inf=true, bool tapa_sup=true);

private:
   float altura;
   float radio;
};

#endif
