#include <SDL/SDL.h>
#include "GraphicEngine.h"

#include <map>

#ifndef EVENTS_ENGINE_H
#define EVENTS_ENGINE_H

class EventsEngine {
	private:
		static EventsEngine* instance;
		const char* EVENTS_DOCUMENT_PATH = "data/Info/Out_Events_Engine.txt";
		
		// Document.
		ofstream Document;
		
		EventsEngine();
		bool hit_plus;
		bool hit_min;
		bool move;
		bool rotate;
		bool rotate_direction;
		
	public:
		static EventsEngine* GetInstance();
		void PerformEvent(SDL_Event event);
		void ChangeState(float time);
		bool Rotate();
		bool RotationDirection();
};

#endif