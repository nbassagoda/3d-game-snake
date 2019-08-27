#include "Objeto.h"

#include <map>

using namespace std;

#ifndef VENUS_H
#define VENUS_H

class Venus: public Objeto {
  protected:
  
  public:
  	int id;
    Venus(float x, float y, float z, float ang_x, float ang_y, float ang_z);
    static int model_s;
    static int model_t;
    void Draw(ModelType m, data_camera camara);
    void TimeEvolution(float t);
    ~Venus();
};

#endif