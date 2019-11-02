// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: objply.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef OBJPLY_H_INCLUDED
#define OBJPLY_H_INCLUDED

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************
class ObjPLY : public Malla3D{
public:
   ObjPLY(const std::string & nombre_archivo);

private:
   int numVertices;
   int numTriangulos;
};

#endif
