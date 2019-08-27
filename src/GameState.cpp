#include "../include/GameState.h"

EstadoJuego* EstadoJuego::instance = NULL;

EstadoJuego* EstadoJuego::get_Instance() {
	if(instance == NULL) instance = new EstadoJuego();
	return instance;
}

EstadoJuego::EstadoJuego() {
	listaAcciones = new list<El_A_Juego>;
	velocidad = 1;
	modelado = MOD_SOLIDO;
	Camera = CAMARA_FIJA;
	Interpolado = true;
	estdo = Inicio;
	Puntage = 0;
	ModoPrueba = false;
	luz.activa = true;
	luz.Posicion = L_Arriba;
	luz.Color = BLANCO;
	FB_Mot = false;
	nivel = 0;
}

void EstadoJuego::AgregarAccionLisa(El_A_Juego a) {
	listaAcciones->push_back(a);
}

void EstadoJuego::VaciarListaAcciones() {
	listaAcciones->clear();
}