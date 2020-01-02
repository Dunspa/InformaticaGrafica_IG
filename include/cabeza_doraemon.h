// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: cabeza_doraemon.h
// Declaraciones de la cabeza del modelo jerárquico Doraemon
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef CABEZADORAEMON_H_INCLUDED
#define CABEZADORAEMON_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objply.h"

class CabezaDoraemon : public Malla3D{
private:
   ObjPLY * cabeza = nullptr;

public:
   CabezaDoraemon();

   // Dibujar la parte del modelo jerárquico
   void draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion);
   void setColorSeleccion(color col) override;
};

#endif
