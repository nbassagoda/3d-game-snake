#include "GameState.h"
#include "ShapeSphere.h"

#include <map>
#include <fstream>
#include <list>

using namespace std;

#ifndef OBJECT_H
#define OBJECT_H

class Object {
	protected:
		static int id_code;
		obj_pos _position;
		object_type _tipo;
		int _id;
		object_class _clase;
		list<Shape*>* _Shape;
		map<int, object_class>* _collisions;

	public:
		void SetSize(float size);
		void SetPosition(float x,float y, float z);
		static int codigoEsfer;
		virtual void TimeEvolution(float time){};
		void AddCollision(int id,object_class tipo);
		virtual bool CollisionAction(){return false;};
		void EmptyCollisions();
		list<Shape*>* GetShape();
		bool Colicion(Object* o);
		virtual void Draw(ModelType m,data_camera camara){};
		int GetId();
		obj_pos GetPosition();
		object_class GetClass();
		virtual void RestoreStart(){};
		virtual ~Object() {};
};

#endif