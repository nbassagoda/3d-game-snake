#include "../include/Apple.h"

int Apple::model_s = 0;
int Apple::model_t = 0;

list<Shape*>* Apple::ShapeApple = new list<Shape*>();

Apple::Apple(float x, float y, float z, float ang_x, float ang_y, float ang_z) {
	_position.pos_x = x;
	_position.pos_y = y+0.5;
	_position.posZ = z;
	_position.angle_x = ang_x;
	_position.angle_y = ang_y;
	_position.angle_z = ang_z;
	_position.size = 0.05;
	_id = id_code++;
	_tipo = T_CHAR;
	_clase = C_APPLE;
	_collisions = new map<int, object_class>();
	_Shape = ShapeApple;
}

void Apple::GenerateShape() {
	ShapeApple->push_back(new ShapeSphere(0, 0, 10, 0.5));
}

void Apple::Draw(ModelType m, data_camera camara) {
	glPushMatrix();
	float n = PointsDistance(_position.pos_x, _position.pos_y, _position.posZ, camara.pos_x, camara.pos_y, camara.posZ);
	if (n < z_far) {
		glEnable(GL_BLEND);
		float d = PointsDistance(camara.direction_x, camara.direction_y, camara.direction_z, camara.pos_x, camara.pos_y, camara.posZ);
		
		glTranslatef(_position.pos_x,_position.pos_y,_position.posZ);
		glRotatef(_position.angle_y,0,1,0);
		glRotatef(90,1,0,0);
		glScaled(_position.size,_position.size,_position.size);
		if(GameState::GetInstance()->Textures)
			glEnable(GL_TEXTURE_2D);
			glColor3f(1,0,0);
		if(m != MOD_COLICION) {
			glCallList(model_s);
		} else {
			list<Shape*>::iterator it;
			glColor3f(0,1,0);
			for (it = ShapeApple->begin();it != ShapeApple->end(); it++) {
				ShapeSphere* forma = dynamic_cast<ShapeSphere*>(*it);
				glPushMatrix();
				glTranslated(forma->pos_x, forma->pos_y, forma->posZ);
				glScaled(forma->radio, forma->radio, forma->radio);
				glCallList(codigoEsfer);
				glPopMatrix();
			}
		}
	}
	glDisable(GL_ALPHA);
	glPopMatrix();
}

void Apple::TimeEvolution(float t) {
	_position.angle_y += 2;
	if (_position.angle_y > 360) _position.angle_y -= 360;
}

bool Apple::CollisionAction() { }

Apple::~Apple() {
	delete(_collisions);
}