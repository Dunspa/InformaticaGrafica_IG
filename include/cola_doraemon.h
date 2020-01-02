// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: cola_doraemon.h
// Declaraciones de la cola del modelo jerárquico Doraemon
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef COLADORAEMON_H_INCLUDED
#define COLADORAEMON_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objply.h"

class ColaDoraemon : Malla3D{
private:
   ObjPLY * cola = nullptr;

public:
   ColaDoraemon();

   // Dibujar la parte del modelo jerárquico
   void draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion);
   void setColorSeleccion(color col) override;
};

#endif
