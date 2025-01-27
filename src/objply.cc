#include "objply.h"
#include "ply_reader.h"

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY(const std::string & nombre_archivo){
   // leer la lista de caras y vértices
   ply::read(nombre_archivo, this->v, this->f);

   numVertices = v.size();
   numTriangulos = f.size();

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

   // Colores
   calcularColores(VERDE, PUNTOS);
   calcularColores(AMARILLO, LINEAS);
   calcularColores(ROJO, SOLIDO);
   calcularColores(AZUL, DIFERIDO);
   calcularColores(AMARILLO, SELECCIONADO);

   // Normales
   calcular_normales();

   // Material
   Material mat(cyanplastico[0], cyanplastico[1], cyanplastico[2], cyanplastico_brillo);
   setMaterial(mat);
   Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
   setMaterialSeleccionado(mat2);
}
