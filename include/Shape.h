#include "Definitions.h"

#ifndef FORMA_H
#define FORMA_H

class Shape {
	protected:
		ShapeType type;
		
	public:
		virtual bool Coliciona(Shape* f, obj_pos mine, obj_pos other) = 0;
		ShapeType get_Type();
};

#endif