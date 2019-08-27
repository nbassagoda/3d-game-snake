#include "Objeto.h"

#include <map>

using namespace std;

#ifndef APPLE_H
#define APPLE_H

class Apple: public Objeto {
	protected:
		static list<Shape*>* ShapeApple;
	
	public:
		Apple(float x, float y, float z, float angX, float angY, float angZ);
		static int modelS;
		static int modelT;
		static void GenerateShape();
		void Draw(ModelType m, Datos_Camara camara);
		void TimeEvolution(float t);
		bool CollisionAction();
		~Apple();
};

#endif
