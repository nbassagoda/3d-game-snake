#include "Objeto.h"

#include <map>

using namespace std;

#ifndef NEPTUNO_H
#define NEPTUNO_H

class Neptuno: public Objeto {
  protected:
  
  public:
  	int id;
    Neptuno(float x, float y, float z, float ang_x, float ang_y, float ang_z);
    static int model_s;
    static int model_t;
    void Draw(ModelType m, data_camera camara);
    void TimeEvolution(float t);
    ~Neptuno();
};

#endif