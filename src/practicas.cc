//**************************************************************************
// Prácticas Informática Gráfica (2019-2020)
//
// Jose Luis Gallego Peña
//
// GPL
//**************************************************************************


#include "aux.h" // includes de OpenGL, windows, y librería std de C++
#include "escena.h"

// variable que contiene un puntero a la escena
Escena *escena = nullptr ;

//***************************************************************************
// Funcion principal que redibuja la escena
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void draw_scene(void){
	if (escena != nullptr)
      escena->dibujar();

	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int newWidth, int newHeight){
	if (escena != nullptr)
      escena->redimensionar(newWidth,newHeight);
	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char tecla, int x, int y){
	int salir = 0;

   if (escena != nullptr)
      salir = escena->teclaPulsada(tecla, x, y);

	if (salir){
		delete escena;
      escena = nullptr;

		exit(0);
	}
   else
		glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce un click en el ratón
//
// el evento manda a la funcion:
// click del raton
// estado del raton
// posición x e y del ratón en la ventana
//***************************************************************************

void clickRaton(int boton, int estado, int x, int y){
	if (escena != nullptr)
		escena->clickRaton(boton, estado, x, y);
}

//***************************************************************************
// Funcion llamada cuando se produce un movimiento en el ratón manteniendo un boton
// Gestiona el cambio de orientación de una cámara activa
//
// el evento manda a la funcion:
// posición x e y del ratón en la ventana
//***************************************************************************

void ratonMovido(int x, int y){
	if (escena != nullptr)
		escena->ratonMovido(x, y);
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void special_keys(int tecla, int x, int y){
	if (escena != nullptr)
		escena->teclaEspecial(tecla, x, y);

	glutPostRedisplay();
}

//***************************************************************************
// Funcion que se encarga de llevar el IDLE en la escena para la animación
//***************************************************************************

void funcion_idle(){
	if (escena != nullptr)
		escena->animarModeloJerarquico();

	glutPostRedisplay();
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv){
	using namespace std;

   // crear la escena (un puntero a la misma)
   escena = new Escena();

   // Incialización de GLUT

   // se llama a la inicialización de glut
   glutInit(&argc, argv);

   // se indica las caracteristicas que se desean para la visualización con OpenGL
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   // variables que determninan la posicion y tamaño de la ventana X
   const int UI_window_pos_x  = 50,
             UI_window_pos_y  = 50,
             UI_window_width  = 500,
             UI_window_height = 500;

   // posicion de la esquina inferior izquierdad de la ventana
   glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

   // tamaño de la ventana (ancho y alto)
   glutInitWindowSize(UI_window_width,UI_window_height);

   // llamada para crear la ventana, indicando el titulo
   // SUSTITUIR EL NOMBRE DEL ALUMNO
   glutCreateWindow("Practicas IG: Jose Luis Gallego Peña");

   // asignación de la funcion llamada "dibujar" al evento de dibujo
   glutDisplayFunc(draw_scene);

   // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
   glutReshapeFunc(change_window_size);

   // asignación de la funcion llamada "tecla_normal" al evento correspondiente
   glutKeyboardFunc(normal_keys);

	// Procesar eventos de ratón
	glutMouseFunc(clickRaton);
	glutMotionFunc(ratonMovido);

   // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
   glutSpecialFunc(special_keys);

	// Asignación de la función idle
	glutIdleFunc(funcion_idle);

   // inicialización de librería GLEW (solo en Linux)
   #ifdef __linux__
   const GLenum codigoError = glewInit();

   if (codigoError != GLEW_OK){	// comprobar posibles errores
      cout << "Imposible inicializar ’GLEW’, mensaje recibido: "
           << glewGetErrorString(codigoError) << endl;
      exit(1);
   }
   #endif

   // funcion de inicialización de la escena (necesita que esté la ventana creada)
   escena->inicializar(UI_window_width, UI_window_height);

   // ejecutar del bucle de eventos
   glutMainLoop();

   return 0;
}
