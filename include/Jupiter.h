#include "Objeto.h"

#include <map>

using namespace std;

#ifndef JUPITER_H
#define JUPITER_H

class Jupiter: public Objeto {
  protected:
  
  public:
  	int id;
    Jupiter(float x, float y, float z, float ang_x, float ang_y, float ang_z);
    static int model_s;
    static int model_t;
    void Draw(ModelType m, data_camera camara);
    void TimeEvolution(float t);
    ~Jupiter();
};

#endif