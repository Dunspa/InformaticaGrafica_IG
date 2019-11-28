#include "brazoizquierdo_doraemon.h"

BrazoIzquierdoDoraemon::BrazoIzquierdoDoraemon(){
   brazo_izquierdo = new ObjPLY("plys/doraemon_brazo_izquierdo.ply");
}

void BrazoIzquierdoDoraemon::draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion){
   brazo_izquierdo->draw(modoVisual, modoDibuj, modoIluminacion);
}
