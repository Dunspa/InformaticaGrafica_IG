// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: objrevolucion.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

class ObjRevolucion : public Malla3D{
public:
   // Constructores
   ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true);
   ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup=true, bool tapa_inf=true);

protected:
   // Crea la malla del objeto de revolución con NM vértices
   void crearMalla(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf);

private:
   int numInstancias;      // Número total de réplicas rotadas (N)
   int numVerticesPerfil;  // Número total de vértices en el perfil original (M)
   int numVertices;        // Número total de vértices de la figura (NM)
};

#endif
