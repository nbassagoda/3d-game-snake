#include "../include/Objeto.h"

int Objeto::Id_CODE = 0;
int Objeto::codigoEsfer = 0;

int Objeto::getId() {
    return _id;
}

void Objeto::SetTamanio(float size) {
	_posicion.size = size;
}

void Objeto::SetPosicion(float x,float y,float z) {
	_posicion.posX = x;
	_posicion.posY = y;
	_posicion.posZ = z;
}

OBJ_POS Objeto::getPos() {
	return _posicion;
}

Clase_Objeto Objeto::getClase() {
	return _clase;
}

list<Shape*>* Objeto::getShape() {
	return _Shape;
}

void Objeto::AgregarColicion(int id,Clase_Objeto tipo) {
	_Coliciones->insert(pair<int, Clase_Objeto>(id,tipo));
}

void Objeto::VaciarColiciones() {
	// map<int,ModelType>::iterator it;
	// for (it = elementos->begin();it != elementos->end(); ++it)
	//delete(it->second);
	_Coliciones->clear();
	delete(_Coliciones);
	_Coliciones = new map<int,Clase_Objeto>();
}

bool Objeto::Colicion(Objeto* o) {
	ofstream Document;
	Document.open("bin/Info/Game_Engine2.txt");
	list<Shape*>* formas = o->getShape();
	bool colicionaron = false;
	list<Shape*>::const_iterator it1;
	for(it1 = _Shape->begin(); (it1 != _Shape->end())&&(!colicionaron); ++it1) {
		Shape* forma1 = *it1;
		list<Shape*>::const_iterator it2;
		for(it2 = formas->begin(); (it2 != formas->end())&&(!colicionaron); ++it2) {
			Shape* forma2 = *it2;
			colicionaron = forma1->Coliciona(forma2, getPos(), o->getPos());
		}
	}
	if (colicionaron) {
		_Coliciones->insert(pair<int, Clase_Objeto>(o->getId(),o->_clase));
		o->AgregarColicion(getId(),_clase);
	}
	return(colicionaron);
}