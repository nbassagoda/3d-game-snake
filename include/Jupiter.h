#include "Objeto.h"

#include <map>

using namespace std;

#ifndef JUPITER_H
#define JUPITER_H

class Jupiter: public Objeto {
  protected:
  
  public:
  	int id;
    Jupiter(float x, float y, float z, float angX, float angY, float angZ);
    static int modelS;
    static int modelT;
    void Draw(ModelType m, Datos_Camara camara);
    void TimeEvolution(float t);
    ~Jupiter();
};

#endif