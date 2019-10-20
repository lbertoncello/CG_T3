#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>

#include "point.h"
#include "color.h"

class Circle
{
private:
    int id;
    Point center;
    float radius;
    Color color;
    bool moving = false;
    bool terrestrial = false;
    bool mainCircle = false;

public:
    Circle() {}

    Circle(Point center, float radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Circle(int id, Point center, float radius)
    {
        this->id = id;
        this->center = center;
        this->radius = radius;
    }

    Circle(float center_x, float center_y, float radius)
    {
        this->center.setX(center_x);
        this->center.setY(center_y);
        this->radius = radius;
    }

    Circle(int id, float center_x, float center_y, float radius)
    {
        this->id = id;
        this->center.setX(center_x);
        this->center.setY(center_y);
        this->radius = radius;
    }

    int getId()
    {
        return id;
    }

    Point getCenter() {
        return center;
    }

    float getCenter_x()
    {
        return center.getX();
    }

    float getCenter_y()
    {
        return center.getY();
    }

    float getRadius()
    {
        return radius;
    }

    Color& getColor()
    {
        return color;
    }

    bool isMoving()
    {
        return moving;
    }

    bool isTerrestrial()
    {
        return terrestrial;
    }

    bool isMainCircle()
    {
        return mainCircle;
    }

    void setId(int id)
    {
        this->id = id;
    }

    void setCenter_x(float center_x)
    {
        this->center.setX(center_x);
    }

    void setCenter_y(float center_y)
    {
        this->center.setY(center_y);
    }

    void setRadius(float radius)
    {
        this->radius = radius;
    }

    void setColor(Color color)
    {
        this->color = color;
    }

    void setMoving(bool moving)
    {
        this->moving = moving;
    }

    void setTerrestrial(bool terrestrial)
    {
        this->terrestrial = terrestrial;
    }

    void setMainCircle(bool mainCircle)
    {
        this->mainCircle = mainCircle;
    }

    void updateCenter(Point p)
    {
        this->center.setX(p.getX());
        this->center.setY(p.getY());
    }

    void updateCenter(float x, float y)
    {
        this->center.setX(x);
        this->center.setY(y);
    }

    bool isPointInCircle(Point p);
    bool isPointInCircle(float x, float y);
    bool checkIntersection(Circle circle, int num_segments);
    bool isInside(Circle circle, int num_segments);
};

#endif