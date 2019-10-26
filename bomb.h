#ifndef BOMB_H
#define BOMB_H

#include "circle.h"
#include "draw.h"

#define BOMB_LIFETIME 4.0

class Bomb
{
    Circle body;
    GLfloat dX;
    GLfloat dY;
    GLfloat speedNorm;
    GLfloat moveAngle;
    Point startPosition;
    Draw drawer;

    GLfloat calcMovement_x(GLfloat deltaIdleTime);
    GLfloat calcMovement_y(GLfloat deltaIdleTime);

public:
    Bomb() {}

    Bomb(Circle body, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngle)
    {
        this->body = body;
        this->speedNorm = speedNorm;
        this->moveAngle = moveAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bomb(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngle, Color color)
    {
        this->body = Circle(bodyCoordinates, radius, color);
        this->speedNorm = speedNorm;
        this->moveAngle = moveAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bomb(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngle)
    {
        this->body = Circle(bodyCoordinates, radius, Color(0.65, 0.2, 0.45));
        this->speedNorm = speedNorm;
        this->moveAngle = moveAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->startPosition.setX(dX);
        this->startPosition.setY(dY);
    }

    Circle &getBody()
    {
        return body;
    }

    GLfloat getSpeed()
    {
        return speedNorm;
    }

    GLfloat getspeedAngle()
    {
        return moveAngle;
    }

    void draw();
    void move(GLfloat deltaIdleTime);
    Point getCurrentPositionAdjusted();
};

#endif