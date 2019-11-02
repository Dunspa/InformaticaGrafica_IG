#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado){
   float x, y, z;

   // Inicializar la tabla de vértices
   v.resize(numVertices);
   v[0] = {0.0, 0.0, 0.0};
   v[1] = {lado, 0.0, 0.0};
   v[2] = {lado/2, 0, alturaCara(lado)};

   /* Calcular las coordenadas del baricentro del tetraedro
   x = (v[0](0) + v[1](0) + v[2](0)) / 3;
   y = 0;
   z = (v[0](3) + v[1](3) + v[2](3)) / 3;
   baricentro = {x, y, z};*/

   v[3] = {lado/2, alturaTetraedro(lado), distanciaBaricentro(lado)};

   // Inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   // de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(numTriangulos);
   f[0]  = {0, 1, 2};   // Base
   f[1]  = {3, 1, 0};
   f[2]  = {3, 2, 1};
   f[3]  = {3, 0 , 2};

   // Triángulos modo ajedrez
   f_par.resize(numTriangulos/2);
   f_impar.resize(numTriangulos/2);
   int i_par = 0, i_impar = 0;
   for (int i = 0 ; i < numTriangulos ; i++){
      // Triángulos pares
      if (i % 2 == 0){
         f_par[i_par] = f[i];
         i_par++;
      }
      // Triángulos impares
      else{
         f_impar[i_impar] = f[i];
         i_impar++;
      }
   }

   // Inicializar la tabla de colores inmediato (verde)
   c.resize(numVertices);
   for (int i = 0 ; i < numVertices ; i++){
      c[i] = {0, 0.8, 0};
   }

   // Inicializar la tabla de colores diferido (amarillo)
   c_dif.resize(numVertices);
   for (int i = 0 ; i < numVertices ; i++){
      c_dif[i] = {1, 0.8, 0};
   }
}

// -----------------------------------------------------------------------------
// Operaciones del tetraedro

// Calcula la distancia del punto medio de una arista al baricentro
float Tetraedro::distanciaBaricentro(float lado){
   return (alturaCara(lado) / 3);
}

// Calcula la altura de la cara
float Tetraedro::alturaCara(float lado){
   return ((lado * sqrt(3)) / 2);
}

// Calcula la altura del tetraedro aplicando Pitágoras
float Tetraedro::alturaTetraedro(float lado){
   return sqrt(pow(alturaCara(lado), 2) - pow(distanciaBaricentro(lado), 2));
}
