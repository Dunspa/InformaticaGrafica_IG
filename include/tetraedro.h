// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: tetraedro.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef TETRAEDRO_H_INCLUDED
#define TETRAEDRO_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Tetraedro con centro en el origen

class Tetraedro : public Malla3D{
public:
   Tetraedro(float lado = 1);

private:
   // Características de un tetraedro
   int altura;
   Tupla3f baricentro;

   // Calcula la distancia del punto medio de una arista al baricentro
   float distanciaBaricentro(float lado);
   // Calcula la altura de la cara
   float alturaCara(float lado);
   // Calcula la altura del tetraedro
   float alturaTetraedro(float lado);
};

#endif
