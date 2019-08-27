#include "../include/Snake.h"
#include "../include/EventsEngine.h"

#define pi 3.1415926535897932384626433832795
#define dos_pi 6.283185307179586476925286766559

GLint Snake::model_s = 0;
GLint Snake::model_t = 0;

list<Shape*>* Snake::formaSnake = new list<Shape*>();

Snake::~Snake() {
	delete(_Coliciones);
}

Snake::Snake(float x, float y, float z, float ang_x, float ang_y, float ang_z) {
	Document.open(SNAKE_DOCUMENT_PATH);
	anguloRad_Ajuste = 0.05;
	anguloRad_Actual = 0;
	anguloGra_Ajuste = anguloRad_Ajuste*360/dos_pi;
	_posicion.pos_x = x;
	_posicion.pos_y = y;
	_posicion.posZ = z;
	_posicion.angle_x = ang_x;
	_posicion.angle_y = ang_y;
	_posicion.angle_z = ang_z;
	_posicion.size = 0.05;
	_id = Id_CODE++;
	_tipo = T_CHAR;
	_clase = C_SNAKE;
	_Coliciones = new map<int, ObjectClass>();
	_Shape = formaSnake;
	srand((unsigned)time(NULL));
	_ColorR=((float) rand() / (RAND_MAX+1));
	_ColorG=((float) rand() / (RAND_MAX+1));
	_ColorB=((float) rand() / (RAND_MAX+1));
}

void Snake::TimeEvolution(float t) {
	_posicion.pos_x += t*sin(anguloRad_Actual);
	_posicion.posZ += t*cos(anguloRad_Actual);
	if((_posicion.pos_x < -field_limit) || (_posicion.posZ < -field_limit) || (field_limit < _posicion.pos_x) || (field_limit < _posicion.posZ)) {
		EstadoJuego::GetInstance()->AddActionList(TO_LOSE);
	}
}

void Snake::Draw(ModelType m,data_camera Camera) {
	if(EstadoJuego::GetInstance()->estdo == ACTIVE) {
		EventsEngine* Motor_Temporal = EventsEngine::GetInstance();
		if(Motor_Temporal->Rotate()) {
			if(Motor_Temporal->RotationDirection()) {
				anguloRad_Actual += anguloRad_Ajuste;
				_posicion.angle_y += anguloGra_Ajuste;
				if (dos_pi < anguloRad_Actual) anguloRad_Actual -= dos_pi;
			} else {
				anguloRad_Actual -= anguloRad_Ajuste;
				_posicion.angle_y -= anguloGra_Ajuste;
				if (anguloRad_Actual < 0) anguloRad_Actual += dos_pi;
			}
		}
	}
	glPushMatrix();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(_posicion.pos_x,_posicion.pos_y,_posicion.posZ);
	glRotatef(_posicion.angle_x,1,0,0);
	glRotatef(_posicion.angle_y,0,1,0);
	glRotatef(_posicion.angle_z,0,0,1);
	glScaled(_posicion.size,_posicion.size,_posicion.size);
	if(EstadoJuego::GetInstance()->Texturas) {
		glEnable(GL_TEXTURE_2D);
		glColor4f(1,1,1,1);
	} else
		glColor4f(_ColorR,_ColorG,_ColorB,1);
	int modelo;
	if(m != MOD_COLICION) {
		if(EstadoJuego::GetInstance()->motion)
			glCallList(model_t);
		else
			glCallList(model_s);
	} else {
		glDisable(GL_TEXTURE_2D);
		list<Shape*>::iterator it;
		glColor3f(0,1,1);
		for (it = formaSnake->begin();it != formaSnake->end(); it++) {
			ShapeSphere* forma = dynamic_cast<ShapeSphere*>(*it);
			glPushMatrix();
			glTranslated(forma->pos_x, forma->pos_y, forma->posZ);
			glScaled(forma->radio, forma->radio, forma->radio);
			glCallList(codigoEsfer);
			glPopMatrix();
		}
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void Snake::GenerateShape() {
	formaSnake->push_back(new ShapeSphere(0,0,0,1));
}

bool Snake::CollisionAction() {
	map<int, ObjectClass>::iterator it ;
	for(it = _Coliciones->begin(); it != _Coliciones->end(); ++it)
		if(it->second == C_APPLE) {
			EstadoJuego::GetInstance()->AddActionList(TO_BONUS_POINT);
		}
		return false;
}

float Snake::get_anguloActual() {
	return anguloRad_Actual;
}