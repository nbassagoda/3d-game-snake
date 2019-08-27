#include "../include/ScreenEngine.h"

Motor_Pantalla* Motor_Pantalla::instance = NULL;

unsigned int Motor_Pantalla::CargaTextura(const char* file) {
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


Motor_Pantalla::Motor_Pantalla() {
	fontMain = TTF_OpenFont("data/Fonts/ITCKRIST.TTF", 128);
	fontMenu = TTF_OpenFont("data/Fonts/Latin Modern Roman.otf", 128);
	screenLoose = CargaTextura("data/Textures/Game_Over.jpg");
	screenInit = CargaTextura("data/Textures/Game_Start.jpg");
	screenWin = CargaTextura("data/Textures/Game_Win.jpg");
}

Motor_Pantalla* Motor_Pantalla::get_Instance() {
	if(instance == NULL) instance = new Motor_Pantalla();
	return instance;
}

void Motor_Pantalla::DibujarHUD() {
	SDL_Color a = {255, 255, 255};
	char Mensage[500];
	sprintf(Mensage, "Score: ");
	glEnable(GL_TEXTURE);
	unsigned int texto = CargaTextoG(Mensage, a);
	
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
	sprintf(Mensage, " %d ",EstadoJuego::get_Instance()->Puntage);

	texto = CargaTextoG(Mensage, a);

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

void Motor_Pantalla::DibujarPausa() {
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
	unsigned int texto = CargaTextoG(Mensage, a);
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
	switch (Menu::get_Instance()->getOpcion()) {
		case O_SolWir:
			TI = {150,150,100};
		break;
		case O_Textura:
			TEX = {150,150,100};
		break;
		case O_Inter:
			INTE = {150,150,100} ;
		break;
		case O_LuzAct:
			LA = {150,150,100};
		break;
		case O_LuZDir:
			LD = {150,150,100};
		break;
		case O_LuzColor:
			LC = {150,150,100};
		break;
		case O_Imortal:
			INM = {150,150,100};
		break;
		case O_Cama:
			CAM = {150,150,100};
		break;
		case O_FBM:
			T2 = {150,150,100};
		break;
	}
	
	// Camera configurations.
	sprintf(Mensage, "Camera");
	texto = CargaTextoC(Mensage, CAM);
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
	switch(EstadoJuego::get_Instance()->Camera) {
		case CAMARA_FIJA:
			sprintf(Mensage, "< Fixed >");
		break;
		case CAMAR_SEGUIR:
			sprintf(Mensage, "< Follow >");
		break;
		case CAMARA_MOUS:
			sprintf(Mensage, "< Mouse >");
		break;
		case CAMARA_P1:
			sprintf(Mensage, "< 1st Person >");
		break;
	}
	texto = CargaTextoC(Mensage ,CAM);
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
	texto = CargaTextoC(Mensage, TI);
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
	switch(EstadoJuego::get_Instance()->modelado) {
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
	
	texto = CargaTextoC(Mensage, TI);
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
	texto = CargaTextoC(Mensage, TEX);
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
	
	if(EstadoJuego::get_Instance()->Texturas) sprintf(Mensage, "< Activated >");
	else sprintf(Mensage, "< Deactivated >");
	
	texto = CargaTextoC(Mensage, TEX);
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
	texto = CargaTextoC(Mensage, INTE);
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
	
	if(EstadoJuego::get_Instance()->Interpolado) sprintf(Mensage, "< Activated >");
	else sprintf(Mensage, "< Deactivated >");

	texto = CargaTextoC(Mensage, INTE);
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
	texto = CargaTextoC(Mensage, LA);
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
	
	if(EstadoJuego::get_Instance()->luz.activa) sprintf(Mensage, "< Activated >");
	else sprintf(Mensage, "< Deactivated >");


	texto = CargaTextoC(Mensage,LA);
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
	texto = CargaTextoC(Mensage,LD);
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
	switch (EstadoJuego::get_Instance()->luz.Posicion) {
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
	texto = CargaTextoC(Mensage,LD);
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
	texto = CargaTextoC(Mensage, LC);
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
	switch (EstadoJuego::get_Instance()->luz.Color) {
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
	texto = CargaTextoC(Mensage, LC);
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

void Motor_Pantalla::DibujarPerder() {
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

void Motor_Pantalla::DibujarGanar() {
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

GLuint Motor_Pantalla::CargaTextoG(const char* file,SDL_Color a) {
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

GLuint Motor_Pantalla::CargaTextoC(const char* file, SDL_Color a) {
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

void Motor_Pantalla::DibujarInicio() {
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

void Motor_Pantalla::DibujarPantalla() {
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

	if(EstadoJuego::get_Instance()->estdo != Inicio) DibujarHUD();
	switch(EstadoJuego::get_Instance()->estdo) {
		case Perdio:
			DibujarPerder();
		break;
		case Pausado:
			DibujarPausa();
		break;
		case Inicio:
			DibujarInicio();
		break;
		case Gano:
			DibujarGanar();
		break;
	}
	// if(EstadoJuego::get_Instance()->estdo != Inicio) DibujarHUD();

	glPopMatrix();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}