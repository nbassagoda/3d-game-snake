#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "Menu.h"

#ifndef SCREEN_ENGINE_H
#define SCREEN_ENGINE_H

class ScreenEngine {
private:
	GLuint screenLoose;
	GLuint screenWin;
	GLuint screenInit;
	static ScreenEngine* instance;
	ScreenEngine();
	TTF_Font* fontMain;
	TTF_Font* fontMenu;
	unsigned int LoadTextC(const char* file, SDL_Color a);
	unsigned int LoadText2(const char* file, SDL_Color a);
	void DrawPause();
	void DrawStart();
	void DrawHud();
	void DrawPerder();
	void DrawWin();
    unsigned int LoadTexture(const char* file);
	
public:
	static ScreenEngine* GetInstance();
	void DrawScreen();
};

#endif