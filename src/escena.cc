#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena(){
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0;
    Observer_angle_y  = 0.0;

    ejes.changeAxisSize(5000);

    // Crear los objetos de la escena
    cubo = new Cubo(50);
    tetraedro = new Tetraedro(50);
    ant = new ObjPLY("plys/ant.ply");
    cilindro = new Cilindro(20, 20, 20, 'Y');
    cono = new Cono(20, 20, 20, 'Y', false, true);
    esfera = new Esfera(20, 20, 20);
}

//**************************************************************************
// destructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::~Escena(){
   delete cubo;
   delete tetraedro;
   delete ant;
   delete cilindro;
   delete cono;
   delete esfera;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height){
	glClearColor(1.0, 1.0, 1.0, 1.0);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);  // se habilita el z-bufer
   glEnable(GL_CULL_FACE);   // se habilita el cull face
   glEnable(GL_NORMALIZE);   // normales invariantes a transformaciones geométricas

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection(float(UI_window_width)/float(UI_window_height));
	glViewport(0, 0, UI_window_width, UI_window_height);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::eligeObjetos(dibujado modoDibuj, objetoEscena obj){
   if (obj == CUBO){
      if (cubo != nullptr && cuboVisible)
         cubo->draw(modoDibuj);
   }
   else if (obj == TETRAEDRO){
      if (tetraedro != nullptr && tetraedroVisible)
         tetraedro->draw(modoDibuj);
   }
   else if (obj == ANT){
      if (ant != nullptr && antVisible)
         ant->draw(modoDibuj);
   }
   else if (obj == CILINDRO){
      if (cilindro != nullptr && cilindroVisible){
         cilindro->draw(modoDibuj);
      }
   }
   else if (obj == CONO){
      if (cono != nullptr && conoVisible){
         cono->draw(modoDibuj);
      }
   }
   else if (obj == ESFERA){
      if (esfera != nullptr && esferaVisible){
         esfera->draw(modoDibuj);
      }
   }
}

void Escena::dibujaObjetos(dibujado modoDibuj, objetoEscena obj){
   // Modo ajedrez
   if (ajedrezVisible){
      glPolygonMode(GL_FRONT, GL_FILL);
      eligeObjetos(modoDibuj, obj);
   }
   // Otros modos (no ajedrez)
   else{
      // Dibujar puntos
      if (puntosVisible){
         glPolygonMode(GL_FRONT, GL_POINT);
         glPointSize(5);   // Puntos más gordos para que se vean bien
         eligeObjetos(modoDibuj, obj);
      }

      // Dibujar líneas
      if (lineasVisible){
         glPolygonMode(GL_FRONT, GL_LINE);
         eligeObjetos(modoDibuj, obj);
      }

      // Dibujar sólidos
      if (solidoVisible){
         glPolygonMode(GL_FRONT, GL_FILL);
         eligeObjetos(modoDibuj, obj);
      }
   }
}

void Escena::dibujar(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
	change_observer();
   ejes.draw();

	// Dibujar todos los objetos de la escena

	// Cubo
	glPushMatrix();
      glScalef(1.0, 1.6, 1.0);
		glTranslatef(50.0, 0.0, 0.0);
		dibujaObjetos(modoDibujado, CUBO);
	glPopMatrix();

   // Tetraedro
   glPushMatrix();
      glTranslatef(50.0, 80.0, 0.0);
      dibujaObjetos(modoDibujado, TETRAEDRO);
   glPopMatrix();

   // Ant (hormiga)
   glPushMatrix();
      glScalef(2.0, 2.0, 2.0);
      glTranslatef(0.0, 10.0, 0.0);
      dibujaObjetos(modoDibujado, ANT);
   glPopMatrix();

   // Cilindro
   glPushMatrix();
      glScalef(2.0, 2.0, 2.0);
      glTranslatef(-50.0, 0.0, 0.0);
      dibujaObjetos(modoDibujado, CILINDRO);
   glPopMatrix();

   // Cono
   glPushMatrix();
      glScalef(2.0, 2.0, 2.0);
      glTranslatef(-50.0, 40.0, 0.0);
      dibujaObjetos(modoDibujado, CONO);
   glPopMatrix();

   // Esfera
   glPushMatrix();
      glScalef(2.0, 2.0, 2.0);
      glTranslatef(0.0, 50.0, 0.0);
      dibujaObjetos(modoDibujado, ESFERA);
   glPopMatrix();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y){
   using namespace std;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir = false;
   switch(toupper(tecla)){
      case 'Q' :
         if (modoMenu != NADA){
            modoMenu = NADA;
            cout << "Menú principal. Opciones: " << endl
                 << " - O: Selección de objeto." << endl
                 << " - V: Selección de visualización." << endl
                 << " - D: Selección de dibujado." << endl
                 << "Q para salir del programa." << endl;
         }
         else{
            salir = true;
            cout << "Cerrando programa" << endl;
         }
         break;

      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu = SELOBJETO;
         cout << "Modo selección de objeto. Opciones: " << endl
              << " - C: Cubo." << endl
              << " - T: Tetraedro." << endl
              << " - H: Ant (Hormiga)." << endl
              << " - I: Cilindro." << endl
              << " - N: Cono." << endl
              << " - E: Esfera." << endl
              << "Q para salir al menú principal." << endl;
         break;

      case 'C' :
         if (modoMenu == SELOBJETO){
            cuboVisible = !cuboVisible;
            cout << "Objeto: Cubo" << endl;
         }
         break;

      case 'T' :
         if (modoMenu == SELOBJETO){
            tetraedroVisible = !tetraedroVisible;
            cout << "Objeto: Tetraedro" << endl;
         }
         break;

      case 'H' :
         if (modoMenu == SELOBJETO){
            antVisible = !antVisible;
            cout << "Objeto: Ant (Hormiga)" << endl;
         }
         break;

      case 'I' :
         if (modoMenu == SELOBJETO){
            cilindroVisible = !cilindroVisible;
            cout << "Objeto: Cilindro" << endl;
         }
         break;

      case 'N' :
         if (modoMenu == SELOBJETO){
            conoVisible = !conoVisible;
            cout << "Objeto: Cono" << endl;
         }
         break;

      case 'E' :
         if (modoMenu == SELOBJETO){
            esferaVisible = !esferaVisible;
            cout << "Objeto: Esfera" << endl;
         }
         break;

      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu = SELVISUALIZACION;
         cout << "Modo selección de visualización. Opciones: " << endl
              << " - P: Visualizar puntos." << endl
              << " - L: Visualizar líneas." << endl
              << " - S: Visualizar sólidos." << endl
              << " - A: Visualizar modo ajedrez." << endl
              << "Q para salir al menú principal." << endl;
         break;

      case 'P' :
         // PUNTOS
         if (modoMenu == SELVISUALIZACION){
            puntosVisible = !puntosVisible;
            cout << "Modo de visualización: puntos" << endl;
         }
         break;

      case 'L' :
         if (modoMenu == SELVISUALIZACION){
            lineasVisible = !lineasVisible;
            cout << "Modo de visualización: líneas" << endl;
         }
         break;

      case 'S' :
         if (modoMenu == SELVISUALIZACION){
            solidoVisible = !solidoVisible;
            cout << "Modo de visualización: sólido" << endl;
         }
         break;

      case 'A' :
         if (modoMenu == SELVISUALIZACION){
            modoDibujado = AJEDREZ;
            ajedrezVisible = !ajedrezVisible;
            if (!ajedrezVisible)
               modoDibujado = INMEDIATO; // Inmediato por defecto
            cout << "Modo de visualización: ajedrez" << endl;
         }
         break;

      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu = SELDIBUJADO;
         cout << "Modo selección de dibujado. Opciones: "
              << " - 1: Dibujado inmediato." << endl
              << " - 2: Dibujado diferido." << endl
              << "Q para salir al menú principal." << endl;
         break;

      case '1' :
         if (modoMenu == SELDIBUJADO){
            modoDibujado = INMEDIATO;
            cout << "Modo de dibujado: inmediato" << endl;
         }
         break;

      case '2' :
         if (modoMenu == SELDIBUJADO){
            modoDibujado = DIFERIDO;
            cout << "Modo de dibujado: diferido" << endl;
         }
         break;
   }

   return salir;
}

//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y){
   switch (Tecla1){
	   case GLUT_KEY_LEFT:
         Observer_angle_y--;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x--;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection(const float ratio_xy){
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy;
   glFrustum(-wx, wx, -Height, Height, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight){
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection(float(newHeight)/float(newWidth));
   glViewport(0, 0, newWidth, newHeight);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer(){
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -Observer_distance);
   glRotatef(Observer_angle_y, 0.0 ,1.0, 0.0);
   glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);
}
