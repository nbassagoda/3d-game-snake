#include "Object.h"

#include <map>

using namespace std;

#ifndef MARS_H
#define MARS_H

class Mars: public Object {
  protected:
  
  public:
  	int id;
    Mars(float x, float y, float z, float ang_x, float ang_y, float ang_z);
    static int model_s;
    static int model_t;
    void Draw(ModelType m, data_camera camara);
    void TimeEvolution(float t);
    ~Mars();
};

#endif