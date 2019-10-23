#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado){
   // Inicializar la tabla de vértices
   v.resize(numVertices);
   v[0] = {0.0, 0.0, lado};
   v[1] = {lado, 0.0, lado};
   v[2] = {0.0, lado, lado};
   v[3] = {lado, lado, lado};
   v[4] = {lado, 0.0, 0.0};
   v[5] = {lado, lado, 0.0};
   v[6] = {0.0, lado, 0.0};
   v[7] = {0.0, 0.0, 0.0};

   // Inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   // de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(numTriangulos);
   f[0]  = {0, 1, 2};
   f[1]  = {1, 3, 2};
   f[2]  = {1, 4, 3};
   f[3]  = {4, 5, 3};
   f[4]  = {4, 6, 5};
   f[5]  = {4, 7, 6};
   f[6]  = {7, 2, 6};
   f[7]  = {7, 0, 2};
   f[8]  = {2, 3, 5};
   f[9]  = {2, 5, 6};
   f[10] = {0, 7, 4};
   f[11] = {0, 4, 1};

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

   // Inicializar la tabla de colores inmediato (rojo)
   c.resize(numVertices);
   c[0] = {204, 0, 0};
   c[1] = {204, 0, 0};
   c[2] = {204, 0, 0};
   c[3] = {204, 0, 0};
   c[4] = {204, 0, 0};
   c[5] = {204, 0, 0};
   c[6] = {204, 0, 0};
   c[7] = {204, 0, 0};

   // Inicializar la tabla de colores diferido (azul)
   c_dif.resize(numVertices);
   c_dif[0] = {255, 0, 127};
   c_dif[1] = {255, 0, 127};
   c_dif[2] = {255, 0, 127};
   c_dif[3] = {255, 0, 127};
   c_dif[4] = {255, 0, 127};
   c_dif[5] = {255, 0, 127};
   c_dif[6] = {255, 0, 127};
   c_dif[7] = {255, 0, 127};
}
