#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************

ObjRevolucion::ObjRevolucion(){

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)
ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf){
   // Leer los vértices del perfil original
   ply::read_vertices(archivo, this->v);
   numVerticesPerfil = v.size();

   // Crear la malla del objeto de revolución
   crearMalla(this->v, num_instancias, tapa_sup, tapa_inf);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf){
   // Leer los vértices del perfil original
   v = archivo;

   // Crear la malla del objeto de revolución
   crearMalla(this->v, num_instancias, tapa_sup, tapa_inf);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf){

}
