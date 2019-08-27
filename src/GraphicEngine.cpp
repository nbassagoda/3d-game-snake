#include "../include/GraphicEngine.h"
#include <typeinfo>

#include <iostream>
#include <fstream>

#define pi 3.14159265

GraphicEngine* GraphicEngine::instance = NULL;

GraphicEngine* GraphicEngine::GetInstance() {
	if (instance == NULL) instance = new GraphicEngine();
	return instance;
}

GraphicEngine::GraphicEngine() {
	Document.open(GRAPHICS_ENGINE_DOCUMENT_PATH);
	EstadoJuego::GetInstance()->modelado = MOD_SOLIDO;
	CargaAmbiente();
	CargaModelos();
	Camera.camar = CAMARA_FIJA;
	Camera.pos_x = 0;
	Camera.pos_y = 0;
	Camera.posZ = 0;
	Camera.r = 5;
	Camera.direction_x = 0;
	Camera.direction_y = 0;
	Camera.direction_z = -5;
	Camera.normal_x = 0;
	Camera.normal_y = 1;
	Camera.normal_yr = 1;
	Camera.normal_z = 0;
	Camera.phi = 0;
	Camera.theta = pi/2;
	Camera.y_up = 1.f;
	Camera.rest_x = false;
	Camera.rest_y = false;

	EstadoJuego::GetInstance()->Texturas = true;
	EstadoJuego::GetInstance()->luz.activa = true;
	Document << "[GraphicEngine] [Motor Grafico inicio correctamente]" << endl;
}

void GraphicEngine::CargaAmbiente() {
	glClearColor(clear_color, clear_color, clear_color, 1);
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

void GraphicEngine::CargaModelos() {
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

	Earth::model_s = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_EARTH);
	Earth::model_t = Earth::model_s;

	Moon::model_s = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_MOON);
	Moon::model_t = Moon::model_s;

	Sun::model_s = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_SUN);
	Sun::model_t = Sun::model_s;

	Mercury::model_s = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_MERCURY);
	Mercury::model_t = Mercury::model_s;

	Venus::model_s = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_VENUS);
	Venus::model_t = Venus::model_s;

	Jupiter::model_s = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_JUPITER);
	Jupiter::model_t = Jupiter::model_s;

	Mars::model_s = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_URANO);
	Mars::model_t = Mars::model_s;

	Neptuno::model_s = CargarObjeto::CaragarSolidTextura(PLANET_OBJECT_PATH, TEXTURE_NEPTUNO);
	Neptuno::model_t = Neptuno::model_s;

	
	Snake::model_s = CargarObjeto::CaragarSolidTextura(SNAKE_OBJECT_PATH, TEXTURE_SNAKE);
    Snake::model_t = Snake::model_s;

    if (EstadoJuego::GetInstance()->level != 0){
        Apple::model_s = CargarObjeto::CaragarSolidTextura(APPLE_OBJECT_PATH, TEXTURE_APPLE);
        Apple::model_t = Apple::model_s;
        Document << "[CargaModelos] deberia ser manzana" << endl;
    }
    else{
    	Document << "[CargaModelos] deberia ser estrella" << endl;
        Apple::model_s = CargarObjeto::CaragarSolidTextura(STAR_OBJECT_PATH, TEXTURE_STAR);
        Apple::model_t = Apple::model_s;
    }
    
    Snake::GenerateShape();
    Apple::GenerateShape();
    Document << "[CargaModelos] [Models loaded]" << endl;
}

void GraphicEngine::CargaTextura(GLuint &texture, const char* texture_name) {
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

void GraphicEngine::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45.0f,(GLfloat)640/(GLfloat)480,0.1f,200.0f);
	glMatrixMode(GL_MODELVIEW);
	if (EstadoJuego::GetInstance()->modelado != MOD_SOLIDO) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	if (EstadoJuego::GetInstance()->interpolate) glShadeModel(GL_SMOOTH);
	else glShadeModel(GL_FLAT);

	DrawLuz();
	DrawCamara();
	DrawAmbiente();
	DrawEsenario();
	
	if (!EstadoJuego::GetInstance()->luz.activa) glDisable(GL_LIGHTING);
	else glEnable(GL_LIGHTING);
	
	DrawPersonajes();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DrawContexto();
}

void GraphicEngine::DrawLuz() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat ambient[] = {0.4f, 0.4f, 0.4f};
	GLfloat diffuseLight[] = {1, 1, 1, 1};
	GLfloat specularLight[] = {0.6f, 0.6f, 0.6f, 1.0f};
	float pos_x,pos_y,posZ;
	float colorR,colorG,colorB;
	switch(EstadoJuego::GetInstance()->luz.Posicion) {
		case L_Arriba:
			pos_x = 0;
			pos_y = 100;
			posZ = 0;
		break;
		case L_Adeante:
			pos_x = 600;
			pos_y = 10;
			posZ = 0;
		break;
		case L_Atras:
			pos_x = -50;
			pos_y = 10;
			posZ = 0;
		break;
		case L_Der:
			pos_x = 250;
			pos_y = 10;
			posZ = 30;
		break;
		case L_Izq:
			pos_x = 250;
			pos_y = 10;
			posZ = -30;
		break;
	}

	switch(EstadoJuego::GetInstance()->luz.Color) {
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
	GLfloat posicion_inicial[] = {pos_x,pos_y,posZ, 1.0f};
	GLfloat color[] = {colorR,colorG,colorB, 1.0f};


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_COLOR,color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion_inicial);
}

void GraphicEngine::DrawContexto() {
	Motor_Pantalla::GetInstance()->DrawPantalla();
}

int ang = 0;

void GraphicEngine::DrawEsenario() {
	float x = 0;
	float y = field_size;
	float z = 0;
	float size = field_size;
	float factor = 0.5;
	
	glPushMatrix();
	glColor4f(1,1,1,1);
	


	if(EstadoJuego::GetInstance()->Texturas) glEnable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);

	if (EstadoJuego::GetInstance()->level == 0){
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
	
	if (EstadoJuego::GetInstance()->level == 0){
		glBindTexture(GL_TEXTURE_2D, TEXTURE_GRASS);
	}
	
	glBegin(GL_QUADS);
		glTexCoord2d(1,1);glVertex3f(x - size, y - size, z - size); // V5
		glTexCoord2d(1,0);glVertex3f(x + size, y - size, z - size); // V6
		glTexCoord2d(0,0);glVertex3f(x + size, y - size, z + size); // V7
		glTexCoord2d(0,1);glVertex3f(x - size, y - size, z + size); // V8
	glEnd();

	if (EstadoJuego::GetInstance()->level == 0)
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
	
	if (EstadoJuego::GetInstance()->level != 0){
		ang += 0.6;
		


		glEnable(GL_BLEND);
		
		glEnable(GL_BLEND);
		glTranslatef(0,2.5,0);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::GetInstance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Sun::model_s);
		//}


		glTranslatef(-10,0,2);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::GetInstance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Earth::model_s);
		//}

		glTranslatef(3,0,3);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::GetInstance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Moon::model_s);
		//}
		glTranslatef(5,0,10);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::GetInstance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Mars::model_s);
		//}
		glTranslatef(-3,0,-7);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::GetInstance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(2,0,-2);
		//if(m != MOD_COLICION) {
			glCallList(Mercury::model_s);
		//}
		glTranslatef(4,0,3);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::GetInstance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
			glCallList(Venus::model_s);

		glTranslatef(3,0,5);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::GetInstance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
			glCallList(Jupiter::model_s);

		glTranslatef(-8,0,1);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(EstadoJuego::GetInstance()->Texturas)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
			glCallList(Neptuno::model_s);
		glDisable(GL_ALPHA);
		glPopMatrix();
	}
	/*map<int,Objeto*>* ambiente = GameEngine::GetInstance()->GetEnv();
	map<int, Objeto*>::iterator it;
	for (it = ambiente->begin(); it != ambiente->end(); ++it){
		if (it->first == 0)
			it->second->Draw(EstadoJuego::GetInstance()->modelado, Camera);
	}*/

}

void GraphicEngine::DrawCamara() {
	Snake* PersonageControlado = GameEngine::GetInstance()->GetCharacter();
	glLoadIdentity();
	switch (EstadoJuego::GetInstance()->Camera) {
		case CAMARA_FIJA:
			if(PersonageControlado != NULL) {
				Camera.pos_x = PersonageControlado->getPos().pos_x;
				Camera.direction_x = PersonageControlado->getPos().pos_x;
				Camera.direction_z = PersonageControlado->getPos().posZ;
			}
			Camera.pos_y = 5;
			Camera.posZ = 15;
			Camera.direction_y =  3;
			Camera.normal_x = 0;
			Camera.normal_y = 1;
			Camera.normal_z = 0;
			Camera.pos_xr = Camera.pos_x;
			Camera.pos_yr = Camera.pos_y;
			Camera.pos_zr = Camera.posZ;
		break;
		case FOLLOW:
			if(PersonageControlado != NULL) {
				Camera.pos_x = (PersonageControlado->getPos().pos_x - sin(PersonageControlado->get_anguloActual())*10);
				Camera.direction_x = PersonageControlado->getPos().pos_x + sin(PersonageControlado->get_anguloActual());
				Camera.direction_z =PersonageControlado->getPos().posZ + cos(PersonageControlado->get_anguloActual());
				Camera.posZ = PersonageControlado->getPos().posZ - cos(PersonageControlado->get_anguloActual())*10;
			}
			Camera.pos_y = 3;
			Camera.direction_y =  3;
			Camera.normal_x = 0;
			Camera.normal_y = 1;
			Camera.normal_z = 0;
		break;
		case FIRST_PERSON:
			if(PersonageControlado != NULL) {
				Camera.pos_x = PersonageControlado->getPos().pos_x;
				Camera.posZ = PersonageControlado->getPos().posZ;
				Camera.direction_x = PersonageControlado->getPos().pos_x + sin(PersonageControlado->get_anguloActual());
				Camera.direction_z = PersonageControlado->getPos().posZ + cos(PersonageControlado->get_anguloActual());
				Camera.pos_y = 0.5;
				Camera.direction_y = 0.5;
			}
			Camera.normal_x = 0;
			Camera.normal_y = 1;
			Camera.normal_z = 0;
		break;
		case MOUSE:
			if(PersonageControlado != NULL) {
				Camera.direction_x = (PersonageControlado->getPos().pos_x);
				Camera.direction_z = PersonageControlado->getPos().posZ;
				Camera.direction_y =  PersonageControlado->getPos().pos_y;
				Camera.pos_x =Camera.pos_xr + Camera.direction_x;
				Camera.pos_y = Camera.pos_yr;
				Camera.posZ=Camera.pos_zr;
				/*Camera.pos_x = PersonageControlado->getPos().pos_x;
				Camera.direction_x = 0;
				Camera.direction_z = 0;
				Camera.direction_y =  0;*/
			}
			Camera.normal_x = 0;
			Camera.normal_y =Camera.normal_yr;
			Camera.normal_z = 0;
		break;
	}
	gluLookAt(Camera.pos_x , Camera.pos_y, Camera.posZ, Camera.direction_x, Camera.direction_y, Camera.direction_z, Camera.normal_x, Camera.normal_y, Camera.normal_z);
}

void GraphicEngine::DrawPersonajes() {
	Snake* personage = GameEngine::GetInstance()->GetCharacter();
	if (personage != NULL) personage->Draw(EstadoJuego::GetInstance()->modelado, Camera);
}

void GraphicEngine::DrawAmbiente() {
	Objeto* Tem = GameEngine::GetInstance()->GetElement();
	if (Tem != NULL) Tem->Draw(EstadoJuego::GetInstance()->modelado, Camera);
}

void GraphicEngine::CambiarCamara() {
	switch (EstadoJuego::GetInstance()->Camera) {
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
	EstadoJuego::GetInstance()->Camera = Camera.camar;
}

void GraphicEngine::CambiarModo() {
	Document.open(GRAPHICS_ENGINE_DOCUMENT_PATH);
	switch (EstadoJuego::GetInstance()->modelado) {
		case MOD_SOLIDO:
			EstadoJuego::GetInstance()->modelado = MOD_LINEAS;
			Document << "[GRAPHIC ENGINE] Cambio Modo: MOD_SOLIDO" << endl;
		break;
		case MOD_LINEAS:
			EstadoJuego::GetInstance()->modelado = MOD_COLICION;
			Document << "[GRAPHIC ENGINE] Cambio Modo: MOD_LINEAS" << endl;
		break;
		case MOD_COLICION:
			EstadoJuego::GetInstance()->modelado = MOD_SOLIDO;
			Document << "[GRAPHIC ENGINE] Cambio Modo: MOD_COLICION" << endl;
		break;
	}
}

void GraphicEngine::MotionCamara(int x, int y) {
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
	
	if (((Camera.theta)> 0)&& (Camera.theta)< pi) Camera.normal_yr = 1;
	else Camera.normal_yr = -1;
	
	Camera.pos_xr = xNuevo;
	Camera.pos_yr = yNuevo;
	Camera.pos_zr = zNuevo;
}

void GraphicEngine::ActivarDesactivarLuz() {
	EstadoJuego::GetInstance()->luz.activa =!EstadoJuego::GetInstance()->luz.activa;
}

void GraphicEngine::ActivarDesctivarTextura() {
	EstadoJuego::GetInstance()->Texturas = !EstadoJuego::GetInstance()->Texturas;
}

void GraphicEngine::ruedita(bool cmp) {
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