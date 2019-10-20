#include "airportRunway.h"

void AirportRunway::setAdjustedBody(float coordinateCorrection_x, float coordinateCorrection_y)
{
    Point p1(-coordinateCorrection_x + this->getBody().getPoint1_x(), -coordinateCorrection_y + this->getBody().getPoint1_y());
    Point p2(-coordinateCorrection_x + this->getBody().getPoint2_x(), -coordinateCorrection_y + this->getBody().getPoint2_y());

    this->adjustedBody = Line(p1, p2);
}

void AirportRunway::draw()
{
    //drawer.drawLine(this->getBody());
    //drawer.drawLine(p1, p2, this->getAdjustedBody());
    drawer.drawLine(this->adjustedBody);
}