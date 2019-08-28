#include "../include/GameEngine.h"
#include "../include/tinyxml.h"

GameEngine* GameEngine::instance = NULL;

GameEngine* GameEngine::GetInstance() {
	if (instance == NULL) instance = new GameEngine();
	return instance;
}

GameEngine::GameEngine() {
	Document.open(GAME_ENGINE_DOCUMENT_PATH);
	states = GameState::GetInstance();
	elements = new map<int, Object*>();
	env = new map<int, Object*>();
	int apple_identification = 2;
	character = NULL;
	now = NULL;
	Document << "[YES] [Game Engine successfully started] " << endl;
}

void GameEngine::CheckCollisions() {
	character->EmptyCollisions();
	map<int,Object*>::iterator it;

			if(character->Colicion(now)) {
				character->CollisionAction();
				apple_identification++;
				map<int, Object*>::iterator it;
				for (it = elements->begin(); it != elements->end(); ++it){
					if (it->first == apple_identification)
						now = it->second;
	}
			}

	for(it = elements->begin(); it != elements->end(); ++it) {
		it->second->CollisionAction();
	}
}

void GameEngine::TimeEvolution(float t) {
	list<to_play>::const_iterator itAc;
	for (itAc = states->actions_list->begin(); itAc != states->actions_list->end(); ++itAc) {
		to_play a = *itAc;
		switch(a) {
			case TO_LOSE:
				YouLoose();
			break;
			case TO_WIN:
				YouWon();
			break;
			case TO_BONUS_POINT:
				GameState* State = GameState::GetInstance();
				State->score += 5;
				if ((State->score == 50) && (State->level == 0)) {
					State->level++;
					DefaultStart();
				} else if ((State->score == 50) && (State->level == 1)) YouWon();
			break;
		}
	}
	states->EmptyActionsList();
	if(states->estdo == ACTIVE) { 
		character->TimeEvolution(t*states->speed);
		if(now != NULL) now->TimeEvolution(t*states->speed);
		CheckCollisions();
	}
}

void GameEngine::RestoreGame() {
	if (character != NULL) delete(character);
	character = new Snake(0,0,0,0,0,0);
	states->score = 0;
	states->estdo = ACTIVE;

	map<int, Object*>::iterator it;
	for (it = elements->begin(); it != elements->end(); ++it) {
		if (it->first == apple_identification)
			now = it->second;
	}
}
void GameEngine::DefaultStart() {
  map<int, Object*>::iterator it;
  Document << "[Default Initiation] [Memory erase started] " << endl;
  for (it = elements->begin(); it != elements->end(); ++it) delete(it->second);
  elements->clear();
  Document << "[Default Initiation] [Memory erase finished] " << endl;
  Document << "[Default Initiation] [New creation started] " << endl;
  
  TiXmlDocument document;
  if(GameState::GetInstance()->level) {
    if(!document.LoadFile("data/Level2.xml")) {
      Document << "[Default Initiation] [Level 2 could not be loaded] " << endl;
      exit(1);
    }
  } else {
    if(!document.LoadFile("data/Level1.xml")) {
      Document << "[Default Initiation] [Level 1 could not be loaded] " << endl;
      exit(1);
    }
  }

  TiXmlElement* raiz = document.FirstChildElement();
  if(raiz == NULL) {
    Document << "[Default Initiation] [Failed to load file: No root element] " << endl;
    document.Clear();
    exit(1);
  }

  int identification = apple_identification;
  int id = 0;
    for(TiXmlElement* elem = raiz->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

    Object* Obj;
    string elem_name = elem->Value();
    if ( (elem_name == "Apple") || (elem_name == "Star") ){
      float pos_x = atof(elem->Attribute("pos_x"));
      float pos_y = atof(elem->Attribute("pos_y"));
      float posZ = atof(elem->Attribute("posZ"));
      Obj = new Apple(pos_x, pos_y, posZ, 0, 0, 0);
      //elements->insert(pair<int, Object*>(Obj->GetId(), Obj));
      elements->insert(pair<int, Object*>(identification, Obj));
      identification++;
    }
    else {

      float pos_x = atof(elem->Attribute("pos_x"));
      float pos_y = atof(elem->Attribute("pos_y"));
      float posZ = atof(elem->Attribute("posZ"));

      if (elem_name == "Earth") {
        Obj = new Earth(pos_x, pos_y, posZ, 0, 0, 0);
      } 
      else if (elem_name == "Moon"){
         Obj = new Moon(pos_x, pos_y, posZ, 0, 0, 0);
      }
      else if (elem_name == "Sun") 
         Obj = new Sun(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elem_name == "Mercury") 
         Obj = new Mercury(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elem_name == "Venus") 
         Obj = new Mercury(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elem_name == "Jupiter") 
         Obj = new Jupiter(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elem_name == "Mars") 
        Obj = new Mars(pos_x, pos_y, posZ, 0, 0, 0);
      else if (elem_name == "Neptuno") 
        Obj = new Neptuno(pos_x, pos_y, posZ, 0, 0, 0);
    }


      //elements->insert(pair<int, Object*>(Obj->GetId(), Obj));
      env->insert(pair<int, Object*>(id, Obj));
      id++;
    

  }
  RestoreGame();
  Document << "[Default Initiation] [New creation finished] " << endl;
}

ObjectState GameEngine::GetState() {
	return states->estdo;
}

map<int,Object*>* GameEngine::GetEnv() {
	return env;
}

map<int,Object*>* GameEngine::GetElements() {
	return elements;
}

Object* GameEngine::GetElement() {
	return now;
}

Snake* GameEngine::GetCharacter() {
	return character;
}

void GameEngine::StartGame(string s) {
	if (states->estdo == START) {
		DefaultStart();
		Document << "[StartGame] [Default game started] " << endl;
	} else
		Document << "[StartGame] [Default game could not be started] " << endl;
}

void GameEngine::Accelerate() {
	if ((states->speed < 10)&(states->estdo == ACTIVE)) {
		states->speed += 0.05;
		Document << "[Accelerate] [Game speed increased] " << endl;
	}
}

void GameEngine::DefaultSpeed() {
	states->speed = 1;
	Document << "[DefaultSpeed] [Default game speed] " << endl;
}

void GameEngine::SlowDown() {
	if ((states->speed > 0) & (states->estdo == ACTIVE)) {
		states->speed -= 0.01;
		Document << "[SlowDown] [Game speed decreased] " << endl;
	} else {
		states->speed = 0;
		Document << "[SlowDown] [Game speed decreased] " << endl;
	}
}

void GameEngine::Substract() {
	if(states->estdo != START) {
		GameState::GetInstance()->level = 0;
		DefaultStart();
		Document << "[Substract] [Game restarted] " << endl;
	}
}

void GameEngine::Pause() {
	switch (states->estdo) {
		case PAUSE:
			states->estdo = ACTIVE;
			Document << "[Pause] [Game resumed] " << endl;
		break;
		case ACTIVE:
			states->estdo = PAUSE;
			Document << "[Pause] [Game paused] " << endl;
		break;
	}
}

void GameEngine::YouLoose() {
	if(!states->TestMode) {
		states->estdo = LOOSE;
		Document << "[YouLoose] [Game over] " << endl;
	}
}

void GameEngine::Quit() {
	states->estdo = QUIT;
	Document << "[Quit] [Game closed] " << endl;
}

void GameEngine::TrialMode() {
	states->TestMode = !states->TestMode;
	Document << "[TrialMode] [Game test] " << endl;
}

void GameEngine::YouWon() {
	states->estdo = WIN;
	Document << "[YouWon] [Game finished] " << endl;
}