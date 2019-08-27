#include "Objeto.h"

#include <map>

using namespace std;

#ifndef MARS_H
#define MARS_H

class Mars: public Objeto {
  protected:
  
  public:
  	int id;
    Mars(float x, float y, float z, float angX, float angY, float angZ);
    static int ModeloS;
    static int ModeloT;
    void Dibujar(Tipo_Modelo m, Datos_Camara camara);
    void EvolucionTiempo(float t);
    ~Mars();
};

#endif