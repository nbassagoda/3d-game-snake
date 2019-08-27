#include "../include/GameState.h"

EstadoJuego* EstadoJuego::instance = NULL;

EstadoJuego* EstadoJuego::GetInstance() {
	if(instance == NULL) instance = new EstadoJuego();
	return instance;
}

EstadoJuego::EstadoJuego() {
	actions_list = new list<to_play>;
	speed = 1;
	modelado = MOD_SOLIDO;
	Camera = CAMARA_FIJA;
	interpolate = true;
	estdo = START;
	score = 0;
	TestMode = false;
	luz.activa = true;
	luz.Posicion = L_Arriba;
	luz.Color = BLANCO;
	motion = false;
	level = 0;
}

void EstadoJuego::AddActionList(to_play a) {
	actions_list->push_back(a);
}

void EstadoJuego::EmptyActionsList() {
	actions_list->clear();
}