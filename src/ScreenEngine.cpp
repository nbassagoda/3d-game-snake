#include "../include/ScreenEngine.h"

ScreenEngine* ScreenEngine::instance = NULL;

unsigned int ScreenEngine::LoadTexture(const char* file) {
	SDL_Surface* img = IMG_Load(file);
	GLint CantColors;
	GLenum formato;
	CantColors = img->format->BytesPerPixel;
	if (CantColors == 4) formato = GL_RGBA;
	else if (CantColors == 3) formato = GL_RGB;
	
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, CantColors, img->w, img->h, 0, formato, GL_UNSIGNED_BYTE, img->pixels);
	SDL_FreeSurface(img);
	return id;
}


ScreenEngine::ScreenEngine() {
	fontMain = TTF_OpenFont("data/Fonts/ITCKRIST.TTF", 128);
	fontMenu = TTF_OpenFont("data/Fonts/Latin Modern Roman.otf", 128);
	screenLoose = LoadTexture("data/Textures/Game_Over.jpg");
	screenInit = LoadTexture("data/Textures/Game_Start.jpg");
	screenWin = LoadTexture("data/Textures/Game_Win.jpg");
}

ScreenEngine* ScreenEngine::GetInstance() {
	if(instance == NULL) instance = new ScreenEngine();
	return instance;
}

void ScreenEngine::DrawHud() {
	SDL_Color a = {255, 255, 255};
	char Mensage[500];
	sprintf(Mensage, "Score: ");
	glEnable(GL_TEXTURE);
	unsigned int texto = LoadText2(Mensage, a);
	
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(0,0,0.1);
		glTexCoord2f(0,1);
		glVertex3f(0,100,0.1);
		glTexCoord2f(1,1);
		glVertex3f(150,100,0.1);
		glTexCoord2f(1,0);
		glVertex3f(150,0,0.1);
	glEnd();
	//glPolygonMode(GL_FRONT,GL_FILL);
	glDeleteTextures(1,&texto);
	sprintf(Mensage, " %d ",GameState::GetInstance()->score);

	texto = LoadText2(Mensage, a);

	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(150,0,0.1);
		glTexCoord2f(0,1);
		glVertex3f(150,100,0.1);
		glTexCoord2f(1,1);
		glVertex3f(200,100,0.1);
		glTexCoord2f(1,0);
		glVertex3f(200,0,0.1);
	glEnd();
	//glPolygonMode(GL_FRONT,GL_FILL);
	glDeleteTextures(1, &texto);
}

void ScreenEngine::DrawPause() {
	glDisable(GL_TEXTURE);
	glColor4f(0,0,0,0.7);
	glBegin(GL_QUADS);
		glVertex3f(0,0,0.2);
		glVertex3f(0,480,0.2);
		glVertex3f(640,480,0.2);
		glVertex3f(640,00,0.2);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor4f(1,0,0,1);
		glVertex3f(500,100,0);
		glColor4f(0,0,1,1);
		glVertex3f(550,25,0);
		glColor4f(0,1,0,1);
		glVertex3f(600,100,0);
	glEnd();
	glEnable(GL_TEXTURE);
	SDL_Color a = {100,25,20};
	char Mensage[500] = "";
	
	// Pause configurations.
	sprintf(Mensage, "Pause");
	unsigned int texto = LoadText2(Mensage, a);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(280,0,0.1);
		glTexCoord2f(0,1);
		glVertex3f(280,100,0.1);
		glTexCoord2f(1,1);
		glVertex3f(360,100,0.1);
		glTexCoord2f(1,0);
		glVertex3f(360,0,0.1);
	glEnd();
	glDeleteTextures(1, &texto);
	SDL_Color TI = {200,0,0};
	SDL_Color TEX = {200,0,0};
	SDL_Color INTE = {200,0,0};
	SDL_Color LA = {200,0,0};
	SDL_Color LD = {200,0,0};
	SDL_Color LC = {200,0,0};
	SDL_Color INM = {200,0,0};
	SDL_Color CAM = {200,0,0};
	SDL_Color T2 = {200,0,0};
	int PosI = 100;
	int Tam  = 40;
	switch (Menu::GetInstance()->getOption()) {
		case O_SUN:
			TI = {150,150,100};
		break;
		case O_TEXTURE:
			TEX = {150,150,100};
		break;
		case O_INTER:
			INTE = {150,150,100} ;
		break;
		case O_LIGHT:
			LA = {150,150,100};
		break;
		case O_LIGHT_DIR:
			LD = {150,150,100};
		break;
		case O_LIGHT_COLOR:
			LC = {150,150,100};
		break;
		case O_TRICK:
			INM = {150,150,100};
		break;
		case O_CAMERA:
			CAM = {150,150,100};
		break;
		case O_TRICK_2:
			T2 = {150,150,100};
		break;
	}
	
	// camera configurations.
	sprintf(Mensage, "camera");
	texto = LoadTextC(Mensage, CAM);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(100,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(100,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(180,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(180,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1, &texto);
	switch(GameState::GetInstance()->camera) {
		case CAMARA_FIJA:
			sprintf(Mensage, "< Fixed >");
		break;
		case FOLLOW:
			sprintf(Mensage, "< Follow >");
		break;
		case MOUSE:
			sprintf(Mensage, "< Mouse >");
		break;
		case FIRST_PERSON:
			sprintf(Mensage, "< 1st Person >");
		break;
	}
	texto = LoadTextC(Mensage ,CAM);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(300,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(300,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(420,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(420,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1,&texto);
	PosI += Tam;

	// Image configurations.
	sprintf(Mensage, "Image");
	texto = LoadTextC(Mensage, TI);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(100,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(100,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(180,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(180,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1,&texto);
	switch(GameState::GetInstance()->model) {
		case MOD_COLICION:
			sprintf(Mensage, "< Collision >");
		break;
		case MOD_SOLIDO:
			sprintf(Mensage, "< Solid >");
		break;
		case MOD_LINEAS:
			sprintf(Mensage, "< Wireframe >");
		break;
	}
	
	texto = LoadTextC(Mensage, TI);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(300,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(300,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(420,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(420,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1,&texto);
	PosI += Tam;

	// Texture configurations.
	sprintf(Mensage, "Texture");
	texto = LoadTextC(Mensage, TEX);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(100,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(100,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(180,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(180,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1, &texto);
	
	if(GameState::GetInstance()->Textures) sprintf(Mensage, "< Activated >");
	else sprintf(Mensage, "< Deactivated >");
	
	texto = LoadTextC(Mensage, TEX);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(300,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(300,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(420,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(420,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1, &texto);
	PosI += Tam;
	
	// Difucion configurations.
	sprintf(Mensage, "Broadcast");
	texto = LoadTextC(Mensage, INTE);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(100,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(100,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(180,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(180,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1, &texto);
	
	if(GameState::GetInstance()->interpolate) sprintf(Mensage, "< Activated >");
	else sprintf(Mensage, "< Deactivated >");

	texto = LoadTextC(Mensage, INTE);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(300,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(300,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(420,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(420,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1,&texto);
	PosI += Tam;

	// Light configurations.
	sprintf(Mensage, "Light");
	texto = LoadTextC(Mensage, LA);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(100,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(100,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(180,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(180,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1, &texto);
	
	if(GameState::GetInstance()->light.activa) sprintf(Mensage, "< Activated >");
	else sprintf(Mensage, "< Deactivated >");


	texto = LoadTextC(Mensage,LA);
	glBindTexture(GL_TEXTURE_2D,texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(300,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(300,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(420,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(420,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1,&texto);
	PosI += Tam;
	
	// Light direction.
	sprintf(Mensage, "Light Direction");
	texto = LoadTextC(Mensage,LD);
	glBindTexture(GL_TEXTURE_2D,texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(100,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(100,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(180,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(180,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1,&texto);
	switch (GameState::GetInstance()->light.position) {
		case L_Arriba:
			sprintf(Mensage, "< Up >");
		break;
		case L_Atras:
			sprintf(Mensage, "< Back >");
		break;
		case L_Adeante:
			sprintf(Mensage, "< Front >");
		break;
		case L_Izq:
			sprintf(Mensage, "< Left >");
		break;
		case L_Der:
			sprintf(Mensage, "< Right >");
		break;
	}
	texto = LoadTextC(Mensage,LD);
	glBindTexture(GL_TEXTURE_2D,texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(300,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(300,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(420,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(420,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1,&texto);
	PosI += Tam;
	
	// Light color.
	sprintf(Mensage, "Light Color");
	texto = LoadTextC(Mensage, LC);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(100,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(100,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(180,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(180,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1, &texto);
	switch (GameState::GetInstance()->light.Color) {
		case BLANCO:
			sprintf(Mensage, "< White >");
		break;
		case ROJO:
			sprintf(Mensage, "< Red >");
		break;
		case AZUL:
			sprintf(Mensage, "< Blue >");
		break;
		case VERDE:
			sprintf(Mensage, "< Green >");
		break;
	}
	texto = LoadTextC(Mensage, LC);
	glBindTexture(GL_TEXTURE_2D, texto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(300,(PosI+Tam),0.1);
		glTexCoord2f(0,0);
		glVertex3f(300,PosI,0.1);
		glTexCoord2f(1,0);
		glVertex3f(420,PosI,0.1);
		glTexCoord2f(1,1);
		glVertex3f(420,(PosI+Tam),0.1);
	glEnd();
	glDeleteTextures(1,&texto);
	PosI += Tam;
}

void ScreenEngine::DrawPerder() {
	glDisable(GL_TEXTURE);
	glColor4f(0,0,0,0.5);
	glBegin(GL_QUADS);
		glVertex3f(0,0,0.1);
		glVertex3f(0,480,0.1);
		glVertex3f(640,480,0.1);
		glVertex3f(640,00,0.1);
	glEnd();
	glEnable(GL_TEXTURE);
	
	glBindTexture(GL_TEXTURE_2D, screenLoose);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
		glColor4f(1,1,1,1);
		glTexCoord2f(0,0);
		glVertex3f(0,0,0.1);
		glTexCoord2f(0,1);
		glVertex3f(0,480,0.1);
		glTexCoord2f(1,1);
		glVertex3f(640,480,0.1);
		glTexCoord2f(1,0);
		glVertex3f(640,0,0.1);
	glEnd();
}

void ScreenEngine::DrawWin() {
	glDisable(GL_TEXTURE);
	glColor4f(0,0,0,0.5);
	glBegin(GL_QUADS);
		glVertex3f(0,0,0.1);
		glVertex3f(0,480,0.1);
		glVertex3f(640,480,0.1);
		glVertex3f(640,00,0.1);
	glEnd();
	glEnable(GL_TEXTURE);

	glBindTexture(GL_TEXTURE_2D, screenWin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBegin(GL_QUADS);
		glColor4f(1,1,1,1);
		glTexCoord2f(0,0);
		glVertex3f(0,0,0.1);
		glTexCoord2f(0,1);
		glVertex3f(0,480,0.1);
		glTexCoord2f(1,1);
		glVertex3f(640,480,0.1);
		glTexCoord2f(1,0);
		glVertex3f(640,0,0.1);
    glEnd();
}

GLuint ScreenEngine::LoadText2(const char* file,SDL_Color a) {
	GLuint id;
	
	SDL_Surface* texto = TTF_RenderText_Blended(fontMain,file,a);
	
	glGenTextures(1 , &id);
	glBindTexture(GL_TEXTURE_2D, id);
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texto->w, texto->h, 0, GL_BGRA,
	GL_UNSIGNED_BYTE, texto->pixels );
	
	SDL_FreeSurface(texto);
	
	return id;
}

GLuint ScreenEngine::LoadTextC(const char* file, SDL_Color a) {
	GLuint id;
	
	SDL_Surface* texto = TTF_RenderText_Blended(fontMenu, file, a);
	glGenTextures(1 , &id);
	glBindTexture(GL_TEXTURE_2D, id);
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texto->w, texto->h, 0, GL_BGRA,
	GL_UNSIGNED_BYTE, texto->pixels );
	
	SDL_FreeSurface(texto);
	
	return id;
}

void ScreenEngine::DrawStart() {
	glDisable(GL_TEXTURE);
	glColor4f(0,0,0,0.5);
	glBegin(GL_QUADS);
		glVertex3f(0,0,0.1);
		glVertex3f(0,480,0.1);
		glVertex3f(640,480,0.1);
		glVertex3f(640,00,0.1);
	glEnd();
	glEnable(GL_TEXTURE);
	
	glBindTexture(GL_TEXTURE_2D, screenInit);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
		glColor4f(1,1,1,1);
		glTexCoord2f(0,0);
		glVertex3f(0,0,0.1);
		glTexCoord2f(0,1);
		glVertex3f(0,480,0.1);
		glTexCoord2f(1,1);
		glVertex3f(640,480,0.1);
		glTexCoord2f(1,0);
		glVertex3f(640,0,0.1);
    glEnd();
}

void ScreenEngine::DrawScreen() {
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	// glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION); // Set the matrix mode to projection
	glLoadIdentity();            // Reset the matrix mode
	glOrtho(0, 640, 480, 0, 1, -1); // Set the orthogonal matrix to flatten the world (3D -> 2D)
	//gluPerspective(45.0f,(GLfloat)640/(GLfloat)480,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);             // Set the matrix mode to modelview
	glLoadIdentity();

	if(GameState::GetInstance()->estdo != START) DrawHud();
	switch(GameState::GetInstance()->estdo) {
		case LOOSE:
			DrawPerder();
		break;
		case PAUSE:
			DrawPause();
		break;
		case START:
			DrawStart();
		break;
		case WIN:
			DrawWin();
		break;
	}
	// if(GameState::GetInstance()->estdo != START) DrawHud();

	glPopMatrix();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}