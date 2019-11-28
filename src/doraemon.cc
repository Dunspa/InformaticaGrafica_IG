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
   incrementoCola = 1.0;

   // Crear las partes del modelo jerárquico
   cabeza = new CabezaDoraemon();
   brazo_izquierdo = new BrazoIzquierdoDoraemon();
   brazo_derecho = new BrazoDerechoDoraemon();
   cola = new ColaDoraemon();
   cuerpo = new CuerpoDoraemon();
}

void Doraemon::modificaGiroBrazoDcho(float valor){
   if (giroBrazoDcho >= 15.0){
      incrementoBrazoDcho *= -valor;
   }
   else if (giroBrazoDcho <= -15.0){
      incrementoBrazoDcho *= -valor;
   }

   giroBrazoDcho += incrementoBrazoDcho;
}

void Doraemon::modificaGiroBrazoIzdo(float valor){
   if (giroBrazoIzdo <= -15.0){
      incrementoBrazoIzdo *= -valor;
   }
   else if (giroBrazoIzdo >= 15.0){
      incrementoBrazoIzdo *= -valor;
   }

   giroBrazoIzdo += incrementoBrazoIzdo;
}

void Doraemon::modificaGiroCabeza(float valor){
   if (giroCabeza <= 360.0){
      incrementoCabeza *= valor;
   }
   else{
      giroCabeza = 0.0;
   }

   giroCabeza += incrementoCabeza;
}

void Doraemon::modificaLongitudCola(float valor){
   if (longitudCola <= -10.0){
      incrementoCola *= -valor;
   }
   else if (longitudCola >= 0.0){
      incrementoCola *= -valor;
   }

   longitudCola += incrementoCola;
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
            glTranslatef(15.0, 17.0, -1.0);
            glRotatef(giroBrazoDcho, 0.0, 0.0, 1.0);
            glScalef(23.0, 23.0, 23.0);
            brazo_derecho->draw(modoVisual, modoDibuj, modoIluminacion);
         glPopMatrix();

         glPushMatrix();
            glTranslatef(-15.0, 17.0, -1.0);
            glRotatef(-180.0, 0.0, 1.0, 0.0);
            glRotatef(giroBrazoIzdo, 0.0, 0.0, 1.0);
            glScalef(23.0, 23.0, 23.0);
            brazo_izquierdo->draw(modoVisual, modoDibuj, modoIluminacion);
         glPopMatrix();
      glPopMatrix();
   glPopMatrix();
}

void Doraemon::animar(parteDoraemon parte, char controlarValor){
   float valor = 0.0;
   if (controlarValor == '+'){
      valor = 1.0;
   }
   else if (controlarValor == '-'){
      valor = -1.0;
   }

   if (parte == TODO){
      modificaGiroBrazoDcho(valor);
      modificaGiroBrazoIzdo(valor);
      modificaGiroCabeza(valor);
      modificaLongitudCola(valor);
   }
   else{
      if (parte == BRAZODERECHO){
         modificaGiroBrazoDcho(valor);
      }
      else if (parte == BRAZOIZQUIERDO){
         modificaGiroBrazoIzdo(valor);
      }
      else if (parte == CABEZA){
         modificaGiroCabeza(valor);
      }
      else if (parte == COLA){
         modificaLongitudCola(valor);
      }
   }
}
