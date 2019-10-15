#include "gameSetup.h"

void GameSetup::display(void)
{
    gameRuntime.keyOperations();
    /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    gameRuntime.getGame().drawGame(deltaIdleTime);

    /* Não esperar */
    //glFlush();
    glutSwapBuffers();
}

void GameSetup::idle(void)
{
    currentIdleTime = glutGet(GLUT_ELAPSED_TIME);
    deltaIdleTime = (currentIdleTime - lastIdleTime) / 1000;
    lastIdleTime = currentIdleTime;
    glutPostRedisplay();
}

void GameSetup::init(void)
{
    glClearColor(gameRuntime.getBackgroundColor().getR(), gameRuntime.getBackgroundColor().getG(), gameRuntime.getBackgroundColor().getB(), 0.0);

    /* Inicializa sistema de viz */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    cout << gameRuntime.getGame().getFlightArea().getArea().getRadius() << endl;

    //    glOrtho(0, window_size_x, 0, window_size_y, -1, 1);
    //glOrtho(200, 800, 800, 200, -1, 1);
    gameRuntime.getGame().getFlightArea().getArea().getCenter_x() - gameRuntime.getGame().getFlightArea().getArea().getRadius();
    glOrtho(gameRuntime.getGame().getFlightArea().getArea().getCenter_x() - gameRuntime.getGame().getFlightArea().getArea().getRadius(),
            gameRuntime.getGame().getFlightArea().getArea().getCenter_x() + gameRuntime.getGame().getFlightArea().getArea().getRadius(),
            gameRuntime.getGame().getFlightArea().getArea().getCenter_y() + gameRuntime.getGame().getFlightArea().getArea().getRadius(),
            gameRuntime.getGame().getFlightArea().getArea().getCenter_y() - gameRuntime.getGame().getFlightArea().getArea().getRadius(),
            -1, 1);

    currentIdleTime = glutGet(GLUT_ELAPSED_TIME);
    lastIdleTime = glutGet(GLUT_ELAPSED_TIME);
}

bool GameSetup::initRuntimeParameters(string filename, string arenaFilename)
{
    this->parametersReading.setGameRuntime(&this->gameRuntime);
    this->parametersReading.setArenaFilename(arenaFilename);

    return parametersReading.parametersInit(filename.c_str());
}

bool GameSetup::initArenaFile() {
    return this->parametersReading.readArenaFile();
}
