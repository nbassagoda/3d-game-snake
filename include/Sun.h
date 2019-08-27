#include "Objeto.h"

#include <map>

using namespace std;

#ifndef SUN_H
#define SUN_H

class Sun: public Objeto {
  protected:
  
  public:
  	int id;
    Sun(float x, float y, float z, float angX, float angY, float angZ);
    static int modelS;
    static int modelT;
    void Draw(ModelType m, Datos_Camara camara);
    void TimeEvolution(float t);
    ~Sun();
};

#endif