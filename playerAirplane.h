#ifndef PLAYER_AIRPLANE_H
#define PLAYER_AIRPLANE_H

#include "circle.h"
#include "draw.h"
#include "calc.h"

#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4

#define PI 3.14159265
class PlayerAirplane
{
    Circle body;
    Point currentPosition;
    Point startPosition;
    float initialRadius;
    float dX = 0; //variação em X
    float dY = 0; //variação em Y
    float inclinationAngle = 0;
    float speedNorm = 0;
    bool turningLeft = false;
    bool turningRight = false;
    bool flying = false;
    bool takingOff = false;
    bool startPositionInitialized = false;
    bool initialRadiusInitialized = false;
    Draw drawer;
    vector<float> speed;
    float moveAngle;
    float speedMultiplier;
    Calc calc;

    void speedInit()
    {
        speed.push_back(0);
        speed.push_back(0);
    }

    void drawMainBody();
    void drawTail();
    void drawCockpit();
    void drawWings();
    void drawPropeller();
    void drawCannon();
    void updateTurnRightAngle(GLfloat deltaIdleTime);
    void updateTurnLeftAngle(GLfloat deltaIdleTime);
    float getNextMoveAngle(GLfloat deltaIdleTime);
    float calcNextMovement_x(GLfloat deltaIdleTime, float nextMoveAngle);
    float calcNextMovement_y(GLfloat deltaIdleTime, float nextMoveAngle);
    void updateInclinationAngle(GLfloat deltaIdleTime);

public:
    PlayerAirplane()
    {
        speedInit();
    }

    PlayerAirplane(Circle body)
    {
        this->body = body;
        initialRadius = body.getRadius();
        initialRadiusInitialized = true;
        speedInit();
    }

    Circle &getBody()
    {
        return body;
    }

    Point getCurrentPosition()
    {
        return currentPosition;
    }

    Point getStartPosition()
    {
        return startPosition;
    }

    float getInitialRadius()
    {
        return initialRadius;
    }

    bool isFlying()
    {
        return flying;
    }

    bool isTakingOff()
    {
        return takingOff;
    }

    bool isTurningLeft()
    {
        return turningLeft;
    }

    bool isTurningRight()
    {
        return turningRight;
    }

    vector<float> &getSpeed()
    {
        return speed;
    }

    float getSpeedMultiplier()
    {
        return speedMultiplier;
    }

    void setBody(Circle body)
    {
        this->body = body;

        if (initialRadiusInitialized == false)
        {
            initialRadius = body.getRadius();
            initialRadiusInitialized = true;
        }
    }

    void setCurrentPosition(Point currentPosition)
    {
        if (startPositionInitialized == false)
        {
            startPosition.setX(currentPosition.getX());
            startPosition.setY(currentPosition.getY());
            startPositionInitialized = true;
        }

        // dX = currentPosition.getX() - this->startPosition.getX();
        // dY = currentPosition.getY() - this->startPosition.getY();

        dX = currentPosition.getX();
        dY = currentPosition.getY();

        this->currentPosition = currentPosition;

        //this->currentPosition.setX(currentPosition.getX() - this->startPosition.getX());
        //this->currentPosition.setY(currentPosition.getY() - this->startPosition.getY());
    }

    void setFlying(bool flying)
    {
        this->flying = flying;
    }

    void setTakingOff(bool takingOff)
    {
        this->takingOff = takingOff;
    }

    void setSpeed(vector<float> speed)
    {
        //float speedNorm = calc.norm(speed) * this->speedMultiplier;
        speedNorm = calc.norm(speed) * this->speedMultiplier;
        moveAngle = -atan2f(speed[1], speed[0]);

        this->speed[0] = (speedNorm * cos(45.0 * 3.14159265 / 180));
        this->speed[1] = (speedNorm * sin(45.0 * 3.14159265 / 180));
    }

    void setSpeedMultiplier(float speedMultiplier)
    {
        this->speedMultiplier = speedMultiplier;
    }

    void setInclinationAngle(float inclinationAngle)
    {
        this->inclinationAngle = inclinationAngle;
    }

    float getInclinationAngle()
    {
        return this->inclinationAngle;
    }

    void setTurningLeft(bool turningLeft)
    {
        this->turningLeft = turningLeft;

        // if (turningLeft == false && turningRight == false)
        // {
        //     moveAngle = PI / 4;
        // }
    }

    void setTurningRight(bool turningRight)
    {
        this->turningRight = turningRight;

        // if (turningLeft == false && turningRight == false)
        // {
        //     moveAngle = PI / 4;
        // }
    }

    void draw();
    void move(GLfloat deltaIdleTime);
    // void moveUp(GLfloat deltaIdleTime);
    // void moveDown(GLfloat deltaIdleTime);
    // void moveLeft(GLfloat deltaIdleTime);
    // void moveRight(GLfloat deltaIdleTime);
    bool checkIntersection(Circle flightAreaBody, Circle enemyBody, GLfloat deltaIdleTime);
    float calcMovement_x(GLfloat deltaIdleTime);
    float calcMovement_y(GLfloat deltaIdleTime);
    Circle getAdjustedBody();
    bool isInside(Circle circle, int moveDirection, GLfloat deltaIdleTime);
    Point getNextPosition(GLfloat deltaIdleTime);
    void updateTurningAngles(GLfloat deltaIdleTime);
    void reset();
};

#endif