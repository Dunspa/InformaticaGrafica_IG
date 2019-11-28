#include "brazoderecho_doraemon.h"

BrazoDerechoDoraemon::BrazoDerechoDoraemon(){
   brazo_derecho = new ObjPLY("plys/doraemon_brazo_derecho.ply");
}

void BrazoDerechoDoraemon::draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion){
   brazo_derecho->draw(modoVisual, modoDibuj, modoIluminacion);
}
