#include "Definitions.h"

#include <list>

#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState {
	private:
		GameState();
		static GameState* instance;
		
	public:
		camera_type camera;
		bool interpolate;
		list<to_play>* actions_list;
		float speed;
		bool TestMode;
		bool Textures;
		bool motion;
		int score;
		ModelType model;
		light_inf light;
		ObjectState estdo;
		static GameState* GetInstance();
		void AddActionList(to_play);
		void EmptyActionsList();
		int level;
};

#endif