// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: objrevolucion.h
//
// Jose Luis Gallego Peña
//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

class ObjRevolucion : public Malla3D{
public:
   // Constructores
   ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, char eje_rotacion='Y');
   ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, char eje_rotacion='Y');

   // Añade las tapas al objeto de revolución (1 o 2 tapas)
   void crearTapas();
   // Elimina las tapas del objeto de revolución (1 o 2 tapas)
   void eliminarTapas();

   bool getTapaInf();
   bool getTapaSup();

   char eje;               // Eje por el cual está rotado el objeto

   const float PI = atan(1)*4.0;	// Número pi

protected:
   // Realiza un glDrawElements según tapas
   void dibujarElementos() override;
   void dibujarCarasPares() override;
   void dibujarCarasImpares() override;
   // Crea la malla del objeto de revolución con NM vértices
   void crearMalla(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_inf, bool tapa_sup, char eje_rotacion);
   // Crear las tapas del objeto de revolución
   void crearTapaInf(char eje_rotacion);
   void crearTapaSup(char eje_rotacion);
   // Eliminar las tapas del objeto de revolución
   void eliminarTapaInf(char eje_rotacion);
   void eliminarTapaSup(char eje_rotacion);

   // Calcula las coordenadas de textura para un objeto de revolucion cilindro
   void calcularTexturas();

   int numInstancias;      // Número total de réplicas rotadas (N)
   int numVerticesPerfil;  // Número total de vértices en el perfil original (M)
   bool tapaSup = true;    // El objeto tiene tapa superior
   bool tapaInf = true;    // El objeto tiene tapa inferior
   std::vector<float> distanciasPerfil;   // Calculo de las distancias en el perfil para coordenadas textura
};

#endif
