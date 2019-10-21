#include "playerAirplane.h"

void PlayerAirplane::draw()
{
    glPushMatrix();
    glTranslatef(dX, dY, 0.0);
    glRotatef(inclinationAngle, 0.0, 0.0, 1.0);
    //glRotatef(-15, 0.0, 0.0, 1.0);

    drawWings();
    drawCannon();
    drawMainBody();
    drawCockpit();
    drawTail();
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
    glPushMatrix();

    Color color(0.0, 0.0, 0.0);

    glTranslatef(-this->body.getRadius() / 2, 0.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5, this->body.getRadius() / 2, color);

    glPopMatrix();
}

void PlayerAirplane::drawCockpit()
{
    glPushMatrix();

    float cockpitRadius = this->body.getRadius() / 2;
    Color cockpitColor(0.0, 0.0, 0.0);

    glTranslatef(this->body.getRadius() / 3, 0.0, 0.0);
    drawer.drawEllipse(cockpitRadius, cockpitColor);

    glPopMatrix();
}

void PlayerAirplane::drawWings()
{
    Color wingsColor(0.0, 0.0, 0.0);

    glPushMatrix();
    Point p1(0, 0);
    Point p2(p1.getX() + this->body.getRadius() / 3, p1.getY());
    Point p3(p1.getX() - this->body.getRadius() / 6, this->body.getRadius());
    Point p4(p1.getX() + this->body.getRadius() / 3 - this->body.getRadius() / 6, this->body.getRadius());

    glPushMatrix();

    glTranslatef(0, this->body.getRadius() / 2, 0.0);
    drawPropeller();

    glPopMatrix();

    drawer.drawRectangle(p4, p2, p1, p3, wingsColor);

    glPopMatrix();

    glPushMatrix();
    Point p5(0, 0);
    Point p6(p1.getX() + this->body.getRadius() / 3, p1.getY());
    Point p7(p1.getX() - this->body.getRadius() / 6, -this->body.getRadius());
    Point p8(p1.getX() + this->body.getRadius() / 3 - this->body.getRadius() / 6, -this->body.getRadius());

    glPushMatrix();

    glTranslatef(0, -this->body.getRadius() / 2, 0.0);
    drawPropeller();

    glPopMatrix();

    drawer.drawRectangle(p6, p8, p7, p5, wingsColor);

    glPopMatrix();
}

void PlayerAirplane::drawPropeller()
{
    glPushMatrix();

    Color rodColor(0.0, 0.0, 0.0);
    //glTranslatef(this->body.getRadius() * 0.9, 0.0, 0.0);

    glPushMatrix();

    glRotatef(-90, 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5.0, this->body.getRadius() / 2.5, rodColor);

    glPopMatrix();

    glPushMatrix();

    Color propellerColor(1.0, 1.0, 0.0);

    Point p1(-this->body.getRadius() / 4, -this->body.getRadius() / 6);
    Point p2(this->body.getRadius() / 4, -this->body.getRadius() / 6);
    Point p3(0, 0);

    Point p4(-this->body.getRadius() / 4, this->body.getRadius() / 6);
    Point p5(this->body.getRadius() / 4, this->body.getRadius() / 6);
    Point p6(0, 0);

    glTranslatef(this->body.getRadius() / 2.0, 0, 0.0);

    drawer.drawTriangle(p3, p2, p1, propellerColor);
    drawer.drawTriangle(p4, p5, p6, propellerColor);

    glPopMatrix();

    glPopMatrix();
}

void PlayerAirplane::drawCannon()
{
    glPushMatrix();

    Color color(0.0, 0.0, 0.0);

    glTranslatef(this->body.getRadius() * 0.9, 0.0, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5, this->body.getRadius() / 2, color);

    glPopMatrix();
}

float PlayerAirplane::calcMovement_x(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * cos(moveAngle);
}

float PlayerAirplane::calcMovement_y(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * sin(moveAngle);
}

void PlayerAirplane::move(GLfloat deltaIdleTime)
{
    updateTurnLeftAngle(deltaIdleTime);
    updateTurnRightAngle(deltaIdleTime);

    dX += calcMovement_x(deltaIdleTime);
    dY -= calcMovement_y(deltaIdleTime);
}

void PlayerAirplane::updateTurningAngles(GLfloat deltaIdleTime)
{
    updateTurnLeftAngle(deltaIdleTime);
    updateTurnRightAngle(deltaIdleTime);
}

float PlayerAirplane::calcNextMovement_x(GLfloat deltaIdleTime, float nextMoveAngle)
{
    return speedNorm * deltaIdleTime * cos(nextMoveAngle);
}

float PlayerAirplane::calcNextMovement_y(GLfloat deltaIdleTime, float nextMoveAngle)
{
    return speedNorm * deltaIdleTime * sin(nextMoveAngle);
}

Point PlayerAirplane::getNextPosition(GLfloat deltaIdleTime)
{
    float nextMoveAngle = getNextMoveAngle(deltaIdleTime);
    Point nextPosition;

    nextPosition.setX(dX + calcNextMovement_x(deltaIdleTime, nextMoveAngle));
    nextPosition.setY(dY - calcNextMovement_y(deltaIdleTime, nextMoveAngle));

    return nextPosition;
}

// void PlayerAirplane::moveUp(GLfloat deltaIdleTime)
// {
//     dY -= calcMovement_y(deltaIdleTime);
// }

// void PlayerAirplane::moveDown(GLfloat deltaIdleTime)
// {
//     dY += calcMovement_y(deltaIdleTime);
// }

// void PlayerAirplane::moveLeft(GLfloat deltaIdleTime)
// {
//     dX -= calcMovement_x(deltaIdleTime);
// }

// void PlayerAirplane::moveRight(GLfloat deltaIdleTime)
// {
//     dX += calcMovement_x(deltaIdleTime);
// }

bool PlayerAirplane::checkIntersection(Circle flightAreaBody, Circle enemyBody, GLfloat deltaIdleTime)
{
    Circle adjustedBody = Circle(this->getNextPosition(deltaIdleTime), this->body.getRadius());
    // adjustedBody.setCenter_x(this->dX);
    // adjustedBody.setCenter_y(this->dY);
    // adjustedBody.setCenter_x(flightAreaBody.getCenter_x() + this->dX);
    // adjustedBody.setCenter_y(flightAreaBody.getCenter_y() + this->dY);
    adjustedBody.setCenter_x(flightAreaBody.getCenter_x() + adjustedBody.getCenter_x());
    adjustedBody.setCenter_y(flightAreaBody.getCenter_y() + adjustedBody.getCenter_y());

    return adjustedBody.checkIntersection(enemyBody, this->drawer.getNumSegments());
}

bool PlayerAirplane::isInside(Circle circle, int moveDirection, GLfloat deltaIdleTime)
{
    Circle adjustedBody = this->body;
    // adjustedBody.setCenter_x(this->dX);
    // adjustedBody.setCenter_y(this->dY);
    adjustedBody.setCenter_x(circle.getCenter_x() + this->dX);
    adjustedBody.setCenter_y(circle.getCenter_y() + this->dY);

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

float PlayerAirplane::getNextMoveAngle(GLfloat deltaIdleTime)
{
    float nextAngle = moveAngle;

    if (isTurningLeft())
    {
        nextAngle += (PI / 2 * deltaIdleTime);
    }

    if (isTurningRight())
    {
        nextAngle -= (PI / 2 * deltaIdleTime);
    }

    return nextAngle;
}

void PlayerAirplane::updateTurnRightAngle(GLfloat deltaIdleTime)
{
    if (isTurningRight())
    {
        moveAngle -= PI / 2 * deltaIdleTime;
    }
}

void PlayerAirplane::updateTurnLeftAngle(GLfloat deltaIdleTime)
{
    if (isTurningLeft())
    {
        moveAngle += PI / 2 * deltaIdleTime;
    }
    //cout << "virando: " << -PI/2 * deltaIdleTime << endl;
}

void PlayerAirplane::reset()
{
    body.setRadius(initialRadius);
    dX = 0; //variação em X
    dY = 0; //variação em Y
    inclinationAngle = 0;
    speedNorm = 0;
    turningLeft = false;
    turningRight = false;
    flying = false;
    takingOff = false;
    startPositionInitialized = false;
    initialRadiusInitialized = false;
}
