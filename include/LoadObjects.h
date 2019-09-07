#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

#ifndef LOAD_OBJECT_H
#define LOAD_OBJECT_H

struct Coordenate {
	float x, y, z;
	Coordenate(float a, float b, float c);
};

struct Side {
	int normal[4];
	bool Cuadrado;
	int vertice[4];
	int textura[4];
	Side(int f1, int f2, int f3, int n1, int n2, int n3);
	Side(int f1, int f2, int f3, int f4, int n1, int n2, int n3, int n4);
	Side(int f1, int f2, int f3, int t1, int t2, int t3, int n1, int n2, int n3);
	Side(int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int n1, int n2, int n3, int n4);
};

class LoadObject {
	public:
		LoadObject();
		~LoadObject();
		static int SidegarWireframe(const char* filename);
		static int SidegarSolid(const char* filename);
		static int LoadTextureSolid(const char* filename, GLuint textura);
};

#endif