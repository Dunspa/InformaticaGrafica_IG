#include "cuerpo_doraemon.h"

CuerpoDoraemon::CuerpoDoraemon(){
   cuerpo = new ObjPLY("plys/doraemon_cuerpo.ply");
}

void CuerpoDoraemon::draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion){
   cuerpo->draw(modoVisual, modoDibuj, modoIluminacion);
}

void CuerpoDoraemon::setColorSeleccion(color col){
   cuerpo->setColorSeleccion(col);
}

void CuerpoDoraemon::calcularCentro(const GLfloat * v_matrix){
   cuerpo->calcularCentro(v_matrix);
}

GLfloat * CuerpoDoraemon::getCentro(){
   return centro;
}
