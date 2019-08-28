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
	GameState::GetInstance()->model = MOD_SOLIDO;
	LoadEnv();
	LoadModels();
	camera.camar = CAMARA_FIJA;
	camera.pos_x = 0;
	camera.pos_y = 0;
	camera.posZ = 0;
	camera.r = 5;
	camera.direction_x = 0;
	camera.direction_y = 0;
	camera.direction_z = -5;
	camera.normal_x = 0;
	camera.normal_y = 1;
	camera.normal_yr = 1;
	camera.normal_z = 0;
	camera.phi = 0;
	camera.theta = pi/2;
	camera.y_up = 1.f;
	camera.rest_x = false;
	camera.rest_y = false;

	GameState::GetInstance()->Textures = true;
	GameState::GetInstance()->light.activa = true;
	Document << "[GraphicEngine] [Graphic engine started correctly]" << endl;
}

void GraphicEngine::LoadEnv() {
	glClearColor(clear_color, clear_color, clear_color, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,z_near,z_far);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_COLOR_ALPHA_PAIRING_ATI);
	Document << "[LoadEnv] [Environment loaded]" << endl;
}

void GraphicEngine::LoadModels() {
	LoadTexture(TEXTURE_GRASS, GRASS_TEXTURE_PATH);
	LoadTexture(TEXTURE_WOOD, WOOD_TEXTURE_PATH);
	LoadTexture(TEXTURE_STONE, STONE_TEXTURE_PATH);
	LoadTexture(TEXTURE_SNAKE, SNAKE_TEXTURE_PATH);
	LoadTexture(TEXTURE_APPLE, APPLE_TEXTURE_PATH);
	LoadTexture(TEXTURE_GALAXY, GALAXY_TEXTURE_PATH);
	LoadTexture(TEXTURE_GRASS, GRASS_TEXTURE_PATH);
  LoadTexture(TEXTURE_WOOD, WOOD_TEXTURE_PATH);
  LoadTexture(TEXTURE_STONE, STONE_TEXTURE_PATH);
  LoadTexture(TEXTURE_SNAKE, SNAKE_TEXTURE_PATH);
  LoadTexture(TEXTURE_APPLE, APPLE_TEXTURE_PATH);
  LoadTexture(TEXTURE_STAR, STAR_TEXTURE_PATH);
  LoadTexture(TEXTURE_EARTH, EARTH_TEXTURE_PATH);
  LoadTexture(TEXTURE_MOON, MOON_TEXTURE_PATH);
  LoadTexture(TEXTURE_SUN, SUN_TEXTURE_PATH);
  LoadTexture(TEXTURE_MERCURY, MERCURY_TEXTURE_PATH);
  LoadTexture(TEXTURE_VENUS, VENUS_TEXTURE_PATH);
  LoadTexture(TEXTURE_JUPITER, JUPITER_TEXTURE_PATH);
  LoadTexture(TEXTURE_MARS, MARS_TEXTURE_PATH);
  LoadTexture(TEXTURE_NEPTUNO, NEPTUNO_TEXTURE_PATH);

	Earth::model_s = LoadObject::LoadTextureSolid(PLANET_OBJECT_PATH, TEXTURE_EARTH);
	Earth::model_t = Earth::model_s;

	Moon::model_s = LoadObject::LoadTextureSolid(PLANET_OBJECT_PATH, TEXTURE_MOON);
	Moon::model_t = Moon::model_s;

	Sun::model_s = LoadObject::LoadTextureSolid(PLANET_OBJECT_PATH, TEXTURE_SUN);
	Sun::model_t = Sun::model_s;

	Mercury::model_s = LoadObject::LoadTextureSolid(PLANET_OBJECT_PATH, TEXTURE_MERCURY);
	Mercury::model_t = Mercury::model_s;

	Venus::model_s = LoadObject::LoadTextureSolid(PLANET_OBJECT_PATH, TEXTURE_VENUS);
	Venus::model_t = Venus::model_s;

	Jupiter::model_s = LoadObject::LoadTextureSolid(PLANET_OBJECT_PATH, TEXTURE_JUPITER);
	Jupiter::model_t = Jupiter::model_s;

	Mars::model_s = LoadObject::LoadTextureSolid(PLANET_OBJECT_PATH, TEXTURE_URANO);
	Mars::model_t = Mars::model_s;

	Neptuno::model_s = LoadObject::LoadTextureSolid(PLANET_OBJECT_PATH, TEXTURE_NEPTUNO);
	Neptuno::model_t = Neptuno::model_s;

	
	Snake::model_s = LoadObject::LoadTextureSolid(SNAKE_OBJECT_PATH, TEXTURE_SNAKE);
    Snake::model_t = Snake::model_s;

    if (GameState::GetInstance()->level != 0){
        Apple::model_s = LoadObject::LoadTextureSolid(APPLE_OBJECT_PATH, TEXTURE_APPLE);
        Apple::model_t = Apple::model_s;
    }
    else{
        Apple::model_s = LoadObject::LoadTextureSolid(STAR_OBJECT_PATH, TEXTURE_STAR);
        Apple::model_t = Apple::model_s;
    }
    
    Snake::GenerateShape();
    Apple::GenerateShape();
    Document << "[LoadModels] [Models loaded]" << endl;
}

void GraphicEngine::LoadTexture(GLuint &texture, const char* texture_name) {
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
	Document << "[LoadTexture] [Texture _" << texture_name << "_ loaded]" << endl;
}

void GraphicEngine::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45.0f,(GLfloat)640/(GLfloat)480,0.1f,200.0f);
	glMatrixMode(GL_MODELVIEW);
	if (GameState::GetInstance()->model != MOD_SOLIDO) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	if (GameState::GetInstance()->interpolate) glShadeModel(GL_SMOOTH);
	else glShadeModel(GL_FLAT);

	DrawLight();
	Drawcamera();
	DrawEnv();
	DrawScene();
	
	if (!GameState::GetInstance()->light.activa) glDisable(GL_LIGHTING);
	else glEnable(GL_LIGHTING);
	
	DrawCharacters();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DrawContexto();
}

void GraphicEngine::DrawLight() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat ambient[] = {0.4f, 0.4f, 0.4f};
	GLfloat diffuseLight[] = {1, 1, 1, 1};
	GLfloat specularLight[] = {0.6f, 0.6f, 0.6f, 1.0f};
	float pos_x,pos_y,posZ;
	float color_r,color_g,color_b;
	switch(GameState::GetInstance()->light.position) {
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

	switch(GameState::GetInstance()->light.Color) {
		case BLANCO:
			color_r =1;
			color_g =1;
			color_b =1;
		break;
		case ROJO:
			color_r =1;
			color_g =0;
			color_b =0;
		break;
		case VERDE:
			color_r =0;
			color_g =1;
			color_b =0;
		break;
		case AZUL:
			color_r =0;
			color_g =0;
			color_b =1;
		break;
	}
	GLfloat posicion_inicial[] = {pos_x,pos_y,posZ, 1.0f};
	GLfloat color[] = {color_r,color_g,color_b, 1.0f};


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_COLOR,color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion_inicial);
}

void GraphicEngine::DrawContexto() {
	ScreenEngine::GetInstance()->DrawScreen();
}

int ang = 0;

void GraphicEngine::DrawScene() {
	float x = 0;
	float y = field_size;
	float z = 0;
	float size = field_size;
	float factor = 0.5;
	
	glPushMatrix();
	glColor4f(1,1,1,1);
	


	if(GameState::GetInstance()->Textures) glEnable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);

	if (GameState::GetInstance()->level == 0){
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
	
	if (GameState::GetInstance()->level == 0){
		glBindTexture(GL_TEXTURE_2D, TEXTURE_GRASS);
	}
	
	glBegin(GL_QUADS);
		glTexCoord2d(1,1);glVertex3f(x - size, y - size, z - size); // V5
		glTexCoord2d(1,0);glVertex3f(x + size, y - size, z - size); // V6
		glTexCoord2d(0,0);glVertex3f(x + size, y - size, z + size); // V7
		glTexCoord2d(0,1);glVertex3f(x - size, y - size, z + size); // V8
	glEnd();

	if (GameState::GetInstance()->level == 0)
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
	
	if (GameState::GetInstance()->level != 0){
		ang += 0.6;
		
		glEnable(GL_BLEND);
		
		glEnable(GL_BLEND);
		glTranslatef(0,2.5,0);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(GameState::GetInstance()->Textures)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Sun::model_s);
		//}

		glTranslatef(-10,0,2);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(GameState::GetInstance()->Textures)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Earth::model_s);
		//}

		glTranslatef(3,0,3);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(GameState::GetInstance()->Textures)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Moon::model_s);
		//}
		glTranslatef(5,0,10);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(GameState::GetInstance()->Textures)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		//if(m != MOD_COLICION) {
			glCallList(Mars::model_s);
		//}
		glTranslatef(-3,0,-7);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(GameState::GetInstance()->Textures)
			glEnable(GL_TEXTURE_2D);
			glColor3f(2,0,-2);
		//if(m != MOD_COLICION) {
			glCallList(Mercury::model_s);
		//}
		glTranslatef(4,0,3);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(GameState::GetInstance()->Textures)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
			glCallList(Venus::model_s);

		glTranslatef(3,0,5);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(GameState::GetInstance()->Textures)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
			glCallList(Jupiter::model_s);

		glTranslatef(-8,0,1);
		glRotatef(ang,0,1,0);
		glScaled(1,1,1);
		if(GameState::GetInstance()->Textures)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
			glCallList(Neptuno::model_s);
		glDisable(GL_ALPHA);
		glPopMatrix();
	}
}

void GraphicEngine::Drawcamera() {
	Snake* character = GameEngine::GetInstance()->GetCharacter();
	glLoadIdentity();
	switch (GameState::GetInstance()->camera) {
		case CAMARA_FIJA:
			if(character != NULL) {
				camera.pos_x = character->GetPosition().pos_x;
				camera.direction_x = character->GetPosition().pos_x;
				camera.direction_z = character->GetPosition().posZ;
			}
			camera.pos_y = 5;
			camera.posZ = 15;
			camera.direction_y =  3;
			camera.normal_x = 0;
			camera.normal_y = 1;
			camera.normal_z = 0;
			camera.pos_xr = camera.pos_x;
			camera.pos_yr = camera.pos_y;
			camera.pos_zr = camera.posZ;
		break;
		case FOLLOW:
			if(character != NULL) {
				camera.pos_x = (character->GetPosition().pos_x - sin(character->GetCurrentAngle())*10);
				camera.direction_x = character->GetPosition().pos_x + sin(character->GetCurrentAngle());
				camera.direction_z =character->GetPosition().posZ + cos(character->GetCurrentAngle());
				camera.posZ = character->GetPosition().posZ - cos(character->GetCurrentAngle())*10;
			}
			camera.pos_y = 3;
			camera.direction_y =  3;
			camera.normal_x = 0;
			camera.normal_y = 1;
			camera.normal_z = 0;
		break;
		case FIRST_PERSON:
			if(character != NULL) {
				camera.pos_x = character->GetPosition().pos_x;
				camera.posZ = character->GetPosition().posZ;
				camera.direction_x = character->GetPosition().pos_x + sin(character->GetCurrentAngle());
				camera.direction_z = character->GetPosition().posZ + cos(character->GetCurrentAngle());
				camera.pos_y = 0.5;
				camera.direction_y = 0.5;
			}
			camera.normal_x = 0;
			camera.normal_y = 1;
			camera.normal_z = 0;
		break;
		case MOUSE:
			if(character != NULL) {
				camera.direction_x = (character->GetPosition().pos_x);
				camera.direction_z = character->GetPosition().posZ;
				camera.direction_y =  character->GetPosition().pos_y;
				camera.pos_x =camera.pos_xr + camera.direction_x;
				camera.pos_y = camera.pos_yr;
				camera.posZ=camera.pos_zr;
			}
			camera.normal_x = 0;
			camera.normal_y =camera.normal_yr;
			camera.normal_z = 0;
		break;
	}
	gluLookAt(camera.pos_x , camera.pos_y, camera.posZ, camera.direction_x, camera.direction_y, camera.direction_z, camera.normal_x, camera.normal_y, camera.normal_z);
}

void GraphicEngine::DrawCharacters() {
	Snake* charact = GameEngine::GetInstance()->GetCharacter();
	if (charact != NULL) charact->Draw(GameState::GetInstance()->model, camera);
}

void GraphicEngine::DrawEnv() {
	Object* tem = GameEngine::GetInstance()->GetElement();
	if (tem != NULL) tem->Draw(GameState::GetInstance()->model, camera);
}

void GraphicEngine::Changecamera() {
	switch (GameState::GetInstance()->camera) {
		case CAMARA_FIJA:
			camera.camar = MOUSE;
		break;
		case FOLLOW:
			camera.camar = FIRST_PERSON;
		break;
		case FIRST_PERSON:
			camera.camar = CAMARA_FIJA;
		break;
		case MOUSE:
			camera.camar = FOLLOW;
		break;
	}
	GameState::GetInstance()->camera = camera.camar;
}

void GraphicEngine::ChangeMode() {
	Document.open(GRAPHICS_ENGINE_DOCUMENT_PATH);
	switch (GameState::GetInstance()->model) {
		case MOD_SOLIDO:
			GameState::GetInstance()->model = MOD_LINEAS;
			Document << "[GRAPHIC ENGINE] Cambio Modo: MOD_SOLIDO" << endl;
		break;
		case MOD_LINEAS:
			GameState::GetInstance()->model = MOD_COLICION;
			Document << "[GRAPHIC ENGINE] Cambio Modo: MOD_LINEAS" << endl;
		break;
		case MOD_COLICION:
			GameState::GetInstance()->model = MOD_SOLIDO;
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

	float phi = asin(deltaX/camera.r);
	float theta =acos(deltaY/camera.r);
	float radio = camera.r;

	dy = abs((pi/2)-(theta));

	if (deltaY > 0)
		camera.theta -= dy;
	else if (0 > deltaY)
		camera.theta += dy;
	
	if (deltaX>0)
		camera.phi += phi;
	else if (0>deltaX)
		camera.phi+=phi;
	
	camera.theta = fmod(camera.theta ,2*pi);
	camera.phi = fmod(camera.phi ,2*pi);
	
	float xNuevo = radio*sin(camera.theta)*sin(camera.phi) ; // x
	float yNuevo = radio*cos(camera.theta) ; // y
	float zNuevo = radio*sin(camera.theta)*cos(camera.phi);
	
	if (((camera.theta)> 0)&& (camera.theta)< pi) camera.normal_yr = 1;
	else camera.normal_yr = -1;
	
	camera.pos_xr = xNuevo;
	camera.pos_yr = yNuevo;
	camera.pos_zr = zNuevo;
}

void GraphicEngine::ManageLight() {
	GameState::GetInstance()->light.activa = !GameState::GetInstance()->light.activa;
}

void GraphicEngine::ManageTexture() {
	GameState::GetInstance()->Textures = !GameState::GetInstance()->Textures;
}

void GraphicEngine::ruedita(bool cmp) {
	if (cmp == false) {
		if (camera.r < 15) {
			camera.r += 0.9;
		}
	}
	if (cmp == true) {
		if (camera.r > 6) {
			camera.r -= 0.9;
		}
	}	
}