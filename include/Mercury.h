#include "Object.h"

#include <map>

using namespace std;

#ifndef MERCURY_H
#define MERCURY_H

class Mercury: public Object {
  protected:
  
  public:
  	int id;
    Mercury(float x, float y, float z, float ang_x, float ang_y, float ang_z);
    static int model_s;
    static int model_t;
    void Draw(ModelType m, data_camera camara);
    void TimeEvolution(float t);
    ~Mercury();
};

#endif