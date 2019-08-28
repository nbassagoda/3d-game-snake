#include "Shape.h"

#ifndef FORMA_ESFER_H
#define FORMA_ESFER_H

class ShapeSphere: public Shape {
	private:
		bool CollisionSphere(ShapeSphere* f, obj_pos mine, obj_pos other);

	public:
		ShapeSphere(float X, float Y, float Z, float R);
		float pos_x;
		float pos_y;
		float posZ;
		float radio;
		bool Collision(Shape* f, obj_pos mine, obj_pos other);
};

#endif