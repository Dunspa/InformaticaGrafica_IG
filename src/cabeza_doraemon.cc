#include "cabeza_doraemon.h"

CabezaDoraemon::CabezaDoraemon(){
   cabeza = new ObjPLY("plys/doraemon_cabeza.ply");
}

void CabezaDoraemon::draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion){
   cabeza->draw(modoVisual, modoDibuj, modoIluminacion);
}
