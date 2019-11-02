#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "cilindro.h"

typedef enum{
   NADA, SELOBJETO, SELVISUALIZACION, SELDIBUJADO
} menu;

typedef enum{
   CUBO, TETRAEDRO, ANT, CILINDRO
} objetoEscena;

class Escena{
private:
   // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   // Transformación de cámara
	void change_projection(const float ratio_xy);
	void change_observer();

   void clear_window();

   // Opciones de menú
   menu modoMenu = NADA;               // Menú principal por defecto
   dibujado modoDibujado = INMEDIATO;  // Modo de dibujado inmediato por defecto

   // Objetos de la escena (importante inicializarlos a nullptr)
   Ejes ejes;
   Cubo * cubo = nullptr;
   Tetraedro * tetraedro = nullptr;
   ObjPLY * ant = nullptr;
   Cilindro * cilindro = nullptr;

   // Controlan la visibilidad de los distintos objetos
   bool cuboVisible      = true;
   bool tetraedroVisible = true;
   bool antVisible       = true;
   bool cilindroVisible  = true;

   // Controlan la visibilidad de los distintos modos
   bool puntosVisible    = false;
   bool lineasVisible    = false;
   bool solidoVisible    = true;
   bool ajedrezVisible   = false;   // Si ajedrez visible, los otros modos invisibles

public:
   Escena();
   ~Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
   void eligeObjetos(dibujado modoDibuj, objetoEscena obj);
   void dibujaObjetos(dibujado modoDibuj, objetoEscena obj);
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

   // Métodos para consultar y cambiar la visibilidad de los objetos
   // Cubo
   bool getCuboVisible();
   void setCuboVisible(bool visib);
   // Tetraedro
   bool getTetraedroVisible();
   void setTetraedroVisible(bool visib);
   // Ant (Hormiga)
   bool getAntVisible();
   void setAntVisible(bool visib);
};

#endif
