#include "Objeto.h"

#include <map>

using namespace std;

#ifndef NEPTUNO_H
#define NEPTUNO_H

class Neptuno: public Objeto {
  protected:
  
  public:
  	int id;
    Neptuno(float x, float y, float z, float angX, float angY, float angZ);
    static int modelS;
    static int modelT;
    void Draw(ModelType m, Datos_Camara camara);
    void TimeEvolution(float t);
    ~Neptuno();
};

#endif