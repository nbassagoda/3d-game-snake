#include "../include/Object.h"

int Object::id_code = 0;
int Object::codigoEsfer = 0;

int Object::GetId() {
    return _id;
}

void Object::SetSize(float size) {
	_position.size = size;
}

void Object::SetPosition(float x,float y,float z) {
	_position.pos_x = x;
	_position.pos_y = y;
	_position.posZ = z;
}

obj_pos Object::GetPosition() {
	return _position;
}

object_class Object::GetClass() {
	return _clase;
}

list<Shape*>* Object::GetShape() {
	return _Shape;
}

void Object::AddCollision(int id,object_class tipo) {
	_collisions->insert(pair<int, object_class>(id,tipo));
}

void Object::EmptyCollisions() {
	_collisions->clear();
	delete(_collisions);
	_collisions = new map<int,object_class>();
}

bool Object::Colicion(Object* o) {
	ofstream Document;
	Document.open("bin/Info/Game_Engine2.txt");
	list<Shape*>* formas = o->GetShape();
	bool colicionaron = false;
	list<Shape*>::const_iterator it1;
	for(it1 = _Shape->begin(); (it1 != _Shape->end())&&(!colicionaron); ++it1) {
		Shape* forma1 = *it1;
		list<Shape*>::const_iterator it2;
		for(it2 = formas->begin(); (it2 != formas->end())&&(!colicionaron); ++it2) {
			Shape* forma2 = *it2;
			colicionaron = forma1->Collision(forma2, GetPosition(), o->GetPosition());
		}
	}
	if (colicionaron) {
		_collisions->insert(pair<int, object_class>(o->GetId(),o->_clase));
		o->AddCollision(GetId(),_clase);
	}
	return(colicionaron);
}