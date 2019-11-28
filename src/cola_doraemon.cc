#include "cola_doraemon.h"

ColaDoraemon::ColaDoraemon(){
   cola = new ObjPLY("plys/doraemon_cola.ply");
}

void ColaDoraemon::draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion){
   cola->draw(modoVisual, modoDibuj, modoIluminacion);
}
