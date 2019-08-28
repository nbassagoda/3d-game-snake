#include "../include/GameState.h"

GameState* GameState::instance = NULL;

GameState* GameState::GetInstance() {
	if(instance == NULL) instance = new GameState();
	return instance;
}

GameState::GameState() {
	actions_list = new list<to_play>;
	speed = 1;
	model = MOD_SOLIDO;
	camera = CAMARA_FIJA;
	interpolate = true;
	estdo = START;
	score = 0;
	TestMode = false;
	light.activa = true;
	light.position = L_Arriba;
	light.Color = BLANCO;
	motion = false;
	level = 0;
}

void GameState::AddActionList(to_play a) {
	actions_list->push_back(a);
}

void GameState::EmptyActionsList() {
	actions_list->clear();
}