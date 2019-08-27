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
		static GLint ModeloS;
		static GLint ModeloT;
		static void GenerateShape();
		void Dibujar(Tipo_Modelo m, Datos_Camara camara);
		void EvolucionTiempo(float t);
		bool AccionColiccion();
		float get_anguloActual();
		~Snake();
};

#endif