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
    Color wingsColor(1.0, 1.0, 0.0);

    glPushMatrix();
    Point p1(this->body.getRadius() / 8, this->body.getRadius() / 8);
    Point p2(p1.getX() + this->body.getRadius() / 3, p1.getY());
    Point p3(p1.getX() - this->body.getRadius() / 6, this->body.getRadius());
    Point p4(p1.getX() + this->body.getRadius() / 3 - this->body.getRadius() / 6, this->body.getRadius());

    drawer.drawRectangle(p4, p2, p1, p3, wingsColor);

    glPopMatrix();

    glPushMatrix();
    Point p5(this->body.getRadius() / 8, -this->body.getRadius() / 8);
    Point p6(p1.getX() + this->body.getRadius() / 3, p1.getY());
    Point p7(p1.getX() - this->body.getRadius() / 6, -this->body.getRadius());
    Point p8(p1.getX() + this->body.getRadius() / 3 - this->body.getRadius() / 6, -this->body.getRadius());

    drawer.drawRectangle(p6, p8, p7, p5, wingsColor);

    glPopMatrix();
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
