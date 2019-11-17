#include "luz.h"

void Luz::activar(){
   // Habilitar uso
   glEnable(id);
   activada = true;

   // Configurar parámetros de la luz
   glLightfv(id, GL_POSITION, posicion);        // Posición de la luz
   glLightfv(id, GL_DIFFUSE, colorDifuso);      // Color de la luz difusa
   glLightfv(id, GL_SPECULAR, colorEspecular);  // Color de la luz especular
   glLightfv(id, GL_AMBIENT, colorAmbiente);    // Color de la luz ambiente
}

void Luz::desactivar(){
   // Deshabilitar usando
   glDisable(id);
   activada = false;
}
