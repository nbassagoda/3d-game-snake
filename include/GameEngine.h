#include "Snake.h"
#include "Apple.h"
#include "Earth.h"
#include "Sun.h"
#include "Moon.h"
#include "Venus.h"
#include "Mars.h"
#include "Jupiter.h"
#include "Neptuno.h"
#include "Mercury.h"



#include <fstream>

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

class GameEngine {
private:
	const char* GAME_ENGINE_DOCUMENT_PATH = "data/Info/Game_Engine.txt";
	ofstream Document;

	//list<float*>* posicionesTub;
	EstadoJuego* estados;
	map<int, Objeto*>* elementos;
	map<int, Objeto*>* ambiente;
	Snake* character;
	static GameEngine* instance;
	GameEngine();
	void CheckCollisions();
	
	//void VerColiciones();
	void IniciarPorDefecto();
	void RestoreGame();
	int apple_identification;
	Objeto* Now;
	
public:
	static GameEngine* GetInstance();
	void TimeEvolution(float t);
	void StartGame(string s);
	void Pause();
	void YouLoose();
	void YouWon();
	void Accelerate();
	void SlowDown();
	void DefaultSpeed();
	void Flap();
	void Substract();
	void Quit();
	void TrialMode();
	GameState GetState();
	map<int,Objeto*>* GetElements();
	Objeto* GetElement();
	map<int,Objeto*>* GetEnv();
	Snake* GetCharacter();
};

#endif