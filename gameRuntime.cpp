#include "gameRuntime.h"

bool *GameRuntime::keyStates = new bool[256];

void GameRuntime::keyOperations(void)
{
    if (!game.isGameOver())
    {
        if (keyStates['a'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayerAirplane().setTurningLeft(true);
            }
        }
        else
        {
            game.getPlayerAirplane().setTurningLeft(false);
        }

        if (keyStates['d'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayerAirplane().setTurningRight(true);
            }
        }
        else
        {
            game.getPlayerAirplane().setTurningRight(false);
        }
        if (keyStates['u'])
        {
            if (game.isPlayerFlying() == false && game.isPlayerTakingOff() == false)
            {
                game.takeOff();
            }
        }
        if (keyStates['+'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayerAirplane().incrementSpeed();
            }
        }
        if (keyStates['-'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayerAirplane().decrementSpeed();
            }
        }
    }

    if (keyStates['r'])
    {
        game.reset();
    }
}

void GameRuntime::keyPress(unsigned char key, int x, int y)
{
    if (key == 'a')
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
    if (key == 'r')
    {
        keyStates[key] = true;
    }
    if (key == '+')
    {
        keyStates[key] = true;
    }
    if (key == '-')
    {
        keyStates[key] = true;
    }
}

void GameRuntime::keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = false; // Set the state of the current key to not pressed
}

void GameRuntime::mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
        }
        else
        {
            game.shoot();
        }
    }

    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_UP)
        {
        }
        else
        {
        }
    }
}

void GameRuntime::motion(int x, int y)
{
    if (!game.isGameOver())
    {
        if (game.isPlayerFlying())
        {
            game.rotatePlayerAirplaneCannon(x - previousX);
            previousX = x;
        }
    }

    if (isLeftMouseButtonPressed)
    {
    }

    if (isRightMouseButtonPressed)
    {
    }
}

void GameRuntime::passiveMotion(int x, int y)
{
    if (!game.isGameOver())
    {
        if (game.isPlayerFlying())
        {
            game.rotatePlayerAirplaneCannon(x - previousX);
            previousX = x;
        }
    }
}
