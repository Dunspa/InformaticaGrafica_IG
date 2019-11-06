#include "cono.h"

Cono::Cono(int num_instancias, float h, float r, char eje_rotacion, bool tapa_inf, bool tapa_sup){
   altura = h;
   radio = r;
   numVerticesPerfil = 2;

   std::vector<Tupla3f> perfil;
   perfil.resize(numVerticesPerfil);

   switch (toupper(eje_rotacion)){
      case 'X' :
         perfil[0] = {0, radio, 0};
         perfil[1] = {altura, 0, 0};
         break;

      case 'Y' :
         perfil[0] = {radio, 0, 0};
         perfil[1] = {0, altura, 0};
         break;

      case 'Z' :
         perfil[0] = {0, radio, 0};
         perfil[1] = {0, 0, altura};
         break;
   }

   crearMalla(perfil, num_instancias, tapa_inf, tapa_sup, eje_rotacion);

   // Triángulos modo ajedrez
   int i_par = 0, i_impar = 0;
   for (int i = 0 ; i < numTriangulos ; i++){
      // Triángulos pares
      if (i % 2 == 0){
         f_par.push_back(f[i]);
         i_par++;
      }
      // Triángulos impares
      else{
         f_impar.push_back(f[i]);
         i_impar++;
      }
   }

   // Inicializar la tabla de colores inmediato (rojo)
   c.resize(numVertices);
   for (int i = 0 ; i < numVertices ; i++){
      c[i] = {1, 0, 0};
   }

   // Inicializar la tabla de colores diferido (azul)
   c_dif.resize(numVertices);
   for (int i = 0 ; i < numVertices ; i++){
      c_dif[i] = {0, 0, 1};
   }
}
