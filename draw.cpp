#include "draw.h"

bool Draw::thereIsCircleMoving()
{
    if (currentCircleMoving == NULL)
    {
        return false;
    }

    return true;
}

void Draw::updateCurrentCircleMoving()
{
    currentCircleMoving->updateCenter(currentCenter);
}

void Draw::drawCircle(float cx, float cy, float r, int num_segments, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glBegin(GL_LINE_LOOP);

    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle

        float x = r * cosf(theta); //calculate the x component
        float y = r * sinf(theta); //calculate the y component

        //glVertex2f(x + cx, y + cy); //output vertex
        glVertex2f(x, y); //output vertex
    }
    glEnd();
}

void Draw::drawEllipse(float cx, float cy, float rx, float ry, Color color, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta); //precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1; //we start at angle = 0
    float y = 0;

    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex2f(x * rx, y * ry); //output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

// #define DEG2RAD 3.14159 / 180.0

// void Draw::drawEllipse(float cx, float cy, float radiusX, float radiusY, Color color, int num_segments)
// {
//     int i;
//     glColor3f(color.getR(), color.getG(), color.getB());

//     glBegin(GL_LINE_LOOP);

//     for (i = 0; i < 360; i++)
//     {
//         float rad = i * DEG2RAD;
//         glVertex2f(cos(rad) * radiusX,
//                    sin(rad) * radiusY);
//     }

//     glEnd();
// }

void Draw::drawFilledCircle(float x1, float y1, double radius, Color color)
{
    //filled circle
    float x2, y2;
    x1 = 0;
    y1 = 0;
    float angle;

    //x1 = 0.5,y1=0.6;
    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);

    for (angle = 1.0f; angle < 361.0f; angle += 0.2)
    {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glVertex2f(x2, y2);
    }

    glEnd();
}

void Draw::drawRectangle(Point p1, Point p2)
{
    glRectf(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void Draw::updateCurrentCenter(float x, float y, float x_window_size, float y_window_size)
{
    //float center_x = x / float(x_window_size);
    //float center_y = 1.0 - (y / float(y_window_size));

    float center_x = x;
    float center_y = y_window_size - y;

    currentCenter.update(center_x, center_y);
}

bool Draw::checkIntersection(Circle circle)
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        if (circle.checkIntersection(*circle_it, num_segments))
        {
            return true;
        }
    }

    return false;
}

void Draw::drawCircle(Circle circle)
{
    drawCircle(circle.getCenter_x(), circle.getCenter_y(), circle.getRadius(), num_segments, circle.getColor());
}

void Draw::drawEllipse(Circle circle)
{
    drawEllipse(circle.getCenter_x(), circle.getCenter_y(), circle.getRadius(), circle.getRadius() / 4, circle.getColor(), num_segments);
}

void Draw::drawCircle(Color color)
{
    drawCircle(currentCenter.getX(), currentCenter.getY(), radius, num_segments, color);
}

void Draw::drawFilledCircle(Color color)
{
    drawFilledCircle(currentCenter.getX(), currentCenter.getY(), radius, color);
}

void Draw::drawFilledCircle(Circle circle)
{
    drawFilledCircle(circle.getCenter_x(), circle.getCenter_y(), circle.getRadius(), circle.getColor());
}

void Draw::drawAllCircles(Color color)
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        drawFilledCircle(circle_it->getCenter_x(), circle_it->getCenter_y(), circle_it->getRadius(), color);
    }
}

void Draw::drawAllCircles()
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        drawFilledCircle(circle_it->getCenter_x(), circle_it->getCenter_y(), circle_it->getRadius(), circle_it->getColor());
    }
}

void Draw::chooseCircleToMove()
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        if (circle_it->isPointInCircle(currentCenter.getX(), currentCenter.getY()))
        {
            circle_it->setMoving(true);
            currentCircleMoving = &(*circle_it);
            break;
        }
    }
}

void Draw::drawLine(Line line)
{
    glColor3f(line.getColor().getR(), line.getColor().getG(), line.getColor().getB());
    glPointSize(0.5);

    glBegin(GL_LINES);
    glVertex2d(line.getPoint1_x(), line.getPoint1_y());
    glVertex2d(line.getPoint2_x(), line.getPoint2_y());
    glEnd();
}

void Draw::drawAllLines()
{
    for (line_it = lines.begin(); line_it != lines.end(); line_it++)
    {
        drawLine(*line_it);
    }
}

void Draw::drawGame()
{
}