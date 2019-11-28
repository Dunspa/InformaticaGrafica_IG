#include "cuerpo_doraemon.h"

CuerpoDoraemon::CuerpoDoraemon(){
   cuerpo = new ObjPLY("plys/doraemon_cuerpo.ply");
}

void CuerpoDoraemon::draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion){
   cuerpo->draw(modoVisual, modoDibuj, modoIluminacion);
}
