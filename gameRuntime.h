#ifndef GAME_RUNTIME_H
#define GAME_RUNTIME_H

#include <string>

#include "color.h"
#include "game.h"

using namespace std;

class GameRuntime
{
private:
    float playerAirplaneSpeedMult;
    float bulletSpeedMult;

    string windowTitle;
    int windowSize_x = 1000;
    int windowSize_y = 1000;
    int windowInitial_x_position = 100;
    int windowInitial_y_position = 100;

    Color backgroundColor;

    bool isLeftMouseButtonPressed = false;
    bool isRightMouseButtonPressed = false;

    Game game;

    static bool *keyStates;

public:
    GameRuntime() {}

    Game& getGame() {
        return this->game;
    }

    Color& getBackgroundColor() {
        return this->backgroundColor;
    }

    float getPlayerAirplaneSpeedMult() {
        return this->playerAirplaneSpeedMult;
    }

    float getBulletSpeedMult() {
        return this->bulletSpeedMult;
    }

    string getWindowTitle() {
        return this->windowTitle;
    }

    int getWindowSize_x() {
        return this->windowSize_x;
    }

    int getWindowSize_y() {
        return this->windowSize_y;
    }

    int getWindowInitial_x_position() {
        return this->windowInitial_x_position;
    }

    int getWindowInitial_y_position() {
        return this->windowInitial_y_position;
    }

    void setPlayerAirplaneSpeedMult(float playerAirplaneSpeedMult) {
        this->playerAirplaneSpeedMult = playerAirplaneSpeedMult;
    }

    void setBulletSpeedMult(float bulletSpeedMult) {
        this->bulletSpeedMult = bulletSpeedMult;
    }

    void setWindowTitle(string windowTitle) {
        this->windowTitle = windowTitle;
    }

    void setWindowsSize_x(int windowSize_x ) {
        this->windowSize_x = windowSize_x;
    }

    void setWindowsSize_y(int windowSize_y ) {
        this->windowSize_y = windowSize_y;
    }

    void setBackgroundColor(Color backgroundColor) {
        this->backgroundColor = backgroundColor;
    }

    void keyOperations(void);
    static void keyPress(unsigned char key, int x, int y);
    static void keyUp(unsigned char key, int x, int y);
};

#endif