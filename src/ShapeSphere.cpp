#include "../include/ShapeSphere.h"

ShapeSphere::ShapeSphere(float X, float Y, float Z, float R) {
	posX = X;
	posY = Y;
	posZ = Z;
	radio = R;
	type = Esfera;
}

bool ShapeSphere::Coliciona(Shape* F, OBJ_POS mine, OBJ_POS other) {
	bool result = false;
	switch(F->get_Type()) {
		case Esfera:
			result = ColicionaSphere(dynamic_cast<ShapeSphere*>(F), mine, other);
		break;
	}
	return result;
}

bool ShapeSphere::ColicionaSphere(ShapeSphere* F, OBJ_POS mine,OBJ_POS other) {
	float R1;
	float R2 = radio + F->radio;
	float X = mine.posX - other.posX;
	float Y = mine.posY - other.posY;
	float Z = mine.posZ - other.posZ;
	R1 = sqrtf((X*X) + (Y*Y) + (Z*Z));
	return (R1 < R2);
}