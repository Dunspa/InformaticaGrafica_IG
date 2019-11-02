#include "cilindro.h"

Cilindro::Cilindro(int num_instancias, float h, float r, char eje_rotacion, bool tapa_sup, bool tapa_inf){
   altura = h;
   radio = r;
   numVerticesPerfil = 2;

   std::vector<Tupla3f> perfil;
   perfil.resize(numVerticesPerfil);

   switch (toupper(eje_rotacion)){
      case 'X' :
         perfil[0] = {0, radio, 0};
         perfil[1] = {altura, radio, 0};
         break;

      case 'Y' :
         perfil[0] = {radio, 0, 0};
         perfil[1] = {radio, altura, 0};
         break;

      case 'Z' :
         perfil[0] = {0, radio, 0};
         perfil[1] = {0, radio, altura};
         break;
   }

   crearMalla(perfil, num_instancias, tapa_sup, tapa_inf, eje_rotacion);
}
