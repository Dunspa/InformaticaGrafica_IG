#include "doraemon.h"

Doraemon::Doraemon(){
   // Grados de libertad por defecto
   giroBrazoDcho = 0.0;
   incrementoBrazoDcho = 1.0;

   giroBrazoIzdo = 15.0;
   incrementoBrazoIzdo = 1.0;

   giroCabeza = 0.0;
   incrementoCabeza = 1.0;

   longitudCola = 0.0;
   incrementoCola = 0.1;

   // Crear las partes del modelo jerárquico
   cabeza = new CabezaDoraemon();
   brazo_izquierdo = new BrazoIzquierdoDoraemon();
   brazo_derecho = new BrazoDerechoDoraemon();
   cola = new ColaDoraemon();
   cuerpo = new CuerpoDoraemon();
}

void Doraemon::modificaGiroBrazoDcho(float valor){
   giroBrazoDcho += valor;

   if (giroBrazoDcho >= 15.0){
      giroBrazoDcho = 15.0;
   }
   else if (giroBrazoDcho <= -15.0){
      giroBrazoDcho = -15.0;
   }
}

void Doraemon::modificaGiroBrazoIzdo(float valor){
   giroBrazoIzdo += valor;

   if (giroBrazoIzdo <= -15.0){
      giroBrazoIzdo = -15.0;
   }
   else if (giroBrazoIzdo >= 15.0){
      giroBrazoIzdo = 15.0;
   }
}

void Doraemon::modificaGiroCabeza(float valor){
   giroCabeza += valor;

   fmod(giroCabeza, 360.0);
}

void Doraemon::modificaLongitudCola(float valor){
   longitudCola += valor;

   if (longitudCola <= -10.0){
      longitudCola = -10.0;
   }
   else if (longitudCola >= 0.0){
      longitudCola = 0.0;
   }
}

void Doraemon::draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion){
   // Construir el modelo jerárquico a partir de las distintas partes de este
   glPushMatrix();
      glPushMatrix();
         glTranslatef(0.0, 10.0, -10.0);
         glTranslatef(0.0, 0.0, longitudCola);
         glRotatef(-180.0, 0.0, 1.0, 0.0);
         glRotatef(-20.0, 1.0, 0.0, 0.0);
         glScalef(30.0, 30.0, 30.0);
         cola->draw(modoVisual, modoDibuj, modoIluminacion);
      glPopMatrix();

      glPushMatrix();
         glPushMatrix();
            glPushMatrix();
               glTranslatef(0.0, 10.0, 0.0);
               glRotatef(180.0, 0.0, 1.0, 0.0);
               glScalef(20.0, 20.0, 20.0);
               cuerpo->draw(modoVisual, modoDibuj, modoIluminacion);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(0.0, 36.0, 0.0);
               glRotatef(giroCabeza, 0.0, 1.0, 0.0);
               glScalef(20.0, 20.0, 20.0);
               cabeza->draw(modoVisual, modoDibuj, modoIluminacion);
            glPopMatrix();
         glPopMatrix();

         glPushMatrix();
            glTranslatef(14.5, 17.5, -1.0);
            glRotatef(15.0, 0.0, 0.0, 1.0);
            glRotatef(giroBrazoDcho, 0.0, 0.0, 1.0);
            glScalef(23.0, 23.0, 23.0);
            brazo_derecho->draw(modoVisual, modoDibuj, modoIluminacion);
         glPopMatrix();

         glPushMatrix();
            glTranslatef(-14.5, 17.5, -1.0);
            glRotatef(-180.0, 0.0, 1.0, 0.0);
            glRotatef(giroBrazoIzdo, 0.0, 0.0, 1.0);
            glScalef(23.0, 23.0, 23.0);
            brazo_izquierdo->draw(modoVisual, modoDibuj, modoIluminacion);
         glPopMatrix();
      glPopMatrix();
   glPopMatrix();
}

void Doraemon::setColorSeleccion(color col){
   cola->setColorSeleccion(col);
   cuerpo->setColorSeleccion(col);
   cabeza->setColorSeleccion(col);
   brazo_derecho->setColorSeleccion(col);
   brazo_izquierdo->setColorSeleccion(col);
}

void Doraemon::animar(){
   if (giroBrazoDcho >= 15.0 || giroBrazoDcho <= -15.0){
      incrementoBrazoDcho *= -1.0;
   }

   if (giroBrazoIzdo <= -15.0 || giroBrazoIzdo >= 15.0){
      incrementoBrazoIzdo *= -1.0;
   }

   if (longitudCola <= -10.0 || longitudCola >= 0.0){
      incrementoCola *= -1.0;
   }

   modificaGiroBrazoDcho(incrementoBrazoDcho);
   modificaGiroBrazoIzdo(incrementoBrazoIzdo);
   modificaGiroCabeza(incrementoCabeza);
   modificaLongitudCola(incrementoCola);
}

void Doraemon::aumentarVelocidad(){
   incrementoBrazoDcho += 0.5;
   incrementoBrazoIzdo += 0.5;
   incrementoCabeza += 0.5;
   incrementoCola += 0.5;

   animar();
}

void Doraemon::disminuirVelocidad(){
   incrementoBrazoDcho -= 0.5;
   incrementoBrazoIzdo -= 0.5;
   incrementoCabeza -= 0.5;
   incrementoCola -= 0.5;

   if (incrementoBrazoDcho <= 0.0)
      incrementoBrazoDcho = 0.0;

   if (incrementoBrazoIzdo <= 0.0)
      incrementoBrazoIzdo = 0.0;

   if (incrementoCabeza <= 0.0)
      incrementoCabeza = 0.0;

   if (incrementoCola <= 0.0)
      incrementoCola = 0.0;

   animar();
}
