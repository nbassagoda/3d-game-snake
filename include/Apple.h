#include "Objeto.h"

#include <map>

using namespace std;

#ifndef APPLE_H
#define APPLE_H

class Apple: public Objeto {
	protected:
		static list<Forma*>* formaApple;
	
	public:
		Apple(float x, float y, float z, float angX, float angY, float angZ);
		static int ModeloS;
		static int ModeloT;
		static void GenerarForma();
		void Dibujar(Tipo_Modelo m, Datos_Camara camara);
		void EvolucionTiempo(float t);
		bool AccionColiccion();
		~Apple();
};

#endif