#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string>

using namespace std;

class Color {
    private:
        float r = 0;
        float g = 0;
        float b = 0;

    public:
        Color() {}

        Color(float r, float g, float b) {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        Color(string colorName) {
            if(colorName == "red") {
                this->r = 1;
            } else if(colorName == string("green")) {
                this->g = 1;
            } else if(colorName == string("blue")) {
                this->b = 1;
            } else if(colorName == string("orange")) {
                this->r = 1;
                this->g = 0.65;
            }
        }

        float getR() {
            return r;
        }

        float getG() {
            return g;
        }

        float getB() {
            return b;
        }

        void setR(float r) {
            this->r = r;
        }        

        void setG(float g) {
            this->g = g;
        }

        void setB(float b) {
            this->b = b;
        }

};

#endif