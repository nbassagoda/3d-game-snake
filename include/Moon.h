#include "Objeto.h"

#include <map>

using namespace std;

#ifndef MOON_H
#define MOON_H

class Moon: public Objeto {
  protected:
  	// Document.
    ofstream Document;
  
  public:
    int id;
    Moon(float x, float y, float z, float angX, float angY, float angZ);
    static int modelS;
    static int modelT;
    void Draw(ModelType m, Datos_Camara camara);
    void TimeEvolution(float t);
    ~Moon();
};

#endif