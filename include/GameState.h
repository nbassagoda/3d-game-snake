#include "Definitions.h"

#include <list>

#ifndef ESTADOSJUEGOS_H
#define ESTADOSJUEGOS_H

class EstadoJuego {
	private:
		EstadoJuego();
		static EstadoJuego* instance;
		
	public:
		Tipo_Camar Camera;
		bool Interpolado;
		list<El_A_Juego>* listaAcciones;
		float velocidad;
		bool ModoPrueba;
		bool Texturas;
		bool FB_Mot;
		int Puntage;
		Tipo_Modelo modelado;
		InfLus luz;
		Estado_Juego estdo;
		static EstadoJuego* get_Instance();
		void AgregarAccionLisa(El_A_Juego);
		void VaciarListaAcciones();
		int nivel;
};

#endif