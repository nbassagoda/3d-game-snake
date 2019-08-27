#include "Definitions.h"

#ifndef FORMA_H
#define FORMA_H

class Forma {
	protected:
		Tipo_Forma type;
		
	public:
		virtual bool Coliciona(Forma* f, OBJ_POS mine, OBJ_POS other) = 0;
		Tipo_Forma get_Type();
};

#endif