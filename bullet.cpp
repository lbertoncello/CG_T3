#include "bullet.h"

void Bullet::draw()
{
    glPushMatrix();

    glTranslatef(dX, dY, 0.0);
    glRotatef(positionAngle + speedAngle, 0.0, 0.0, 1.0);
    drawer.drawFilledCircle(this->body);

    glPopMatrix();
}