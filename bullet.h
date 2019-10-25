#ifndef BULLET_H
#define BULLET_H

#include "circle.h"
#include "draw.h"

class Bullet
{
    Circle body;
    GLfloat dX;
    GLfloat dY;
    GLfloat speed;
    GLfloat speedAngle;
    GLfloat positionAngle = 0;
    Draw drawer;

public:
    Bullet() {}

    Bullet(Circle body, Point moveCoordinates, GLfloat speed, GLfloat speedAngle)
    {
        this->body = body;
        this->speed = speed;
        this->speedAngle = speedAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bullet(Point bodyCoordinates, Point moveCoordinates, GLfloat speed, GLfloat speedAngle, Color color)
    {
        this->body = Circle(bodyCoordinates, 4, color);
        this->speed = speed;
        this->speedAngle = speedAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bullet(Point bodyCoordinates, Point moveCoordinates, GLfloat speed, GLfloat speedAngle)
    {
        this->body = Circle(bodyCoordinates, 4, Color(1, 0, 1));
        this->speed = speed;
        this->speedAngle = speedAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bullet(Point bodyCoordinates, Point moveCoordinates, GLfloat speed, GLfloat speedAngle, GLfloat positionAgle)
    {
        this->body = Circle(bodyCoordinates, 4, Color(1, 0, 1));
        this->speed = speed;
        this->speedAngle = speedAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->positionAngle = positionAgle;
    }

    Circle getBody()
    {
        return body;
    }

    GLfloat getSpeed()
    {
        return speed;
    }

    GLfloat getspeedAngle()
    {
        return speedAngle;
    }

    void draw();
};

#endif