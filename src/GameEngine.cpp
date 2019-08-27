#include "../include/GameEngine.h"
#include "../include/tinyxml.h"

Motor_Juego* Motor_Juego::instance = NULL;

Motor_Juego* Motor_Juego::get_Instance() {
	if (instance == NULL) instance = new Motor_Juego();
	return instance;
}

Motor_Juego::Motor_Juego() {
	Document.open(GAME_ENGINE_DOCUMENT_PATH);
	estados = EstadoJuego::get_Instance();
	elementos = new map<int, Objeto*>();
	ambiente = new map<int, Objeto*>();
	int apple_identification = 2;
	PersonjeControlable = NULL;
	Now = NULL;
	Document << "[YES] [Game Engine successfully started] " << endl;
}

void Motor_Juego::VerColicionesPersonaje() {
	PersonjeControlable->VaciarColiciones();
	map<int,Objeto*>::iterator it;

			if(PersonjeControlable->Colicion(Now)) {
				PersonjeControlable->CollisionAction();
				apple_identification++;
				map<int, Objeto*>::iterator it;
				for (it = elementos->begin(); it != elementos->end(); ++it){
					if (it->first == apple_identification)
						Now = it->second;
	}
			}

	for(it = elementos->begin(); it != elementos->end(); ++it) {
		it->second->CollisionAction();
	}
}

void Motor_Juego::TimeEvolution(float t) {
	list<to_play>::const_iterator itAc;
	for (itAc = estados->listaAcciones->begin(); itAc != estados->listaAcciones->end(); ++itAc) {
		to_play a = *itAc;
		switch(a) {
			case TO_LOSE:
				AccionPerder();
			break;
			case TO_WIN:
				AccionGanar();
			break;
			case TO_BONUS_POINT:
				EstadoJuego* Estado = EstadoJuego::get_Instance();
				Estado->Puntage += 5;
				if ((Estado->Puntage == 50) && (Estado->nivel == 0)) {
					Estado->nivel++;
					IniciarPorDefecto();
				} else if ((Estado->Puntage == 50) && (Estado->nivel == 1)) AccionGanar();
			break;
		}
	}
	estados->VaciarListaAcciones();
	if(estados->estdo == Activo) { 
		PersonjeControlable->TimeEvolution(t*estados->velocidad);
		if(Now != NULL) Now->TimeEvolution(t*estados->velocidad);
		VerColicionesPersonaje();
	}
}

void Motor_Juego::RestableserJuego() {
	if (PersonjeControlable != NULL) delete(PersonjeControlable);
	PersonjeControlable = new Snake(0,0,0,0,0,0);
	estados->Puntage = 0;
	estados->estdo = Activo;

	map<int, Objeto*>::iterator it;
	for (it = elementos->begin(); it != elementos->end(); ++it) {
		if (it->first == apple_identification)
			Now = it->second;
	}
}
void Motor_Juego::IniciarPorDefecto() {
  map<int, Objeto*>::iterator it;
  Document << "[IniciarPorDefecto] [Memory erase started] " << endl;
  for (it = elementos->begin(); it != elementos->end(); ++it) delete(it->second);
  elementos->clear();
  Document << "[IniciarPorDefecto] [Memory erase finished] " << endl;
  Document << "[IniciarPorDefecto] [New creation started] " << endl;
  
  TiXmlDocument document;
  if(EstadoJuego::get_Instance()->nivel) {
    if(!document.LoadFile("data/Level2.xml")) {
      Document << "[IniciarPorDefecto] [Level 2 could not be loaded] " << endl;
      exit(1);
    }
  } else {
    if(!document.LoadFile("data/Level1.xml")) {
      Document << "[IniciarPorDefecto] [Level 1 could not be loaded] " << endl;
      exit(1);
    }
  }

  TiXmlElement* raiz = document.FirstChildElement();
  if(raiz == NULL) {
    Document << "[IniciarPorDefecto] [Failed to load file: No root element] " << endl;
    document.Clear();
    exit(1);
  }

  int identification = apple_identification;
  int id = 0;
    for(TiXmlElement* elem = raiz->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

    Objeto* Obj;
    string elemName = elem->Value();
    if ( (elemName == "Apple") || (elemName == "Star") ){
      float posX = atof(elem->Attribute("posX"));
      float posY = atof(elem->Attribute("posY"));
      float posZ = atof(elem->Attribute("posZ"));
      Obj = new Apple(posX, posY, posZ, 0, 0, 0);
      //elementos->insert(pair<int, Objeto*>(Obj->getId(), Obj));
      elementos->insert(pair<int, Objeto*>(identification, Obj));
      identification++;
    }
    else {

      float posX = atof(elem->Attribute("posX"));
      float posY = atof(elem->Attribute("posY"));
      float posZ = atof(elem->Attribute("posZ"));

      if (elemName == "Earth") {
      	Document << "[IniciarPorDefecto] [entre] " << endl;
        Obj = new Earth(posX, posY, posZ, 0, 0, 0);
      	Document << "[IniciarPorDefecto] [sali] " << endl;
      } 
      else if (elemName == "Moon"){
      	Document << "[IniciarPorDefecto] [entre] " << endl;
         Obj = new Moon(posX, posY, posZ, 0, 0, 0);
      }
      else if (elemName == "Sun") 
         Obj = new Sun(posX, posY, posZ, 0, 0, 0);
      else if (elemName == "Mercury") 
         Obj = new Mercury(posX, posY, posZ, 0, 0, 0);
      else if (elemName == "Venus") 
         Obj = new Mercury(posX, posY, posZ, 0, 0, 0);
      else if (elemName == "Jupiter") 
         Obj = new Jupiter(posX, posY, posZ, 0, 0, 0);
      else if (elemName == "Mars") 
        Obj = new Mars(posX, posY, posZ, 0, 0, 0);
      else if (elemName == "Neptuno") 
        Obj = new Neptuno(posX, posY, posZ, 0, 0, 0);
    }


      //elementos->insert(pair<int, Objeto*>(Obj->getId(), Obj));
      ambiente->insert(pair<int, Objeto*>(id, Obj));
      id++;
    

  }
  RestableserJuego();
  Document << "[IniciarPorDefecto] [New creation finished] " << endl;
}

Estado_Juego Motor_Juego::getEstado() {
	return estados->estdo;
}

map<int,Objeto*>* Motor_Juego::getAmbiente() {
	return ambiente;
}

map<int,Objeto*>* Motor_Juego::getElementos() {
	return elementos;
}

Objeto* Motor_Juego::getElemento() {
	return Now;
}

Snake* Motor_Juego::getPersonajeControlable() {
	return PersonjeControlable;
}

void Motor_Juego::AccionIniciarJuego(string s) {
	if (estados->estdo == Inicio) {
		IniciarPorDefecto();
		Document << "[AccionIniciarJuego] [Default game started] " << endl;
	} else
		Document << "[AccionIniciarJuego] [Default game could not be started] " << endl;
}

void Motor_Juego::AccionAccelerar() {
	if ((estados->velocidad < 10)&(estados->estdo == Activo)) {
		estados->velocidad += 0.01;
		Document << "[AccionAccelerar] [Game speed increased] " << endl;
	}
}

void Motor_Juego::AccionVelocidadPorDefecot() {
	estados->velocidad = 1;
	Document << "[AccionVelocidadPorDefecot] [Default game speed] " << endl;
}

void Motor_Juego::AccionEnlentecer() {
	if ((estados->velocidad > 0) & (estados->estdo == Activo)) {
		estados->velocidad -= 0.01;
		Document << "[AccionEnlentecer] [Game speed decreased] " << endl;
	} else {
		estados->velocidad = 0;
		Document << "[AccionEnlentecer] [Game speed decreased] " << endl;
	}
}

void Motor_Juego::AccionRestar() {
	if(estados->estdo != Inicio) {
		EstadoJuego::get_Instance()->nivel = 0;
		IniciarPorDefecto();
		Document << "[AccionRestar] [Game restarted] " << endl;
	}
}

void Motor_Juego::AccionPausar() {
	switch (estados->estdo) {
		case Pausado:
			estados->estdo = Activo;
			Document << "[AccionPausar] [Game resumed] " << endl;
		break;
		case Activo:
			estados->estdo = Pausado;
			Document << "[AccionPausar] [Game paused] " << endl;
		break;
	}
}

void Motor_Juego::AccionPerder() {
	if(!estados->ModoPrueba) {
		estados->estdo = Perdio;
		Document << "[AccionPerder] [Game over] " << endl;
	}
}

void Motor_Juego::AccionSalir() {
	estados->estdo = Salir;
	Document << "[AccionSalir] [Game closed] " << endl;
}

void Motor_Juego::AccionModoPrueba() {
	estados->ModoPrueba = !estados->ModoPrueba;
	Document << "[AccionModoPrueba] [Game test] " << endl;
}

void Motor_Juego::AccionGanar() {
	estados->estdo = Gano;
	Document << "[AccionGanar] [Game finished] " << endl;
}