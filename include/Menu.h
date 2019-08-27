#include "GameState.h"

#ifndef MENU_H
#define MENU_H

enum Opcion {O_Cama, O_SolWir, O_Textura, O_Inter, O_LuzAct, O_LuZDir, O_LuzColor, O_Imortal, O_FBM};

class Menu {
private:
	static Menu* instance;
	Opcion pocision;
	Menu();
	void AccionCamara(bool der);
	void AccionSolWar(bool der);
	void AccionText(bool der);
	void AccionInter(bool der);
	void AccionALuz(bool der);
	void AccionDirLuz(bool der);
	void AccionColLuz(bool der);
	void AccionTruco(bool der);
	void AccionTruco2(bool der);
	
public:
	Opcion getOpcion();
	static Menu* get_Instance();
	void AccionCambiarAriba();
	void AccionCambiarAbajo();
	void AccionElegir(bool der);
};

#endif