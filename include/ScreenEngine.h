#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "Menu.h"

#ifndef MOTOR_PANTALLA_H
#define MOTOR_PANTALLA_H

class Motor_Pantalla {
private:
	GLuint screenLoose;
	GLuint screenWin;
	GLuint screenInit;
	static Motor_Pantalla* instance;
	Motor_Pantalla();
	TTF_Font* fontMain;
	TTF_Font* fontMenu;
	unsigned int CargaTextoC(const char* file, SDL_Color a);
	unsigned int CargaTextoG(const char* file, SDL_Color a);
	void DrawPausa();
	void DrawInicio();
	void DrawHUD();
	void DrawPerder();
	void DrawGanar();
    unsigned int CargaTextura(const char* file);
	
public:
	static unsigned int puto;
	static Motor_Pantalla* get_Instance();
	void DrawPantalla();
};

#endif