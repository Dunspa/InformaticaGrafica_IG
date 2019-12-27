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
   float y = cos(angle)*(eye(Y) - at(Y)) - sin(angle)*(eye(Z) - at(Z));
   float z = sin(angle)*(eye(Y) - at(Y)) + cos(angle)*(eye(Z) - at(Z));

   eye(X) = x + at(X);
   eye(Y) = y + at(Y);
   eye(Z) = z + at(Z);
}

void Camara::rotarYExaminar(float angle){
   float x = cos(angle)*(eye(X) - at(X)) + sin(angle)*(eye(Z) - at(Z));
   float y = eye(Y) - at(Y);
   float z = -sin(angle)*(eye(X) - at(X)) + cos(angle)*(eye(Z) - at(Z));

   eye(X) = x + at(X);
   eye(Y) = y + at(Y);
   eye(Z) = z + at(Z);
}

void Camara::rotarZExaminar(float angle){

}

void Camara::rotarXFirstPerson(float angle){

}

void Camara::rotarYFirstPerson(float angle){

}

void Camara::rotarZFirstPerson(float angle){

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
   eye(X) = x;
   eye(Y) = y;
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
