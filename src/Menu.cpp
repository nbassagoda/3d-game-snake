#include "../include/Menu.h"

Menu* Menu::instance = NULL;

 Menu::Menu() {
	pocision = O_SolWir;
}

Menu* Menu::GetInstance() {
	if (instance == NULL) instance = new Menu();
	return instance;
}

void Menu::AccionCambiarAbajo() {
	if(EstadoJuego::GetInstance()->estdo == PAUSE)
		switch(pocision) {
			case O_Cama:
				pocision = O_SolWir;
			break;
			case O_SolWir:
				pocision = O_Textura;
			break;
			case O_Textura:
				pocision = O_Inter;
			break;
			case O_Inter:
				pocision = O_LuzAct;
			break;
			case O_LuzAct:
				pocision = O_LuZDir;
			break;
			case O_LuZDir:
				pocision = O_LuzColor;
			break;
			case O_LuzColor:
				pocision = O_Imortal;
			break;
			case O_Imortal:
				pocision = O_FBM;
			break;
			case O_FBM:
				pocision = O_Cama;
			break;
		}
}

void Menu::AccionCambiarAriba() {
	if(EstadoJuego::GetInstance()->estdo == PAUSE)
		switch(pocision) {
			case O_Cama:
				pocision = O_FBM;
			break;
			case O_SolWir:
				pocision = O_Cama;
			break;
			case O_Textura:
				pocision = O_SolWir;
			break;
			case O_Inter:
				pocision = O_Textura;
			break;
			case O_LuzAct:
				pocision = O_Inter;
			break;
			case O_LuZDir:
				pocision = O_LuzAct;
			break;
			case O_LuzColor:
				pocision = O_LuZDir;
			break;
			case O_Imortal:
				pocision = O_LuzColor;
			break;
			case O_FBM:
				pocision = O_Imortal;
			break;
		}
}

void Menu::AccionDirLuz(bool der) {
	if (der) {
		switch (EstadoJuego::GetInstance()->luz.Posicion) {
			case L_Arriba:
				EstadoJuego::GetInstance()->luz.Posicion = L_Atras;
			break;
			case L_Atras:
				EstadoJuego::GetInstance()->luz.Posicion = L_Adeante;
			break;
			case L_Adeante:
				EstadoJuego::GetInstance()->luz.Posicion = L_Izq;
			break;
			case L_Izq:
				EstadoJuego::GetInstance()->luz.Posicion = L_Der;
			break;
			case L_Der:
				EstadoJuego::GetInstance()->luz.Posicion = L_Arriba;
			break;
		}
	} else {
		switch (EstadoJuego::GetInstance()->luz.Posicion) {
			case L_Arriba:
				EstadoJuego::GetInstance()->luz.Posicion = L_Der;
			break;
			case L_Atras:
				EstadoJuego::GetInstance()->luz.Posicion = L_Arriba;
			break;
			case L_Adeante:
				EstadoJuego::GetInstance()->luz.Posicion = L_Atras;
			break;
			case L_Izq:
				EstadoJuego::GetInstance()->luz.Posicion = L_Adeante;
			break;
			case L_Der:
				EstadoJuego::GetInstance()->luz.Posicion = L_Izq;
			break;
		}
	}
}

void Menu::AccionElegir(bool der) {
	if (EstadoJuego::GetInstance()->estdo == PAUSE)
		switch(pocision) {
			case O_Cama:
				AccionCamara(der);
			break;
			case O_SolWir:
				AccionSolWar(der);
			break;
			case O_Textura:
				AccionText(der);
			break;
			case O_Inter:
				AccionInter(der);
			break;
			case O_LuzAct:
				AccionALuz(der);
			break;
			case O_LuZDir:
				AccionDirLuz(der);
			break;
			case O_LuzColor:
				AccionColLuz(der);
			break;
			case O_Imortal:
				AccionTruco(der);
			break;
			case O_FBM:
				AccionTruco2(der);
			break;
		}
}

void Menu::AccionColLuz(bool der) {
	if(der) {
		switch (EstadoJuego::GetInstance()->luz.Color) {
			case(BLANCO):
				EstadoJuego::GetInstance()->luz.Color = ROJO;
			break;
			case(ROJO):
				EstadoJuego::GetInstance()->luz.Color = AZUL;
			break;
			case(AZUL):
				EstadoJuego::GetInstance()->luz.Color = VERDE;
			break;
			case(VERDE):
				EstadoJuego::GetInstance()->luz.Color = BLANCO;
			break;
        }
	}
    else {
		switch (EstadoJuego::GetInstance()->luz.Color) {
			case(BLANCO):
				EstadoJuego::GetInstance()->luz.Color = VERDE;
			break;
			case(ROJO):
				EstadoJuego::GetInstance()->luz.Color = BLANCO;
			break;
			case(AZUL):
				EstadoJuego::GetInstance()->luz.Color = ROJO;
			break;
			case(VERDE):
				EstadoJuego::GetInstance()->luz.Color = AZUL;
			break;
		}
	}
}

void Menu::AccionTruco(bool der) {
	EstadoJuego::GetInstance()->TestMode = !EstadoJuego::GetInstance()->TestMode;
}

void Menu::AccionTruco2(bool der) {
	EstadoJuego::GetInstance()->motion= !EstadoJuego::GetInstance()->motion;
}

void Menu::AccionALuz(bool der) {
	EstadoJuego::GetInstance()->luz.activa = !EstadoJuego::GetInstance()->luz.activa;
}

void Menu::AccionText(bool der) {
	EstadoJuego::GetInstance()->Texturas =! EstadoJuego::GetInstance()->Texturas;
}

void Menu::AccionInter(bool der) {
	EstadoJuego::GetInstance()->interpolate = ! EstadoJuego::GetInstance()->interpolate;
}

void Menu::AccionCamara(bool der) {
	if (der) {
		switch(EstadoJuego::GetInstance()->Camera) {
			case CAMARA_FIJA:
				EstadoJuego::GetInstance()->Camera = MOUSE;
			break;
			case MOUSE:
				EstadoJuego::GetInstance()->Camera = FOLLOW;
			break;
			case FOLLOW:
				EstadoJuego::GetInstance()->Camera = FIRST_PERSON;
			break;
			case FIRST_PERSON:
				EstadoJuego::GetInstance()->Camera = CAMARA_FIJA;
			break;
		}
    } else {
		switch(EstadoJuego::GetInstance()->Camera) {
			case CAMARA_FIJA:
				EstadoJuego::GetInstance()->Camera = FIRST_PERSON;
			break;
			case MOUSE:
				EstadoJuego::GetInstance()->Camera = CAMARA_FIJA;
			break;
			case FOLLOW:
				EstadoJuego::GetInstance()->Camera = MOUSE;
			break;
			case FIRST_PERSON:
				EstadoJuego::GetInstance()->Camera = FOLLOW;
			break;
		}
	}
}

void Menu::AccionSolWar(bool der) {
	if (der) {
		switch(EstadoJuego::GetInstance()->modelado) {
			case MOD_LINEAS:
				EstadoJuego::GetInstance()->modelado = MOD_COLICION;
			break;
			case MOD_COLICION:
				EstadoJuego::GetInstance()->modelado = MOD_SOLIDO;
			break;
			case MOD_SOLIDO:
				EstadoJuego::GetInstance()->modelado = MOD_LINEAS;
			break;
		}
	} else {
		switch(EstadoJuego::GetInstance()->modelado) {
			case MOD_LINEAS:
				EstadoJuego::GetInstance()->modelado = MOD_SOLIDO;
			break;
			case MOD_COLICION:
				EstadoJuego::GetInstance()->modelado = MOD_LINEAS;
			break;
			case MOD_SOLIDO:
				EstadoJuego::GetInstance()->modelado = MOD_COLICION;
			break;
		}
	}
}

Opcion Menu::getOpcion() {
	return pocision;
}