#include "../include/GameEngine.h"
#include "../include/tinyxml.h"

GameEngine* GameEngine::instance = NULL;

GameEngine* GameEngine::GetInstance() {
	if (instance == NULL) instance = new GameEngine();
	return instance;
}

GameEngine::GameEngine() {
	Document.open(GAME_ENGINE_DOCUMENT_PATH);
	estados = EstadoJuego::GetInstance();
	elementos = new map<int, Objeto*>();
	ambiente = new map<int, Objeto*>();
	int apple_identification = 2;
	character = NULL;
	Now = NULL;
	Document << "[YES] [Game Engine successfully started] " << endl;
}

void GameEngine::CheckCollisions() {
	character->VaciarColiciones();
	map<int,Objeto*>::iterator it;

			if(character->Colicion(Now)) {
				character->CollisionAction();
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

void GameEngine::TimeEvolution(float t) {
	list<to_play>::const_iterator itAc;
	for (itAc = estados->actions_list->begin(); itAc != estados->actions_list->end(); ++itAc) {
		to_play a = *itAc;
		switch(a) {
			case TO_LOSE:
				YouLoose();
			break;
			case TO_WIN:
				YouWon();
			break;
			case TO_BONUS_POINT:
				EstadoJuego* Estado = EstadoJuego::GetInstance();
				Estado->score += 5;
				if ((Estado->score == 50) && (Estado->level == 0)) {
					Estado->level++;
					IniciarPorDefecto();
				} else if ((Estado->score == 50) && (Estado->level == 1)) YouWon();
			break;
		}
	}
	estados->EmptyActionsList();
	if(estados->estdo == ACTIVE) { 
		character->TimeEvolution(t*estados->speed);
		if(Now != NULL) Now->TimeEvolution(t*estados->speed);
		CheckCollisions();
	}
}

void GameEngine::RestoreGame() {
	if (character != NULL) delete(character);
	character = new Snake(0,0,0,0,0,0);
	estados->score = 0;
	estados->estdo = ACTIVE;

	map<int, Objeto*>::iterator it;
	for (it = elementos->begin(); it != elementos->end(); ++it) {
		if (it->first == apple_identification)
			Now = it->second;
	}
}
void GameEngine::IniciarPorDefecto() {
  map<int, Objeto*>::iterator it;
  Document << "[IniciarPorDefecto] [Memory erase started] " << endl;
  for (it = elementos->begin(); it != elementos->end(); ++it) delete(it->second);
  elementos->clear();
  Document << "[IniciarPorDefecto] [Memory erase finished] " << endl;
  Document << "[IniciarPorDefecto] [New creation started] " << endl;
  
  TiXmlDocument document;
  if(EstadoJuego::GetInstance()->level) {
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
      float pos_x = atof(elem->Attribute("pos_x"));
      float pos_y = atof(elem->Attribute("pos_y"));
      float posZ = atof(elem->Attribute("posZ"));
      Obj = new Apple(pos_x, pos_y, posZ, 0, 0, 0);
      //elementos->insert(pair<int, Objeto*>(Obj->getId(), Obj));
      elementos->insert(pair<int, Objeto*>(identification, Obj));
      identification++;
    }
    else {

      float pos_x = atof(elem->Attribute("pos_x"));
      float pos_y = atof(elem->Attribute("pos_y"));
      float posZ = atof(elem->Attribute("posZ"));

      if (elemName == "Earth") {
      	Document << "[IniciarPorDefecto] [entre] " << endl;
        Obj = new Earth(pos_x, pos_y, posZ, 0, 0, 0);
      	Document << "[IniciarPorDefecto] [sali] " << endl;
      } 
      else if (elemName == "Moon"){
      	Document << "[IniciarPorDefecto] [entre] " << endl;
         Obj = new Moon(pos_x, pos_y, posZ, 0, 0, 0);
      }
      else if (elemName == "Sun") 
         Obj = new Sun(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elemName == "Mercury") 
         Obj = new Mercury(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elemName == "Venus") 
         Obj = new Mercury(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elemName == "Jupiter") 
         Obj = new Jupiter(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elemName == "Mars") 
        Obj = new Mars(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elemName == "Neptuno") 
        Obj = new Neptuno(pos_x, pos_y, posZ, 0, 0, 0);
    }


      //elementos->insert(pair<int, Objeto*>(Obj->getId(), Obj));
      ambiente->insert(pair<int, Objeto*>(id, Obj));
      id++;
    

  }
  RestoreGame();
  Document << "[IniciarPorDefecto] [New creation finished] " << endl;
}

GameState GameEngine::GetState() {
	return estados->estdo;
}

map<int,Objeto*>* GameEngine::GetEnv() {
	return ambiente;
}

map<int,Objeto*>* GameEngine::GetElements() {
	return elementos;
}

Objeto* GameEngine::GetElement() {
	return Now;
}

Snake* GameEngine::GetCharacter() {
	return character;
}

void GameEngine::StartGame(string s) {
	if (estados->estdo == START) {
		IniciarPorDefecto();
		Document << "[StartGame] [Default game started] " << endl;
	} else
		Document << "[StartGame] [Default game could not be started] " << endl;
}

void GameEngine::Accelerate() {
	if ((estados->speed < 10)&(estados->estdo == ACTIVE)) {
		estados->speed += 0.01;
		Document << "[Accelerate] [Game speed increased] " << endl;
	}
}

void GameEngine::DefaultSpeed() {
	estados->speed = 1;
	Document << "[DefaultSpeed] [Default game speed] " << endl;
}

void GameEngine::SlowDown() {
	if ((estados->speed > 0) & (estados->estdo == ACTIVE)) {
		estados->speed -= 0.01;
		Document << "[SlowDown] [Game speed decreased] " << endl;
	} else {
		estados->speed = 0;
		Document << "[SlowDown] [Game speed decreased] " << endl;
	}
}

void GameEngine::Substract() {
	if(estados->estdo != START) {
		EstadoJuego::GetInstance()->level = 0;
		IniciarPorDefecto();
		Document << "[Substract] [Game restarted] " << endl;
	}
}

void GameEngine::Pause() {
	switch (estados->estdo) {
		case PAUSE:
			estados->estdo = ACTIVE;
			Document << "[Pause] [Game resumed] " << endl;
		break;
		case ACTIVE:
			estados->estdo = PAUSE;
			Document << "[Pause] [Game paused] " << endl;
		break;
	}
}

void GameEngine::YouLoose() {
	if(!estados->TestMode) {
		estados->estdo = LOOSE;
		Document << "[YouLoose] [Game over] " << endl;
	}
}

void GameEngine::Quit() {
	estados->estdo = QUIT;
	Document << "[Quit] [Game closed] " << endl;
}

void GameEngine::TrialMode() {
	estados->TestMode = !estados->TestMode;
	Document << "[TrialMode] [Game test] " << endl;
}

void GameEngine::YouWon() {
	estados->estdo = WIN;
	Document << "[YouWon] [Game finished] " << endl;
}