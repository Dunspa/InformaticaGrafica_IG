// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: textura.h
// Declaraciones de clase Textura
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"
#include "jpg_imagen.h"

class Textura{
private:
   GLuint textura_id = 0;
   std::vector<unsigned char> data;
   unsigned int width;
   unsigned int height;

public:
   Textura(std::string archivo);
   void activar();
};

#endif
