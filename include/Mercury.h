#include "Objeto.h"

#include <map>

using namespace std;

#ifndef MERCURY_H
#define MERCURY_H

class Mercury: public Objeto {
  protected:
  
  public:
  	int id;
    Mercury(float x, float y, float z, float angX, float angY, float angZ);
    static int modelS;
    static int modelT;
    void Draw(ModelType m, Datos_Camara camara);
    void TimeEvolution(float t);
    ~Mercury();
};

#endif