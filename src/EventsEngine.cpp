#include "../include/EventsEngine.h"

Motor_Eventos* Motor_Eventos::instance = NULL;

Motor_Eventos* Motor_Eventos::get_Instance() {
	if (instance == NULL)
		instance = new Motor_Eventos();
	return instance;
}

Motor_Eventos::Motor_Eventos() {
	Document.open(EVENTS_DOCUMENT_PATH);
	Apretados_min = false;
	Apretados_plus = false;
	quieroMover = false;
	quieroRotar = false;
	Document << "[Motor_Eventos] [Motor Eventos inicio correctamente]" << endl;
}

void Motor_Eventos::RealizarEvento(SDL_Event event) {
	while(SDL_PollEvent(&event))
		switch(event.type) {
			case SDL_QUIT:
				Motor_Juego::get_Instance()->AccionSalir();
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						Motor_Juego::get_Instance()->AccionSalir();
					break;
					case SDLK_q:
						Motor_Juego::get_Instance()->AccionSalir();
					break;
					case SDLK_KP_PLUS:
						Apretados_plus = true;
					break;
					case SDLK_KP_MINUS:
						Apretados_min = true;
					break;
					case SDLK_SPACE:
						Motor_Juego::get_Instance()->AccionIniciarJuego("Defecto");
					break;
					case SDLK_m:
						Motor_Grafico::get_Instance()->CambiarModo();
					break;
					case SDLK_UP:
						Menu::get_Instance()->AccionCambiarAriba();
					break;
					case SDLK_DOWN:
						Menu::get_Instance()->AccionCambiarAbajo();
					break;
					case SDLK_v:
						Motor_Grafico::get_Instance()->CambiarCamara();
					break;
					case SDLK_f:
						EstadoJuego::get_Instance()->Interpolado = !EstadoJuego::get_Instance()->Interpolado;
					break;
					case SDLK_t:
						Motor_Grafico::get_Instance()->ActivarDesctivarTextura();
					break;
					case SDLK_l:
						Motor_Grafico::get_Instance()->ActivarDesactivarLuz();
					break;
					case SDLK_p:
						Motor_Juego::get_Instance()->AccionPausar();
					break;
					case SDLK_r:
						Motor_Juego::get_Instance()->AccionRestar();
					break;
					case SDLK_F1:
						Motor_Juego::get_Instance()->AccionModoPrueba();
					break;
					case SDLK_KP_ENTER:
						Motor_Juego::get_Instance()->AccionVelocidadPorDefecot();
					break;
					case SDLK_F2:
						Motor_Juego::get_Instance()->AccionIniciarJuego("Defecto");
					break;
					case SDLK_RIGHT:
						Menu::get_Instance()->AccionElegir(true);
						quieroRotar = true;
						direccionRotacion = false;
					break;
					case SDLK_LEFT:
						Menu::get_Instance()->AccionElegir(false);
						quieroRotar = true;
						direccionRotacion = true;
					break;
					default:
					break;
				}
			break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
					case SDLK_KP_MINUS:
						Apretados_min = false;
					break;
					case SDLK_KP_PLUS:
						Apretados_plus = false;
					break;
					case SDLK_RIGHT:
						quieroRotar = false;
					break;
					case SDLK_LEFT:
						quieroRotar = false;
					break;
					default:
					break;
				}
			break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_RIGHT) {
					quieroMover = true;
				}
				switch(event.button.button) {
					case SDL_BUTTON_WHEELUP:
						Motor_Grafico::get_Instance()->ruedita(true);
					break;
					case SDL_BUTTON_WHEELDOWN:
						Motor_Grafico::get_Instance()->ruedita(false);
					break;
				}
			break;
		break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_RIGHT) {
				quieroMover = false;
			}
		case SDL_MOUSEMOTION:
			if (quieroMover) {
				int xrel = event.motion.xrel;
				int yrel = event.motion.yrel;
				Motor_Grafico::get_Instance()->MotionCamara(xrel, yrel);
			}
		break;
		default:
		break;
	}
}

void Motor_Eventos::Evolucion_Estados(float time) {
	Motor_Juego::get_Instance()->TimeEvolution(time);
	if (Apretados_plus) Motor_Juego::get_Instance()->AccionAccelerar();
	if(Apretados_min) Motor_Juego::get_Instance()->AccionEnlentecer();
}

bool Motor_Eventos::Quiero_Rotar() {
	return quieroRotar;
}

bool Motor_Eventos::Direccion_Rotacion() {
	return direccionRotacion;
}