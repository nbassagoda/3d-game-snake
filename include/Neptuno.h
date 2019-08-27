#include "Objeto.h"

#include <map>

using namespace std;

#ifndef NEPTUNO_H
#define NEPTUNO_H

class Neptuno: public Objeto {
  protected:
  
  public:
  	int id;
    Neptuno(float x, float y, float z, float angX, float angY, float angZ);
    static int ModeloS;
    static int ModeloT;
    void Dibujar(Tipo_Modelo m, Datos_Camara camara);
    void EvolucionTiempo(float t);
    ~Neptuno();
};

#endif