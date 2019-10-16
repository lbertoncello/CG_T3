#include "terrestrialEnemy.h"

void TerrestrialEnemy::draw()
{
    glTranslatef(this->getBody().getCenter_x(), this->getBody().getCenter_y(), 0.0);
    drawer.drawFilledCircle(this->getBody());
}