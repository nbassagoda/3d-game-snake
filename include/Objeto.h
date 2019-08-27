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
		OBJ_POS _posicion;
		Tipo_Obejto _tipo;
		int _id;
		Clase_Objeto _clase;
		list<Forma*>* _Forma;
		map<int, Clase_Objeto>* _Coliciones;

	public:
		void SetTamanio(float size);
		void SetPosicion(float x,float y, float z);
		static int codigoEsfer;
		virtual void EvolucionTiempo(float time){};
		void AgregarColicion(int id,Clase_Objeto tipo);
		//Agrega la id a la listas de los objrtod con los que coliciono
		virtual bool AccionColiccion(){return false;};
		//Genera las Acciones que corresponden a las coliciones de la lista de Coliciones
		void VaciarColiciones();
		//Vacia la lista de Coliciones
		list<Forma*>* getForma();
		bool Colicion(Objeto* o);
		//Rutina de colicion con el objeto o
		virtual void Dibujar(Tipo_Modelo m,Datos_Camara camara){};
		int getId();
		OBJ_POS getPos();
		Clase_Objeto getClase();
		virtual void RestbleserInicio(){};
		virtual ~Objeto() {};
};

#endif