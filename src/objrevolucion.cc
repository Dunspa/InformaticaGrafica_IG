#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************

ObjRevolucion::ObjRevolucion(){

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)
ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, char eje_rotacion){
   // Leer los vértices del perfil original
   ply::read_vertices(archivo, this->v);
   numVerticesPerfil = v.size();

   // Crear la malla del objeto de revolución
   crearMalla(this->v, num_instancias, tapa_sup, tapa_inf, eje_rotacion);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf, char eje_rotacion){
   // Leer los vértices del perfil original
   v = archivo;

   // Crear la malla del objeto de revolución
   crearMalla(this->v, num_instancias, tapa_sup, tapa_inf, eje_rotacion);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf, char eje_rotacion){
   // Se supone que el perfil se da de abajo a arriba
   float x, y, z;
   bool existe_original_sup, existe_original_inf;
   numInstancias = num_instancias;
   numVerticesPerfil = perfil.size();

   // Comprobación de polos en el perfil original
   switch (toupper(eje_rotacion)){
      case 'X' :
         existe_original_inf = perfil[0](X) == 0 && perfil[0](Z) == 0;
         existe_original_sup = perfil[numVerticesPerfil-1](Y) == 0 && perfil[numVerticesPerfil-1](Z) == 0;
         break;

      case 'Y' :
         existe_original_inf = perfil[0](X) == 0 && perfil[0](Z) == 0;
         existe_original_sup = perfil[numVerticesPerfil-1](X) == 0 && perfil[numVerticesPerfil-1](Z) == 0;
         break;

      case 'Z' :
         existe_original_inf = perfil[0](0) == 0 && perfil[0](Y) == 0;
         existe_original_sup = perfil[numVerticesPerfil-1](X) == 0 && perfil[numVerticesPerfil-1](Y) == 0;
         break;
   }

   // Se parte de la tabla de vértices y triángulos vacías
   v.clear();
   f.clear();

   // Creación de la tabla de vértices TO DO
   for (int i = 0 ; i < numInstancias ; i++){	// Réplicas rotadas
      for (int j = 0 ; j < numVerticesPerfil ; j++){	// Vértices de una réplica
         // Vértice obtenido rotando j 2pi i / n en el eje elegido
         switch (toupper(eje_rotacion)){
            case 'X' :
               x = perfil[j](X);
               y = cos(2.0*PI*i/numInstancias)*perfil[j](Y) - sin(2.0*PI*i/numInstancias)*perfil[j](Z);
               z = sin(2.0*PI*i/numInstancias)*perfil[j](Y) + cos(2.0*PI*i/numInstancias)*perfil[j](Z);
               break;

            case 'Y' :
               x = cos(2.0*PI*i/numInstancias)*perfil[j](X) + sin(2.0*PI*i/numInstancias)*perfil[j](Z);
               y = perfil[j](Y);
               z = -sin(2.0*PI*i/numInstancias)*perfil[j](X) + cos(2.0*PI*i/numInstancias)*perfil[j](Z);
               break;

            case 'Z' :
               x = cos(2.0*PI*i/numInstancias)*perfil[j](X) - sin(2.0*PI*i/numInstancias)*perfil[j](Y);
               y = sin(2.0*PI*i/numInstancias)*perfil[j](X) + cos(2.0*PI*i/numInstancias)*perfil[j](Y);
               z = perfil[j](2);
               break;
         }

         // Añadir a la tabla de vértices
         Tupla3f v_rot = {x, y, z};
         v.push_back(v_rot);
      }
   }

   numVertices = v.size();

   // Creación de la tabla de triángulos
   for (int i = 0 ; i < numInstancias ; i++){
      for (int j = 0 ; j < numVerticesPerfil - 1 ; j++){
         int a = numVerticesPerfil * i + j;
         int b = numVerticesPerfil * ((i + 1) % numInstancias) + j;

         // Triángulo por los índices a, b y b+1
         Tupla3i t1 = {a, b, b+1};
         f.push_back(t1);
         // Triángulo por los índices a, b+1 y a+1
         Tupla3i t2 = {a, b+1, a+1};
         f.push_back(t2);
      }
   }

   // Comprobar si se desean añadir tapas a la malla
   if (tapa_inf){
      // Índice del polo sur en la tabla de vértices (para triangulos)
      int i_sur;
      switch (toupper(eje_rotacion)){
         case 'X' :
            i_sur = numInstancias * numVerticesPerfil + 1;
            break;

         case 'Y' :
            i_sur = numInstancias * numVerticesPerfil;
            break;

         case 'Z' :
            i_sur = numInstancias * numVerticesPerfil;
            break;
      }

      // No existe el vértice del polo sur en el perfil original
      if (!existe_original_inf){
         // Proyección del vértice extremo sobre el eje de rotación
         switch (toupper(eje_rotacion)){
            case 'X' :
               x = v[0](X);
               y = 0;
               z = 0;
               break;

            case 'Y' :
               x = 0;
               y = v[0](Y);
               z = 0;
               break;

            case 'Z' :
               x = 0;
               y = 0;
               z = v[0](Z);
               break;
         }

         Tupla3f polo_sur = {x, y, z};
         v.push_back(polo_sur);
      }

      // Insertar triángulos de la tapa
      for (int i = 0 ; i < numInstancias ; i++){
         f.push_back({numVerticesPerfil * ((i+1)%numInstancias), numVerticesPerfil * (i%numInstancias), i_sur});
      }
   }

   if (tapa_sup){
      // Índice del polo norte en la tabla de vértices (para triangulos)
      int i_norte;
      switch (toupper(eje_rotacion)){
         case 'X' :
            i_norte = numInstancias * numVerticesPerfil;
            break;

         case 'Y' :
            i_norte = numInstancias * numVerticesPerfil + 1;
            break;

         case 'Z' :
            i_norte = numInstancias * numVerticesPerfil + 1;
            break;
      }

      // No existe el vértice del polo sur en el perfil original
      if (!existe_original_sup){
         // Proyección del vértice extremo sobre el eje de rotación
         switch (toupper(eje_rotacion)){
            case 'X' :
               x = v[1](X);
               y = 0;
               z = 0;
               break;

            case 'Y' :
               x = 0;
               y = v[1](Y);
               z = 0;
               break;

            case 'Z' :
               x = 0;
               y = 0;
               z = v[1](Z);
               break;
         }

         Tupla3f polo_norte = {x, y, z};
         v.push_back(polo_norte);
      }

      // Insertar triángulos de la tapa
      for (int i = 0 ; i < numInstancias ; i++){
         Tupla3i cosa = {i_norte, numVerticesPerfil * (i+1) - 1, numVerticesPerfil * ((i+1) % numInstancias) + 1};
         f.push_back({i_norte, numVerticesPerfil * (i+1) - 1, numVerticesPerfil * ((i+1) % numInstancias) + 1});
         std::cout << cosa << std::endl;
      }
   }

   numVertices = v.size();
   numTriangulos = f.size();

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
   for (int i = 0 ; i < numVertices ; i++){
      c[i] = {1, 0, 0};
   }

   // Inicializar la tabla de colores diferido (azul)
   c_dif.resize(numVertices);
   for (int i = 0 ; i < numVertices ; i++){
      c_dif[i] = {0, 0, 1};
   }

   /*for (int i = 0 ; i < numVertices ; i++){
      std::cout << v[i] << " ";
   }*/
}
