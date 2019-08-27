#include "Objeto.h"

#include <map>

using namespace std;

#ifndef SUN_H
#define SUN_H

class Sun: public Objeto {
  protected:
  
  public:
  	int id;
    Sun(float x, float y, float z, float angX, float angY, float angZ);
    static int ModeloS;
    static int ModeloT;
    void Dibujar(Tipo_Modelo m, Datos_Camara camara);
    void EvolucionTiempo(float t);
    ~Sun();
};

#endif