#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <fstream>

#include "../include/EventsEngine.h"
#include "../include/GraphicEngine.h"
#include "../include/GameEngine.h"

const char* MAIN_DOCUMENT_PATH = "data/Info/Out_Main.txt";
const char* MAIN_ICON_PATH = "data/Textures/Game_Icon.bmp";

using namespace std;

int main(int argc, char* argv[]) {
	// Initialize the truetype font API.
	TTF_Init();
	
	// Opens the file identified by argument filename, associating it with the stream object, so that input/output operations are performed on its content.
	ofstream Document; Document.open(MAIN_DOCUMENT_PATH);
	
	// Initializes the SDL library.
	// Returns 0 on success or a negative error code on failure.
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Document << "[NO] [SDL could not be started]: " << SDL_GetError() << endl; Document.close();
		cerr << "[NO] [SDL could not be started]: " << SDL_GetError() << endl;
		exit(1);
	} else Document << "[YES] [SDL successfully started] " << endl;
	
	// Sets up a video mode.
	// Returns the requested framebuffer surface on success or NULL on failure.
	SDL_Surface* screen = SDL_SetVideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_OPENGL);
	if(screen == NULL) {
		Document << "[NO] [Video mode could not be setted]: " << SDL_GetError() << endl; Document.close();
		cerr << "[NO] [Video mode could not be setted]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	} else Document << "[YES] [Video mode successfully started] " << endl;
	
	// Sets the title-bar and icon name of the display window. 
	SDL_WM_SetCaption("The Pro Snake", NULL);
	
	// Sets the icon for the display window.
	SDL_WM_SetIcon(SDL_LoadBMP(MAIN_ICON_PATH), NULL);
	
	// Sets the game state.
	bool running = true;
	
	// Initializes the game engines.
	GraphicEngine* motor_grafico = GraphicEngine::GetInstance(); Document << "[YES] [GraphicEngine successfully setted] " << endl;
	EventsEngine* motor_eventos = EventsEngine::GetInstance(); Document << "[YES] [EventsEngine successfully setted] " << endl;
	
	SDL_Event event;
	Uint32 start = SDL_GetTicks();
	
	// Main loop.
	Document << "[YES] [Main loop successfully started] " << endl;
	while(running) {
		motor_eventos->PerformEvent(event);
		
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		
		motor_grafico->Draw();
		
		Uint32 tiempo = (SDL_GetTicks() - start);
		start = SDL_GetTicks();
		SDL_GL_SwapBuffers();
		SDL_Flip(screen);
		motor_eventos->ChangeState(tiempo*0.002);
		
		if (GameEngine::GetInstance()->GetState() == QUIT) running = false;
	}
	
	// Closes the file currently associated with the object, disassociating it from the stream.
	TTF_Quit();
	SDL_Quit();
	Document << "[YES] [Snake successfully finished]"; Document.close();
	return 0;
}