#include "../include/Apple.h"

int Apple::ModeloS = 0;
int Apple::ModeloT = 0;

list<Shape*>* Apple::formaApple = new list<Shape*>();

Apple::Apple(float x, float y, float z, float angX, float angY, float angZ) {
	_posicion.posX = x;
	_posicion.posY = y+0.5;
	_posicion.posZ = z;
	_posicion.angleX = angX;
	_posicion.angleY = angY;
	_posicion.angleZ = angZ;
	_posicion.size = 0.05;
	_id = Id_CODE++;
	_tipo = T_PERSONAGE;
	_clase = C_APPLE;
	_Coliciones = new map<int, Clase_Objeto>();
	_Shape = formaApple;
}

void Apple::GenerateShape() {
	formaApple->push_back(new ShapeSphere(0, 0, 10, 0.5));
}

void Apple::Dibujar(Tipo_Modelo m, Datos_Camara camara) {
	glPushMatrix();
	float n = Distancia_Puntos(_posicion.posX, _posicion.posY, _posicion.posZ, camara.posX, camara.posY, camara.posZ);
	if (n < FB_ZFar) {
		glEnable(GL_BLEND);
		float d = Distancia_Puntos(camara.direccionX, camara.direccionY, camara.direccionZ, camara.posX, camara.posY, camara.posZ);
		
		glTranslatef(_posicion.posX,_posicion.posY,_posicion.posZ);
		glRotatef(_posicion.angleY,0,1,0);
		glRotatef(90,1,0,0);
		glScaled(_posicion.size,_posicion.size,_posicion.size);
		if(EstadoJuego::get_Instance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		if(m != MOD_COLICION) {
			glCallList(ModeloS);
		} else {
			list<Shape*>::iterator it;
			glColor3f(0,1,0);
			for (it = formaApple->begin();it != formaApple->end(); it++) {
				ShapeSphere* forma = dynamic_cast<ShapeSphere*>(*it);
				glPushMatrix();
				glTranslated(forma->posX, forma->posY, forma->posZ);
				glScaled(forma->radio, forma->radio, forma->radio);
				glCallList(codigoEsfer);
				glPopMatrix();
			}
		}
	}
	glDisable(GL_ALPHA);
	glPopMatrix();
}

void Apple::EvolucionTiempo(float t) {
	_posicion.angleY += 2;
	if(_posicion.angleY > 360) _posicion.angleY -= 360;
}

bool Apple::AccionColiccion() { }

Apple::~Apple() {
	delete(_Coliciones);
}