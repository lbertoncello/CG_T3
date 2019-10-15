#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include "gameSetup.h"

using namespace std;

const string CONFIG_BASE_FILENAME = "/config.xml";
GameSetup* gameSetup = new GameSetup();

void gameSetupDisplayFunctionWrapper(void) {
    gameSetup->display();
}

void gameSetupIdleFunctionWrapper(void) {
    gameSetup->idle();
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        string filename = argv[1] + CONFIG_BASE_FILENAME;
        string arenaFilename = argv[1] + string("/");

        if (gameSetup->initRuntimeParameters(filename, arenaFilename))
        {
            if (gameSetup->initArenaFile())
            {
                glutInit(&argc, argv);
                glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
                glutInitWindowSize(gameSetup->getGameRuntime().getWindowSize_x(), gameSetup->getGameRuntime().getWindowSize_y());
                glutInitWindowPosition(gameSetup->getGameRuntime().getWindowInitial_x_position(), gameSetup->getGameRuntime().getWindowInitial_y_position());
                glutCreateWindow(gameSetup->getGameRuntime().getWindowTitle().c_str());
                gameSetup->init();
                //glutDisplayFunc(gameSetup->display);
                glutDisplayFunc(gameSetupDisplayFunctionWrapper);

                glutKeyboardFunc(gameSetup->getGameRuntime().keyPress);
                glutKeyboardUpFunc(gameSetup->getGameRuntime().keyUp);

                glutIdleFunc(gameSetupIdleFunctionWrapper);
                glutMainLoop();

                return 0;
            }
            else
            {
                cout << "Erro ao carregar os dados da arena." << endl;

                return 1;
            }
        }
    }
    else
    {
        cout << "Voce deve passar como parametro o diretorio de arquivo config.xml" << endl;

        return 1;
    }
}