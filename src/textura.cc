#include "textura.h"

Textura::Textura(std::string archivo){
   // Puntero a la imagen
   jpg::Imagen * pimg = nullptr;

   // Cargar la imagen
   pimg = new jpg::Imagen(archivo);

   // Parámetros de la textura
   width = pimg->tamX();
   height = pimg->tamY();
   // Copio a data la matriz de pixels al revés (operación de reflejo horizontal)
   for (int i = height - 1 ; i >= 0 ; i--){
      for (int j = 0 ; j < width ; j++){
         unsigned char * d = pimg->leerPixel(j, i);
         data.push_back(d[0]); // R
         data.push_back(d[1]); // G
         data.push_back(d[2]); // B
      }
   }
}

// Lee los texels de un archivo y los envía a la GPU
void Textura::activar(){
   // Se habilitan las texturas en OpenGL
   glEnable(GL_TEXTURE_2D);

   // Creación de la textura (una sola vez)
   if (textura_id == 0){
      // Generar un nuevo identificador de textura único
      glGenTextures(1, &textura_id);
      // Activa textura según su id
      glBindTexture(GL_TEXTURE_2D, textura_id);
      // Especificar cuál será la imagen de textura asociada al id activo
      gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
   }
   else{
      // Activa textura según su id
      glBindTexture(GL_TEXTURE_2D, textura_id);
   }
}
