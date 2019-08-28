#include "../include/ShapeSphere.h"

ShapeSphere::ShapeSphere(float X, float Y, float Z, float R) {
	pos_x = X;
	pos_y = Y;
	posZ = Z;
	radio = R;
	type = SPHERE;
}

bool ShapeSphere::Collision(Shape* F, obj_pos mine, obj_pos other) {
	bool result = false;
	switch(F->get_Type()) {
		case SPHERE:
			result = CollisionSphere(dynamic_cast<ShapeSphere*>(F), mine, other);
		break;
	}
	return result;
}

bool ShapeSphere::CollisionSphere(ShapeSphere* F, obj_pos mine,obj_pos other) {
	float R1;
	float R2 = radio + F->radio;
	float X = mine.pos_x - other.pos_x;
	float Y = mine.pos_y - other.pos_y;
	float Z = mine.posZ - other.posZ;
	R1 = sqrtf((X*X) + (Y*Y) + (Z*Z));
	return (R1 < R2);
}