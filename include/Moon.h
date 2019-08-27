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
    Moon(float x, float y, float z, float ang_x, float ang_y, float ang_z);
    static int model_s;
    static int model_t;
    void Draw(ModelType m, data_camera camara);
    void TimeEvolution(float t);
    ~Moon();
};

#endif