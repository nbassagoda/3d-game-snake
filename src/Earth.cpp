#include "../include/Earth.h"

int Earth::model_s = 0;
int Earth::model_t = 0;

Earth::Earth(float x, float y, float z, float ang_x, float ang_y, float ang_z) {
    Document.open("data/Info/Events_Out.txt");
    Document << "[GraphicEngine]" << _posicion.pos_x <<  _posicion.pos_y <<  _posicion.posZ << endl;
    _posicion.pos_x = x;
    _posicion.pos_y = y + 1;
    _posicion.posZ = z;
    _posicion.angle_x = ang_x;
    _posicion.angle_y = ang_y;
    _posicion.angle_z = ang_z;
    _posicion.size = 0.5;
    id = 0;
}

void Earth::Draw(ModelType m, data_camera camara) {
    glPushMatrix();
    float n = PointsDistance(_posicion.pos_x, _posicion.pos_y, _posicion.posZ, camara.pos_x, camara.pos_y, camara.posZ);
    if (n < z_far) {
        glEnable(GL_BLEND);
        float d = PointsDistance(camara.direction_x, camara.direction_y, camara.direction_z, camara.pos_x, camara.pos_y, camara.posZ);

        glTranslatef(_posicion.pos_x,_posicion.pos_y,_posicion.posZ);
        glRotatef(_posicion.angle_y,0,1,0);
        glScaled(_posicion.size,_posicion.size,_posicion.size);
        if(EstadoJuego::GetInstance()->Texturas)
            glEnable(GL_TEXTURE_2D);
            glColor3f(1,0,0);
        if(m != MOD_COLICION) {
            glCallList(model_s);
        }
    }
    glDisable(GL_ALPHA);
    glPopMatrix();
    Document << "[GraphicEngine]" << _posicion.pos_x <<  _posicion.pos_y <<  _posicion.posZ << endl;
}

void Earth::TimeEvolution(float t) {
    _posicion.angle_y += 0.6;
    if(_posicion.angle_y > 360) _posicion.angle_y -= 360;
}

Earth::~Earth() {
}