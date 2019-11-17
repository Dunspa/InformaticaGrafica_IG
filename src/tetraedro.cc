#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado){
   float x, y, z;
   numVertices = 4;
   numTriangulos = 4;

   // Inicializar la tabla de vértices
   v.resize(numVertices);
   v[0] = {0.0, 0.0, 0.0};
   v[1] = {lado, 0.0, 0.0};
   v[2] = {lado/2, 0, alturaCara(lado)};
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
   calcularModoAjedrez();

   // Colores
   calcularColores(VERDE, AMARILLO);

   // Normales
   calcular_normales();
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
