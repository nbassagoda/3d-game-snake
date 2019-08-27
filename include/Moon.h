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
    Moon(float x, float y, float z, float angX, float angY, float angZ);
    static int ModeloS;
    static int ModeloT;
    void Dibujar(Tipo_Modelo m, Datos_Camara camara);
    void EvolucionTiempo(float t);
    ~Moon();
};

#endif