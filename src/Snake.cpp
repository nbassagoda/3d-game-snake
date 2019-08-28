#include "../include/Snake.h"
#include "../include/EventsEngine.h"

#define pi 3.1415926535897932384626433832795
#define dos_pi 6.283185307179586476925286766559

GLint Snake::model_s = 0;
GLint Snake::model_t = 0;

list<Shape*>* Snake::snake_shape = new list<Shape*>();

Snake::~Snake() {
	delete(_collisions);
}

Snake::Snake(float x, float y, float z, float ang_x, float ang_y, float ang_z) {
	Document.open(SNAKE_DOCUMENT_PATH);
	angle_adjust_rad = 0.05;
	current_angle_rad = 0;
	angle_adjust_gr = angle_adjust_rad*360/dos_pi;
	_position.pos_x = x;
	_position.pos_y = y;
	_position.posZ = z;
	_position.angle_x = ang_x;
	_position.angle_y = ang_y;
	_position.angle_z = ang_z;
	_position.size = 0.05;
	_id = id_code++;
	_tipo = T_CHAR;
	_clase = C_SNAKE;
	_collisions = new map<int, object_class>();
	_Shape = snake_shape;
	srand((unsigned)time(NULL));
	_color_r=((float) rand() / (RAND_MAX+1));
	_color_g=((float) rand() / (RAND_MAX+1));
	_color_b=((float) rand() / (RAND_MAX+1));
}

void Snake::TimeEvolution(float t) {
	_position.pos_x += t*sin(current_angle_rad);
	_position.posZ += t*cos(current_angle_rad);
	if((_position.pos_x < -field_limit) || (_position.posZ < -field_limit) || (field_limit < _position.pos_x) || (field_limit < _position.posZ)) {
		GameState::GetInstance()->AddActionList(TO_LOSE);
	}
}

void Snake::Draw(ModelType m,data_camera camera) {
	if(GameState::GetInstance()->estdo == ACTIVE) {
		EventsEngine* Motor_temporal = EventsEngine::GetInstance();
		if(Motor_temporal->Rotate()) {
			if(Motor_temporal->RotationDirection()) {
				current_angle_rad += angle_adjust_rad;
				_position.angle_y += angle_adjust_gr;
				if (dos_pi < current_angle_rad) current_angle_rad -= dos_pi;
			} else {
				current_angle_rad -= angle_adjust_rad;
				_position.angle_y -= angle_adjust_gr;
				if (current_angle_rad < 0) current_angle_rad += dos_pi;
			}
		}
	}
	glPushMatrix();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(_position.pos_x,_position.pos_y,_position.posZ);
	glRotatef(_position.angle_x,1,0,0);
	glRotatef(_position.angle_y,0,1,0);
	glRotatef(_position.angle_z,0,0,1);
	glScaled(_position.size,_position.size,_position.size);
	if(GameState::GetInstance()->Textures) {
		glEnable(GL_TEXTURE_2D);
		glColor4f(1,1,1,1);
	} else
		glColor4f(_color_r,_color_g,_color_b,1);
	int modelo;
	if(m != MOD_COLICION) {
		if(GameState::GetInstance()->motion)
			glCallList(model_t);
		else
			glCallList(model_s);
	} else {
		glDisable(GL_TEXTURE_2D);
		list<Shape*>::iterator it;
		glColor3f(0,1,1);
		for (it = snake_shape->begin();it != snake_shape->end(); it++) {
			ShapeSphere* forma = dynamic_cast<ShapeSphere*>(*it);
			glPushMatrix();
			glTranslated(forma->pos_x, forma->pos_y, forma->posZ);
			glScaled(forma->radio, forma->radio, forma->radio);
			glCallList(codigoEsfer);
			glPopMatrix();
		}
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void Snake::GenerateShape() {
	snake_shape->push_back(new ShapeSphere(0,0,0,1));
}

bool Snake::CollisionAction() {
	map<int, object_class>::iterator it ;
	for(it = _collisions->begin(); it != _collisions->end(); ++it)
		if(it->second == C_APPLE) {
			GameState::GetInstance()->AddActionList(TO_BONUS_POINT);
		}
		return false;
}

float Snake::GetCurrentAngle() {
	return current_angle_rad;
}