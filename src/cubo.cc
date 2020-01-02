#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado){
   numVertices = 8;
   numTriangulos = 12;

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
   calcularModoAjedrez();

   // Colores
   calcularColores(VERDE, PUNTOS);
   calcularColores(AMARILLO, LINEAS);
   calcularColores(ROJO, SOLIDO);
   calcularColores(AZUL, DIFERIDO);
   
   // Normales
   calcular_normales();

   // Material
   Material mat(esmeralda[0], esmeralda[1], esmeralda[2], esmeralda_brillo);
   setMaterial(mat);
}
