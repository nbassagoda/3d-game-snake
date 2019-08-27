#include "../include/Snake.h"
#include "../include/EventsEngine.h"

#define pi 3.1415926535897932384626433832795
#define dos_pi 6.283185307179586476925286766559

GLint Snake::ModeloS = 0;
GLint Snake::ModeloT = 0;

list<Shape*>* Snake::formaSnake = new list<Shape*>();

Snake::~Snake() {
	delete(_Coliciones);
}

Snake::Snake(float x, float y, float z, float angX, float angY, float angZ) {
	Document.open(SNAKE_DOCUMENT_PATH);
	anguloRad_Ajuste = 0.05;
	anguloRad_Actual = 0;
	anguloGra_Ajuste = anguloRad_Ajuste*360/dos_pi;
	_posicion.posX = x;
	_posicion.posY = y;
	_posicion.posZ = z;
	_posicion.angleX = angX;
	_posicion.angleY = angY;
	_posicion.angleZ = angZ;
	_posicion.size = 0.05;
	_id = Id_CODE++;
	_tipo = T_PERSONAGE;
	_clase = C_SNAKE;
	_Coliciones = new map<int, Clase_Objeto>();
	_Shape = formaSnake;
	srand((unsigned)time(NULL));
	_ColorR=((float) rand() / (RAND_MAX+1));
	_ColorG=((float) rand() / (RAND_MAX+1));
	_ColorB=((float) rand() / (RAND_MAX+1));
}

void Snake::EvolucionTiempo(float t) {
	_posicion.posX += t*sin(anguloRad_Actual);
	_posicion.posZ += t*cos(anguloRad_Actual);
	if((_posicion.posX < -Field_Limit) || (_posicion.posZ < -Field_Limit) || (Field_Limit < _posicion.posX) || (Field_Limit < _posicion.posZ)) {
		EstadoJuego::get_Instance()->AgregarAccionLisa(A_Perder);
	}
}

void Snake::Dibujar(Tipo_Modelo m,Datos_Camara Camera) {
	if(EstadoJuego::get_Instance()->estdo == Activo) {
		Motor_Eventos* Motor_Temporal = Motor_Eventos::get_Instance();
		if(Motor_Temporal->Quiero_Rotar()) {
			if(Motor_Temporal->Direccion_Rotacion()) {
				anguloRad_Actual += anguloRad_Ajuste;
				_posicion.angleY += anguloGra_Ajuste;
				if (dos_pi < anguloRad_Actual) anguloRad_Actual -= dos_pi;
			} else {
				anguloRad_Actual -= anguloRad_Ajuste;
				_posicion.angleY -= anguloGra_Ajuste;
				if (anguloRad_Actual < 0) anguloRad_Actual += dos_pi;
			}
		}
	}
	glPushMatrix();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(_posicion.posX,_posicion.posY,_posicion.posZ);
	glRotatef(_posicion.angleX,1,0,0);
	glRotatef(_posicion.angleY,0,1,0);
	glRotatef(_posicion.angleZ,0,0,1);
	glScaled(_posicion.size,_posicion.size,_posicion.size);
	if(EstadoJuego::get_Instance()->Texturas) {
		glEnable(GL_TEXTURE_2D);
		glColor4f(1,1,1,1);
	} else
		glColor4f(_ColorR,_ColorG,_ColorB,1);
	int modelo;
	if(m != MOD_COLICION) {
		if(EstadoJuego::get_Instance()->FB_Mot)
			glCallList(ModeloT);
		else
			glCallList(ModeloS);
	} else {
		glDisable(GL_TEXTURE_2D);
		list<Shape*>::iterator it;
		glColor3f(0,1,1);
		for (it = formaSnake->begin();it != formaSnake->end(); it++) {
			ShapeSphere* forma = dynamic_cast<ShapeSphere*>(*it);
			glPushMatrix();
			glTranslated(forma->posX, forma->posY, forma->posZ);
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

bool Snake::AccionColiccion() {
	map<int, Clase_Objeto>::iterator it ;
	for(it = _Coliciones->begin(); it != _Coliciones->end(); ++it)
		if(it->second == C_APPLE) {
			EstadoJuego::get_Instance()->AgregarAccionLisa(A_BONUS_Point);
		}
		return false;
}

float Snake::get_anguloActual() {
	return anguloRad_Actual;
}