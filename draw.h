#ifndef DRAW_H
#define DRAW_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "circle.h"
#include "line.h"

using namespace std;

class Draw
{
private:
    float PI = 3.14159;
    int num_segments = 300;
    float radius = 0.1;

    Point currentCenter;
    vector<Circle> circles;
    vector<Circle>::iterator circle_it;
    vector<Line> lines;
    vector<Line>::iterator line_it;
    Circle *currentCircleMoving = NULL;

    void drawCircle(float cx, float cy, float r, int num_segments, Color color);
    void drawFilledCircle(float x1, float y1, double radius, Color color);

public:
    Draw() {}

    int getNumSegments()
    {
        return num_segments;
    }

    float getRadius()
    {
        return radius;
    }

    Point &getCurrentCenter()
    {
        return currentCenter;
    }

    Circle *getCurrentCircleMoving()
    {
        currentCircleMoving;
    }

    void setRadius(float radius)
    {
        this->radius = radius;
    }

    void setCurrentCircleMoving(Circle *circle)
    {
        this->currentCircleMoving = circle;
    }

    void addCircle(Circle circle)
    {
        circles.push_back(circle);
    }

    void addLine(Line line)
    {
        lines.push_back(line);
    }

    void addCircleAtCurrentCenter();
    bool thereIsCircleMoving();
    void updateCurrentCircleMoving();
    void updateCurrentCenter(float x, float y, float x_window_size, float y_window_size);
    bool checkIntersection(Circle circle);
    void drawCircle(Color color);
    void drawCircle(Circle circle);
    void drawFilledCircle(Color color);
    void drawFilledCircle(Circle circle);
    void drawAllCircles(Color color);
    void drawAllCircles();
    void drawLine(Line line);
    void drawAllLines();
    void drawGame();
    void chooseCircleToMove();
};

#endif