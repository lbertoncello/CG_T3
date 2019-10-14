#ifndef CALC_H
#define CALC_H

#include <vector>

#include "point.h"

using namespace std;

class Calc
{
public:
    Calc() {}

    float calcAccelerationRequired(float initialPosition, float finalPosition, float initialSpeed, float time);
    vector<float> calcAccelerationRequired(Point initialPosition, Point finalPosition, vector<float> initialSpeed, float time);
    float calcTimeRequired(float initialSpeed, float finalSpeed, float acceleration);
    float calcPositionRequired(float finalPosition, float acceleration, float time);
    float calcCurrentPositionVariation(float initialPosition, float acceleration, float initialSpeed, float time);
    Point calcCurrentPositionVariation(Point initialPosition, vector<float> acceleration, vector<float> initialSpeed, float time);
    float calcInitialSpeedRequired(float finalSpeed, float acceleration, float initialPosition, float finalPosition);
    float calcFinalSpeedRequired(float initialSpeed, float acceleration, float time);
    vector<float> calcFinalSpeedRequired(vector<float> initialSpeed, vector<float> acceleration, float time);
    float euclideanDistance(int x1, int y1, int x2, int y2);
    float euclideanDistance(Point point1, Point point2);
    float norm(vector<float> v);
    vector<float> zerosVector(int numOfDimensions);
};

#endif