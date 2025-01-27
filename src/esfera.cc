#include "esfera.h"

Esfera::Esfera(float r, int num_instancias, int num_vert_perfil){
   radio = r;
   numVerticesPerfil = num_vert_perfil;
   numInstancias = num_instancias;
   float x, y, z;

   std::vector<Tupla3f> perfil;
   // Se pone un punto en el eje y y se rota en z para obtener la semicircunferencia
   for (int i = 0 ; i < numVerticesPerfil ; i++){
      x = -sin(PI*i/numVerticesPerfil)*(-radio);
      y = cos(PI*i/numVerticesPerfil)*(-radio);
      z = 0;

      perfil.push_back({x, y, z});
   }

   crearMalla(perfil, num_instancias, true, true, 'Y'); // No importa el eje de rotación

   // Triángulos modo ajedrez
   calcularModoAjedrez();

   // Colores
   calcularColores(VERDE, PUNTOS);
   calcularColores(AMARILLO, LINEAS);
   calcularColores(ROJO, SOLIDO);
   calcularColores(AZUL, DIFERIDO);
   calcularColores(AMARILLO, SELECCIONADO);

   // Material
   Material mat(jade[0], jade[1], jade[2], jade_brillo);
   setMaterial(mat);
   Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
   setMaterialSeleccionado(mat2);
}
