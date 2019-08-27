#include "../include/LoadObjects.h"

const char* LOAD_DOCUMENT_PATH = "data/Info/Load_Object.txt";

Cordenada::Cordenada(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

Cara::Cara(int a, int b, int c, int n1, int n2, int n3) {
	Cuadrado = false;
	vertice[0] = a;
	vertice[1] = b;
	vertice[2] = c;
	normal[0] = n1;
	normal[1] = n2;
	normal[2] = n3;
}

Cara::Cara(int a, int b, int c, int d, int n1, int n2, int n3, int n4) {
	Cuadrado = true;
	vertice[0] = a;
	vertice[1] = b;
	vertice[2] = c;
	vertice[3] = d;
	normal[0] = n1;
	normal[1] = n2;
	normal[2] = n3;
	normal[3] = n4;
}

Cara::Cara(int a, int b, int c, int t1, int t2, int t3, int n1, int n2, int n3) {
	Cuadrado = false;
	vertice[0] = a;
	vertice[1] = b;
	vertice[2] = c;
	textura[0] = t1;
	textura[1] = t2;
	textura[2] = t3;
	normal[0] = n1;
	normal[1] = n2;
	normal[2] = n3;
}

Cara::Cara(int a, int b, int c, int d, int t1, int t2, int t3, int t4, int n1, int n2, int n3, int n4) {
	Cuadrado = true;
	vertice[0] = a;
	vertice[1] = b;
	vertice[2] = c;
	vertice[3] = d;
	textura[0] = t1;
	textura[1] = t2;
	textura[2] = t3;
	textura[3] = t4;
	normal[0] = n1;
	normal[1] = n2;
	normal[2] = n3;
	normal[3] = n4;
}

int CargarObjeto::CaragarWireframe(const char* filename) {
	ofstream Document; Document.open(LOAD_DOCUMENT_PATH);
	std::vector<std::string*> tira;
	std::vector<Cordenada*> punto;
	std::vector<Cara*> figura;
	std::vector<Cordenada*> normale;
	std::ifstream in(filename);
	
	if(!in.is_open()) {
		exit(1);
	}
	char buf[256];
	
	while(!in.eof()) {
		in.getline(buf,256);
		tira.push_back(new std::string(buf));
	}
	for(int i = 0; i < tira.size(); i++) {
		if(tira[i]->c_str()[0] == '#') {
			continue;
		
		} else if(tira[i]->c_str()[0] == 'v' && tira[i]->c_str()[1] == ' ') {
			float tmpx, tmpy, tmpz;
			sscanf(tira[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
			punto.push_back(new Cordenada(tmpx, tmpy, tmpz));
			
		} else if(tira[i]->c_str()[0] == 'v' && tira[i]->c_str()[1] == 'n') {
			float tmpx, tmpy, tmpz;
			sscanf(tira[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			normale.push_back(new Cordenada(tmpx, tmpy, tmpz));
			
		} else if(tira[i]->c_str()[0] == 'f') {
			int a, c, d, e, n1, n2, n3, n4;
			if(count(tira[i]->begin(),tira[i]->end(),' ') == 3) {
				sscanf(tira[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &n1, &c, &n2, &d, &n3);
				figura.push_back(new Cara(a, c, d, n1, n2, n3));
			} else {
				sscanf(tira[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &n1, &c, &n2, &d, &n3, &e, &n4);
				figura.push_back(new Cara(a, c, d, e, n1, n2, n3, n4));
			}
		}
	}
	int num;
	num = glGenLists(1);
	glNewList(num,GL_COMPILE);
	for(int i = 0; i < figura.size(); i++) {
		if(figura[i]->Cuadrado) {
			glBegin(GL_LINE_LOOP);
				glVertex3f(punto[figura[i]->vertice[0]-1]->x,punto[figura[i]->vertice[0]-1]->y,punto[figura[i]->vertice[0]-1]->z);
				glVertex3f(punto[figura[i]->vertice[1]-1]->x,punto[figura[i]->vertice[1]-1]->y,punto[figura[i]->vertice[1]-1]->z);
				glVertex3f(punto[figura[i]->vertice[2]-1]->x,punto[figura[i]->vertice[2]-1]->y,punto[figura[i]->vertice[2]-1]->z);
				glVertex3f(punto[figura[i]->vertice[3]-1]->x,punto[figura[i]->vertice[3]-1]->y,punto[figura[i]->vertice[3]-1]->z);
			glEnd();
		} else {
			glBegin(GL_LINE_LOOP);
				glVertex3f(punto[figura[i]->vertice[0]-1]->x,punto[figura[i]->vertice[0]-1]->y,punto[figura[i]->vertice[0]-1]->z);
				glVertex3f(punto[figura[i]->vertice[1]-1]->x,punto[figura[i]->vertice[1]-1]->y,punto[figura[i]->vertice[1]-1]->z);
				glVertex3f(punto[figura[i]->vertice[2]-1]->x,punto[figura[i]->vertice[2]-1]->y,punto[figura[i]->vertice[2]-1]->z);
			glEnd();
		}
	}
	glEndList();
	
	for(int i = 0; i < tira.size(); i++) delete tira[i];
	for(int i = 0; i < figura.size(); i++) delete figura[i];
	for(int i = 0; i < normale.size(); i++) delete normale[i];
	for(int i = 0; i < punto.size(); i++) delete punto[i];
	
	tira.clear();
	figura.clear();
	normale.clear();
	punto.clear();
	return num;
}

int CargarObjeto::CaragarSolid(const char* filename) {
	ofstream Document; Document.open(LOAD_DOCUMENT_PATH);
	std::vector<std::string*> tira;
	std::vector<Cordenada*> punto;
	std::vector<Cara*> figura;
	std::vector<Cordenada*> normale;
	std::ifstream in(filename);
	
	if(!in.is_open()) {
		exit(1);
	}
	char buf[256];
	
	while(!in.eof()) {
		in.getline(buf,256);
		tira.push_back(new std::string(buf));
	}
	for(int i = 0; i<tira.size(); i++) {
		if(tira[i]->c_str()[0] == '#') {
			continue;

		} else if(tira[i]->c_str()[0] == 'v' && tira[i]->c_str()[1] == ' ') {
			float tmpx, tmpy, tmpz;
			sscanf(tira[i]->c_str(),"v %f %f %f", &tmpx, &tmpy, &tmpz);
			punto.push_back(new Cordenada(tmpx, tmpy, tmpz));

		} else if(tira[i]->c_str()[0] == 'v' && tira[i]->c_str()[1] == 'n') {
			float tmpx, tmpy, tmpz;
			sscanf(tira[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			normale.push_back(new Cordenada(tmpx, tmpy, tmpz));

		} else if(tira[i]->c_str()[0] == 'f') {
			int a, c, d, e, n1, n2, n3, n4;
			if(count(tira[i]->begin(), tira[i]->end(),' ') == 3) {
				sscanf(tira[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &n1, &c, &n2, &d, &n3);
				figura.push_back(new Cara(a, c, d, n1, n2, n3));
			} else {
				sscanf(tira[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &n1, &c, &n2, &d, &n3, &e, &n4);
				figura.push_back(new Cara(a, c, d, e, n1, n2, n3, n4));
			}
		}
	}
	int num = glGenLists(1);
	glNewList(num,GL_COMPILE);
	for(int i = 0; i < figura.size(); i++) {
		if(figura[i]->Cuadrado) {
			glBegin(GL_QUADS);
				int normal;
				normal = (figura[i]->normal[0] - 1);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[0]-1]->x,punto[figura[i]->vertice[0]-1]->y,punto[figura[i]->vertice[0]-1]->z);
				normal = (figura[i]->normal[1] - 1);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[1]-1]->x,punto[figura[i]->vertice[1]-1]->y,punto[figura[i]->vertice[1]-1]->z);
				normal = (figura[i]->normal[2] - 1);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[2]-1]->x,punto[figura[i]->vertice[2]-1]->y,punto[figura[i]->vertice[2]-1]->z);
				normal = (figura[i]->normal[3] - 1);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[3]-1]->x,punto[figura[i]->vertice[3]-1]->y,punto[figura[i]->vertice[3]-1]->z);
			glEnd();
		} else {
			glBegin(GL_TRIANGLES);
				int normal;
				normal = (figura[i]->normal[0] - 1);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[0]-1]->x,punto[figura[i]->vertice[0]-1]->y,punto[figura[i]->vertice[0]-1]->z);
				normal = (figura[i]->normal[1] - 1);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[1]-1]->x,punto[figura[i]->vertice[1]-1]->y,punto[figura[i]->vertice[1]-1]->z);
				normal = (figura[i]->normal[2] - 1);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[2]-1]->x,punto[figura[i]->vertice[2]-1]->y,punto[figura[i]->vertice[2]-1]->z);
			glEnd();
		}
	}
	glEndList();
	
	for(int i = 0; i < tira.size(); i++) delete tira[i];
	for(int i = 0; i < figura.size(); i++) delete figura[i];
	for(int i = 0; i < normale.size(); i++) delete normale[i];
	for(int i = 0; i < punto.size(); i++) delete punto[i];
	
	tira.clear();
	figura.clear();
	normale.clear();
	punto.clear();
	return num;
}

int CargarObjeto::CaragarSolidTextura(const char* filename, GLuint imagen) {
	ofstream Document; Document.open(LOAD_DOCUMENT_PATH);
	std::vector<std::string*> tira;
	std::vector<Cordenada*> punto;
	std::vector<Cara*> figura;
	std::vector<Cordenada*> normale;
	std::vector<Cordenada*> textura;
	std::ifstream in(filename);
	
	if(!in.is_open()) {
		exit(1);
	}
	char buf[256];
	
	while(!in.eof()) {
		in.getline(buf,256);
		tira.push_back(new std::string(buf));
	}
	for(int i = 0; i < tira.size(); i++) {
		if(tira[i]->c_str()[0] == '#') {
			continue;
		
		} else if(tira[i]->c_str()[0] == 'v' && tira[i]->c_str()[1] == ' ') {
			float tmpx, tmpy, tmpz;
			sscanf(tira[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
			punto.push_back(new Cordenada(tmpx, tmpy, tmpz));
			
		} else if(tira[i]->c_str()[0] == 'v' && tira[i]->c_str()[1] == 'n') {
			float tmpx, tmpy, tmpz;
			sscanf(tira[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			normale.push_back(new Cordenada(tmpx, tmpy, tmpz));
			
		} else if(tira[i]->c_str()[0] == 'v' && tira[i]->c_str()[1] == 't') {
			float tmpx, tmpy, tmpz;
			sscanf(tira[i]->c_str(), "vt %f %f %f", &tmpx, &tmpy, &tmpz);
			textura.push_back(new Cordenada(tmpx, tmpy, tmpz));
			
		} else if(tira[i]->c_str()[0] == 'f') {
			int a, c, d, e, n1, n2, n3, n4, t1, t2, t3, t4;
			if(count(tira[i]->begin(),tira[i]->end(), ' ') == 3) {
				sscanf(tira[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t1, &n1, &c, &t2, &n2, &d, &t3, &n3);
				figura.push_back(new Cara(a, c, d, t1, t2, t3, n1, n2, n3));
			} else {
				sscanf(tira[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t1, &n1, &c, &t2, &n2, &d, &t3, &n3, &e, &t4, &n4);
				figura.push_back(new Cara(a, c, d, e, t1, t2, t3, t4, n1, n2, n3, n4));
			}
		}
	}
	int num = glGenLists(1);
	glNewList(num,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D,imagen);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	for(int i = 0; i < figura.size(); i++) {
		if(figura[i]->Cuadrado) {
			glBegin(GL_QUADS);
				int normal;
				normal = (figura[i]->normal[0] - 1);
				int txtind= (figura[i]->textura[0] - 1);
				glTexCoord2f(textura[txtind]->x,-textura[txtind]->y);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[0]-1]->x,punto[figura[i]->vertice[0]-1]->y,punto[figura[i]->vertice[0]-1]->z);
				
				normal = (figura[i]->normal[1] - 1);
				txtind= (figura[i]->textura[1] - 1);
				glTexCoord2f(textura[txtind]->x,-textura[txtind]->y);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[1]-1]->x,punto[figura[i]->vertice[1]-1]->y,punto[figura[i]->vertice[1]-1]->z);


				txtind= (figura[i]->textura[2] - 1);
				glTexCoord2f(textura[txtind]->x,-textura[txtind]->y);
				normal = (figura[i]->normal[2] - 1);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[2]-1]->x,punto[figura[i]->vertice[2]-1]->y,punto[figura[i]->vertice[2]-1]->z);


				normal = (figura[i]->normal[3] - 1);
				txtind= (figura[i]->textura[3] - 1);
				glTexCoord2f(textura[txtind]->x,-textura[txtind]->y);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[3]-1]->x,punto[figura[i]->vertice[3]-1]->y,punto[figura[i]->vertice[3]-1]->z);
			glEnd();
		} else {
			glBegin(GL_TRIANGLES);
				int normal;
				int txtind= (figura[i]->textura[0] - 1);
				normal = (figura[i]->normal[0] - 1);
				glTexCoord2d(textura[txtind]->x,-textura[txtind]->y);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[0]-1]->x,punto[figura[i]->vertice[0]-1]->y,punto[figura[i]->vertice[0]-1]->z);

				normal = (figura[i]->normal[1] - 1);
				txtind= (figura[i]->textura[1] - 1);
				glTexCoord2d(textura[txtind]->x,-textura[txtind]->y);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[1]-1]->x,punto[figura[i]->vertice[1]-1]->y,punto[figura[i]->vertice[1]-1]->z);

				normal = (figura[i]->normal[2] - 1);
				txtind= (figura[i]->textura[2] - 1);
				glTexCoord2d(textura[txtind]->x,-textura[txtind]->y);
				glNormal3f(normale[normal]->x,normale[normal]->y,normale[normal]->z);
				glVertex3f(punto[figura[i]->vertice[2]-1]->x,punto[figura[i]->vertice[2]-1]->y,punto[figura[i]->vertice[2]-1]->z);
			glEnd();
		}
	}
	glEndList();
	
	for(int i = 0; i < tira.size(); i++) delete tira[i];
	for(int i = 0; i < figura.size(); i++) delete figura[i];
	for(int i = 0; i < normale.size(); i++) delete normale[i];
	for(int i = 0; i < punto.size(); i++) delete punto[i];
	
	tira.clear();
	figura.clear();
	normale.clear();
	punto.clear();
	return num;
}