#include <SDL/SDL.h>
#include "GraphicEngine.h"

#include <map>

#ifndef MOTOR_DE_EVENTOS_H
#define MOTOR_DE_EVENTOS_H

class Motor_Eventos {
	private:
		static Motor_Eventos* instance;
		const char* EVENTS_DOCUMENT_PATH = "data/Info/Out_Events_Engine.txt";
		
		// Document.
		ofstream Document;
		
		Motor_Eventos();
		bool Apretados_plus;
		bool Apretados_min;
		bool quieroMover;
		bool quieroRotar;
		bool direccionRotacion;
		
	public:
		static Motor_Eventos* get_Instance();
		void RealizarEvento(SDL_Event event);
		void Evolucion_Estados(float time);
		bool Quiero_Rotar();
		bool Direccion_Rotacion();
};

#endif