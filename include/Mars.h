#include "Objeto.h"

#include <map>

using namespace std;

#ifndef MARS_H
#define MARS_H

class Mars: public Objeto {
  protected:
  
  public:
  	int id;
    Mars(float x, float y, float z, float angX, float angY, float angZ);
    static int modelS;
    static int modelT;
    void Draw(ModelType m, Datos_Camara camara);
    void TimeEvolution(float t);
    ~Mars();
};

#endif