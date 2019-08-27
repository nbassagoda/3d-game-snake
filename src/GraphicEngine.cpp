#include "../include/GraphicEngine.h"
#include <typeinfo>

#include <iostream>
#include <fstream>

#define pi 3.14159265

Motor_Grafico* Motor_Grafico::instance = NULL;

Motor_Grafico* Motor_Grafico::get_Instance() {
	if (instance == NULL) instance = new Motor_Grafico();
	return instance;
}

Motor_Grafico::Motor_Grafico() {
	Document.open(GRAPHICS_ENGINE_DOCUMENT_PATH);
	EstadoJuego::get_Instance()->modelado = MOD_SOLIDO;
	CargaAmbiente();
	CargaModelos();
	Camera.camar = CAMARA_FIJA;
	Camera.posX = 0;
	Camera.posY = 0;
	Camera.posZ = 0;
	Camera.r = 5;
	Camera.direccionX = 0;
	Camera.direccionY = 0;
	Camera.direccionZ = -5;
	Camera.normalX = 0;
	Camera.normalY = 1;
	Camera.normalYR = 1;
	Camera.normalZ = 0;
	Camera.phi = 0;
	Camera.theta = pi/2;
	Camera.Yup = 1.f;
	Camera.restaX = false;
	Camera.restaY = false;

	EstadoJuego::get_Instance()->Texturas = true;
	EstadoJuego::get_Instance()->luz.activa = true;
	Document << "[Motor_Grafico] [Motor Grafico inicio correctamente]" << endl;
}

void Motor_Grafico::CargaAmbiente() {
	glClearColor(Clear_Color, Clear_Color, Clear_Color, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,z_near,z_far);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_COLOR_ALPHA_PAIRING_ATI);
	Document << "[CargaAmbiente] [Environment loaded]" << endl;
}

void Motor_Grafico::CargaModelos() {
	CargaTextura(TEXTURE_GRASS, GRASS_TEXTURE_PATH);
	CargaTextura(TEXTURE_WOOD, WOOD_TEXTURE_PATH);
	CargaTextura(TEXTURE_STONE, STONE_TEXTURE_PATH);
	CargaTextura(TEXTURE_SNAKE, SNAKE_TEXTURE_PATH);
	CargaTextura(TEXTURE_APPLE, APPLE_TEXTURE_PATH);
	CargaTextura(TEXTURE_GALAXY, GALAXY_TEXTURE_PATH);
	CargaTextura(TEXTURE_GRASS, GRASS_TEXTURE_PATH);
  CargaTextura(TEXTURE_WOOD, WOOD_TEXTURE_PATH);
  CargaTextura(TEXTURE_STONE, STONE_TEXTURE_PATH);
  CargaTextura(TEXTURE_SNAKE, SNAKE_TEXTURE_PATH);
  CargaTextura(TEXTURE_APPLE, APPLE_TEXTURE_PATH);
  CargaTextura(TEXTURE_STAR, STAR_TEXTURE_PATH);
  CargaTextura(TEXTURE_EARTH, EARTH_TEXTURE_PATH);
  CargaTextura(TEXTURE_MOON, MOON_TEXTURE_PATH);
  CargaTextura(TEXTURE_SUN, SUN_TEXTURE_PATH);
  CargaTextura(TEXTURE_MERCURY, MERCURY_TEXTURE_PATH);
  CargaTextura(TEXTURE_VENUS, VENUS_TEXTURE_PATH);
  CargaTextura(TEXTURE_JUPITER, JUPITER_TEXTURE_PATH);
  CargaTextura(TEXTURE_MARS, MARS_TEXTURE_PATH);
  CargaTextura(TEXTURE_NEPTUNO, NEPTUNO_TEXTURE_PATH);

	Earth::modelS = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_EARTH);
	Earth::modelT = Earth::modelS;

	Moon::modelS = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_MOON);
	Moon::modelT = Moon::modelS;

	Sun::modelS = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_SUN);
	Sun::modelT = Sun::modelS;

	Mercury::modelS = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_MERCURY);
	Mercury::modelT = Mercury::modelS;

	Venus::modelS = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_VENUS);
	Venus::modelT = Venus::modelS;

	Jupiter::modelS = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_JUPITER);
	Jupiter::modelT = Jupiter::modelS;

	Mars::modelS = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_URANO);
	Mars::modelT = Mars::modelS;

	Neptuno::modelS = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_NEPTUNO);
	Neptuno::modelT = Neptuno::modelS;

	
	Snake::modelS = CargarObjeto::CaragarSolidTextura(SNAKE_OBJECT_PATH, TEXTURE_SNAKE);
    Snake::modelT = Snake::modelS;

    if (EstadoJuego::get_Instance()->nivel != 0){
        Apple::modelS = CargarObjeto::CaragarSolidTextura(APPLE_OBJECT_PATH, TEXTURE_APPLE);
        Apple::modelT = Apple::modelS;
        Document << "[CargaModelos] deberia ser manzana" << endl;
    }
    else{
    	Document << "[CargaModelos] deberia ser estrella" << endl;
        Apple::modelS = CargarObjeto::CaragarSolidTextura(STAR_OBJECT_PATH, TEXTURE_STAR);
        Apple::modelT = Apple::modelS;
    }
    
    Snake::GenerateShape();
    Apple::GenerateShape();
    Document << "[CargaModelos] [Models loaded]" << endl;
}

void Motor_Grafico::CargaTextura(GLuint &texture, const char* texture_name) {
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(texture_name);
	FIBITMAP* bitmap = FreeImage_Load(fif, texture_name);
	bitmap = FreeImage_ConvertTo24Bits(bitmap);
	
	int width = FreeImage_GetWidth(bitmap);
	int height = FreeImage_GetHeight(bitmap);
	
	glGenTextures(1, &texture);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, FreeImage_GetBits(bitmap));
	Document << "[CargaTextura] [Texture _" << texture_name << "_ loaded]" << endl;
}

void Motor_Grafico::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45.0f,(GLfloat)640/(GLfloat)480,0.1f,200.0f);
	glMatrixMode(GL_MODELVIEW);
	if (EstadoJuego::get_Instance()->modelado != MOD_SOLIDO) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	if (EstadoJuego::get_Instance()->Interpolado) glShadeModel(GL_SMOOTH);
	else glShadeModel(GL_FLAT);

	DrawLuz();
	DrawCamara();
	DrawAmbiente();
	DrawEsenario();
	
	if (!EstadoJuego::get_Instance()->luz.activa) glDisable(GL_LIGHTING);
	else glEnable(GL_LIGHTING);
	
	DrawPersonajes();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DrawContexto();
}

void Motor_Grafico::DrawLuz() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat ambient[] = {0.4f, 0.4f, 0.4f};
	GLfloat diffuseLight[] = {1, 1, 1, 1};
	GLfloat specularLight[] = {0.6f, 0.6f, 0.6f, 1.0f};
	float posX,posY,posZ;
	float colorR,colorG,colorB;
	switch(EstadoJuego::get_Instance()->luz.Posicion) {
		case L_Arriba:
			posX = 0;
			posY = 100;
			posZ = 0;
		break;
		case L_Adeante:
			posX = 600;
			posY = 10;
			posZ = 0;
		break;
		case L_Atras:
			posX = -50;
			posY = 10;
			posZ = 0;
		break;
		case L_Der:
			posX = 250;
			posY = 10;
			posZ = 30;
		break;
		case L_Izq:
			posX = 250;
			posY = 10;
			posZ = -30;
		break;
	}

	switch(EstadoJuego::get_Instance()->luz.Color) {
		case BLANCO:
			colorR =1;
			colorG =1;
			colorB =1;
		break;
		case ROJO:
			colorR =1;
			colorG =0;
			colorB =0;
		break;
		case VERDE:
			colorR =0;
			colorG =1;
			colorB =0;
		break;
		case AZUL:
			colorR =0;
			colorG =0;
			colorB =1;
		break;
	}
	GLfloat posicion_inicial[] = {posX,posY,posZ, 1.0f};
	GLfloat color[] = {colorR,colorG,colorB, 1.0f};


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_COLOR,color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion_inicial);
}

void Motor_Grafico::DrawContexto() {
	Motor_Pantalla::get_Instance()->DrawPantalla();
}

int ang = 0;

void Motor_Grafico::DrawEsenario() {
	float x = 0;
	float y = Field_Size;
	float z = 0;
	float size = Field_Size;
	float factor = 0.5;
	
	glPushMatrix();
	glColor4f(1,1,1,1);
	


	if(EstadoJuego::get_Instance()->Texturas) glEnable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);

	if (EstadoJuego::get_Instance()->nivel == 0){
	  glBindTexture(GL_TEXTURE_2D, TEXTURE_STONE);
	}
	else{
	  glBindTexture(GL_TEXTURE_2D, TEXTURE_GALAXY);
	}

	glBegin(GL_QUADS);
		glTexCoord2d(0,1);glVertex3f(x + size, y, z - size); // V2
		glTexCoord2d(1,1);glVertex3f(x - size, y, z - size); // V1
		glTexCoord2d(1,0);glVertex3f(x - size, y - size, z - size); // V5
		glTexCoord2d(0,0);glVertex3f(x + size, y - size, z - size); // V6
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2d(0,1);glVertex3f(x + size, y, z + size); // V3
		glTexCoord2d(1,1);glVertex3f(x + size, y, z - size); // V2
		glTexCoord2d(1,0);glVertex3f(x + size, y - size, z - size); // V6
		glTexCoord2d(0,0);glVertex3f(x + size, y - size, z + size); // V7
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2d(0,1);glVertex3f(x - size, y, z + size); // V4
		glTexCoord2d(1,1);glVertex3f(x + size, y, z + size); // V3
		glTexCoord2d(1,0);glVertex3f(x + size, y - size, z + size); // V7
		glTexCoord2d(0,0);glVertex3f(x - size, y - size, z + size); // V8
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2d(0,1);glVertex3f(x - size, y, z - size); // V1
		glTexCoord2d(1,1);glVertex3f(x - size, y, z + size); // V4
		glTexCoord2d(1,0);glVertex3f(x - size, y - size, z + size); // V8
		glTexCoord2d(0,0);glVertex3f(x - size, y - size, z - size); // V5
	glEnd();
	
	if (EstadoJuego::get_Instance()->nivel == 0){
		glBindTexture(GL_TEXTURE_2D, TEXTURE_GRASS);
	}
	
	glBegin(GL_QUADS);
		glTexCoord2d(1,1);glVertex3f(x - size, y - size, z - size); // V5
		glTexCoord2d(1,0);glVertex3f(x + size, y - size, z - size); // V6
		glTexCoord2d(0,0);glVertex3f(x + size, y - size, z + size); // V7
		glTexCoord2d(0,1);glVertex3f(x - size, y - size, z + size); // V8
	glEnd();

	if (EstadoJuego::get_Instance()->nivel == 0)
		glBindTexture(GL_TEXTURE_2D, TEXTURE_WOOD);
	else
		glBindTexture(GL_TEXTURE_2D, TEXTURE_GALAXY);

		glBegin(GL_QUADS);
			glTexCoord2d(0,1);glVertex3f(x + size - factor, y, z - size);
			glTexCoord2d(1,1);glVertex3f(x + size - factor, y, z - size + factor);
			glTexCoord2d(1,0);glVertex3f(x + size - factor, y - size, z - size + factor);
			glTexCoord2d(0,0);glVertex3f(x + size - factor, y - size, z - size);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2d(0,1);glVertex3f(x + size - factor, y, z - size + factor);
			glTexCoord2d(1,1);glVertex3f(x + size, y, z - size + factor);
			glTexCoord2d(1,0);glVertex3f(x + size, y - size, z - size + factor);
			glTexCoord2d(0,0);glVertex3f(x + size - factor, y - size, z - size + factor);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2d(0,1);glVertex3f(x - size, y, z - size + factor);
			glTexCoord2d(1,1);glVertex3f(x - size + factor, y, z - size + factor);
			glTexCoord2d(1,0);glVertex3f(x - size + factor, y - size, z - size + factor);
			glTexCoord2d(0,0);glVertex3f(x - size, y - size, z - size + factor);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2d(0,1);glVertex3f(x - size + factor, y, z - size + factor);
			glTexCoord2d(1,1);glVertex3f(x - size + factor, y, z - size);
			glTexCoord2d(1,0);glVertex3f(x - size + factor, y - size, z - size);
			glTexCoord2d(0,0);glVertex3f(x - size + factor, y - size, z - size + factor);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2d(0,1);glVertex3f(x - size + factor, y, z + size - factor);
			glTexCoord2d(1,1);glVertex3f(x - size, y, z + size - factor);
			glTexCoord2d(1,0);glVertex3f(x - size, y - size, z + size - factor);
			glTexCoord2d(0,0);glVertex3f(x - size + factor, y - size, z + size - factor);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2d(0,1);glVertex3f(x - size + factor, y, z + size);
			glTexCoord2d(1,1);glVertex3f(x - size + factor, y, z + size - factor);
			glTexCoord2d(1,0);glVertex3f(x - size + factor, y - size, z + size - factor);
			glTexCoord2d(0,0);glVertex3f(x - size + factor, y - size, z + size);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2d(0,1);glVertex3f(x + size - factor, y, z + size - factor);
			glTexCoord2d(1,1);glVertex3f(x + size - factor, y, z + size);
			glTexCoord2d(1,0);glVertex3f(x + size - factor, y - size, z + size);
			glTexCoord2d(0,0);glVertex3f(x + size - factor, y - size, z + size - factor);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2d(0,1);glVertex3f(x + size, y, z + size - factor);
			glTexCoord2d(1,1);glVertex3f(x + size - factor, y, z + size - factor);
			glTexCoord2d(1,0);glVertex3f(x + size - factor, y - size, z + size - factor);
			glTexCoord2d(0,0);glVertex3f(x + size, y - size, z + size - factor);
		glEnd();
	
	glDisable(GL_TEXTURE_2D);
	
	if (EstadoJuego::get_Instance()->nivel != 0){
		ang += 0.6;
		


		glEnable(GL_BLEND);
		
		glEnable(GL_BLEND);
		glTranslatef(0,2.5,0);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::get_Instance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Sun::modelS);
		//}


		glTranslatef(-10,0,2);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::get_Instance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Earth::modelS);
		//}

		glTranslatef(3,0,3);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::get_Instance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Moon::modelS);
		//}
		glTranslatef(5,0,10);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::get_Instance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Mars::modelS);
		//}
		glTranslatef(-3,0,-7);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::get_Instance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(2,0,-2);
		//if(m != MOD_COLICION) {
			glCallList(Mercury::modelS);
		//}
		glTranslatef(4,0,3);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::get_Instance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
			glCallList(Venus::modelS);

		glTranslatef(3,0,5);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::get_Instance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
			glCallList(Jupiter::modelS);

		glTranslatef(-8,0,1);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::get_Instance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
			glCallList(Neptuno::modelS);
		glDisable(GL_ALPHA);
		glPopMatrix();
	}
	/*map<int,Objeto*>* ambiente = Motor_Juego::get_Instance()->getAmbiente();
	map<int, Objeto*>::iterator it;
	for (it = ambiente->begin(); it != ambiente->end(); ++it){
		if (it->first == 0)
			it->second->Draw(EstadoJuego::get_Instance()->modelado, Camera);
	}*/

}

void Motor_Grafico::DrawCamara() {
	Snake* PersonageControlado = Motor_Juego::get_Instance()->getPersonajeControlable();
	glLoadIdentity();
	switch (EstadoJuego::get_Instance()->Camera) {
		case CAMARA_FIJA:
			if(PersonageControlado != NULL) {
				Camera.posX = PersonageControlado->getPos().posX;
				Camera.direccionX = PersonageControlado->getPos().posX;
				Camera.direccionZ = PersonageControlado->getPos().posZ;
			}
			Camera.posY = 5;
			Camera.posZ = 15;
			Camera.direccionY =  3;
			Camera.normalX = 0;
			Camera.normalY = 1;
			Camera.normalZ = 0;
			Camera.posXR = Camera.posX;
			Camera.posYR = Camera.posY;
			Camera.posZR = Camera.posZ;
		break;
		case FOLLOW:
			if(PersonageControlado != NULL) {
				Camera.posX = (PersonageControlado->getPos().posX - sin(PersonageControlado->get_anguloActual())*10);
				Camera.direccionX = PersonageControlado->getPos().posX + sin(PersonageControlado->get_anguloActual());
				Camera.direccionZ =PersonageControlado->getPos().posZ + cos(PersonageControlado->get_anguloActual());
				Camera.posZ = PersonageControlado->getPos().posZ - cos(PersonageControlado->get_anguloActual())*10;
			}
			Camera.posY = 3;
			Camera.direccionY =  3;
			Camera.normalX = 0;
			Camera.normalY = 1;
			Camera.normalZ = 0;
		break;
		case FIRST_PERSON:
			if(PersonageControlado != NULL) {
				Camera.posX = PersonageControlado->getPos().posX;
				Camera.posZ = PersonageControlado->getPos().posZ;
				Camera.direccionX = PersonageControlado->getPos().posX + sin(PersonageControlado->get_anguloActual());
				Camera.direccionZ = PersonageControlado->getPos().posZ + cos(PersonageControlado->get_anguloActual());
				Camera.posY = 0.5;
				Camera.direccionY = 0.5;
			}
			Camera.normalX = 0;
			Camera.normalY = 1;
			Camera.normalZ = 0;
		break;
		case MOUSE:
			if(PersonageControlado != NULL) {
				Camera.direccionX = (PersonageControlado->getPos().posX);
				Camera.direccionZ = PersonageControlado->getPos().posZ;
				Camera.direccionY =  PersonageControlado->getPos().posY;
				Camera.posX =Camera.posXR + Camera.direccionX;
				Camera.posY = Camera.posYR;
				Camera.posZ=Camera.posZR;
				/*Camera.posX = PersonageControlado->getPos().posX;
				Camera.direccionX = 0;
				Camera.direccionZ = 0;
				Camera.direccionY =  0;*/
			}
			Camera.normalX = 0;
			Camera.normalY =Camera.normalYR;
			Camera.normalZ = 0;
		break;
	}
	gluLookAt(Camera.posX , Camera.posY, Camera.posZ, Camera.direccionX, Camera.direccionY, Camera.direccionZ, Camera.normalX, Camera.normalY, Camera.normalZ);
}

void Motor_Grafico::DrawPersonajes() {
	Snake* personage = Motor_Juego::get_Instance()->getPersonajeControlable();
	if (personage != NULL) personage->Draw(EstadoJuego::get_Instance()->modelado, Camera);
}

void Motor_Grafico::DrawAmbiente() {
	Objeto* Tem = Motor_Juego::get_Instance()->getElemento();
	if (Tem != NULL) Tem->Draw(EstadoJuego::get_Instance()->modelado, Camera);
}

void Motor_Grafico::CambiarCamara() {
	switch (EstadoJuego::get_Instance()->Camera) {
		case CAMARA_FIJA:
			Camera.camar = MOUSE;
		break;
		case FOLLOW:
			Camera.camar = FIRST_PERSON;
		break;
		case FIRST_PERSON:
			Camera.camar = CAMARA_FIJA;
		break;
		case MOUSE:
			Camera.camar = FOLLOW;
		break;
	}
	EstadoJuego::get_Instance()->Camera = Camera.camar;
}

void Motor_Grafico::CambiarModo() {
	Document.open(GRAPHICS_ENGINE_DOCUMENT_PATH);
	switch (EstadoJuego::get_Instance()->modelado) {
		case MOD_SOLIDO:
			EstadoJuego::get_Instance()->modelado = MOD_LINEAS;
			Document << "[GRAPHIC ENGINE] Cambio Modo: MOD_SOLIDO" << endl;
		break;
		case MOD_LINEAS:
			EstadoJuego::get_Instance()->modelado = MOD_COLICION;
			Document << "[GRAPHIC ENGINE] Cambio Modo: MOD_LINEAS" << endl;
		break;
		case MOD_COLICION:
			EstadoJuego::get_Instance()->modelado = MOD_SOLIDO;
			Document << "[GRAPHIC ENGINE] Cambio Modo: MOD_COLICION" << endl;
		break;
	}
}

void Motor_Grafico::MotionCamara(int x, int y) {
	Document.open(GRAPHICS_ENGINE_DOCUMENT_PATH);
	float deltaY = (float)y /25;
	float deltaX = (float)-x/25;
	float dy;
	float dx;

	float phi = asin(deltaX/Camera.r);
	float theta =acos(deltaY/Camera.r);
	float radio = Camera.r;

	dy = abs((pi/2)-(theta));

	if (deltaY > 0)
		Camera.theta -= dy;
	else if (0 > deltaY)
		Camera.theta += dy;
	
	if (deltaX>0)
		Camera.phi += phi;
	else if (0>deltaX)
		Camera.phi+=phi;
	
	Camera.theta = fmod(Camera.theta ,2*pi);
	Camera.phi = fmod(Camera.phi ,2*pi);
	
	
	float xNuevo = radio*sin(Camera.theta)*sin(Camera.phi) ; // x
	float yNuevo = radio*cos(Camera.theta) ; // y
	float zNuevo = radio*sin(Camera.theta)*cos(Camera.phi);
	
	if (((Camera.theta)> 0)&& (Camera.theta)< pi) Camera.normalYR = 1;
	else Camera.normalYR = -1;
	
	Camera.posXR = xNuevo;
	Camera.posYR = yNuevo;
	Camera.posZR = zNuevo;
}

void Motor_Grafico::ActivarDesactivarLuz() {
	EstadoJuego::get_Instance()->luz.activa =!EstadoJuego::get_Instance()->luz.activa;
}

void Motor_Grafico::ActivarDesctivarTextura() {
	EstadoJuego::get_Instance()->Texturas = !EstadoJuego::get_Instance()->Texturas;
}

void Motor_Grafico::ruedita(bool cmp) {
	if (cmp == false) {
		if (Camera.r < 15) {
			Camera.r += 0.9;
		}
	}
	if (cmp == true) {
		if (Camera.r > 6) {
			Camera.r -= 0.9;
		}
	}	
}