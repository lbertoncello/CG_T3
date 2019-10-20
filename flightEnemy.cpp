#include "flightEnemy.h"

void FlightEnemy::draw()
{
    // glTranslatef(-500 + this->getBody().getCenter_x(), -500 + this->getBody().getCenter_y(), 0.0);
    drawer.drawFilledCircle(this->getBody());
}
