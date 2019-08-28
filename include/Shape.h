#include "Definitions.h"

#ifndef FORMA_H
#define FORMA_H

class Shape {
	protected:
		shape_type type;
		
	public:
		virtual bool Collision(Shape* f, obj_pos mine, obj_pos other) = 0;
		shape_type get_Type();
};

#endif