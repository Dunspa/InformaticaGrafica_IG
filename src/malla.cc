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
   else if (modoVisual == SELECCION){
      // Colores de la seleccion
      glColorPointer(3, GL_FLOAT, 0, c_selec.data());
   }
   else if (modoVisual == SELECCIONADO){
      // Colores del objeto seleccionado
      glColorPointer(3, GL_FLOAT, 0, c_seleccionado.data());
   }

   // Habilitar vertex arrays
   glEnableClientState(GL_VERTEX_ARRAY);
   // Especificar puntero a tabla de vertices
   glVertexPointer(3, GL_FLOAT, 0, v.data());


   if (glIsEnabled(GL_LIGHTING)){
      // Habilitar normales
      glEnableClientState(GL_NORMAL_ARRAY);
      // Especificar puntero a tabla de normales
      glNormalPointer(GL_FLOAT, 0, nv.data());
   }


   // Habilitar coordenadas de texturas (en caso de que existan)
   if (textura != nullptr && !ct.empty() && modoVisual){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
   }

   // Dibujar usando vertices indexados
   dibujarElementos();

   // Deshabilitar array de colores
   glDisableClientState(GL_COLOR_ARRAY);
   // Deshabilitar vertex arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   if (glIsEnabled(GL_LIGHTING)){
      // Habilitar normales
      glDisableClientState(GL_NORMAL_ARRAY);
   }
   // Deshabilitar coordenadas de texturas
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
      glColorPointer(3, GL_FLOAT, 0, c_dif.data());
   }
   else if (modoVisual == SELECCION){
      // Colores de la seleccion
      glColorPointer(3, GL_FLOAT, 0, c_selec.data());
   }
   else if (modoVisual == SELECCIONADO){
      // Colores del objeto seleccionado
      glColorPointer(3, GL_FLOAT, 0, c_seleccionado.data());
   }

   // Especificar localización y formato de la tabla de vértices y habilitarla
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);   // Activar VBO de vértices
   glVertexPointer(3, GL_FLOAT, 0, 0);          // Especifica formato y offset 0
   glBindBuffer(GL_ARRAY_BUFFER, 0);            // Desactivar VBO de vértices
   glEnableClientState(GL_VERTEX_ARRAY);        // Habilitar tabla de vértices

   if (glIsEnabled(GL_LIGHTING)){
      // Habilitar normales
      glEnableClientState(GL_NORMAL_ARRAY);
      // Especificar puntero a tabla de normales
      glNormalPointer(GL_FLOAT, 0, nv.data());
   }

   // Habilitar coordenadas de texturas (en caso de que existan)
   if (!ct.empty()){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
   }

   // Visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // Activar VBO de triángulos
   dibujarElementos(); // Dibujar usando vertices indexados
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Desactivar VBO de triángulos

   // Desactivar uso de array de colores
   glDisableClientState(GL_COLOR_ARRAY);
   // Desactivar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
   if (glIsEnabled(GL_LIGHTING)){
      // Desactivar uso de array de normales
      glDisableClientState(GL_NORMAL_ARRAY);
   }
   // Deshabilitar coordenadas de texturas
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
   dibujarCarasPares();
   // Deshabilitar vertex arrays
   glDisableClientState(GL_VERTEX_ARRAY);

   // Colores de los triángulos impares
   glColorPointer(3, GL_FLOAT, 0, c_dif.data());
   // Habilitar vertex arrays
   glEnableClientState(GL_VERTEX_ARRAY);
   // Especificar puntero a tabla de vertices
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   // Dibujar usando vertices indexados
   dibujarCarasImpares();
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
   if (modoVisual == SELECCIONADO)
      m_seleccionado.aplicar();
   else
      m.aplicar();

   // Activar textura
   if (textura != nullptr && !ct.empty() && modoVisual != SELECCION)
      textura->activar();

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

   glDisable(GL_TEXTURE_2D);
}

void Malla3D::dibujarElementos(){
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
}

void Malla3D::dibujarCarasPares(){
   glDrawElements(GL_TRIANGLES, 3*f_par.size(), GL_UNSIGNED_INT, f_par.data());
}

void Malla3D::dibujarCarasImpares(){
   glDrawElements(GL_TRIANGLES, 3*f_impar.size(), GL_UNSIGNED_INT, f_impar.data());
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
         else if (col == TEXTURA){
            c_vert[i] = colorTextura;
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
         else if (col == TEXTURA){
            c_arist[i] = colorTextura;
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
         else if (col == TEXTURA){
            c[i] = colorTextura;
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
         else if (col == TEXTURA){
            c_dif[i] = colorTextura;
         }
      }
   }
   else if (modoVisual == SELECCIONADO){
      // Colores del modo diferido (impar en ajedrez)
      c_seleccionado.resize(numVertices);
      for (int i = 0 ; i < numVertices ; i++){
         if (col == ROJO){
            c_seleccionado[i] = colorRojo;
         }
         else if (col == VERDE){
            c_seleccionado[i] = colorVerde;
         }
         else if (col == AZUL){
            c_seleccionado[i] = colorAzul;
         }
         else if (col == AMARILLO){
            c_seleccionado[i] = colorAmarillo;
         }
         else if (col == TEXTURA){
            c_seleccionado[i] = colorTextura;
         }
      }
   }
}

void Malla3D::setColorSeleccion(color col){
   // Colores del modo seleccion
   c_selec.resize(numVertices);
   for (int i = 0 ; i < numVertices ; i++){
      if (col == SEL1){
         c_selec[i] = colorSel1;
      }
      else if (col == SEL2){
         c_selec[i] = colorSel2;
      }
      else if (col == SEL3){
         c_selec[i] = colorSel3;
      }
      else if (col == SEL4){
         c_selec[i] = colorSel4;
      }
      else if (col == SEL5){
         c_selec[i] = colorSel5;
      }
      else if (col == SEL6){
         c_selec[i] = colorSel6;
      }
      else if (col == SEL7){
         c_selec[i] = colorSel7;
      }
      else if (col == SEL8){
         c_selec[i] = colorSel8;
      }
      else if (col == SEL9){
         c_selec[i] = colorSel9;
      }
   }
}

/*void Malla3D::setColorSeleccionado(){
   std::vector<Tupla3f> intercambio = c;
   c = c_anterior;
   c_anterior = intercambio;
}*/

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
   nf.resize(f.size());
   for (int i = 0 ; i < f.size() ; i++){
      Tupla3f p = v[f[i](X)];
      Tupla3f q = v[f[i](Y)];
      Tupla3f r = v[f[i](Z)];

      // Vectores correspondientes a dos aristas
      Tupla3f a = q - p;
      Tupla3f b = r - p;
      // Vector perpendicular a la cara
      Tupla3f m = a.cross(b);

      if (m.lengthSq() > 0){
         // Vector perpendicular a la cara, normalizado
         Tupla3f n = m.normalized();
         // Añadir normal de la cara i
         nf[i] = n;
      }
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
   
   nv.resize(v.size());

   for (int i = 0 ; i < v.size() ; i++){
      if (m[i].lengthSq() > 0){
         // Vector perpendicular al vértice, normalizado
         Tupla3f n = m[i].normalized();
         // Añadir normal del vértice i
         nv[i] = n;
      }
   }

   numNormalesVertices = nv.size();
}

void Malla3D::calcularCentro(const GLfloat * v_mat){
   // Obtener matriz modelview para tener las coordenadas reales del objeto
   GLfloat v_matrix[16];

   for (int i = 0; i < 16; i++){
      v_matrix[i] = v_mat[i];
   }

   GLfloat m_matrix[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix);

   float cx, cy, cz;
   float x, y, z;
   // Despejar N matriz de modelado de la matriz modelview M = NV -> N = M(V^-1)
   // Inversa de V (CÓDIGO OBTENIDO DE LA IMPLEMENTACIÓN DE MESA DE LA BIBLIOTECA GLU)
   GLfloat inv[16], det;
    inv[0] = v_matrix[5]  * v_matrix[10] * v_matrix[15] -
             v_matrix[5]  * v_matrix[11] * v_matrix[14] -
             v_matrix[9]  * v_matrix[6]  * v_matrix[15] +
             v_matrix[9]  * v_matrix[7]  * v_matrix[14] +
             v_matrix[13] * v_matrix[6]  * v_matrix[11] -
             v_matrix[13] * v_matrix[7]  * v_matrix[10];

    inv[4] = -v_matrix[4]  * v_matrix[10] * v_matrix[15] +
              v_matrix[4]  * v_matrix[11] * v_matrix[14] +
              v_matrix[8]  * v_matrix[6]  * v_matrix[15] -
              v_matrix[8]  * v_matrix[7]  * v_matrix[14] -
              v_matrix[12] * v_matrix[6]  * v_matrix[11] +
              v_matrix[12] * v_matrix[7]  * v_matrix[10];

    inv[8] = v_matrix[4]  * v_matrix[9] * v_matrix[15] -
             v_matrix[4]  * v_matrix[11] * v_matrix[13] -
             v_matrix[8]  * v_matrix[5] * v_matrix[15] +
             v_matrix[8]  * v_matrix[7] * v_matrix[13] +
             v_matrix[12] * v_matrix[5] * v_matrix[11] -
             v_matrix[12] * v_matrix[7] * v_matrix[9];

    inv[12] = -v_matrix[4]  * v_matrix[9] * v_matrix[14] +
               v_matrix[4]  * v_matrix[10] * v_matrix[13] +
               v_matrix[8]  * v_matrix[5] * v_matrix[14] -
               v_matrix[8]  * v_matrix[6] * v_matrix[13] -
               v_matrix[12] * v_matrix[5] * v_matrix[10] +
               v_matrix[12] * v_matrix[6] * v_matrix[9];

    inv[1] = -v_matrix[1]  * v_matrix[10] * v_matrix[15] +
              v_matrix[1]  * v_matrix[11] * v_matrix[14] +
              v_matrix[9]  * v_matrix[2] * v_matrix[15] -
              v_matrix[9]  * v_matrix[3] * v_matrix[14] -
              v_matrix[13] * v_matrix[2] * v_matrix[11] +
              v_matrix[13] * v_matrix[3] * v_matrix[10];

    inv[5] = v_matrix[0]  * v_matrix[10] * v_matrix[15] -
             v_matrix[0]  * v_matrix[11] * v_matrix[14] -
             v_matrix[8]  * v_matrix[2] * v_matrix[15] +
             v_matrix[8]  * v_matrix[3] * v_matrix[14] +
             v_matrix[12] * v_matrix[2] * v_matrix[11] -
             v_matrix[12] * v_matrix[3] * v_matrix[10];

    inv[9] = -v_matrix[0]  * v_matrix[9] * v_matrix[15] +
              v_matrix[0]  * v_matrix[11] * v_matrix[13] +
              v_matrix[8]  * v_matrix[1] * v_matrix[15] -
              v_matrix[8]  * v_matrix[3] * v_matrix[13] -
              v_matrix[12] * v_matrix[1] * v_matrix[11] +
              v_matrix[12] * v_matrix[3] * v_matrix[9];

    inv[13] = v_matrix[0]  * v_matrix[9] * v_matrix[14] -
              v_matrix[0]  * v_matrix[10] * v_matrix[13] -
              v_matrix[8]  * v_matrix[1] * v_matrix[14] +
              v_matrix[8]  * v_matrix[2] * v_matrix[13] +
              v_matrix[12] * v_matrix[1] * v_matrix[10] -
              v_matrix[12] * v_matrix[2] * v_matrix[9];

    inv[2] = v_matrix[1]  * v_matrix[6] * v_matrix[15] -
             v_matrix[1]  * v_matrix[7] * v_matrix[14] -
             v_matrix[5]  * v_matrix[2] * v_matrix[15] +
             v_matrix[5]  * v_matrix[3] * v_matrix[14] +
             v_matrix[13] * v_matrix[2] * v_matrix[7] -
             v_matrix[13] * v_matrix[3] * v_matrix[6];

    inv[6] = -v_matrix[0]  * v_matrix[6] * v_matrix[15] +
              v_matrix[0]  * v_matrix[7] * v_matrix[14] +
              v_matrix[4]  * v_matrix[2] * v_matrix[15] -
              v_matrix[4]  * v_matrix[3] * v_matrix[14] -
              v_matrix[12] * v_matrix[2] * v_matrix[7] +
              v_matrix[12] * v_matrix[3] * v_matrix[6];

    inv[10] = v_matrix[0]  * v_matrix[5] * v_matrix[15] -
              v_matrix[0]  * v_matrix[7] * v_matrix[13] -
              v_matrix[4]  * v_matrix[1] * v_matrix[15] +
              v_matrix[4]  * v_matrix[3] * v_matrix[13] +
              v_matrix[12] * v_matrix[1] * v_matrix[7] -
              v_matrix[12] * v_matrix[3] * v_matrix[5];

    inv[14] = -v_matrix[0]  * v_matrix[5] * v_matrix[14] +
               v_matrix[0]  * v_matrix[6] * v_matrix[13] +
               v_matrix[4]  * v_matrix[1] * v_matrix[14] -
               v_matrix[4]  * v_matrix[2] * v_matrix[13] -
               v_matrix[12] * v_matrix[1] * v_matrix[6] +
               v_matrix[12] * v_matrix[2] * v_matrix[5];

    inv[3] = -v_matrix[1] * v_matrix[6] * v_matrix[11] +
              v_matrix[1] * v_matrix[7] * v_matrix[10] +
              v_matrix[5] * v_matrix[2] * v_matrix[11] -
              v_matrix[5] * v_matrix[3] * v_matrix[10] -
              v_matrix[9] * v_matrix[2] * v_matrix[7] +
              v_matrix[9] * v_matrix[3] * v_matrix[6];

    inv[7] = v_matrix[0] * v_matrix[6] * v_matrix[11] -
             v_matrix[0] * v_matrix[7] * v_matrix[10] -
             v_matrix[4] * v_matrix[2] * v_matrix[11] +
             v_matrix[4] * v_matrix[3] * v_matrix[10] +
             v_matrix[8] * v_matrix[2] * v_matrix[7] -
             v_matrix[8] * v_matrix[3] * v_matrix[6];

    inv[11] = -v_matrix[0] * v_matrix[5] * v_matrix[11] +
               v_matrix[0] * v_matrix[7] * v_matrix[9] +
               v_matrix[4] * v_matrix[1] * v_matrix[11] -
               v_matrix[4] * v_matrix[3] * v_matrix[9] -
               v_matrix[8] * v_matrix[1] * v_matrix[7] +
               v_matrix[8] * v_matrix[3] * v_matrix[5];

    inv[15] = v_matrix[0] * v_matrix[5] * v_matrix[10] -
              v_matrix[0] * v_matrix[6] * v_matrix[9] -
              v_matrix[4] * v_matrix[1] * v_matrix[10] +
              v_matrix[4] * v_matrix[2] * v_matrix[9] +
              v_matrix[8] * v_matrix[1] * v_matrix[6] -
              v_matrix[8] * v_matrix[2] * v_matrix[5];

    det = v_matrix[0] * inv[0] + v_matrix[1] * inv[4] + v_matrix[2] * inv[8] + v_matrix[3] * inv[12];

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
      v_matrix[i] = inv[i] * det;

   centro = {0.0f, 0.0f, 0.0f};

   // Calcular centro geometrico como la suma de todas las coordenadas dividido por el numero de puntos
   for (int i = 0 ; i < v.size() ; i++){
      centro = centro + v[i];
   }

   centro = centro / v.size();

   // Aplicar modelview
   x = m_matrix[0] * centro(X) + m_matrix[4] * centro(Y) + m_matrix[8] * centro(Z) + m_matrix[12];
   y = m_matrix[1] * centro(X) + m_matrix[5] * centro(Y) + m_matrix[9] * centro(Z) + m_matrix[13];
   z = m_matrix[2] * centro(X) + m_matrix[6] * centro(Y) + m_matrix[10] * centro(Z) + m_matrix[14];

   centro = {x, y, z};

   // Aplicar inversa de V
   x = v_matrix[0] * centro(X) + v_matrix[4] * centro(Y) + v_matrix[8] * centro(Z) + v_matrix[12];
   y = v_matrix[1] * centro(X) + v_matrix[5] * centro(Y) + v_matrix[9] * centro(Z) + v_matrix[13];
   z = v_matrix[2] * centro(X) + v_matrix[6] * centro(Y) + v_matrix[10] * centro(Z) + v_matrix[14];

   centro = {x, y, z};
}

// -----------------------------------------------------------------------------
// Aplica un material a la malla 3D
void Malla3D::setMaterial(Material mat){
   m = mat;
}

void Malla3D::setMaterialSeleccionado(Material mat){
   m_seleccionado = mat;
}

Tupla3f Malla3D::getCentro(){
   return centro;
}

// -----------------------------------------------------------------------------
// Aplica una textura a la malla 3D
void Malla3D::setTextura(std::string archivo){
   textura = new Textura(archivo);
}
