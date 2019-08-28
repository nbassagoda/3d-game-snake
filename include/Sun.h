#include "Object.h"

#include <map>

using namespace std;

#ifndef SUN_H
#define SUN_H

class Sun: public Object {
  protected:
  
  public:
  	int id;
    Sun(float x, float y, float z, float ang_x, float ang_y, float ang_z);
    static int model_s;
    static int model_t;
    void Draw(ModelType m, data_camera camara);
    void TimeEvolution(float t);
    ~Sun();
};

#endif