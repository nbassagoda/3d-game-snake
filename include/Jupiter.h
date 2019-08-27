#include "Objeto.h"

#include <map>

using namespace std;

#ifndef JUPITER_H
#define JUPITER_H

class Jupiter: public Objeto {
  protected:
  
  public:
  	int id;
    Jupiter(float x, float y, float z, float angX, float angY, float angZ);
    static int ModeloS;
    static int ModeloT;
    void Dibujar(Tipo_Modelo m, Datos_Camara camara);
    void EvolucionTiempo(float t);
    ~Jupiter();
};

#endif