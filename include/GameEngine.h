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

#ifndef MOTOR_JUEGO_H
#define MOTOR_JUEGO_H

class Motor_Juego {
private:
	const char* GAME_ENGINE_DOCUMENT_PATH = "data/Info/Game_Engine.txt";
	ofstream Document;
	//list<float*>* posicionesTub;
	EstadoJuego* estados;
	map<int, Objeto*>* elementos;
	map<int, Objeto*>* ambiente;
	Snake* PersonjeControlable;
	static Motor_Juego* instance;
	Motor_Juego();
	void VerColicionesPersonaje();
	//void VerColiciones();
	void IniciarPorDefecto();
	void RestableserJuego();
	int apple_identification;
	Objeto* Now;
	
public:
	static Motor_Juego* get_Instance();
	void EvolucionTiempo(float t);
	void AccionIniciarJuego(string s);
	void AccionPausar();
	void AccionPerder();
	void AccionGanar();
	void AccionAccelerar();
	void AccionEnlentecer();
	void AccionVelocidadPorDefecot();
	void AccionFlap();
	void AccionRestar();
	void AccionSalir();
	void AccionModoPrueba();
	Estado_Juego getEstado();
	map<int,Objeto*>* getElementos();
	Objeto* getElemento();
	map<int,Objeto*>* getAmbiente();
	Snake* getPersonajeControlable();
};

#endif