#include "cilindro.h"

Cilindro::Cilindro(float h, float r, int num_instancias, char eje_rotacion){
   altura = h;
   radio = r;
   numVerticesPerfil = 2;

   std::vector<Tupla3f> perfil;
   perfil.resize(numVerticesPerfil);

   switch (toupper(eje_rotacion)){
      case 'X' :
         perfil[0] = {0.0, radio, 0.0};
         perfil[1] = {altura, radio, 0.0};
         break;

      case 'Y' :
         perfil[1] = {radio, 0.0, 0.0};
         perfil[0] = {radio, altura, 0.0};
         break;

      case 'Z' :
         perfil[0] = {0.0, radio, 0.0};
         perfil[1] = {0.0, radio, altura};
         break;
   }

   crearMalla(perfil, num_instancias, tapaInf, tapaSup, eje_rotacion);

   // Triángulos modo ajedrez
   calcularModoAjedrez();

   // Colores
   calcularColores(VERDE, PUNTOS);
   calcularColores(AMARILLO, LINEAS);
   calcularColores(TEXTURA, SOLIDO);
   calcularColores(AZUL, DIFERIDO);
   calcularColores(AMARILLO, SELECCIONADO);

   // Normales
   calcular_normales();

   // Textura
   setTextura("text-lata-1.jpg");
   calcularTexturas();

   // Material
   Material mat(obsidiana[0], obsidiana[1], obsidiana[2], obsidiana_brillo);
   setMaterial(mat);
   Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
   setMaterialSeleccionado(mat2);
}
