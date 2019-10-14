#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>

#include "circle.h"

using namespace std;

bool Circle::isPointInCircle(Point p)
{
    float d = sqrt(pow((p.getX() - center.getX()), 2) + pow((p.getY() - center.getY()), 2));
    //cout << "d: " << d << endl;

    if (d > radius)
    {
        return false;
    }

    return true;
}

bool Circle::isPointInCircle(float x, float y)
{
    return isPointInCircle(Point(x, y));
}

bool Circle::checkIntersection(Circle circle, int num_segments)
{
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle

        float x = circle.getRadius() * cosf(theta) + circle.getCenter_x(); //calculate the x component
        float y = circle.getRadius() * sinf(theta) + circle.getCenter_y(); //calculate the y component

        if (isPointInCircle(x, y))
        {
            return true;
        }
    }

    return false;
}

//Verifica se o circulo circle está dentro deste
bool Circle::isInside(Circle circle, int num_segments)
{
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle

        float x = circle.getRadius() * cosf(theta) + circle.getCenter_x(); //calculate the x component
        float y = circle.getRadius() * sinf(theta) + circle.getCenter_y(); //calculate the y component

        if (isPointInCircle(x, y) == false)
        {
            return false;
        }
    }

    return true;
}