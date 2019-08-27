#include "Definitions.h"

#include <list>

#ifndef GAME_STATE_H
#define GAME_STATE_H

class EstadoJuego {
	private:
		EstadoJuego();
		static EstadoJuego* instance;
		
	public:
		camera_type Camera;
		bool interpolate;
		list<to_play>* actions_list;
		float speed;
		bool TestMode;
		bool Texturas;
		bool motion;
		int score;
		ModelType modelado;
		light_inf luz;
		GameState estdo;
		static EstadoJuego* GetInstance();
		void AddActionList(to_play);
		void EmptyActionsList();
		int level;
};

#endif