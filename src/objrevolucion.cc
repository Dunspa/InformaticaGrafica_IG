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
ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, char eje_rotacion){
   // Leer los vértices del perfil original
   ply::read_vertices(archivo, this->v);
   std::vector<Tupla3f> perfil = this->v;
   numVerticesPerfil = v.size();

   // Crear la malla del objeto de revolución
   crearMalla(perfil, num_instancias, tapaSup, tapaInf, eje_rotacion);

   // Triángulos modo ajedrez
   calcularModoAjedrez();

   // Colores
   calcularColores(VERDE, PUNTOS);
   calcularColores(AMARILLO, LINEAS);
   calcularColores(ROJO, SOLIDO);
   calcularColores(VERDE, DIFERIDO);

   // Normales
   calcular_normales();

   // Material
   Material mat(jade[0], jade[1], jade[2], jade_brillo);
   setMaterial(mat);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, char eje_rotacion){
   // Leer los vértices del perfil original
   std::vector<Tupla3f> perfil = archivo;

   // Crear la malla del objeto de revolución
   crearMalla(perfil, num_instancias, tapaSup, tapaInf, eje_rotacion);

   // Triángulos modo ajedrez
   calcularModoAjedrez();

   // Colores
   calcularColores(VERDE, PUNTOS);
   calcularColores(AMARILLO, LINEAS);
   calcularColores(ROJO, SOLIDO);
   calcularColores(VERDE, DIFERIDO);

   // Normales
   calcular_normales();

   // Material
   Material mat(jade[0], jade[1], jade[2], jade_brillo);
   setMaterial(mat);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_inf, bool tapa_sup, char eje_rotacion){
   // Se supone que el perfil se da de abajo a arriba
   bool sentido_perfil_ascendente;
   float x, y, z;
   Tupla3f polo_sur, polo_norte;
   numInstancias = num_instancias;
   numVerticesPerfil = perfil.size();
   eje = eje_rotacion;

   // Se parte de la tabla de vértices y triángulos vacías
   v.clear();
   f.clear();

   // Comprobar sentido del perfil
   switch (toupper(eje_rotacion)){
      case 'X' :

         break;

      case 'Y' :
         break;

      case 'Z' :
         break;
   }

   // Comprobación de polos en el perfil original
   bool existe_original_inf, existe_original_sup;
   switch (toupper(eje_rotacion)){
      case 'X' :
         existe_original_inf = perfil.front()(Y) == 0 && perfil.front()(Z) == 0;
         existe_original_sup = perfil.back()(Y) == 0 && perfil.back()(Z) == 0;
         break;

      case 'Y' :
         existe_original_inf = perfil.front()(X) == 0 && perfil.front()(Z) == 0;
         existe_original_sup = perfil.back()(X) == 0 && perfil.back()(Z) == 0;
         break;

      case 'Z' :
         existe_original_inf = perfil.front()(X) == 0 && perfil.front()(Y) == 0;
         existe_original_sup = perfil.back()(X) == 0 && perfil.back()(Y) == 0;
         break;
   }

   // No existe el vértice del polo sur en el perfil original
   if (!existe_original_inf){
      // Proyección del vértice extremo sobre el eje de rotación
      switch (toupper(eje_rotacion)){
         case 'X' :
            x = perfil.front()(X);
            y = 0;
            z = 0;
            break;

         case 'Y' :
            x = 0;
            y = perfil.front()(Y);
            z = 0;
            break;

         case 'Z' :
            x = 0;
            y = 0;
            z = perfil.front()(Z);
            break;
      }

      polo_sur = {x, y, z};
   }
   else{
      polo_sur = perfil.front();
      perfil.erase(perfil.begin());
   }

   // No existe el vértice del polo sur en el perfil original
   if (!existe_original_sup){
      // Proyección del vértice extremo sobre el eje de rotación
      switch (toupper(eje_rotacion)){
         case 'X' :
            x = perfil.back()(X);
            y = 0;
            z = 0;
            break;

         case 'Y' :
            x = 0;
            y = perfil.back()(Y);
            z = 0;
            break;

         case 'Z' :
            x = 0;
            y = 0;
            z = perfil.back()(Z);
            break;
      }

      polo_norte = {x, y, z};
      //v.push_back(polo_norte);
   }
   else{
      polo_norte = perfil.back();
      perfil.pop_back();
   }

   numVerticesPerfil = perfil.size();

   // Creación de la tabla de vértices
   for (int i = 0 ; i < numInstancias ; i++){	// Réplicas rotadas
      for (int j = 0 ; j < numVerticesPerfil ; j++){	// Vértices de una réplica
         // Vértice obtenido rotando 2*PI*i / N en el eje elegido
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
               z = perfil[j](Z);
               break;
         }

         // Añadir a la tabla de vértices
         Tupla3f v_rot = {x, y, z};
         v.push_back(v_rot);
      }
   }

   v.push_back(polo_sur);
   v.push_back(polo_norte);

   // Creación de la tabla de triángulos
   for (int i = 0 ; i < numInstancias ; i++){
      for (int j = 0 ; j < numVerticesPerfil - 1 ; j++){
         int a = numVerticesPerfil * i + j;
         int b = numVerticesPerfil * ((i + 1) % numInstancias) + j;

         // Triángulo por los índices a, b y b+1 (pares)
         Tupla3i t1 = {a, b, b+1};
         f.push_back(t1);
         // Triángulo por los índices a, b+1 y a+1 (impares)
         Tupla3i t2 = {a, b+1, a+1};
         f.push_back(t2);
      }
   }

   numVertices = v.size();
   numTriangulos = f.size();

   if (tapa_inf)
      crearTapaInf(eje_rotacion);

   if (tapa_sup)
      crearTapaSup(eje_rotacion);
}

void ObjRevolucion::crearTapaInf(char eje_rotacion){
   bool tapaInf = true;

   // Índice del polo sur en la tabla de vértices (para triangulos)
   int i_sur = numInstancias * numVerticesPerfil;

   // Insertar triángulos de la tapa
   for (int i = 0 ; i < numInstancias ; i++){
      f.push_back({(numVerticesPerfil + numVerticesPerfil * i)%i_sur, numVerticesPerfil * i, i_sur});
   }

   numVertices = v.size();
   numTriangulos = f.size();
}

void ObjRevolucion::crearTapaSup(char eje_rotacion){
   bool tapaSup = true;

   // Índice del polo norte en la tabla de vértices (para triangulos)
   int i_norte = numInstancias * numVerticesPerfil + 1;

   // Insertar triángulos de la tapa
   for (int i = 0 ; i < numInstancias - 1 ; i++){
      f.push_back({i_norte, numVerticesPerfil * (i+1) - 1, (numVerticesPerfil * (i+1) - 1) + numVerticesPerfil});
   }

   // Insertar último triángulo
   f.push_back({i_norte, numVerticesPerfil * numInstancias - 1, numVerticesPerfil - 1});

   numVertices = v.size();
   numTriangulos = f.size();
}

void ObjRevolucion::crearTapas(int numTapas, char eje_rotacion){
   if (numTapas == 1){
      bool tapaInf = true;
      float x, y, z;
      std::vector<Tupla3i>::iterator it = f.begin();
      int i;

      // Índice del polo sur en la tabla de vértices (para triangulos)
      int i_sur = numInstancias * numVerticesPerfil;

      // Insertar triángulos de la tapa
      for (int i = 0 ; i < numInstancias ; i++){
         f.insert(it, {(numVerticesPerfil + numVerticesPerfil * i)%i_sur, numVerticesPerfil * i, i_sur});
         ++it;
      }

      numTriangulos = f.size();

      // Triángulos modo ajedrez
      for (int i = 0 ; i < numInstancias ; i++){
         // Triángulos pares
         if (i % 2 == 0){
            f_par.push_back(f[i]);
         }
         // Triángulos impares
         else{
            f_impar.push_back(f[i]);
         }
      }
   }
   else{
      crearTapaInf(eje_rotacion);
      crearTapaSup(eje_rotacion);

      // Triángulos modo ajedrez
      calcularModoAjedrez();
   }

   numVertices = v.size();
   numTriangulos = f.size();
}

void ObjRevolucion::eliminarTapas(int numTapas){
   // Si es una tapa, se elimina la inferior
   if (numTapas == 1){
      std::vector<Tupla3i>::iterator it = f.end();
      --it;
      int i;
      // Índice del polo sur en la tabla de vértices (para triangulos)
      int i_sur = numInstancias * numVerticesPerfil;

      // Pasar tapa superior sin tocarla
      for (i = 0 ; i < numInstancias ; --it, i++);
      // Eliminar solo tapa inferior
      for (i = 0 ; i < numInstancias ; i++){
         f.erase(it);
         --it;
      }
   }
   // Si son dos tapas, se eliminan la superior y la inferior
   else{
      for (int i = 0 ; i < numInstancias*2 ; i++){
         f.pop_back();
      }
   }

   numVertices = v.size();
   numTriangulos = f.size();
   f_par.clear();
   f_impar.clear();

   // Triángulos modo ajedrez
   int i_par = 0, i_impar = 0;
   calcularModoAjedrez();
}
