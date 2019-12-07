#include "lienzo.h"

Lienzo::Lienzo(float l){
   numVertices = 4;
   numTriangulos = 2;
   lado = l;

   // Inicializar la tabla de vértices
   v.push_back({0.0, 0.0, 0.0});
   v.push_back({l, 0.0, 0.0});
   v.push_back({0.0, l, 0.0});
   v.push_back({l, l, 0.0});

   // Inicializar la tabla de caras o triángulos:
   f.push_back({0, 1, 2});
   f.push_back({1, 3, 2});

   // Triángulos modo ajedrez
   calcularModoAjedrez();

   // Colores
   calcularColores(TEXTURA, PUNTOS);
   calcularColores(TEXTURA, LINEAS);
   calcularColores(TEXTURA, SOLIDO);
   calcularColores(TEXTURA, DIFERIDO);

   // Normales
   calcular_normales();

   // Material
   Material mat(esmeralda[0], esmeralda[1], esmeralda[2], esmeralda_brillo);
   setMaterial(mat);

   // Textura
   setTextura("mapa.jpg");
   calcularTexturas();
}
