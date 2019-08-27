#include "Shape.h"

#ifndef FORMA_ESFER_H
#define FORMA_ESFER_H

class ShapeSphere: public Shape {
	private:
		bool ColicionaSphere(ShapeSphere* f, obj_pos mia, obj_pos otro);

	public:
		ShapeSphere(float X, float Y, float Z, float R);
		float pos_x;
		float pos_y;
		float posZ;
		float radio;
		bool Coliciona(Shape* f, obj_pos mine, obj_pos other);
};

#endif