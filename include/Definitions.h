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

enum to_play {TO_LOSE, TO_WIN, TO_BONUS_POINT};
enum camera_type {CAMARA_FIJA, FIRST_PERSON, MOUSE, FOLLOW};
enum m_fb {MOD_N, MOD_T};
const float z_far = 100;
const float z_near = 1;
const float field_size = 15;
const float field_limit = field_size - 1.2;

struct data_camera {
	camera_type camar;
	float pos_x;
	float pos_y;
	float posZ;
	float pos_xr;
	float pos_yr;
	float pos_zr;
	float direction_x;
	float direction_y;
	float direction_z;
	float normal_x;
	float normal_y;
	float normal_yr;
	float normal_z;
	float phi;
	float theta;
	float y_up;
	float r;
	bool rest_x;
	bool rest_y;
};

struct obj_pos {
	float pos_x;
	float pos_y;
	float posZ;
	float angle_x;
	float angle_y;
	float angle_z;
	float size;
};

enum in_pos {L_Arriba, L_Atras, L_Adeante, L_Izq, L_Der};
enum in_col {BLANCO, ROJO, AZUL, VERDE};

struct light_inf {
    bool activa;
    in_col Color;
    in_pos position;
};

enum ObjectState {PAUSE, ACTIVE, WIN, LOOSE, START, QUIT};
enum shape_type {SPHERE};
enum object_type {T_SOLID, T_CHAR, T_BACKGROUND};
enum object_class {C_APPLE, C_SNAKE};
enum ModelType {MOD_SOLIDO, MOD_LINEAS, MOD_COLICION};

float PointsDistance(float x1, float y1, float z1, float x2, float y2, float y3);

#endif