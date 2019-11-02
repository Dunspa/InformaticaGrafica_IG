#include "esfera.h"

Esfera::Esfera(int num_vert_perfil, int num_instancias, float r){
   radio = r;
   numVerticesPerfil = num_vert_perfil;
   float x, y, z;

   std::vector<Tupla3f> perfil;
   perfil.resize(numVerticesPerfil);

   // Se pone un punto en el eje y y se rota en z para obtener la semicircunferencia
   for (int i = 0 ; i < numVerticesPerfil ; i++){
      x = cos(2.0*PI*i/numInstancias)*0 - sin(2.0*PI*i/numInstancias)*(-radio);
      y = sin(2.0*PI*i/numInstancias)*0 + cos(2.0*PI*i/numInstancias)*(-radio);
      z = 0;

      perfil.push_back({x, y, z});
   }

   crearMalla(perfil, num_instancias, false, false, 'Y'); // No importa el eje de rotación
}
