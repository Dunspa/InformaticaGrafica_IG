// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: brazoizquierdo_doraemon.h
// Declaraciones del brazo izquierdo del modelo jerárquico Doraemon
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef BRAZOIZQUIERDODORAEMON_H_INCLUDED
#define BRAZOIZQUIERDODORAEMON_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objply.h"

class BrazoIzquierdoDoraemon : Malla3D{
private:
   ObjPLY * brazo_izquierdo = nullptr;

public:
   BrazoIzquierdoDoraemon();

   // Dibujar la parte del modelo jerárquico
   void draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion);
};

#endif
