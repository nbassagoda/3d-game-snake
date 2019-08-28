#include "GameState.h"

#ifndef MENU_H
#define MENU_H

enum Option {O_CAMERA, O_SUN, O_TEXTURE, O_INTER, O_LIGHT, O_LIGHT_DIR, O_LIGHT_COLOR, O_TRICK, O_TRICK_2};

class Menu {
private:
	static Menu* instance;
	Option position;
	Menu();
	void cameraAction(bool der);
	void SunAction(bool der);
	void TextAction(bool der);
	void InterAction(bool der);
	void LightAction(bool der);
	void LightDirection(bool der);
	void LightColAction(bool der);
	void TrickAction(bool der);
	void TrickAction2(bool der);
	
public:
	Option getOption();
	static Menu* GetInstance();
	void ChangeUp();
	void ChangeDown();
	void ChooseAction(bool der);
};

#endif