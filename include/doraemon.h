// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: doraemon.h
// Declaraciones del modelo jerárquico Doraemon
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef DORAEMON_H_INCLUDED
#define DORAEMON_H_INCLUDED

#include "aux.h"
#include "cabeza_doraemon.h"
#include "cuerpo_doraemon.h"
#include "brazoizquierdo_doraemon.h"
#include "brazoderecho_doraemon.h"
#include "cola_doraemon.h"

typedef enum {
   BRAZODERECHO, BRAZOIZQUIERDO, CABEZA, COLA
} parteDoraemon;

class Doraemon{
private:
   // Partes del modelo jerárquico
   CabezaDoraemon * cabeza;
   CuerpoDoraemon * cuerpo;
   BrazoIzquierdoDoraemon * brazo_izquierdo;
   BrazoDerechoDoraemon * brazo_derecho;
   ColaDoraemon * cola;

   // Grados de libertad
   float giroBrazoDcho;
   float incrementoBrazoDcho;

   float giroBrazoIzdo;
   float incrementoBrazoIzdo;

   float giroCabeza;
   float incrementoCabeza;

   float longitudCola;
   float incrementoCola;

public:
   Doraemon();

   // Modificar valores del modelo jerárquico (cuatro grados de libertad)
   void modificaGiroBrazoDcho(float valor);
   void modificaGiroBrazoIzdo(float valor);
   void modificaGiroCabeza(float valor);
   void modificaLongitudCola(float valor);

   // Construir el modelo jerárquico
   void draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion);

   void setColorSeleccion(color col);
   void setColorSeleccionado();
   void calcularCentro(const GLfloat * v_matrix);
   Tupla3f getCentro();

   // Animar el modelo jerárquico
   void animar();
   // Animar el modelo jerárquico con mayor o menor velocidad
   void aumentarVelocidad();
   void disminuirVelocidad();
};

#endif
