#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f & posicion, GLenum idLuzOpenGL, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular){
   this->posicion = {posicion(X), posicion(Y), posicion(Z), 1};
   id = idLuzOpenGL;
   colorAmbiente = ambiente;
   colorDifuso = difuso;
   colorEspecular = especular;
   activada = false;
}
