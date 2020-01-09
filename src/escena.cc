
#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
using namespace std;
//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena(){
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Xraton = 0.0;
    Yraton = 0.0;

    ejes.changeAxisSize(5000);

    // Crear los objetos de la escena
    cubo = new Cubo(50.0);                                       // Cubo(lado)
    tetraedro = new Tetraedro(50.0);                             // Tetraedro(lado)
    peon = new ObjRevolucion("plys/peon.ply", 20.0);             // Peon(perfil.ply, num_instancias)
    puertaMagica = new ObjPLY("plys/puerta_magica.ply");         // Puerta Mágica(ant.ply)
    cilindro = new Cilindro(50.0, 20.0, 20.0);                       // Cilindro(altura, radio, num_instancias)
    cono = new Cono(20.0, 20.0, 20.0);                               // Cono(altura, radio, num_instancias)
    esfera = new Esfera(20.0, 20.0, 20.0);                           // Esfera(radio, num_instancias, num_vert_perfil)
    doraemon = new Doraemon();
    lienzo = new Lienzo(50.0);

    // Crear las luces de la escena
    luzposicional = new LuzPosicional({100.0, 100.0, 100.0}, GL_LIGHT0, {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});
    luzdireccional = new LuzDireccional({0.0, 100.0, 100.0}, GL_LIGHT1, {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});

    // Crear las cámaras de la escena
    camaras.push_back(Camara({0.0, 100.0, 300.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, -100.0, 100.0, -100.0, 100.0, 100.0, 2000.0, PERSPECTIVA));
    camaras.push_back(Camara({-100.0, 150.0, 150.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, -100.0, 100.0, -100.0, 100.0, 100.0, 2000.0, ORTOGONAL));
    camaras.push_back(Camara({0.0, 100.0, -300.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, -1000.0, 1000.0, -1000.0, 1000.0, 100.0, 2000.0, PERSPECTIVA));

    // Asignar colores de selección a los objetos de la escena
    cubo->setColorSeleccion(SEL1);
    tetraedro->setColorSeleccion(SEL2);
    peon->setColorSeleccion(SEL3);
    puertaMagica->setColorSeleccion(SEL4);
    cilindro->setColorSeleccion(SEL5);
    cono->setColorSeleccion(SEL6);
    esfera->setColorSeleccion(SEL7);
    doraemon->setColorSeleccion(SEL8);
    lienzo->setColorSeleccion(SEL9);
}

//**************************************************************************
// destructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::~Escena(){
   delete cubo;
   delete tetraedro;
   delete peon;
   delete puertaMagica;
   delete cilindro;
   delete cono;
   delete esfera;
   delete doraemon;
   delete luzposicional;
   delete luzdireccional;
   delete lienzo;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height){
	glClearColor(1.0, 1.0, 1.0, 1.0);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);   // Se habilita el z-bufer
   glEnable(GL_CULL_FACE);    // Se habilita el cull face
   glEnable(GL_NORMALIZE);    // Normales invariantes a transformaciones geométricas

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

void Escena::eligeObjetos(dibujado modoVisual, dibujado modoDibuj, objetoEscena obj){
   if (obj == CUBO){
      if (cubo != nullptr && cuboVisible){
         cubo->draw(modoVisual, modoDibuj, modoIluminacion);

         if (modoVisual == SELECCION)
            cubo->calcularCentro(m_vista);
      }
   }
   else if (obj == TETRAEDRO){
      if (tetraedro != nullptr && tetraedroVisible){
         tetraedro->draw(modoVisual, modoDibuj, modoIluminacion);

         if (modoVisual == SELECCION)
            tetraedro->calcularCentro(m_vista);
      }
   }
   else if (obj == PEON){
      if (peon != nullptr && peonVisible){
         peon->draw(modoVisual, modoDibuj, modoIluminacion);

         if (modoVisual == SELECCION)
            peon->calcularCentro(m_vista);
      }
   }
   else if (obj == PUERTAMAGICA){
      if (puertaMagica != nullptr && puertaMagicaVisible){
         puertaMagica->draw(modoVisual, modoDibuj, modoIluminacion);

         if (modoVisual == SELECCION)
            puertaMagica->calcularCentro(m_vista);
      }
   }
   else if (obj == CILINDRO){
      if (cilindro != nullptr && cilindroVisible){
         cilindro->draw(modoVisual, modoDibuj, modoIluminacion);

         if (modoVisual == SELECCION)
            cilindro->calcularCentro(m_vista);
      }
   }
   else if (obj == CONO){
      if (cono != nullptr && conoVisible){
         cono->draw(modoVisual, modoDibuj, modoIluminacion);

         if (modoVisual == SELECCION)
            cono->calcularCentro(m_vista);
      }
   }
   else if (obj == ESFERA){
      if (esfera != nullptr && esferaVisible){
         esfera->draw(modoVisual, modoDibuj, modoIluminacion);

         if (modoVisual == SELECCION)
            esfera->calcularCentro(m_vista);
      }
   }
   else if (obj == DORAEMON){
      if (doraemon != nullptr && doraemonVisible){
         doraemon->draw(modoVisual, modoDibuj, modoIluminacion);

         if (modoVisual == SELECCION)
            doraemon->calcularCentro(m_vista);
      }
   }
   else if (obj == LIENZO){
      if (lienzo != nullptr && lienzoVisible){
         lienzo->draw(modoVisual, modoDibuj, modoIluminacion);

         if (modoVisual == SELECCION)
            lienzo->calcularCentro(m_vista);
      }
   }
}

void Escena::dibujaObjetos(dibujado modoDibuj, objetoEscena obj){
   // Modo ajedrez
   if (ajedrezVisible){
      glPolygonMode(GL_FRONT, GL_FILL);
      eligeObjetos(SOLIDO, modoDibuj, obj);
   }
   // Otros modos (no ajedrez)
   else{
      // Dibujar modo selección
      if (seleccionVisible){
         glPolygonMode(GL_FRONT, GL_FILL);
         eligeObjetos(SELECCION, modoDibuj, obj);
      }
      else {
         if (camaras[camaraActiva].getObjetoSelec() == obj){
            glPolygonMode(GL_FRONT, GL_FILL);
            eligeObjetos(SELECCIONADO, modoDibuj, obj);
         }
         else{
            // Dibujar puntos
            if (puntosVisible){
               glPolygonMode(GL_FRONT, GL_POINT);
               glPointSize(5);   // Puntos más gordos para que se vean bien
               eligeObjetos(PUNTOS, modoDibuj, obj);
            }

            // Dibujar líneas
            if (lineasVisible){
               glPolygonMode(GL_FRONT, GL_LINE);
               eligeObjetos(LINEAS, modoDibuj, obj);
            }

            // Dibujar sólidos
            if (solidoVisible){
               glPolygonMode(GL_FRONT, GL_FILL);
               eligeObjetos(SOLIDO, modoDibuj, obj);
            }
         }
      }
   }
}

void Escena::posicionaObjetos(){
   // Cubo
	glPushMatrix();
      glScalef(1.0, 1.0, 1.0);
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
      glTranslatef(-7.5, 5.0, 0.0);
      dibujaObjetos(modoDibujado, PEON);
   glPopMatrix();

   // Puerta Mágica
   glPushMatrix();
      glScalef(15.0, 15.0, 15.0);
      glRotatef(90, 0, 1, 0);
      glTranslatef(0.0, 1.2, -2.4);
      dibujaObjetos(modoDibujado, PUERTAMAGICA);
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
      glTranslatef(-50.0, 60.0, 0.0);
      dibujaObjetos(modoDibujado, CONO);
   glPopMatrix();

   // Esfera
   glPushMatrix();
      glScalef(2.0, 2.0, 2.0);
      glTranslatef(-100.0, 150.0, 0.0);
      dibujaObjetos(modoDibujado, ESFERA);
   glPopMatrix();

   // Modelo jerárquico
   glPushMatrix();
      dibujaObjetos(modoDibujado, DORAEMON);
   glPopMatrix();

   // Lienzo
   glPushMatrix();
      glScalef(10.0, 10.0, 10.0);
      glRotatef(-90.0, 1.0, 0.0, 0.0);
      glTranslatef(-25.0, -25.0, -0.5);
      dibujaObjetos(modoDibujado, LIENZO);
   glPopMatrix();
}

void Escena::eliminaTapas(){
   if (peon != nullptr)
      peon->eliminarTapas();

   if (cilindro != nullptr)
      cilindro->eliminarTapas();

   if (cono != nullptr)
      cono->eliminarTapas();

   if (esfera != nullptr)
      esfera->eliminarTapas();
}

void Escena::dibujaTapas(){
   if (peon != nullptr)
      peon->crearTapas();

   if (cilindro != nullptr)
      cilindro->crearTapas();

   if (cono != nullptr)
      cono->crearTapas();

   if (esfera != nullptr)
      esfera->crearTapas();
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

	// Dibujar y posicionar todos los objetos de la escena
   posicionaObjetos();

   if (luzposicionalVisible){
      glPushMatrix();
         glRotatef(luzposicional->giroLuz, 0.0, 1.0, 0.0);
         luzposicional->activar();
      glPopMatrix();
   }
   else{
      luzposicional->desactivar();
   }

   if (luzdireccionalVisible){
      luzdireccional->activar();
   }
   else{
      luzdireccional->desactivar();
   }
}

void Escena::dibujaSeleccion(){
   glDisable(GL_DITHER);   // Deshabilita el degradado para tener colores homogeneos
   glDisable(GL_LIGHTING); // Deshabilita luces
   glDisable(GL_TEXTURE_2D);  // Deshabilita texturas

   seleccionVisible = true;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
	change_observer();

   // Un color para cada objeto
   posicionaObjetos();

   glEnable(GL_DITHER);
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);

   seleccionVisible = false;
}

void Escena::objetoSeleccionado(GLfloat * pixeles){
   Tupla3f p;
   for (int i = 0 ; i <= 2 ; i++)
      p(i) = pixeles[i];

   if (comparaColores(p, colorSel1)){
      cout << "Objeto seleccionado: Cubo" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != CUBO){
         enfocarObjeto(CUBO);
         camaras[camaraActiva].setObjetoSelec(CUBO);
      }
   }
   else if (comparaColores(p, colorSel2)){
      cout << "Objeto seleccionado: Tetraedro" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != TETRAEDRO){
         enfocarObjeto(TETRAEDRO);
         camaras[camaraActiva].setObjetoSelec(TETRAEDRO);
      }
   }
   else if (comparaColores(p, colorSel3)){
      cout << "Objeto seleccionado: Peon" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != PEON){
         enfocarObjeto(PEON);
         camaras[camaraActiva].setObjetoSelec(PEON);
      }
   }
   else if (comparaColores(p, colorSel4)){
      cout << "Objeto seleccionado: Puerta Mágica" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != PUERTAMAGICA){
         enfocarObjeto(PUERTAMAGICA);
         camaras[camaraActiva].setObjetoSelec(PUERTAMAGICA);
      }
   }
   else if (comparaColores(p, colorSel5)){
      cout << "Objeto seleccionado: Cilindro" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != CILINDRO){
         enfocarObjeto(CILINDRO);
         camaras[camaraActiva].setObjetoSelec(CILINDRO);
      }
   }
   else if (comparaColores(p, colorSel6)){
      cout << "Objeto seleccionado: Cono" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != CONO){
         enfocarObjeto(CONO);
         camaras[camaraActiva].setObjetoSelec(CONO);
      }
   }
   else if (comparaColores(p, colorSel7)){
      cout << "Objeto seleccionado: Esfera" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != ESFERA){
         enfocarObjeto(ESFERA);
         camaras[camaraActiva].setObjetoSelec(ESFERA);
      }
   }
   else if (comparaColores(p, colorSel8)){
      cout << "Objeto seleccionado: Doraemon" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != DORAEMON){
         enfocarObjeto(DORAEMON);
         camaras[camaraActiva].setObjetoSelec(DORAEMON);
      }
   }
   else if (comparaColores(p, colorSel9)){
      cout << "Objeto seleccionado: Lienzo" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != LIENZO){
         enfocarObjeto(LIENZO);
         camaras[camaraActiva].setObjetoSelec(LIENZO);
      }
   }
   else{
      // No enfocar ningún objeto: enfocar el origen de coordenadas
      cout << "Objeto seleccionado: Fondo (deselecciona cualquier objeto)." << endl;
      enfocarObjeto(NINGUNO);
      camaras[camaraActiva].setObjetoSelec(NINGUNO);
      estadoR = MOVIENDO_CAMARA_FIRSTPERSON;
   }
}


bool Escena::comparaColores(Tupla3f c1, Tupla3f c2){
   // Comparar tuplas3f de colores, si su diferencia es menor que un pequeño error, son el mismo color
   return (fabs(c1(X) - c2(X)) < 0.003) && (fabs(c1(Y) - c2(Y)) < 0.003) && (fabs(c1(Z) - c2(Z)) < 0.003);
}

// **************************************************************************
//
// función de animación del modelo jerárquico en la escena
//
// **************************************************************************

void Escena::animarModeloJerarquico(){
   if (animarModelo){
      if (controlarValor == '+'){
         doraemon->aumentarVelocidad();
      }
      else if (controlarValor == '-'){
         doraemon->disminuirVelocidad();
      }
      else{
         doraemon->animar();
      }

      luzposicional->animar();

      controlarValor = '=';
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y){
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir = false;

   // Menús
   switch(toupper(tecla)){
      case 'Q' :
         if (modoMenu == SELOBJETO || modoMenu == SELVISUALIZACION || modoMenu == SELDIBUJADO || modoMenu == SELCAMARA || modoMenu == JERARQUICOAUTOMATICO || modoMenu == JERARQUICOMANUAL){
            modoMenu = NADA;
            cout << "Menú principal. Opciones: " << endl
                 << " - O: Selección de objeto." << endl
                 << " - V: Selección de visualización." << endl
                 << " - D: Selección de dibujado." << endl
                 << " - A: Animación automática de los objetos de la escena." << endl
                 << " - M: Animación manual del modelo jerárquico." << endl
                 << " - C: Selección de cámara" << endl
                 << "Q para salir del programa." << endl;
         }
         else if (modoMenu == ILUMINACION){
            modoMenu = SELVISUALIZACION;
            cout << "Modo selección de visualización. Opciones: " << endl
                 << " - P: Visualizar puntos." << endl
                 << " - L: Visualizar líneas." << endl
                 << " - S: Visualizar sólidos." << endl
                 << " - A: Visualizar modo ajedrez." << endl
                 << " - T: Visualizar tapas." << endl
                 << " - I: Visualizar iluminación." << endl
                 << "Q para salir al menú principal." << endl;
         }
         else if (modoMenu == NADA){
            salir = true;
            cout << "Cerrando programa" << endl;
         }
         break;
   }

   if (modoMenu == NADA){
      switch (toupper(tecla)){
         case 'O' :
            // ESTAMOS EN MODO SELECCION DE OBJETO
            modoMenu = SELOBJETO;
            cout << "Modo selección de objeto. Opciones: " << endl
                 << " - C: Cubo." << endl
                 << " - T: Tetraedro." << endl
                 << " - P: Peon." << endl
                 << " - M: Puerta Mágica." << endl
                 << " - L: Cilindro." << endl
                 << " - O: Cono." << endl
                 << " - E: Esfera." << endl
                 << " - J: Doraemon (Modelo jerárquico)." << endl
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
                 << " - 1: Dibujado inmediato." << endl
                 << " - 2: Dibujado diferido." << endl
                 << "Q para salir al menú principal." << endl;
            break;

         case 'A' :
            modoMenu = JERARQUICOAUTOMATICO;
            animarModelo = !animarModelo;
            cout << "Modo animación automática de los objetos de la escena. Opciones: " << endl
                 << "- +: Aumenta la velocidad de la animación." << endl
                 << "- -: Disminuye la velocidad de la animación." << endl
                 << "Q para salir al menú principal." << endl;
            break;

         case 'M' :
            modoMenu = JERARQUICOMANUAL;
            animarModelo = false;
            cout << "Modo animación manual del grado de libertad del objeto jerárquico. Opciones: " << endl
                 << " - 0: Seleccionar grado de libertad 0 (giro brazo derecho)." << endl
                 << " - 1: Seleccionar grado de libertad 1 (giro brazo izquierdo)." << endl
                 << " - 2: Seleccionar grado de libertad 2 (giro cabeza)." << endl
                 << " - 3: Seleccionar grado de libertad 3 (longitud cola)." << endl
                 << " - +: Aumentar el valor del grado de libertad seleccionado." << endl
                 << " - -: Disminuir el valor del grado de libertad seleccionado." << endl
                 << "Q para salir al menú principal." << endl;
            break;

         case 'C' :
            modoMenu = SELCAMARA;
            cout << "Modo selección de cámara. Opciones: " << endl
                 << " - 0: Seleccionar cámara 0 (Perspectiva)." << endl
                 << " - 1: Seleccionar cámara 1 (Ortogonal)." << endl
                 << " - 2: Seleccionar cámara 2 (Perspectiva)." << endl
                 << "Q para salir al menú principal." << endl;
      }
      tecla = 0;
   }

   // Modo selección de objeto
   if (modoMenu == SELOBJETO){
      switch (toupper(tecla)){
         case 'C' :
            cuboVisible = !cuboVisible;
            cout << "Objeto: Cubo" << endl;
            break;

         case 'T' :
            tetraedroVisible = !tetraedroVisible;
            cout << "Objeto: Tetraedro" << endl;
            break;

         case 'P' :
            peonVisible = !peonVisible;
            cout << "Objeto: Peon (PLY revolucionado)" << endl;
            break;

         case 'M' :
            puertaMagicaVisible = !puertaMagicaVisible;
            cout << "Objeto: Puerta Magica (PLY)" << endl;
            break;

         case 'L' :
            cilindroVisible = !cilindroVisible;
            cout << "Objeto: Cilindro" << endl;
            break;

         case 'O' :
            conoVisible = !conoVisible;
            cout << "Objeto: Cono" << endl;
            break;

         case 'E' :
            esferaVisible = !esferaVisible;
            cout << "Objeto: Esfera" << endl;
            break;

         case 'J' :
            doraemonVisible = !doraemonVisible;
            cout << "Objeto: Doraemon (Modelo jerárquico)" << endl;
            break;
      }
   }

   // Modo selección de modo de visualización
   if (modoMenu == SELVISUALIZACION){
      switch (toupper(tecla)){
         case 'P' :
            // PUNTOS
            puntosVisible = !puntosVisible;
            iluminado = false;
            cout << "Modo de visualización: puntos" << endl;
            break;

         case 'L' :
            // LINEAS
            lineasVisible = !lineasVisible;
            iluminado = false;
            cout << "Modo de visualización: líneas" << endl;
            break;

         case 'S' :
            // SÓLIDO
            solidoVisible = !solidoVisible;
            iluminado = false;
            cout << "Modo de visualización: sólido" << endl;
            break;

         case 'A' :
            // AJEDREZ
            modoDibujado = AJEDREZ;
            ajedrezVisible = !ajedrezVisible;
            iluminado = false;
            if (!ajedrezVisible)
               modoDibujado = INMEDIATO; // Inmediato por defecto
            cout << "Modo de visualización: ajedrez" << endl;
            break;

         case 'T' :
            cout << "Modo de visualización: tapas." << endl;

            // Dibujar tapas
            if (tapasVisible){
               eliminaTapas();
            }
            else{
               dibujaTapas();
            }

            tapasVisible = !tapasVisible;
            break;

         case 'I' :
            modoMenu = ILUMINACION;
            iluminado = !iluminado;
            solidoVisible = true;
            puntosVisible = false;
            lineasVisible = false;
            cout << "Modo de visualización: iluminación. Opciones: " << endl
                 << " - 0 al 7: Activar distintas luces." << endl
                 << " - A: Modo variación del ángulo alpha." << endl
                 << " - B: Modo variación del ángulo beta." << endl
                 << " - F: Modo de iluminación FLAT o SMOOTH" << endl
                 << "Q para salir al menú principal." << endl;
            break;
      }
   }

   // Modo iluminación
   if (modoMenu == ILUMINACION){
      switch (toupper(tecla)){
         case '0' :
            cout << "Luz 0 activada: posicional" << endl;
            if (!luzposicionalVisible){
               luzposicionalVisible = true;
            }
            else{
               luzposicionalVisible = false;
            }
            break;

         case '1' :
            cout << "Luz 1 activada: direccional" << endl;
            if (!luzdireccionalVisible){
               luzdireccionalVisible = true;
            }
            else{
               luzdireccionalVisible = false;
            }
            break;

         case 'A' :
            anguloAlpha = true;
            anguloBeta = false;
            cout << "Modo de iluminación: variación del ángulo alpha. Opciones: " << endl
                 << " - >: Incrementa el ángulo." << endl
                 << " - <: Decrementa el ángulo." << endl
                 << "Q para salir al menú principal." << endl;
            break;

         case 'B' :
            anguloBeta = true;
            anguloAlpha = false;
            cout << "Modo de iluminación: variación del ángulo beta. Opciones: " << endl
                 << " - >: Incrementa el ángulo." << endl
                 << " - <: Decrementa el ángulo." << endl
                 << "Q para salir al menú principal." << endl;
            break;

         case '>' :
            if (anguloAlpha){
               luzdireccional->variarAnguloAlpha(0.1);
               luzdireccional->activar();
               cout << "Aumentando ángulo alpha" << endl;
            }
            else if (anguloBeta){
               luzdireccional->variarAnguloBeta(0.1);
               luzdireccional->activar();
               cout << "Aumentando ángulo beta" << endl;
            }
            break;

         case '<' :
            if (anguloAlpha){
               luzdireccional->variarAnguloAlpha(-0.1);
               luzdireccional->activar();
               cout << "Disminuyendo ángulo alpha" << endl;
            }
            else if (anguloBeta){
               luzdireccional->variarAnguloBeta(-0.1);
               luzdireccional->activar();
               cout << "Disminuyendo ángulo beta" << endl;
            }
            break;

         case 'F' :
            modoIluminacion = !modoIluminacion;
            if (modoIluminacion)
               cout << "Modo de iluminación: FLAT.";
            else
               cout << "Modo de iluminación: SMOOTH.";
            break;
      }
   }

   // Modo de animación automática del modelo jerárquico
   if (modoMenu == JERARQUICOAUTOMATICO){
      switch(toupper(tecla)){
         case '+' :
            controlarValor = '+';
            cout << "Aumentando velocidad" << endl;
            break;

         case '-' :
            controlarValor = '-';
            cout << "Disminuyendo velocidad" << endl;
            break;
      }
   }

   // Modo de animación manual del modelo jearárquico
   if (modoMenu == JERARQUICOMANUAL){
      switch(toupper(tecla)){
         case '0' :
            parte = BRAZODERECHO;
            cout << "Control del grado de libertad 0 (giro brazo derecho)." << endl;
            break;

         case '1' :
            parte = BRAZOIZQUIERDO;
            cout << "Control del grado de libertad 1 (giro brazo izquierdo)." << endl;
            break;

         case '2' :
            parte = CABEZA;
            cout << "Control del grado de libertad 2 (giro cabeza)." << endl;
            break;

         case '3' :
            parte = COLA;
            cout << "Control del grado de libertad 3 (longitud cola)." << endl;
            break;

         case '+' :
            cout << "Aumentando valor del grado de libertad ";
            if (parte == BRAZODERECHO){
               controlarValor = '+';
               doraemon->modificaGiroBrazoDcho(0.5);
               cout << "0 (giro brazo derecho)" << endl;
            }
            else if (parte == BRAZOIZQUIERDO){
               controlarValor = '+';
               doraemon->modificaGiroBrazoIzdo(0.5);
               cout << "1 (giro brazo izquierd)" << endl;
            }
            else if (parte == CABEZA){
               controlarValor = '+';
               doraemon->modificaGiroCabeza(1.0);
               cout << "2 (giro cabeza)" << endl;
            }
            else if (parte == COLA){
               controlarValor = '+';
               doraemon->modificaLongitudCola(-0.5);
               cout << "3 (longitud cola)" << endl;
            }
            break;

         case '-' :
            cout << "Disminuyendo valor del grado de libertad ";
            if (parte == BRAZODERECHO){
               controlarValor = '-';
               doraemon->modificaGiroBrazoDcho(-0.5);
               cout << "0 (giro brazo derecho)" << endl;
            }
            else if (parte == BRAZOIZQUIERDO){
               controlarValor = '-';
               doraemon->modificaGiroBrazoIzdo(-0.5);
               cout << "1 (giro brazo izquierdo)" << endl;
            }
            else if (parte == CABEZA){
               controlarValor = '-';
               doraemon->modificaGiroCabeza(-1.0);
               cout << "2 (giro cabeza)" << endl;
            }
            else if (parte == COLA){
               controlarValor = '-';
               doraemon->modificaLongitudCola(0.5);
               cout << "3 (longitud cola)" << endl;
            }
            break;
      }
   }

   // Modo selección de dibujado
   if (modoMenu == SELDIBUJADO){
      switch(toupper(tecla)){
         case '1' :
            modoDibujado = INMEDIATO;
            cout << "Modo de dibujado: inmediato." << endl;
            break;

         case '2' :
            modoDibujado = DIFERIDO;
            cout << "Modo de dibujado: diferido." << endl;
            break;
      }
   }

   // Modo selección de cámara
   if (modoMenu == SELCAMARA){
      switch (toupper(tecla)){
         case '0' :
            camaraActiva = 0;
            cout << "Cámara 0 seleccionada (Perspectiva)." << endl;
            break;

         case '1' :
            camaraActiva = 1;
            cout << "Cámara 1 seleccionada (Ortogonal)." << endl;
            break;

         case '2':
            camaraActiva = 2;
            cout << "Cámara 2 seleccionada (Perspectiva)." << endl;
            break;
      }

      change_observer();
      change_projection(1);
   }

   return salir;
}

//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y){
   switch (Tecla1){
	   case GLUT_KEY_LEFT:
         camaras[camaraActiva].rotarYExaminar(-0.1);
         break;

	   case GLUT_KEY_RIGHT:
         camaras[camaraActiva].rotarYExaminar(0.1);
         break;

	   case GLUT_KEY_UP:
         camaras[camaraActiva].rotarXExaminar(0.1);
         break;

	   case GLUT_KEY_DOWN:
         camaras[camaraActiva].rotarXExaminar(-0.1);
         break;

	   case GLUT_KEY_PAGE_UP:
         camaras[camaraActiva].zoom(0.9);
         change_projection(1);
         break;

	   case GLUT_KEY_PAGE_DOWN:
         camaras[camaraActiva].zoom(1.1);
         change_projection(1);
         break;

      case 3:
         camaras[camaraActiva].zoom(0.9);
         change_projection(1);
         break;

      case 4:
         camaras[camaraActiva].zoom(1.1);
         change_projection(1);
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************

void Escena::ratonMovido(int x, int y){
   if (estadoR == MOVIENDO_CAMARA_FIRSTPERSON && camaras[camaraActiva].getObjetoSelec() == NINGUNO){
      camaras[camaraActiva].girar(x - Xraton, y - Yraton);
   }
   else if (estadoR == MOVIENDO_CAMARA_EXAMINAR && camaras[camaraActiva].getObjetoSelec() != NINGUNO){
      camaras[camaraActiva].rotarXExaminar((y - Yraton)*(PI/180.0));
      camaras[camaraActiva].rotarYExaminar((x - Xraton)*(PI/180.0));
   }

   Xraton = x;
   Yraton = y;
}

void Escena::clickRaton(int boton, int estado, int x, int y){
   // Click derecho del ratón para mover la cámara en primera persona
	if (boton == GLUT_RIGHT_BUTTON){
		actualizarPosicionRaton(x, y);

		// Se pulsa el botón, por lo que se entra en el estado "moviendo cámara"
		if (estado == GLUT_DOWN){
 			actualizarEstadoRaton(MOVIENDO_CAMARA_FIRSTPERSON);

         if (camaras[camaraActiva].getObjetoSelec() != NINGUNO)
            actualizarEstadoRaton(MOVIENDO_CAMARA_EXAMINAR);
		}
		// Se levanta el botón, por lo que se sale del estado "moviendo cámara"
		else if (estado == GLUT_UP){
			actualizarEstadoRaton(QUIETA);
		}
	}
	// Click izquierdo del raton selecciona objetos
	else if (boton == GLUT_LEFT_BUTTON){
		if (estado == GLUT_DOWN){
         dibujaSeleccion();

   		// Leer el pixel dado por la función gestora del evento de ratón
   		GLint viewport[4];
   		GLfloat pixeles[3];
   		glGetIntegerv(GL_VIEWPORT, viewport);
   		glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_FLOAT, (void *)pixeles);

   		// Averiguar a qué objeto hemos asignado el color de dicho píxel
   		objetoSeleccionado(pixeles);
      }
	}
	// Scroll del raton
	else if (boton == 3 || boton == 4){
		teclaEspecial(boton, x, y);
	}
}

void Escena::enfocarObjeto(objetoEscena obj){
   // Si no se ha seleccionado ningun objeto, se selecciona el origen
   Tupla3f enfoque = {0, 0, 0};

   if (obj == CUBO){
      enfoque = cubo->getCentro();
   }
   else if (obj == TETRAEDRO){
      enfoque = tetraedro->getCentro();
   }
   else if (obj == PEON){
      enfoque = peon->getCentro();
   }
   else if (obj == PUERTAMAGICA){
      enfoque = puertaMagica->getCentro();
   }
   else if (obj == CILINDRO){
      enfoque = cilindro->getCentro();
   }
   else if (obj == CONO){
      enfoque = cono->getCentro();
   }
   else if (obj == ESFERA){
      enfoque = esfera->getCentro();
   }
   else if (obj == DORAEMON){
      //enfoque = doraemon->getCentro();
   }
   else if (obj == LIENZO){
      enfoque = lienzo->getCentro();
   }

   // Cambiar el at y poner nuevo observador
   camaras[camaraActiva].setAt(enfoque);
}

//**************************************************************************

void Escena::actualizarPosicionRaton(int x, int y){
	Xraton = x;
	Yraton = y;
}

void Escena::actualizarEstadoRaton(estadoRaton estado){
   estadoR = estado;
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
   camaras[camaraActiva].setProyeccion();
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight){
   // Cambiar left y right para adaptarse a la redimensión de la ventana (en todas las cámaras)
   float ratio = float(newWidth/10.0) / float(newHeight/10.0);
   for (int i = 0 ; i < camaras.size() ; i++){
      camaras[i].setRight(camaras[i].getTop() * ratio);
      camaras[i].setLeft(camaras[i].getBottom() * ratio);
   }

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
   camaras[camaraActiva].setObserver();
   glGetFloatv(GL_MODELVIEW_MATRIX, m_vista);
}
