#include "../include/Moon.h"

int Moon::model_s = 0;
int Moon::model_t = 0;

Moon::Moon(float x, float y, float z, float ang_x, float ang_y, float ang_z) {
    Document.open("data/Info/Events_Out.txt");
    _position.pos_x = x;
    _position.pos_y = y + 1;
    _position.posZ = z;
    _position.angle_x = ang_x;
    _position.angle_y = ang_y;
    _position.angle_z = ang_z;
    _position.size = 0.5;
    id = 1;
}

void Moon::Draw(ModelType m, data_camera camara) {
    glPushMatrix();
    float n = PointsDistance(_position.pos_x, _position.pos_y, _position.posZ, camara.pos_x, camara.pos_y, camara.posZ);
    if (n < z_far) {
        glEnable(GL_BLEND);
        float d = PointsDistance(camara.direction_x, camara.direction_y, camara.direction_z, camara.pos_x, camara.pos_y, camara.posZ);

        glTranslatef(_position.pos_x,_position.pos_y,_position.posZ);
        glRotatef(_position.angle_y,0,1,0);
        glScaled(_position.size,_position.size,_position.size);
        if(GameState::GetInstance()->Textures)
            glEnable(GL_TEXTURE_2D);
            glColor3f(1,0,0);
        if(m != MOD_COLICION) {
            glCallList(model_s);
        }
    }
    glDisable(GL_ALPHA);
    glPopMatrix();

    Document << "[GraphicEngine]" << _position.pos_x <<  _position.pos_y <<  _position.posZ << endl;
}

void Moon::TimeEvolution(float t) {
    _position.angle_y += 0.6;
    if(_position.angle_y > 360) _position.angle_y -= 360;
}

Moon::~Moon() {
}