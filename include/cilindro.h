// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: cilindro.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
// Cilindro con centro en el origen y altura unidad por defecto
// Es un objeto de revolución que puede girar sobre cualquier eje

class Cilindro : public ObjRevolucion{
public:
   Cilindro(int num_instancias=20, float h=1, float r=1, char eje_rotacion='Y', bool tapa_sup=true, bool tapa_inf=true);

private:
   float altura;
   float radio;
};

#endif
