#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <map>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include <limits>
#include <ctime>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

#ifndef DEFINICIONES_H
#define DEFINICIONES_H

enum El_A_Juego {A_Perder, A_Ganar, A_BONUS_Point};
enum Tipo_Camar {CAMARA_FIJA, CAMARA_P1, CAMARA_MOUS, CAMAR_SEGUIR};
enum M_FB {MOD_N, MOD_T};
const float FB_ZFar = 100;
const float FB_ZNear = 1;
const float Field_Size = 15;
const float Field_Limit = Field_Size - 1.2;

struct Datos_Camara {
	Tipo_Camar camar;
	float posX;
	float posY;
	float posZ;
	float posXR;
	float posYR;
	float posZR;
	float direccionX;
	float direccionY;
	float direccionZ;
	float normalX;
	float normalY;
	float normalYR;
	float normalZ;
	float phi;
	float theta;
	float Yup;
	float r;
	bool restaX;
	bool restaY;
};

struct OBJ_POS {
	float posX;
	float posY;
	float posZ;
	float angleX;
	float angleY;
	float angleZ;
	float size;
};

enum En_P {L_Arriba, L_Atras, L_Adeante, L_Izq, L_Der};
enum En_C {BLANCO, ROJO, AZUL, VERDE};

struct InfLus {
    bool activa;
    En_C Color;
    En_P Posicion;
};

enum Estado_Juego {Pausado, Activo, Gano, Perdio, Inicio, Salir};
enum Tipo_Shape {Esfera};
enum Tipo_Obejto {T_SOLIDO, T_PERSONAGE, T_FONDO};
enum Clase_Objeto{C_APPLE, C_SNAKE};
enum ModelType{MOD_SOLIDO, MOD_LINEAS, MOD_COLICION};

float Distancia_Puntos(float x1, float y1, float z1, float x2, float y2, float y3);

#endif