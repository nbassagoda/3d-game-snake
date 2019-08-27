#include "Definitions.h"

#ifndef FORMA_H
#define FORMA_H

class Shape {
	protected:
		Tipo_Shape type;
		
	public:
		virtual bool Coliciona(Shape* f, OBJ_POS mine, OBJ_POS other) = 0;
		Tipo_Shape get_Type();
};

#endif