// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: Malla3D.h
// Declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

typedef enum{
   PUNTOS, LINEAS, SOLIDO, DIFERIDO, INMEDIATO, AJEDREZ, SELECCION
} dibujado;

typedef enum{
   ROJO, AZUL, VERDE, AMARILLO, TEXTURA,
   SEL1, SEL2, SEL3, SEL4, SEL5, SEL6, SEL7, SEL8, SEL9
} color;

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

// Colores
const Tupla3f colorRojo = {1.0, 0.0, 0.0};
const Tupla3f colorAzul = {0.0, 0.0, 1.0};
const Tupla3f colorVerde = {0.0, 0.8, 0.0};
const Tupla3f colorAmarillo = {1.0, 0.8, 0.0};
const Tupla3f colorTextura = {0.9, 0.9, 0.9};
// Colores para el modo seleccion
const Tupla3f colorSel1 = {1.0, 0.0, 0.0};
const Tupla3f colorSel2 = {0.0, 1.0, 0.0};
const Tupla3f colorSel3 = {0.0, 0.0, 1.0};
const Tupla3f colorSel4 = {0.0, 1.0, 1.0};
const Tupla3f colorSel5 = {1.0, 0.0, 1.0};
const Tupla3f colorSel6 = {1.0, 1.0, 0.0};
const Tupla3f colorSel7 = {0.1, 0.2, 0.3};
const Tupla3f colorSel8 = {0.0, 0.0, 0.0};
const Tupla3f colorSel9 = {0.9, 0.9, 0.9};

class Malla3D{
public:
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(dibujado modoVisual);

   // crea un VBO (Virtual Buffer Object)
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);
   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(dibujado modoVisual);

   // dibuja el objeto en modo inmediato y ajedrez
   void draw_ModoAjedrez();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   // o bien a draw_ModoAjedrez (modo ajedrez con inmediato)
   void draw(dibujado modoVisual, dibujado modoDibuj, bool modoIluminacion);

   // Asigna colores especificos para el modo selección
   virtual void setColorSeleccion(color col);

protected:
   virtual void dibujarElementos(); // Realiza un glDrawElements
   virtual void dibujarCarasPares(); // Realiza un glDrawElements de las caras pares (ajedrez)
   virtual void dibujarCarasImpares(); // Realiza un glDrawElements de las caras impares (ajedrez)
   void calcularColores(color col_inm, dibujado modoVisual); // Calcula las tablas de colores
   void calcularModoAjedrez();      // Calcula los colores de las caras para el modo ajedrez
   void calcular_normales();        // calcula tabla de normales de vértices (práctica 3)
   void setMaterial(Material mat);
   void setTextura(std::string archivo);

   // Geometría y topología
   std::vector<Tupla3f> v;    // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f;    // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f_par;      // Tabla de triángulos pares (modo ajedrez)
   std::vector<Tupla3i> f_impar;    // Tabla de triángulos impares (modo ajedrez)

   // Tabla de colores de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3f> c;       // Color sólido modo inmediato (par en ajedrez)
   std::vector<Tupla3f> c_dif;   // Color sólido modo diferido (impar en ajedrez)
   std::vector<Tupla3f> c_vert;  // Color de los vértices
   std::vector<Tupla3f> c_arist; // Color de las aristas
   std::vector<Tupla3f> c_selec; // Color para las selecciones

   // Normales
   std::vector<Tupla3f> nf;   // tabla de normales de las caras
   std::vector<Tupla3f> nv;   // tabla de normales de los vértices
   int numNormalesCaras;      // Número total de normales en las caras
   int numNormalesVertices;   // Número total de normales en los vértices
   int numVertices;           // Número total de vértices de la figura
   int numTriangulos;         // Número total de triángulos de la figura

   // Texturas
   Textura * textura = nullptr;

   // Tabla de coordenadas de texturas
   std::vector<Tupla2f> ct;   // Asocia coordenadas de textura a cada vértice

   // Material
   Material m;

   // Tipos de materiales (reflectividad difusa, especular y ambiente)
   std::vector<Tupla4f> esmeralda = {{0.07568, 0.61424, 0.07568, 1.0}, {0.633, 0.727811, 0.633, 1.0}, {0.0215, 0.1745, 0.0215, 1.0}};
   float esmeralda_brillo = 0.6;
   std::vector<Tupla4f> jade = {{0.54, 0.89, 0.63, 1.0}, {0.316228, 0.316228, 0.316228, 1.0}, {0.135, 0.2225, 0.1575, 1.0}};
   float jade_brillo = 0.1;
   std::vector<Tupla4f> obsidiana = {{0.18275, 0.17, 0.22525, 1.0}, {0.332741, 0.328634, 0.346435, 1.0}, {0.05375, 0.05, 0.06625, 1.0}};
   float obsidiana_brillo = 0.3;
   std::vector<Tupla4f> cyanplastico = {{0.0, 0.50980392, 0.50980392, 1.0}, {0.50196078, 0.50196078, 0.50196078, 1.0}, {0.0, 0.1, 0.06, 1.0}};
   float cyanplastico_brillo = 0.25;
   std::vector<Tupla4f> blanco = {{0.0, 0.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}};
   float blanco_brillo = 0.25;
   std::vector<Tupla4f> amarillo = {{0.5, 0.5, 0.0, 1.0}, {0.6, 0.6, 0.5, 1.0}, {0.0, 0.0, 0.0, 1.0}};
   float amarillo_brillo = 0.25;

   // Identificadores de VBOs, ambos inicialmente a 0 (VBO no creados)
   GLuint id_vbo_ver = 0;  // Identificador para el VBO de tabla de vértices
   GLuint id_vbo_tri = 0;  // Identificador para el VBO de tabla de triángulos
};

#endif
