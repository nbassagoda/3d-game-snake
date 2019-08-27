#include "Objeto.h"

#include <map>

using namespace std;

#ifndef EARTH_H
#define EARTH_H

class Earth: public Objeto {
  protected:
  // Document.
    ofstream Document;
  public:
  	int id;
    Earth(float x, float y, float z, float ang_x, float ang_y, float ang_z);
    static int model_s;
    static int model_t;
    void Draw(ModelType m, data_camera camara);
    void TimeEvolution(float t);
    ~Earth();
};

#endif