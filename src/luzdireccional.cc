#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla3f & orientacion, GLenum idLuzOpenGL, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular){
   posicion = {orientacion(X), orientacion(Y), orientacion(Z), 0};
   id = idLuzOpenGL;
   colorAmbiente = ambiente;
   colorDifuso = difuso;
   colorEspecular = especular;
   activada = false;

   float radio = sqrt(pow(posicion(X), 2.0) + pow(posicion(Y), 2.0) + pow(posicion(Z), 2.0));
   alpha = acos(posicion(Z) / radio);
   beta = atan2(posicion(Y), posicion(Z));
}

void LuzDireccional::variarAnguloAlpha(float incremento){
   alpha += incremento;

   // Cambiar vector de posicion
   float radio = sqrt(pow(posicion(X), 2.0) + pow(posicion(Y), 2.0) + pow(posicion(Z), 2.0));
   posicion(X) = radio * sin(alpha) * cos(beta);
   posicion(Y) = radio * sin(alpha) * sin(beta);
   posicion(Z) = radio * cos(alpha);
}

void LuzDireccional::variarAnguloBeta(float incremento){
   beta += incremento;

   // Cambiar vector de posición
   float radio = sqrt(pow(posicion(X), 2.0) + pow(posicion(Y), 2.0) + pow(posicion(Z), 2.0));
   posicion(X) = radio * sin(alpha) * cos(beta);
   posicion(Y) = radio * sin(alpha) * sin(beta);
   posicion(Z) = radio * cos(alpha);
}
