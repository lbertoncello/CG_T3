#ifndef BULLET_H
#define BULLET_H

#include "circle.h"
#include "draw.h"

class Bullet
{
    Circle body;
    float dX;
    float dY;
    float speed;
    float speedAngle;
    float positionAngle = 0;
    Draw drawer;

public:
    Bullet() {}

    Bullet(Circle body, Point moveCoordinates, float speed, float speedAngle)
    {
        this->body = body;
        this->speed = speed;
        this->speedAngle = speedAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bullet(Point bodyCoordinates, Point moveCoordinates, float speed, float speedAngle, Color color)
    {
        this->body = Circle(bodyCoordinates, 4, color);
        this->speed = speed;
        this->speedAngle = speedAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bullet(Point bodyCoordinates, Point moveCoordinates, float speed, float speedAngle)
    {
        this->body = Circle(bodyCoordinates, 4, Color(1, 0, 1));
        this->speed = speed;
        this->speedAngle = speedAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bullet(Point bodyCoordinates, Point moveCoordinates, float speed, float speedAngle, float positionAgle)
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

    float getSpeed()
    {
        return speed;
    }

    float getspeedAngle()
    {
        return speedAngle;
    }

    void draw();
};

#endif