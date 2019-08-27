#include "Shape.h"

#ifndef FORMA_ESFER_H
#define FORMA_ESFER_H

class Forma_Esfera: public Forma {
	private:
		bool Coliciona_Esfera(Forma_Esfera* f, OBJ_POS mia, OBJ_POS otro);

	public:
		Forma_Esfera(float X, float Y, float Z, float R);
		float posX;
		float posY;
		float posZ;
		float radio;
		bool Coliciona(Forma* f, OBJ_POS mine, OBJ_POS other);
};

#endif