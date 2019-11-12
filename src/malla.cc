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
void Malla3D::draw_ModoInmediato(){
   // Habilitar uso de array de colores
   glEnableClientState(GL_COLOR_ARRAY);
   // Colores de los vértices
   glColorPointer(3, GL_FLOAT, 0, c.data());

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
void Malla3D::draw_ModoDiferido(){
   // Crear VBOs y guardar sus identificadores (si no existen)
   if (id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3*v.size()*sizeof(float), v.data());

   if (id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f.size()*sizeof(int), f.data());

   // Especificar localización y formato de la tabla de vértices y habilitarla
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);   // Activar VBO de vértices
   glVertexPointer(3, GL_FLOAT, 0, 0);          // Especifica formato y offset 0
   glBindBuffer(GL_ARRAY_BUFFER, 0);            // Desactivar VBO de vértices
   glEnableClientState(GL_VERTEX_ARRAY);        // Habilitar tabla de vértices

   // Visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // Activar VBO de triángulos
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Desactivar VBO de triángulos

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
void Malla3D::draw(dibujado modoDibuj, bool modoIluminacion){
   if (modoIluminacion)
      glShadeModel(GL_SMOOTH);
   else
      glShadeModel(GL_FLAT);

   if (modoDibuj == INMEDIATO)
      draw_ModoInmediato();
   else if (modoDibuj == DIFERIDO)
      draw_ModoDiferido();
   else if (modoDibuj == AJEDREZ)
      draw_ModoAjedrez();
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
