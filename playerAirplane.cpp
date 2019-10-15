#include "playerAirplane.h"

void PlayerAirplane::draw()
{
    glTranslatef(dX, dY, 0.0);
    //drawer.drawFilledCircle(this->body);
    drawMainBody();
    drawTail();
    drawCockpit();
    drawWings();
    drawCannon();
}

void PlayerAirplane::drawMainBody()
{
    drawer.drawEllipse(this->body);
}

void PlayerAirplane::drawTail()
{
}

void PlayerAirplane::drawCockpit()
{
}

void PlayerAirplane::drawWings()
{
    Point p1 = this->body.getCenter();
    Point p2;
    p2.setX(p1.getX() + 20.0);
    p2.setY(p1.getY() + 5.0);

    drawer.drawRectangle(p1, p2);
}

void PlayerAirplane::drawPropeller()
{
}

void PlayerAirplane::drawCannon()
{
}

float PlayerAirplane::calcMovement_x(GLfloat deltaIdleTime)
{
    return speed[0] * deltaIdleTime;
}

float PlayerAirplane::calcMovement_y(GLfloat deltaIdleTime)
{
    return speed[1] * deltaIdleTime;
}

void PlayerAirplane::moveUp(GLfloat deltaIdleTime)
{
    dY -= calcMovement_y(deltaIdleTime);
}

void PlayerAirplane::moveDown(GLfloat deltaIdleTime)
{
    dY += calcMovement_y(deltaIdleTime);
}

void PlayerAirplane::moveLeft(GLfloat deltaIdleTime)
{
    dX -= calcMovement_x(deltaIdleTime);
}

void PlayerAirplane::moveRight(GLfloat deltaIdleTime)
{
    dX += calcMovement_x(deltaIdleTime);
}

bool PlayerAirplane::checkIntersection(Circle circle, int moveDirection, GLfloat deltaIdleTime)
{
    Circle adjustedBody = this->body;
    adjustedBody.setCenter_x(adjustedBody.getCenter_x() + this->dX);
    adjustedBody.setCenter_y(adjustedBody.getCenter_y() + this->dY);

    switch (moveDirection)
    {
    case MOVE_UP:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() - calcMovement_y(deltaIdleTime));
        break;
    case MOVE_DOWN:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() + calcMovement_y(deltaIdleTime));
        break;
    case MOVE_LEFT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() - calcMovement_x(deltaIdleTime));
        break;
    case MOVE_RIGHT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() + calcMovement_x(deltaIdleTime));
        break;
    }

    return adjustedBody.checkIntersection(circle, this->drawer.getNumSegments());
}

bool PlayerAirplane::isInside(Circle circle, int moveDirection, GLfloat deltaIdleTime)
{
    Circle adjustedBody = this->body;
    adjustedBody.setCenter_x(adjustedBody.getCenter_x() + this->dX);
    adjustedBody.setCenter_y(adjustedBody.getCenter_y() + this->dY);

    switch (moveDirection)
    {
    case MOVE_UP:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() - calcMovement_y(deltaIdleTime));
        break;
    case MOVE_DOWN:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() + calcMovement_y(deltaIdleTime));
        break;
    case MOVE_LEFT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() - calcMovement_x(deltaIdleTime));
        break;
    case MOVE_RIGHT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() + calcMovement_x(deltaIdleTime));
        break;
    }

    return circle.isInside(adjustedBody, this->drawer.getNumSegments());
}

Circle PlayerAirplane::getAdjustedBody()
{
    Circle adjustedBody = this->body;
    adjustedBody.setCenter_x(adjustedBody.getCenter_x() + this->dX);
    adjustedBody.setCenter_y(adjustedBody.getCenter_y() + this->dY);

    return adjustedBody;
}
