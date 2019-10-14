#ifndef POINT_H
#define POINT_H

class Point {
    private:
        float x = 0;
        float y = 0;
    public:
        Point(float x, float y) {
            this->x = x;
            this->y = y;
        }

        Point() {}

        float getX() {
            return x;
        }

        float getY() {
            return y;
        }

        void setX(float x) {
            this->x = x;
        }

        void setY(float y) {
            this->y = y;
        }
        
        void update(Point p) {
            this->x = p.getX();
            this->y = p.getY();
        }

        void update(float x, float y) {
            this->x = x;
            this->y = y;
        }
};

#endif