#include "../include/Menu.h"

Menu* Menu::instance = NULL;

 Menu::Menu() {
	pocision = O_SolWir;
}

Menu* Menu::get_Instance() {
	if (instance == NULL) instance = new Menu();
	return instance;
}

void Menu::AccionCambiarAbajo() {
	if(EstadoJuego::get_Instance()->estdo == Pausado)
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
	if(EstadoJuego::get_Instance()->estdo == Pausado)
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
		switch (EstadoJuego::get_Instance()->luz.Posicion) {
			case L_Arriba:
				EstadoJuego::get_Instance()->luz.Posicion = L_Atras;
			break;
			case L_Atras:
				EstadoJuego::get_Instance()->luz.Posicion = L_Adeante;
			break;
			case L_Adeante:
				EstadoJuego::get_Instance()->luz.Posicion = L_Izq;
			break;
			case L_Izq:
				EstadoJuego::get_Instance()->luz.Posicion = L_Der;
			break;
			case L_Der:
				EstadoJuego::get_Instance()->luz.Posicion = L_Arriba;
			break;
		}
	} else {
		switch (EstadoJuego::get_Instance()->luz.Posicion) {
			case L_Arriba:
				EstadoJuego::get_Instance()->luz.Posicion = L_Der;
			break;
			case L_Atras:
				EstadoJuego::get_Instance()->luz.Posicion = L_Arriba;
			break;
			case L_Adeante:
				EstadoJuego::get_Instance()->luz.Posicion = L_Atras;
			break;
			case L_Izq:
				EstadoJuego::get_Instance()->luz.Posicion = L_Adeante;
			break;
			case L_Der:
				EstadoJuego::get_Instance()->luz.Posicion = L_Izq;
			break;
		}
	}
}

void Menu::AccionElegir(bool der) {
	if (EstadoJuego::get_Instance()->estdo == Pausado)
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
		switch (EstadoJuego::get_Instance()->luz.Color) {
			case(BLANCO):
				EstadoJuego::get_Instance()->luz.Color = ROJO;
			break;
			case(ROJO):
				EstadoJuego::get_Instance()->luz.Color = AZUL;
			break;
			case(AZUL):
				EstadoJuego::get_Instance()->luz.Color = VERDE;
			break;
			case(VERDE):
				EstadoJuego::get_Instance()->luz.Color = BLANCO;
			break;
        }
	}
    else {
		switch (EstadoJuego::get_Instance()->luz.Color) {
			case(BLANCO):
				EstadoJuego::get_Instance()->luz.Color = VERDE;
			break;
			case(ROJO):
				EstadoJuego::get_Instance()->luz.Color = BLANCO;
			break;
			case(AZUL):
				EstadoJuego::get_Instance()->luz.Color = ROJO;
			break;
			case(VERDE):
				EstadoJuego::get_Instance()->luz.Color = AZUL;
			break;
		}
	}
}

void Menu::AccionTruco(bool der) {
	EstadoJuego::get_Instance()->ModoPrueba = !EstadoJuego::get_Instance()->ModoPrueba;
}

void Menu::AccionTruco2(bool der) {
	EstadoJuego::get_Instance()->FB_Mot= !EstadoJuego::get_Instance()->FB_Mot;
}

void Menu::AccionALuz(bool der) {
	EstadoJuego::get_Instance()->luz.activa = !EstadoJuego::get_Instance()->luz.activa;
}

void Menu::AccionText(bool der) {
	EstadoJuego::get_Instance()->Texturas =! EstadoJuego::get_Instance()->Texturas;
}

void Menu::AccionInter(bool der) {
	EstadoJuego::get_Instance()->Interpolado = ! EstadoJuego::get_Instance()->Interpolado;
}

void Menu::AccionCamara(bool der) {
	if (der) {
		switch(EstadoJuego::get_Instance()->Camera) {
			case CAMARA_FIJA:
				EstadoJuego::get_Instance()->Camera = CAMARA_MOUS;
			break;
			case CAMARA_MOUS:
				EstadoJuego::get_Instance()->Camera = CAMAR_SEGUIR;
			break;
			case CAMAR_SEGUIR:
				EstadoJuego::get_Instance()->Camera = CAMARA_P1;
			break;
			case CAMARA_P1:
				EstadoJuego::get_Instance()->Camera = CAMARA_FIJA;
			break;
		}
    } else {
		switch(EstadoJuego::get_Instance()->Camera) {
			case CAMARA_FIJA:
				EstadoJuego::get_Instance()->Camera = CAMARA_P1;
			break;
			case CAMARA_MOUS:
				EstadoJuego::get_Instance()->Camera = CAMARA_FIJA;
			break;
			case CAMAR_SEGUIR:
				EstadoJuego::get_Instance()->Camera = CAMARA_MOUS;
			break;
			case CAMARA_P1:
				EstadoJuego::get_Instance()->Camera = CAMAR_SEGUIR;
			break;
		}
	}
}

void Menu::AccionSolWar(bool der) {
	if (der) {
		switch(EstadoJuego::get_Instance()->modelado) {
			case MOD_LINEAS:
				EstadoJuego::get_Instance()->modelado = MOD_COLICION;
			break;
			case MOD_COLICION:
				EstadoJuego::get_Instance()->modelado = MOD_SOLIDO;
			break;
			case MOD_SOLIDO:
				EstadoJuego::get_Instance()->modelado = MOD_LINEAS;
			break;
		}
	} else {
		switch(EstadoJuego::get_Instance()->modelado) {
			case MOD_LINEAS:
				EstadoJuego::get_Instance()->modelado = MOD_SOLIDO;
			break;
			case MOD_COLICION:
				EstadoJuego::get_Instance()->modelado = MOD_LINEAS;
			break;
			case MOD_SOLIDO:
				EstadoJuego::get_Instance()->modelado = MOD_COLICION;
			break;
		}
	}
}

Opcion Menu::getOpcion() {
	return pocision;
}