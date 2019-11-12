#include "esfera.h"

Esfera::Esfera(int num_vert_perfil, int num_instancias, float r){
   radio = r;
   numVerticesPerfil = num_vert_perfil;
   numInstancias = num_instancias;
   float x, y, z;

Tupla3f a;
   std::vector<Tupla3f> perfil;
   // Se pone un punto en el eje y y se rota en z para obtener la semicircunferencia
   for (int i = 0 ; i < numVerticesPerfil ; i++){
      x = -sin(PI*i/numVerticesPerfil)*(-radio);
      y = cos(PI*i/numVerticesPerfil)*(-radio);
      z = 0;

      perfil.push_back({x, y, z});
   }

   // Cerar la esfera
   //perfil.push_back({0, radio, 0});

   crearMalla(perfil, num_instancias, true, true, 'Y'); // No importa el eje de rotación

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

   calcular_normales();
}
