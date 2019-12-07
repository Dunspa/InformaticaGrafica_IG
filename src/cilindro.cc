#include "cilindro.h"

Cilindro::Cilindro(float h, float r, int num_instancias, char eje_rotacion){
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
         perfil[1] = {radio, 0, 0};
         perfil[0] = {radio, altura, 0};
         break;

      case 'Z' :
         perfil[0] = {0, radio, 0};
         perfil[1] = {0, radio, altura};
         break;
   }

   crearMalla(perfil, num_instancias, tapaInf, tapaSup, eje_rotacion);

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
   Material mat(obsidiana[0], obsidiana[1], obsidiana[2], obsidiana_brillo);
   setMaterial(mat);
}
