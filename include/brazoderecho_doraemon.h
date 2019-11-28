// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: brazoderecho_doraemon.h
// Declaraciones del brazo derecho del modelo jerárquico Doraemon
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef BRAZODERECHODORAEMON_H_INCLUDED
#define BRAZODERECHODORAEMON_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objply.h"

class BrazoDerechoDoraemon : Malla3D{
private:
   ObjPLY * brazo_derecho = nullptr;

public:
   BrazoDerechoDoraemon();

   // Dibujar la parte del modelo jerárquico
   void draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion);
};

#endif
