#include "Objeto.h"

#include <map>

using namespace std;

#ifndef VENUS_H
#define VENUS_H

class Venus: public Objeto {
  protected:
  
  public:
  	int id;
    Venus(float x, float y, float z, float angX, float angY, float angZ);
    static int modelS;
    static int modelT;
    void Draw(ModelType m, Datos_Camara camara);
    void TimeEvolution(float t);
    ~Venus();
};

#endif