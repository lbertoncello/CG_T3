#ifndef BOMB_H
#define BOMB_H

#include "circle.h"
#include "draw.h"

class Bomb
{
    Circle body;
    GLfloat speed;
    GLfloat angle;
    Color color;
    Point position;
    Draw drawer;

public:
    Bomb() {}

    Bomb(Circle body, GLfloat speed, GLfloat angle, Color color, Point position)
    {
        this->body = body;
        this->speed = speed;
        this->angle = angle;
        this->color = color;
        this->position = position;
    }

    Circle getBody()
    {
        return body;
    }

    GLfloat getSpeed()
    {
        return speed;
    }

    GLfloat getAngle()
    {
        return angle;
    }

    void draw();
};

#endif