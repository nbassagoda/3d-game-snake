#include "Object.h"

#include <map>

using namespace std;

#ifndef APPLE_H
#define APPLE_H

class Apple: public Object {
	protected:
		static list<Shape*>* ShapeApple;
	
	public:
		Apple(float x, float y, float z, float ang_x, float ang_y, float ang_z);
		static int model_s;
		static int model_t;
		static void GenerateShape();
		void Draw(ModelType m, data_camera camara);
		void TimeEvolution(float t);
		bool CollisionAction();
		~Apple();
};

#endif
