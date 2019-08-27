#include "GameState.h"
#include "ShapeSphere.h"

#include <map>
#include <fstream>
#include <list>

using namespace std;

#ifndef OBJETO_H
#define OBJETO_H

class Objeto{
	protected:
		static int Id_CODE;
		obj_pos _posicion;
		ObjectType _tipo;
		int _id;
		ObjectClass _clase;
		list<Shape*>* _Shape;
		map<int, ObjectClass>* _Coliciones;

	public:
		void SetTamanio(float size);
		void SetPosicion(float x,float y, float z);
		static int codigoEsfer;
		virtual void TimeEvolution(float time){};
		void AgregarColicion(int id,ObjectClass tipo);
		//Agrega la id a la listas de los objrtod con los que coliciono
		virtual bool CollisionAction(){return false;};
		//Genera las Acciones que corresponden a las coliciones de la lista de Coliciones
		void VaciarColiciones();
		//Vacia la lista de Coliciones
		list<Shape*>* getShape();
		bool Colicion(Objeto* o);
		//Rutina de colicion con el objeto o
		virtual void Draw(ModelType m,data_camera camara){};
		int getId();
		obj_pos getPos();
		ObjectClass getClase();
		virtual void RestbleserSTART(){};
		virtual ~Objeto() {};
};

#endif