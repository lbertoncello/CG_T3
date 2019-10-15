#include "gameRuntime.h"

bool* GameRuntime::keyStates = new bool[256];

void GameRuntime::keyOperations(void)
{
    if (keyStates['w'])
    { // If the 'a' key has been pressed
        if (game.isPlayerFlying())
        {
            game.movePlayerAirplaneUp();
        }
    }
    if (keyStates['a'])
    {
        if (game.isPlayerFlying())
        {
            game.movePlayerAirplaneLeft();
        }
    }
    if (keyStates['s'])
    {
        if (game.isPlayerFlying())
        {
            game.movePlayerAirplaneDown();
        }
    }
    if (keyStates['d'])
    {
        if (game.isPlayerFlying())
        {
            game.movePlayerAirplaneRight();
        }
    }
    if (keyStates['u'])
    {
        if (game.isPlayerFlying() == false && game.isPlayerTakingOff() == false)
        {
            game.takeOff();
        }
    }
}

void GameRuntime::keyPress(unsigned char key, int x, int y)
{
    if (key == 'w')
    {
        keyStates[key] = true;
    }
    if (key == 'a')
    {
        keyStates[key] = true;
    }
    if (key == 's')
    {
        keyStates[key] = true;
    }
    if (key == 'd')
    {
        keyStates[key] = true;
    }
    if (key == 'u')
    {
        keyStates[key] = true;
    }
}

void GameRuntime::keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = false; // Set the state of the current key to not pressed
}