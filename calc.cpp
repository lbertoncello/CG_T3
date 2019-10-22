#include "calc.h"

#include <cmath>

using namespace std;

//S=So+Vot+at2/2

float Calc::euclideanDistance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}

float Calc::norm(vector<float> v)
{
	float sum = 0;

	for (vector<float>::iterator it = v.begin(); it != v.end(); ++it)
	{
		sum += (*it * *it);
	}

	return sqrt(sum);
}

float Calc::euclideanDistance(Point point1, Point point2)
{
    return euclideanDistance(point1.getX(), point1.getY(), point2.getX(), point2.getY());
}

float Calc::calcAccelerationRequired(float initialPosition, float finalPosition, float initialSpeed, float time)
{
    return 2 * (finalPosition - initialPosition - initialSpeed * time) / (time * time);
}

float Calc::calcCurrentPositionVariation(float initialPosition, float acceleration, float initialSpeed, float time)
{
    return (initialSpeed * time + (acceleration * pow(time, 2)) / 2);
}

vector<float> Calc::calcAccelerationRequired(Point initialPosition, Point finalPosition, vector<float> initialSpeed, float time)
{
    vector<float> acceleration;

    float acceleration_x = calcAccelerationRequired(initialPosition.getX(), finalPosition.getX(), initialSpeed[0], time);
    float acceleration_y = calcAccelerationRequired(initialPosition.getY(), finalPosition.getY(), initialSpeed[1], time);

    acceleration.push_back(acceleration_x);
    acceleration.push_back(acceleration_y);

    return acceleration;
}

float Calc::calcTimeRequired(float initialSpeed, float finalSpeed, float acceleration)
{
    return (finalSpeed - initialSpeed) / acceleration;
}

Point Calc::calcCurrentPositionVariation(Point initialPosition, vector<float> acceleration, vector<float> initialSpeed, float time)
{
    Point currentPosition;

    float currentPosition_x = calcCurrentPositionVariation(initialPosition.getX(), acceleration[0], initialSpeed[0], time);
    float currentPosition_y = calcCurrentPositionVariation(initialPosition.getY(), acceleration[1], initialSpeed[1], time);

    currentPosition.setX(currentPosition_x);
    currentPosition.setY(currentPosition_y);

    return currentPosition;
}

float Calc::calcFinalSpeedRequired(float initialSpeed, float acceleration, float time)
{
    return initialSpeed + acceleration * time;
}

vector<float> Calc::calcFinalSpeedRequired(vector<float> initialSpeed, vector<float> acceleration, float time)
{
    vector<float> finalSpeed;

    finalSpeed.push_back(calcFinalSpeedRequired(initialSpeed[0], acceleration[0], time));
    finalSpeed.push_back(calcFinalSpeedRequired(initialSpeed[1], acceleration[1], time));

    return finalSpeed;
}

float Calc::calcInitialSpeedRequired(float finalSpeed, float acceleration, float initialPosition, float finalPosition)
{
    return sqrt(pow(finalSpeed, 2) - 2 * acceleration * (finalPosition - initialPosition));
}

float Calc::radiansToDegrees(float radians)
{
    return radians * (180.0 / 3.141592653589793238463);
}

vector<float> Calc::zerosVector(int numOfDimensions)
{
    vector<float> zeros;

    for (int i = 0; i < numOfDimensions; i++)
    {
        zeros.push_back(0);
    }

    return zeros;
}