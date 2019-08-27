#include "Definitions.h"

#include <list>

#ifndef ESTADOSJUEGOS_H
#define ESTADOSJUEGOS_H

class EstadoJuego {
	private:
		EstadoJuego();
		static EstadoJuego* instance;
		
	public:
		camera_type Camera;
		bool Interpolado;
		list<to_play>* listaAcciones;
		float velocidad;
		bool ModoPrueba;
		bool Texturas;
		bool FB_Mot;
		int Puntage;
		ModelType modelado;
		InfLus luz;
		Estado_Juego estdo;
		static EstadoJuego* get_Instance();
		void AgregarAccionLisa(to_play);
		void VaciarListaAcciones();
		int nivel;
};

#endif