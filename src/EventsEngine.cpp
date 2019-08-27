#include "../include/EventsEngine.h"

EventsEngine* EventsEngine::instance = NULL;

EventsEngine* EventsEngine::GetInstance() {
	if (instance == NULL)
		instance = new EventsEngine();
	return instance;
}

EventsEngine::EventsEngine() {
	Document.open(EVENTS_DOCUMENT_PATH);
	hit_min = false;
	hit_plus = false;
	move = false;
	rotate = false;
	Document << "[EventsEngine] [Motor Eventos inicio correctamente]" << endl;
}

void EventsEngine::PerformEvent(SDL_Event event) {
	while(SDL_PollEvent(&event))
		switch(event.type) {
			case SDL_QUIT:
				GameEngine::GetInstance()->Quit();
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						GameEngine::GetInstance()->Quit();
					break;
					case SDLK_q:
						GameEngine::GetInstance()->Quit();
					break;
					case SDLK_KP_PLUS:
						hit_plus = true;
					break;
					case SDLK_KP_MINUS:
						hit_min = true;
					break;
					case SDLK_SPACE:
						GameEngine::GetInstance()->StartGame("Defecto");
					break;
					case SDLK_m:
						GraphicEngine::GetInstance()->CambiarModo();
					break;
					case SDLK_UP:
						Menu::GetInstance()->AccionCambiarAriba();
					break;
					case SDLK_DOWN:
						Menu::GetInstance()->AccionCambiarAbajo();
					break;
					case SDLK_v:
						GraphicEngine::GetInstance()->CambiarCamara();
					break;
					case SDLK_f:
						EstadoJuego::GetInstance()->interpolate = !EstadoJuego::GetInstance()->interpolate;
					break;
					case SDLK_t:
						GraphicEngine::GetInstance()->ActivarDesctivarTextura();
					break;
					case SDLK_l:
						GraphicEngine::GetInstance()->ActivarDesactivarLuz();
					break;
					case SDLK_p:
						GameEngine::GetInstance()->Pause();
					break;
					case SDLK_r:
						GameEngine::GetInstance()->Substract();
					break;
					case SDLK_F1:
						GameEngine::GetInstance()->TrialMode();
					break;
					case SDLK_KP_ENTER:
						GameEngine::GetInstance()->DefaultSpeed();
					break;
					case SDLK_F2:
						GameEngine::GetInstance()->StartGame("Defecto");
					break;
					case SDLK_RIGHT:
						Menu::GetInstance()->AccionElegir(true);
						rotate = true;
						rotate_direction = false;
					break;
					case SDLK_LEFT:
						Menu::GetInstance()->AccionElegir(false);
						rotate = true;
						rotate_direction = true;
					break;
					default:
					break;
				}
			break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
					case SDLK_KP_MINUS:
						hit_min = false;
					break;
					case SDLK_KP_PLUS:
						hit_plus = false;
					break;
					case SDLK_RIGHT:
						rotate = false;
					break;
					case SDLK_LEFT:
						rotate = false;
					break;
					default:
					break;
				}
			break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_RIGHT) {
					move = true;
				}
				switch(event.button.button) {
					case SDL_BUTTON_WHEELUP:
						GraphicEngine::GetInstance()->ruedita(true);
					break;
					case SDL_BUTTON_WHEELDOWN:
						GraphicEngine::GetInstance()->ruedita(false);
					break;
				}
			break;
		break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_RIGHT) {
				move = false;
			}
		case SDL_MOUSEMOTION:
			if (move) {
				int xrel = event.motion.xrel;
				int yrel = event.motion.yrel;
				GraphicEngine::GetInstance()->MotionCamara(xrel, yrel);
			}
		break;
		default:
		break;
	}
}

void EventsEngine::ChangeState(float time) {
	GameEngine::GetInstance()->TimeEvolution(time);
	if (hit_plus) GameEngine::GetInstance()->Accelerate();
	if(hit_min) GameEngine::GetInstance()->SlowDown();
}

bool EventsEngine::Rotate() {
	return rotate;
}

bool EventsEngine::RotationDirection() {
	return rotate_direction;
}