#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// Jose Luis Gallego Peña
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'
void Malla3D::draw_ModoInmediato(dibujado modoVisual){
   // Habilitar uso de array de colores
   glEnableClientState(GL_COLOR_ARRAY);

   if (modoVisual == PUNTOS){
      // Colores de los vértices
      glColorPointer(3, GL_FLOAT, 0, c_vert.data());
   }
   else if (modoVisual == LINEAS){
      // Colores de las aristas
      glColorPointer(3, GL_FLOAT, 0, c_arist.data());
   }
   else if (modoVisual == SOLIDO){
      // Colores del sólido
      glColorPointer(3, GL_FLOAT, 0, c.data());
   }

   // Habilitar vertex arrays
   glEnableClientState(GL_VERTEX_ARRAY);
   // Especificar puntero a tabla de vertices
   glVertexPointer(3, GL_FLOAT, 0, v.data());

   // Habilitar normales
   glEnableClientState(GL_NORMAL_ARRAY);
   // Especificar puntero a tabla de normales
   glNormalPointer(GL_FLOAT, 0, nv.data());

   // Dibujar usando vertices indexados
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

   // Deshabilitar array de colores
   glDisableClientState(GL_COLOR_ARRAY);
   // Deshabilitar vertex arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   // Deshabilitar array de normales
   glDisableClientState(GL_NORMAL_ARRAY);
}

// -----------------------------------------------------------------------------
// Crea un VBO y devuelve su identificador
GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
   GLuint id_vbo; // Resultado: identificador de VBO
   glGenBuffers(1, &id_vbo);  // Crear nuevo VBO, obtener identificador (nunca 0)
   glBindBuffer(tipo_vbo, id_vbo);  // Activar el VBO usando su identificador

   // Esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

   glBindBuffer(tipo_vbo, 0); // Desactivación del VBO (activar 0)

   return id_vbo;
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)
// Dibuja en un color distinto al modo inmediato para distinguirlos
void Malla3D::draw_ModoDiferido(dibujado modoVisual){
   // Crear VBOs y guardar sus identificadores (si no existen)
   if (id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3*v.size()*sizeof(float), v.data());

   if (id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f.size()*sizeof(int), f.data());

   // Habilitar uso de array de colores
   glEnableClientState(GL_COLOR_ARRAY);
   
   if (modoVisual == PUNTOS){
      // Colores de los vértices
      glColorPointer(3, GL_FLOAT, 0, c_vert.data());
   }
   else if (modoVisual == LINEAS){
      // Colores de las aristas
      glColorPointer(3, GL_FLOAT, 0, c_arist.data());
   }
   else if (modoVisual == SOLIDO){
      // Colores del sólido
      glColorPointer(3, GL_FLOAT, 0, c.data());
   }

   // Especificar localización y formato de la tabla de vértices y habilitarla
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);   // Activar VBO de vértices
   glVertexPointer(3, GL_FLOAT, 0, 0);          // Especifica formato y offset 0
   glBindBuffer(GL_ARRAY_BUFFER, 0);            // Desactivar VBO de vértices
   glEnableClientState(GL_VERTEX_ARRAY);        // Habilitar tabla de vértices

   // Visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // Activar VBO de triángulos
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Desactivar VBO de triángulos

   // Desactivar uso de array de colores
   glDisableClientState(GL_COLOR_ARRAY);
   // Desactivar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
}

// -----------------------------------------------------------------------------
// Visualización en modo inmediato y usando ajedrez
// Dibuja las caras pares en un color y las impares en otro
void Malla3D::draw_ModoAjedrez(){
   // Habilitar uso de array de colores
   glEnableClientState(GL_COLOR_ARRAY);

   // Colores de los triángulos pares
   glColorPointer(3, GL_FLOAT, 0, c.data());
   // Habilitar vertex arrays
   glEnableClientState(GL_VERTEX_ARRAY);
   // Especificar puntero a tabla de vertices
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   // Dibujar usando vertices indexados
   glDrawElements(GL_TRIANGLES, 3*f_par.size(), GL_UNSIGNED_INT, f_par.data());
   // Deshabilitar vertex arrays
   glDisableClientState(GL_VERTEX_ARRAY);

   // Colores de los triángulos impares
   glColorPointer(3, GL_FLOAT, 0, c_dif.data());
   // Habilitar vertex arrays
   glEnableClientState(GL_VERTEX_ARRAY);
   // Especificar puntero a tabla de vertices
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   // Dibujar usando vertices indexados
   glDrawElements(GL_TRIANGLES, 3*f_impar.size(), GL_UNSIGNED_INT, f_impar.data());
   // Deshabilitar vertex arrays
   glDisableClientState(GL_VERTEX_ARRAY);

   // Deshabilitar array de colores
   glDisableClientState(GL_COLOR_ARRAY);
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a draw_ModoInmediato o bien a draw_ModoDiferido
void Malla3D::draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion){
   // Aplicar material a la malla
   m.aplicar();

   // Modo de iluminación SMOOTH o FLAT
   if (modoIluminacion)
      glShadeModel(GL_SMOOTH);
   else
      glShadeModel(GL_FLAT);

   // Dibujar en modo inmediato, diferido o ajedrez (inmediato por defecto)
   if (modoDibuj == INMEDIATO)
      draw_ModoInmediato(modoVisual);
   else if (modoDibuj == DIFERIDO)
      draw_ModoDiferido(modoVisual);
   else if (modoDibuj == AJEDREZ)
      draw_ModoAjedrez();
}

// -----------------------------------------------------------------------------
// Calcula las tablas de colores de cualquier malla 3D (normal y diferido)
void Malla3D::calcularColores(color col, dibujado modoVisual){
   if (modoVisual == PUNTOS){
      // Colores de los vértices
      c_vert.resize(numVertices);
      for (int i = 0 ; i < numVertices ; i++){
         if (col == ROJO){
            c_vert[i] = colorRojo;
         }
         else if (col == VERDE){
            c_vert[i] = colorVerde;
         }
         else if (col == AZUL){
            c_vert[i] = colorAzul;
         }
         else if (col == AMARILLO){
            c_vert[i] = colorAmarillo;
         }
      }
   }
   else if (modoVisual == LINEAS){
      // Colores de las aristas
      c_arist.resize(numVertices);
      for (int i = 0 ; i < numVertices ; i++){
         if (col == ROJO){
            c_arist[i] = colorRojo;
         }
         else if (col == VERDE){
            c_arist[i] = colorVerde;
         }
         else if (col == AZUL){
            c_arist[i] = colorAzul;
         }
         else if (col == AMARILLO){
            c_arist[i] = colorAmarillo;
         }
      }
   }
   else if (modoVisual == SOLIDO){
      // Colores del sólido
      c.resize(numVertices);
      for (int i = 0 ; i < numVertices ; i++){
         if (col == ROJO){
            c[i] = colorRojo;
         }
         else if (col == VERDE){
            c[i] = colorVerde;
         }
         else if (col == AZUL){
            c[i] = colorAzul;
         }
         else if (col == AMARILLO){
            c[i] = colorAmarillo;
         }
      }
   }
   else if (modoVisual == DIFERIDO){
      // Colores del modo diferido (impar en ajedrez)
      c_dif.resize(numVertices);
      for (int i = 0 ; i < numVertices ; i++){
         if (col == ROJO){
            c_dif[i] = colorRojo;
         }
         else if (col == VERDE){
            c_dif[i] = colorVerde;
         }
         else if (col == AZUL){
            c_dif[i] = colorAzul;
         }
         else if (col == AMARILLO){
            c_dif[i] = colorAmarillo;
         }
      }
   }
}

// -----------------------------------------------------------------------------
// Calcula las caras para el modo ajedrez de cualquier malla 3D
void Malla3D::calcularModoAjedrez(){
   for (int i = 0 ; i < numTriangulos ; i++){
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

// -----------------------------------------------------------------------------
// Calcula las normales de cualquier malla 3D
void Malla3D::calcular_normales(){
   // Calcular tabla de normales de las caras
   for (int i = 0 ; i < f.size() ; i++){
      Tupla3f p = v[f[i](X)];
      Tupla3f q = v[f[i](Y)];
      Tupla3f r = v[f[i](Z)];

      // Vectores correspondientes a dos aristas
      Tupla3f a = q - p;
      Tupla3f b = r - p;
      // Vector perpendicular a la cara
      Tupla3f m = a.cross(b);
      // Vector perpendicular a la cara, normalizado
      Tupla3f n = m.normalized();

      // Añadir normal de la cara i
      nf.push_back(n);
   }

   numNormalesCaras = nf.size();

   // Calcular tabla de normales de los vértices
   std::vector<Tupla3f> m(v.size());
   for (int i = 0 ; i < f.size() ; i++){
      int v1 = f[i](X);
      int v2 = f[i](Y);
      int v3 = f[i](Z);

      // Vector perpendicular al vértice
      m[v1] = m[v1] + nf[i];
      m[v2] = m[v2] + nf[i];
      m[v3] = m[v3] + nf[i];
   }

   for (int i = 0 ; i < v.size() ; i++){
      // Vector perpendicular al vértice, normalizado
      Tupla3f n = m[i].normalized();
      // Añadir normal del vértice i
      nv.push_back(n);
   }

   numNormalesVertices = nv.size();
}

// -----------------------------------------------------------------------------
// Aplica un material a la malla 3D
void Malla3D::setMaterial(Material mat){
   m = mat;
}
