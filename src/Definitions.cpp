#include "../include/Definitions.h"

float Distancia_Puntos(float x1, float y1, float z1, float x2, float y2, float z2) {
	float a = (x1 - x2);
	float b = (y1 - y2);
	float c = (z1 - z2);
	float r = sqrtf(((a*a) + (b*b) + (c*c)));
	return r;
}