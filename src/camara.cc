#include "camara.h"

Camara::Camara(Tupla3f e, Tupla3f a, Tupla3f u, float l, float r, float b, float t, float n, float f, TipoCamara tip){
   eye = e;
   at = a;
   up = u;
   left = l;
   right = r;
   bottom = b;
   top = t;
   near = n;
   far = f;
   tipo = tip;
}

void Camara::rotarXExaminar(float angle){
   float x = eye(X) - at(X);
   float y = cos(angle) * (eye(Y) - at(Y)) - sin(angle) * (eye(Z) - at(Z));
   float z = sin(angle) * (eye(Y) - at(Y)) + cos(angle) * (eye(Z) - at(Z));

   eye(X) = x + at(X);
   eye(Y) = y + at(Y);
   eye(Z) = z + at(Z);
}

void Camara::rotarYExaminar(float angle){
   float x = cos(angle) * (eye(X) - at(X)) + sin(angle) * (eye(Z) - at(Z));
   float y = eye(Y) - at(Y);
   float z = -sin(angle) * (eye(X) - at(X)) + cos(angle) * (eye(Z) - at(Z));

   eye(X) = x + at(X);
   eye(Y) = y + at(Y);
   eye(Z) = z + at(Z);
}

void Camara::rotarXFirstPerson(float angle){
   float x = at(X) - eye(X);
   float y = cos(angle) * (at(Y) - eye(Y)) - sin(angle) * (at(Z) - eye(Z));
   float z = sin(angle) * (at(Y) - eye(Y)) + cos(angle) * (at(Z) - eye(Z));

   at(X) = x + eye(X);
   at(Y) = y + eye(Y);
   at(Z) = z + eye(Z);
}

void Camara::rotarYFirstPerson(float angle){
   float x = cos(angle) * (at(X) - eye(X)) + sin(angle) * (at(Z) - eye(Z));
   float y = at(Y) - eye(Y);
   float z = -sin(angle) * (at(X) - eye(X)) + cos(angle) * (at(Z) - eye(Z));

   at(X) = x + eye(X);
   at(Y) = y + eye(Y);
   at(Z) = z + eye(Z);
}

void Camara::mover(float x, float y, float z){

}

void Camara::zoom(float factor){
   left *= factor;
   right *= factor;
   bottom *= factor;
   top *= factor;
}

void Camara::girar(float x, float y){
   // Rotar en primera persona con el ratón (angulo en radianes)
   rotarXFirstPerson(y*(PI/180.0));
   rotarYFirstPerson(x*(PI/180.0));
}

void Camara::setObserver(){
   gluLookAt(eye(X), eye(Y), eye(Z), at(X), at(Y), at(Z), up(X), up(Y), up(Z));
}

void Camara::setProyeccion(){
   if (tipo == ORTOGONAL){
      glOrtho(left, right, bottom, top, near, far);
   }
   else if (tipo == PERSPECTIVA){
      glFrustum(left, right, bottom, top, near, far);
   }
}

void Camara::setLeft(float valor){
   left = valor;
}

void Camara::setRight(float valor){
   right = valor;
}

void Camara::setAt(Tupla3f valor){
   at = valor;
}

float Camara::getBottom(){
   return bottom;
}

float Camara::getTop(){
   return top;
}

void Camara::setObjetoSelec(int obj){
   objetoSelec = obj;
}

int Camara::getObjetoSelec(){
   return objetoSelec;
}
