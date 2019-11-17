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
    cubo = new Cubo(50);                                       // Cubo(lado)
    tetraedro = new Tetraedro(50);                             // Tetraedro(lado)
    peon = new ObjRevolucion("plys/peon.ply", 20); // Peon(perfil.ply, num_instancias)
    cilindro = new Cilindro(20, 20, 20);                       // Cilindro(altura, radio, num_instancias)
    cono = new Cono(20, 20, 20);                               // Cono(altura, radio, num_instancias)
    esfera = new Esfera(20, 20, 20);                           // Esfera(radio, num_instancias, num_vert_perfil)

    // Crear las luces de la escena
    luzposicional = new LuzPosicional({10, 10, 10}, GL_LIGHT0, {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});
    luzdireccional = new LuzDireccional({0, 0, 10}, GL_LIGHT1, {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});
}

//**************************************************************************
// destructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::~Escena(){
   delete cubo;
   delete tetraedro;
   delete peon;
   delete cilindro;
   delete cono;
   delete esfera;
   delete luzposicional;
   delete luzdireccional;
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
         cubo->draw(modoDibuj, modoIluminacion);
   }
   else if (obj == TETRAEDRO){
      if (tetraedro != nullptr && tetraedroVisible)
         tetraedro->draw(modoDibuj, modoIluminacion);
   }
   else if (obj == PEON){
      if (peon != nullptr && peonVisible)
         peon->draw(modoDibuj, modoIluminacion);
   }
   else if (obj == CILINDRO){
      if (cilindro != nullptr && cilindroVisible)
         cilindro->draw(modoDibuj, modoIluminacion);
   }
   else if (obj == CONO){
      if (cono != nullptr && conoVisible)
         cono->draw(modoDibuj, modoIluminacion);
   }
   else if (obj == ESFERA){
      if (esfera != nullptr && esferaVisible)
         esfera->draw(modoDibuj, modoIluminacion);
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

void Escena::eliminaTapas(){
   if (peon != nullptr)
      peon->eliminarTapas(2);

   if (cilindro != nullptr)
      cilindro->eliminarTapas(2);

   if (cono != nullptr)
      cono->eliminarTapas(1);

   if (esfera != nullptr)
      esfera->eliminarTapas(2);
}

void Escena::dibujaTapas(){
   if (peon != nullptr)
      peon->crearTapas(2, peon->eje);

   if (cilindro != nullptr)
      cilindro->crearTapas(2, cilindro->eje);

   if (cono != nullptr)
      cono->crearTapas(1, cono->eje);

   if (esfera != nullptr)
      esfera->crearTapas(2, esfera->eje);
}

void Escena::dibujar(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
	change_observer();
   glDisable(GL_LIGHTING);
   ejes.draw();

   if (iluminado){
      glEnable(GL_LIGHTING);
      //glEnable(GL_LIGHT0); // Luz 0 por defecto
   }

	// Dibujar todos los objetos de la escena

	// Cubo
	glPushMatrix();
      //glScalef(1.0, 1.6, 1.0);
		glTranslatef(25.0, 0.0, 0.0);
		dibujaObjetos(modoDibujado, CUBO);
	glPopMatrix();

   // Tetraedro
   glPushMatrix();
      glTranslatef(50.0, 80.0, 0.0);
      dibujaObjetos(modoDibujado, TETRAEDRO);
   glPopMatrix();

   // Peon
   glPushMatrix();
      glScalef(15.0, 15.0, 15.0);
      glTranslatef(0.0, 0.0, 0.0);
      dibujaObjetos(modoDibujado, PEON);
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
              << " - P: Peon." << endl
              << " - L: Cilindro." << endl
              << " - O: Cono." << endl
              << " - E: Esfera." << endl
              << "Q para salir al menú principal." << endl;
         break;

      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu = SELVISUALIZACION;
         cout << "Modo selección de visualización. Opciones: " << endl
              << " - P: Visualizar puntos." << endl
              << " - L: Visualizar líneas." << endl
              << " - S: Visualizar sólidos." << endl
              << " - A: Visualizar modo ajedrez." << endl
              << " - T: Visualizar tapas." << endl
              << " - I: Visualizar iluminación." << endl
              << "Q para salir al menú principal." << endl;
         break;

      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu = SELDIBUJADO;
         cout << "Modo selección de dibujado. Opciones: " << endl
              << " - 8: Dibujado inmediato." << endl
              << " - 9: Dibujado diferido." << endl
              << "Q para salir al menú principal." << endl;
         break;
   }

   // Modo selección de objeto
   switch (toupper(tecla)){
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

      case 'P' :
         if (modoMenu == SELOBJETO){
            peonVisible = !peonVisible;
            cout << "Objeto: Peon" << endl;
         }
         break;

      case 'L' :
         if (modoMenu == SELOBJETO){
            cilindroVisible = !cilindroVisible;
            cout << "Objeto: Cilindro" << endl;
         }
         break;

      case 'O' :
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
   }

   // Modo selección de modo de visualización
   switch (toupper(tecla)){
      case 'P' :
         // PUNTOS
         if (modoMenu == SELVISUALIZACION){
            puntosVisible = !puntosVisible;
            iluminado = false;
            cout << "Modo de visualización: puntos" << endl;
         }
         break;

      case 'L' :
         // LINEAS
         if (modoMenu == SELVISUALIZACION){
            lineasVisible = !lineasVisible;
            iluminado = false;
            cout << "Modo de visualización: líneas" << endl;
         }
         break;

      case 'S' :
         // SÓLIDO
         if (modoMenu == SELVISUALIZACION){
            solidoVisible = !solidoVisible;
            iluminado = false;
            cout << "Modo de visualización: sólido" << endl;
         }
         break;

      case 'A' :
         // AJEDREZ
         if (modoMenu == SELVISUALIZACION){
            modoDibujado = AJEDREZ;
            ajedrezVisible = !ajedrezVisible;
            iluminado = false;
            if (!ajedrezVisible)
               modoDibujado = INMEDIATO; // Inmediato por defecto
            cout << "Modo de visualización: ajedrez" << endl;
         }
         break;

      case 'T' :
         if (modoMenu == SELVISUALIZACION){
            cout << "Modo de visualización: tapas." << endl;

            // Dibujar tapas
            if (tapasVisible){
               eliminaTapas();
            }
            else{
               dibujaTapas();
            }

            tapasVisible = !tapasVisible;
         }
         break;

      case 'I' :
         if (modoMenu == SELVISUALIZACION){
            modoMenu = ILUMINACION;
            iluminado = true;
            solidoVisible = true;
            puntosVisible = false;
            lineasVisible = false;
            cout << "Modo de visualización: iluminación. Opciones: " << endl
                 << " - 0 al 7: Activar distintas luces." << endl
                 << " - A: Modo variación del ángulo alpha." << endl
                 << " - B: Modo variación del ángulo beta." << endl
                 << " - F: Modo de iluminación FLAT o SMOOTH" << endl
                 << "Q para salir al menú principal." << endl;
         }
         break;
   }

   // Modo iluminación
   switch (toupper(tecla)){
      case '0' :
         if (modoMenu == ILUMINACION){
            cout << "Luz 0 activada: posicional" << endl;
            luzposicional->activar();
         }
         break;

      case '1' :
         if (modoMenu == ILUMINACION){
            cout << "Luz 1 activada: direccional" << endl;
            luzdireccional->activar();
         }
         break;

      case 'A' :
         if (modoMenu == ILUMINACION){
            anguloAlpha = !anguloAlpha;
            cout << "Modo de iluminación: variación del ángulo alpha. Opciones: " << endl
                 << " - >: Incrementa el ángulo." << endl
                 << " - <: Decrementa el ángulo." << endl
                 << "Q para salir al menú principal." << endl;
         }
         break;

      case 'B' :
         if (modoMenu == ILUMINACION){
            anguloBeta = !anguloBeta;
            cout << "Modo de iluminación: variación del ángulo beta. Opciones: " << endl
                 << " - >: Incrementa el ángulo." << endl
                 << " - <: Decrementa el ángulo." << endl
                 << "Q para salir al menú principal." << endl;
         }
         break;

      case '>' :
         if (anguloAlpha){
            luzdireccional->variarAnguloAlpha(10);
         }
         else if (anguloBeta){
            luzdireccional->variarAnguloBeta(10);
         }
         cout << "Aumentando ángulo alpha" << endl;
         break;

      case '<' :
         if (anguloAlpha){
            luzdireccional->variarAnguloAlpha(-10);
         }
         else if (anguloBeta){
            luzdireccional->variarAnguloBeta(-10);
         }
         cout << "Aumentando ángulo beta" << endl;
         break;

      case 'F' :
         modoIluminacion = !modoIluminacion;
         if (modoIluminacion)
            cout << "Modo de iluminación: FLAT.";
         else
            cout << "Modo de iluminación: SMOOTH.";
         break;
   }

   // Modo selección de dibujado
   switch(toupper(tecla)){
      case '8' :
         if (modoMenu == SELDIBUJADO){
            modoDibujado = INMEDIATO;
            cout << "Modo de dibujado: inmediato" << endl;
         }
         break;

      case '9' :
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
