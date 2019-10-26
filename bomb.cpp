#include "bomb.h"

void Bomb::move(GLfloat deltaIdleTime)
{
    dX += calcMovement_x(deltaIdleTime);
    dY += calcMovement_y(deltaIdleTime);
}

GLfloat Bomb::calcMovement_x(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * cos(moveAngle);
}

GLfloat Bomb::calcMovement_y(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * sin(moveAngle);
}

Point Bomb::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() - startPosition.getX() + dX);
    currentPositionAdjusted.setY(this->body.getCenter_y() - startPosition.getY() + dY);

    return currentPositionAdjusted;
}

void Bomb::draw()
{
    glPushMatrix();

    glTranslatef(dX, dY, 0.0);
    drawer.drawFilledCircle(this->body);

    glPopMatrix();
}