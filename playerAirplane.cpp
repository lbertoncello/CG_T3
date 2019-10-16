#include "playerAirplane.h"

void PlayerAirplane::draw()
{
    glPushMatrix();
    glTranslatef(dX, dY, 0.0);
    glRotatef(-15, 0.0, 0.0, 1.0);

    drawMainBody();
    drawTail();
    drawCockpit();
    drawWings();
    drawCannon();
    glPopMatrix();
}

void PlayerAirplane::drawMainBody()
{
    glPushMatrix();

    drawer.drawEllipse(this->body);
    drawer.drawCircle(this->body);

    glPopMatrix();
}

void PlayerAirplane::drawTail()
{
}

void PlayerAirplane::drawCockpit()
{
}

void PlayerAirplane::drawWings()
{
    Point p1(0, 0);
    Point p2;

    glPushMatrix();

    glRotatef(120, 0.0, 0.0, 1.0);
    glTranslatef(this->body.getRadius() / 2, this->body.getRadius() / 6, 0.0);

    p2.setX(this->body.getRadius() / 1);
    p2.setY(this->body.getRadius() / 3);

    drawer.drawRectangle(p1, p2);

    glPopMatrix();

    glPushMatrix();

    glRotatef(-120, 0.0, 0.0, 1.0);
    glTranslatef(this->body.getRadius() / 2, this->body.getRadius() / 6, 0.0);

    p2.setX(this->body.getRadius() / 1);
    p2.setY(this->body.getRadius() / 3);

    drawer.drawRectangle(p1, p2);

    glPopMatrix();

    // glPushMatrix();

    // p2.setX(this->body.getRadius() / 1);
    // p2.setY(this->body.getRadius() / 3);

    // glTranslatef(this->body.getRadius() / 4, -this->body.getRadius() / 4, 0.0);
    // glRotatef(210, 0.0, 0.0, 1.0);
    // drawer.drawRectangle(p1, p2);

    // glPopMatrix();
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
    adjustedBody.setCenter_x(this->dX);
    adjustedBody.setCenter_y(this->dY);

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
    adjustedBody.setCenter_x(this->dX);
    adjustedBody.setCenter_y(this->dY);

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
