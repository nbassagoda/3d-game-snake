#include "../include/Menu.h"

Menu* Menu::instance = NULL;

 Menu::Menu() {
	position = O_SUN;
}

Menu* Menu::GetInstance() {
	if (instance == NULL) instance = new Menu();
	return instance;
}

void Menu::ChangeDown() {
	if(GameState::GetInstance()->estdo == PAUSE)
		switch(position) {
			case O_CAMERA:
				position = O_SUN;
			break;
			case O_SUN:
				position = O_TEXTURE;
			break;
			case O_TEXTURE:
				position = O_INTER;
			break;
			case O_INTER:
				position = O_LIGHT;
			break;
			case O_LIGHT:
				position = O_LIGHT_DIR;
			break;
			case O_LIGHT_DIR:
				position = O_LIGHT_COLOR;
			break;
			case O_LIGHT_COLOR:
				position = O_TRICK;
			break;
			case O_TRICK:
				position = O_TRICK_2;
			break;
			case O_TRICK_2:
				position = O_CAMERA;
			break;
		}
}

void Menu::ChangeUp() {
	if(GameState::GetInstance()->estdo == PAUSE)
		switch(position) {
			case O_CAMERA:
				position = O_TRICK_2;
			break;
			case O_SUN:
				position = O_CAMERA;
			break;
			case O_TEXTURE:
				position = O_SUN;
			break;
			case O_INTER:
				position = O_TEXTURE;
			break;
			case O_LIGHT:
				position = O_INTER;
			break;
			case O_LIGHT_DIR:
				position = O_LIGHT;
			break;
			case O_LIGHT_COLOR:
				position = O_LIGHT_DIR;
			break;
			case O_TRICK:
				position = O_LIGHT_COLOR;
			break;
			case O_TRICK_2:
				position = O_TRICK;
			break;
		}
}

void Menu::LightDirection(bool der) {
	if (der) {
		switch (GameState::GetInstance()->light.position) {
			case L_Arriba:
				GameState::GetInstance()->light.position = L_Atras;
			break;
			case L_Atras:
				GameState::GetInstance()->light.position = L_Adeante;
			break;
			case L_Adeante:
				GameState::GetInstance()->light.position = L_Izq;
			break;
			case L_Izq:
				GameState::GetInstance()->light.position = L_Der;
			break;
			case L_Der:
				GameState::GetInstance()->light.position = L_Arriba;
			break;
		}
	} else {
		switch (GameState::GetInstance()->light.position) {
			case L_Arriba:
				GameState::GetInstance()->light.position = L_Der;
			break;
			case L_Atras:
				GameState::GetInstance()->light.position = L_Arriba;
			break;
			case L_Adeante:
				GameState::GetInstance()->light.position = L_Atras;
			break;
			case L_Izq:
				GameState::GetInstance()->light.position = L_Adeante;
			break;
			case L_Der:
				GameState::GetInstance()->light.position = L_Izq;
			break;
		}
	}
}

void Menu::ChooseAction(bool der) {
	if (GameState::GetInstance()->estdo == PAUSE)
		switch(position) {
			case O_CAMERA:
				cameraAction(der);
			break;
			case O_SUN:
				SunAction(der);
			break;
			case O_TEXTURE:
				TextAction(der);
			break;
			case O_INTER:
				InterAction(der);
			break;
			case O_LIGHT:
				LightAction(der);
			break;
			case O_LIGHT_DIR:
				LightDirection(der);
			break;
			case O_LIGHT_COLOR:
				LightColAction(der);
			break;
			case O_TRICK:
				TrickAction(der);
			break;
			case O_TRICK_2:
				TrickAction2(der);
			break;
		}
}

void Menu::LightColAction(bool der) {
	if(der) {
		switch (GameState::GetInstance()->light.Color) {
			case(BLANCO):
				GameState::GetInstance()->light.Color = ROJO;
			break;
			case(ROJO):
				GameState::GetInstance()->light.Color = AZUL;
			break;
			case(AZUL):
				GameState::GetInstance()->light.Color = VERDE;
			break;
			case(VERDE):
				GameState::GetInstance()->light.Color = BLANCO;
			break;
        }
	}
    else {
		switch (GameState::GetInstance()->light.Color) {
			case(BLANCO):
				GameState::GetInstance()->light.Color = VERDE;
			break;
			case(ROJO):
				GameState::GetInstance()->light.Color = BLANCO;
			break;
			case(AZUL):
				GameState::GetInstance()->light.Color = ROJO;
			break;
			case(VERDE):
				GameState::GetInstance()->light.Color = AZUL;
			break;
		}
	}
}

void Menu::TrickAction(bool der) {
	GameState::GetInstance()->TestMode = !GameState::GetInstance()->TestMode;
}

void Menu::TrickAction2(bool der) {
	GameState::GetInstance()->motion= !GameState::GetInstance()->motion;
}

void Menu::LightAction(bool der) {
	GameState::GetInstance()->light.activa = !GameState::GetInstance()->light.activa;
}

void Menu::TextAction(bool der) {
	GameState::GetInstance()->Textures =! GameState::GetInstance()->Textures;
}

void Menu::InterAction(bool der) {
	GameState::GetInstance()->interpolate = ! GameState::GetInstance()->interpolate;
}

void Menu::cameraAction(bool der) {
	if (der) {
		switch(GameState::GetInstance()->camera) {
			case CAMARA_FIJA:
				GameState::GetInstance()->camera = MOUSE;
			break;
			case MOUSE:
				GameState::GetInstance()->camera = FOLLOW;
			break;
			case FOLLOW:
				GameState::GetInstance()->camera = FIRST_PERSON;
			break;
			case FIRST_PERSON:
				GameState::GetInstance()->camera = CAMARA_FIJA;
			break;
		}
    } else {
		switch(GameState::GetInstance()->camera) {
			case CAMARA_FIJA:
				GameState::GetInstance()->camera = FIRST_PERSON;
			break;
			case MOUSE:
				GameState::GetInstance()->camera = CAMARA_FIJA;
			break;
			case FOLLOW:
				GameState::GetInstance()->camera = MOUSE;
			break;
			case FIRST_PERSON:
				GameState::GetInstance()->camera = FOLLOW;
			break;
		}
	}
}

void Menu::SunAction(bool der) {
	if (der) {
		switch(GameState::GetInstance()->model) {
			case MOD_LINEAS:
				GameState::GetInstance()->model = MOD_COLICION;
			break;
			case MOD_COLICION:
				GameState::GetInstance()->model = MOD_SOLIDO;
			break;
			case MOD_SOLIDO:
				GameState::GetInstance()->model = MOD_LINEAS;
			break;
		}
	} else {
		switch(GameState::GetInstance()->model) {
			case MOD_LINEAS:
				GameState::GetInstance()->model = MOD_SOLIDO;
			break;
			case MOD_COLICION:
				GameState::GetInstance()->model = MOD_LINEAS;
			break;
			case MOD_SOLIDO:
				GameState::GetInstance()->model = MOD_COLICION;
			break;
		}
	}
}

Option Menu::getOption() {
	return position;
}