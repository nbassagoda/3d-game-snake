#include "Object.h"

#include <cmath>
#include <ctime>

#ifndef SNAKE_H
#define SNAKE_H

class Snake : public Object {
	private:
		const char* SNAKE_DOCUMENT_PATH = "data/Info/Out_Snake.txt";
		ofstream Document;
		float current_angle_rad;
		float angle_adjust_rad;
		float current_angle_gr;
		float angle_adjust_gr;
		static list<Shape*>* snake_shape;
		float _color_r;
		float _color_g;
		float _color_b;

	public:
		Snake(float x, float y, float z, float ang_x, float ang_y, float ang_z);
		static GLint model_s;
		static GLint model_t;
		static void GenerateShape();
		void Draw(ModelType m, data_camera camara);
		void TimeEvolution(float t);
		bool CollisionAction();
		float GetCurrentAngle();
		~Snake();
};

#endif