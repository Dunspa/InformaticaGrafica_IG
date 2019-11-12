#include "luz.h"

void Luz::activar(){
   // Habilitar uso
   if(!activada){
      glEnable(id);
      activada = true;
   }
   else{
      glDisable(id);
      activada = false;
   }

   // Configurar parámetros de la luz
   glLightfv(id, GL_POSITION, posicion);        // Posición de la luz
   glLightfv(id, GL_DIFFUSE, colorDifuso);      // Color de la luz difusa
   glLightfv(id, GL_SPECULAR, colorEspecular);  // Color de la luz especular
   glLightfv(id, GL_AMBIENT, colorAmbiente);    // Color de la luz ambiente
}
