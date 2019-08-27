#include "Objeto.h"

#include <cmath>
#include <ctime>

#ifndef SNAKE_H
#define SNAKE_H

class Snake : public Objeto {
	private:
		const char* SNAKE_DOCUMENT_PATH = "data/Info/Out_Snake.txt";
		ofstream Document;
		float anguloRad_Actual;
		float anguloRad_Ajuste;
		float anguloGra_Actual;
		float anguloGra_Ajuste;
		static list<Shape*>* formaSnake;
		float _ColorR;
		float _ColorG;
		float _ColorB;

	public:
		Snake(float x, float y, float z, float angX, float angY, float angZ);
		static GLint modelS;
		static GLint modelT;
		static void GenerateShape();
		void Draw(ModelType m, Datos_Camara camara);
		void TimeEvolution(float t);
		bool CollisionAction();
		float get_anguloActual();
		~Snake();
};

#endif