#include "game.h"

#include <iostream>

#include "calc.h"

high_resolution_clock::time_point takeOffStartTime;
high_resolution_clock::time_point sizeIncreaseStartTime;
vector<float> takeOffAcceleration;
float sizeIncreaseAcceleration;
bool beforeAirportRunwayMiddle;

Calc calc;

vector<float> Game::calcTakeOffAcceleration()
{
    Point initialPosition = airportRunway.getAdjustedBody().getPoint1();
    //float finalPosition = calc.euclideanDistance(airportRunway.getBody().getPoint1(), airportRunway.getBody().getPoint2());
    Point finalPosition = airportRunway.getAdjustedBody().getPoint2();
    vector<float> initialSpeed = calc.zerosVector(2);
    float time = TAKEOFF_TIME;

    return calc.calcAccelerationRequired(initialPosition, finalPosition, initialSpeed, time);
}

void Game::reset()
{
    playerAirplane.reset();
    init();
}

void Game::init()
{
    airportRunway.setAdjustedBody(flightArea.getArea().getCenter_x(), flightArea.getArea().getCenter_y());
    playerAirplane.setCurrentPosition(airportRunway.getAdjustedBody().getPoint1());
    playerAirplane.setInclinationAngle(airportRunway.calcInclinationAngle());
    beforeAirportRunwayMiddle = true;
}

void Game::takeOff()
{
    playerAirplane.setTakingOff(true);
    playerAirplane.setCurrentPosition(airportRunway.getAdjustedBody().getPoint1());
    takeOffAcceleration = calcTakeOffAcceleration();
    sizeIncreaseAcceleration = calcSizeIncreaseAcceleration();
    takeOffStartTime = std::chrono::high_resolution_clock::now();
    playerAirplane.setSpeed(calc.calcFinalSpeedRequired(calc.zerosVector(2), takeOffAcceleration, TAKEOFF_TIME));
}

Point Game::currentTakeOffPosition(float time)
{
    Point initialPosition = airportRunway.getAdjustedBody().getPoint1();
    vector<float> acceleration = takeOffAcceleration;
    vector<float> initialSpeed = calc.zerosVector(2);

    return calc.calcCurrentPositionVariation(initialPosition, acceleration, initialSpeed, time);
}

float Game::calcSizeIncreaseAcceleration()
{
    float airportRunwayScalarSize = calc.euclideanDistance(airportRunway.getAdjustedBody().getPoint1(), airportRunway.getAdjustedBody().getPoint2());
    airportRunway.setScalarMiddle(airportRunwayScalarSize / 2.0);
    float airportRunwayScalarAcceleration = calc.calcAccelerationRequired(0.0, airportRunwayScalarSize, 0.0, TAKEOFF_TIME);

    float finalSpeed = calc.calcFinalSpeedRequired(0.0, airportRunwayScalarAcceleration, TAKEOFF_TIME);

    float initialSize = playerAirplane.getBody().getRadius();
    float finalSize = 2 * initialSize;
    float initialSpeed = calc.calcInitialSpeedRequired(finalSpeed, airportRunwayScalarAcceleration, airportRunwayScalarSize / 2, airportRunwayScalarSize);
    float time = calc.calcTimeRequired(initialSpeed, finalSpeed, airportRunwayScalarAcceleration);

    return calc.calcAccelerationRequired(initialSize, finalSize, 0, time);
}

float Game::currentRadius(float time)
{
    float initialPosition = playerAirplane.getInitialRadius();
    float acceleration = sizeIncreaseAcceleration;
    float initialSpeed = 0;

    return calc.calcCurrentPositionVariation(initialPosition, acceleration, initialSpeed, time);
}

void Game::updateTakeOff(high_resolution_clock::time_point currentTime, float takeOffTimeElapsed)
{
    Point currentPositionVariation = currentTakeOffPosition(takeOffTimeElapsed);
    Point currentPosition(playerAirplane.getStartPosition().getX() + currentPositionVariation.getX(), playerAirplane.getStartPosition().getY() + currentPositionVariation.getY());
    playerAirplane.setCurrentPosition(currentPosition);

    if (beforeAirportRunwayMiddle == false)
    {
        duration<float> timeSpan = duration_cast<duration<float>>(currentTime - sizeIncreaseStartTime);
        float sizeIncreaseTimeElapsed = timeSpan.count();

        float newRadius = playerAirplane.getInitialRadius() + currentRadius(sizeIncreaseTimeElapsed);
        playerAirplane.getBody().setRadius(newRadius);
    }
    else
    {
        float distance = calc.euclideanDistance(playerAirplane.getCurrentPosition(), airportRunway.getAdjustedBody().getPoint2());

        if (distance < airportRunway.getScalarMiddle())
        {
            beforeAirportRunwayMiddle = false;
            sizeIncreaseStartTime = high_resolution_clock::now();
        }
    }
}

void Game::drawFlightArea()
{
    glPushMatrix();
    flightArea.draw();
    glPopMatrix();
}

void Game::drawPlayerAirplane()
{
    glPushMatrix();
    if (playerAirplane.isTakingOff())
    {
        high_resolution_clock::time_point currentTime = high_resolution_clock::now();
        duration<float> timeSpan = duration_cast<duration<float>>(currentTime - takeOffStartTime);
        float timeElapsed = timeSpan.count();

        if (timeElapsed >= TAKEOFF_TIME)
        {
            playerAirplane.setTakingOff(false);
            playerAirplane.setFlying(true);
        }

        updateTakeOff(currentTime, timeElapsed);
    }

    if (playerAirplane.isFlying())
    {
        if (!checkFlightEnemiesCollision())
        {
            playerAirplane.move(deltaIdleTime);
        } else {
            playerAirplane.updateTurningAngles(deltaIdleTime);
        }
    }

    //glTranslatef(-flightArea.getArea().getCenter_x() + playerAirplane.getBody().getCenter_x(), -flightArea.getArea().getCenter_y() + playerAirplane.getBody().getCenter_y(), 0.0);
    playerAirplane.draw();
    glPopMatrix();
}

void Game::drawAirportRunway()
{
    glPushMatrix();
    //glTranslatef(flightArea.getArea().getCenter_x() - airportRunway.getBody().getPoint2_x(), flightArea.getArea().getCenter_y() - airportRunway.getBody().getPoint2_y(), 0.0);
    airportRunway.draw();
    glPopMatrix();
}

void Game::drawFlightEnemies()
{
    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        glPushMatrix();
        glTranslatef(-flightArea.getArea().getCenter_x() + flightEnemy_it->getBody().getCenter_x(), -flightArea.getArea().getCenter_y() + flightEnemy_it->getBody().getCenter_y(), 0.0);
        flightEnemy_it->draw();
        glPopMatrix();
    }
}

void Game::drawTerrestrialEnemies()
{
    vector<TerrestrialEnemy>::iterator terrestrialEnemies_it;
    for (terrestrialEnemies_it = terrestrialEnemies.begin(); terrestrialEnemies_it != terrestrialEnemies.end(); terrestrialEnemies_it++)
    {
        glPushMatrix();
        glTranslatef(-flightArea.getArea().getCenter_x() + terrestrialEnemies_it->getBody().getCenter_x(), -flightArea.getArea().getCenter_y() + terrestrialEnemies_it->getBody().getCenter_y(), 0.0);
        terrestrialEnemies_it->draw();
        glPopMatrix();
    }
}

void Game::drawGame(GLfloat deltaIdleTime)
{
    this->deltaIdleTime = deltaIdleTime;
    glPushMatrix();

    drawFlightArea();
    drawTerrestrialEnemies();
    drawFlightEnemies();
    drawAirportRunway();
    drawPlayerAirplane();

    glPopMatrix();
}

bool Game::checkFlightEnemiesCollision()
{
    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        if (playerAirplane.checkIntersection(flightArea.getArea(), flightEnemy_it->getBody(), deltaIdleTime))
        {
            return true;
        }
    }

    return false;
}

bool Game::isPlayerAirplaneInsideFlightArea(int moveDirection)
{
    return playerAirplane.isInside(flightArea.getArea(), moveDirection, deltaIdleTime);
}

// void Game::movePlayerAirplaneUp()
// {
//     if (checkFlightEnemiesCollision(MOVE_UP) == false && isPlayerAirplaneInsideFlightArea(MOVE_UP))
//     {
//         playerAirplane.moveUp(deltaIdleTime);
//     }
//     /*
//     else
//     {
//         if (isPlayerAirplaneInsideFlightArea(MOVE_DOWN))
//         {
//             playerAirplane.moveDown();
//         }
//     }
//     */
// }

// void Game::movePlayerAirplaneDown()
// {
//     if (checkFlightEnemiesCollision(MOVE_DOWN) == false && isPlayerAirplaneInsideFlightArea(MOVE_DOWN))
//     {
//         playerAirplane.moveDown(deltaIdleTime);
//     } /*
//     else
//     {
//         if (isPlayerAirplaneInsideFlightArea(MOVE_UP))
//         {
//             playerAirplane.moveUp();
//         }
//     }
//     */
// }

void Game::turnPlayerAirplaneLeft()
{
    // if (checkFlightEnemiesCollision(MOVE_LEFT) == false && isPlayerAirplaneInsideFlightArea(MOVE_LEFT))
    // {
    //     playerAirplane.turnLeft(deltaIdleTime);
    // }
    playerAirplane.setTurningLeft(true);

    /*
    else
    {
        if (isPlayerAirplaneInsideFlightArea(MOVE_RIGHT))
        {
            playerAirplane.moveRight();
        }
    }
    */
}

void Game::turnPlayerAirplaneRight()
{
    // if (checkFlightEnemiesCollision(MOVE_RIGHT) == false && isPlayerAirplaneInsideFlightArea(MOVE_RIGHT))
    // {
    //     playerAirplane.turnRight(deltaIdleTime);
    // }
    playerAirplane.setTurningRight(true);
    /*
    else
    {
        if (isPlayerAirplaneInsideFlightArea(MOVE_LEFT))
        {
            playerAirplane.moveLeft();
        }
    }
    */
}

void Game::stopPlayerAirplaneTurningLeft()
{
    playerAirplane.setTurningLeft(false);
}

void Game::stopPlayerAirplaneTurningRight()
{
    playerAirplane.setTurningRight(false);
}