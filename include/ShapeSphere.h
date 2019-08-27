#include "Shape.h"

#ifndef FORMA_ESFER_H
#define FORMA_ESFER_H

class ShapeSphere: public Shape {
	private:
		bool ColicionaSphere(ShapeSphere* f, OBJ_POS mia, OBJ_POS otro);

	public:
		ShapeSphere(float X, float Y, float Z, float R);
		float posX;
		float posY;
		float posZ;
		float radio;
		bool Coliciona(Shape* f, OBJ_POS mine, OBJ_POS other);
};

#endif