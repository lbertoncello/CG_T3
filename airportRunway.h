#ifndef AIRPORT_RUNWAY_H
#define AIRPORT_RUNWAY_H

#include "line.h"
#include "draw.h"

class AirportRunway
{
    Line body;
    Line adjustedBody;
    float scalarMiddle;
    Draw drawer;

public:
    AirportRunway() {}

    AirportRunway(Line body)
    {
        this->body = body;
    }

    Line &getBody()
    {
        return body;
    }

    float getScalarMiddle()
    {
        return scalarMiddle;
    }

    void setBody(Line body)
    {
        this->body = body;
    }

    void setScalarMiddle(float scalarMiddle)
    {
        this->scalarMiddle = scalarMiddle;
    }

    Line getAdjustedBody() {
        return this->adjustedBody;
    }
    
    void setAdjustedBody(float coordinateCorrection_x, float coordinateCorrection_y);

    void draw();
    float calcInclinationAngle();
};

#endif