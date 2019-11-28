// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: cuerpo_doraemon.h
// Declaraciones del cuerpo del modelo jerárquico Doraemon
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef CUERPODORAEMON_H_INCLUDED
#define CUERPODORAEMON_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objply.h"

class CuerpoDoraemon : public Malla3D{
private:
   ObjPLY * cuerpo = nullptr;

public:
   CuerpoDoraemon();

   // Dibujar la parte del modelo jerárquico
   void draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion);
};

#endif
