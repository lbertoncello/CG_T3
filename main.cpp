#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "game.h"
#include "tinyxml.h"

using namespace std;

const string config_base_filename = "/config.xml";
string arenaFilename;
float speedMult;

string window_title;
int window_size_x = 1000;
int window_size_y = 1000;
int window_initial_x_position = 100;
int window_initial_y_position = 100;

Color circleDefaultColor;
Color circleModelDefaultColor;
Color circleModelOverlapColor;
Color backgroundColor;

bool isLeftMouseButtonPressed = false;
bool isRightMouseButtonPressed = false;

GLfloat currentIdleTime;
GLfloat lastIdleTime;
GLfloat deltaIdleTime;

Game game;

bool *keyStates = new bool[256];

void keyOperations(void)
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

void keyPress(unsigned char key, int x, int y)
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

void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = false; // Set the state of the current key to not pressed
}

void arenaInit(TiXmlElement *application)
{
    TiXmlElement *arquivoArena = application->FirstChildElement("arquivoDaArena");
    string filename = arquivoArena->FirstChildElement("nome")->GetText();
    string format = arquivoArena->FirstChildElement("tipo")->GetText();
    string path = arquivoArena->FirstChildElement("caminho")->GetText();

    arenaFilename += path + "/" + filename + "." + format;
}

void jogadorInit(TiXmlElement *application)
{
    TiXmlElement *jogador = application->FirstChildElement("jogador");
    TiXmlAttribute *jogadorAttribute = jogador->FirstAttribute();

    while (jogadorAttribute)
    {
        if (strcmp(jogadorAttribute->Name(), "vel") == 0)
        {
            speedMult = stof(jogadorAttribute->Value());
        }

        jogadorAttribute = jogadorAttribute->Next();
    }
}

bool parametersInit(const char *filename)
{
    TiXmlDocument doc(filename);
    bool loadOkay = doc.LoadFile();

    if (loadOkay)
    {
        TiXmlElement *application = doc.RootElement();

        arenaInit(application);
        jogadorInit(application);

        return true;
    }
    else
    {
        cout << "Failed to load file" << endl;

        return false;
    }
}

void display(void)
{
    keyOperations();
    /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    game.drawGame(deltaIdleTime);

    /* Não esperar */
    //glFlush();
    glutSwapBuffers();
}

void idle(void)
{
    currentIdleTime = glutGet(GLUT_ELAPSED_TIME);
    deltaIdleTime = (currentIdleTime - lastIdleTime) / 1000;
    lastIdleTime = currentIdleTime;
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(backgroundColor.getR(), backgroundColor.getG(), backgroundColor.getB(), 0.0);

    /* Inicializa sistema de viz */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //    glOrtho(0, window_size_x, 0, window_size_y, -1, 1);
    //glOrtho(200, 800, 800, 200, -1, 1);
    game.getFlightArea().getArea().getCenter_x() - game.getFlightArea().getArea().getRadius();
    glOrtho(game.getFlightArea().getArea().getCenter_x() - game.getFlightArea().getArea().getRadius(),
            game.getFlightArea().getArea().getCenter_x() + game.getFlightArea().getArea().getRadius(),
            game.getFlightArea().getArea().getCenter_y() + game.getFlightArea().getArea().getRadius(),
            game.getFlightArea().getArea().getCenter_y() - game.getFlightArea().getArea().getRadius(),
            -1, 1);

    currentIdleTime = glutGet(GLUT_ELAPSED_TIME);
    lastIdleTime = glutGet(GLUT_ELAPSED_TIME);
}

void windowInit(float x_size, float y_size)
{
    window_size_x = x_size;
    window_size_y = y_size;
}

void readCircle(TiXmlElement *circle)
{
    TiXmlAttribute *circleAttribute = circle->FirstAttribute();
    Circle _circle;
    string color;

    while (circleAttribute)
    {
        if (strcmp(circleAttribute->Name(), "cx") == 0)
        {
            _circle.setCenter_x(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "cy") == 0)
        {
            _circle.setCenter_y(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "r") == 0)
        {
            _circle.setRadius(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "fill") == 0)
        {
            _circle.setColor(Color(circleAttribute->Value()));
            color = circleAttribute->Value();
        }
        else if (strcmp(circleAttribute->Name(), "id") == 0)
        {
            _circle.setId(stoi(circleAttribute->Value()));
        }

        circleAttribute = circleAttribute->Next();
    }

    if (color == string("blue"))
    {
        FlightArea flightArea(_circle);
        game.setFlightArea(flightArea);

        float diameter = 2 * _circle.getRadius();
        windowInit(diameter, diameter);
    }
    else if (color == string("green"))
    {
        PlayerAirplane playerAirplane(_circle);
        game.setPlayerAirplane(playerAirplane);
    }
    else if (color == string("red"))
    {
        FlightEnemy flightEnemy(_circle);
        game.addFlightEnemy(flightEnemy);
    }
    else if (color == string("orange"))
    {
        TerrestrialEnemy terrestrialEnemy(_circle);
        game.addTerrestrialEnemy(terrestrialEnemy);
    }
}

Color readSVGRGBColor(string style)
{
    string delimiter = ":";
    string rgb = style.substr(style.find(delimiter) + 5, 5);
    float r = stof(rgb.substr(0, 1)) / 255.0;
    float g = stof(rgb.substr(2, 1)) / 255.0;
    float b = stof(rgb.substr(4, 1)) / 255.0;

    return Color(r, g, b);
}

void readLine(TiXmlElement *line)
{
    TiXmlAttribute *lineAttribute = line->FirstAttribute();
    Line _line;

    while (lineAttribute)
    {
        if (strcmp(lineAttribute->Name(), "x1") == 0)
        {
            _line.setPoint1_x(stof(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "y1") == 0)
        {
            _line.setPoint1_y(stof(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "x2") == 0)
        {
            _line.setPoint2_x(stof(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "y2") == 0)
        {
            _line.setPoint2_y(stof(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "style") == 0)
        {
            _line.setColor(readSVGRGBColor(lineAttribute->Value()));
        }
        else if (strcmp(lineAttribute->Name(), "id") == 0)
        {
            _line.setId(stoi(lineAttribute->Value()));
        }

        lineAttribute = lineAttribute->Next();
    }

    AirportRunway airportRunway(_line);
    game.setAirportRunway(airportRunway);
}

bool readArenaFile()
{
    TiXmlDocument doc(arenaFilename.c_str());
    bool loadOkay = doc.LoadFile();

    if (loadOkay)
    {
        //TiXmlElement *arenaDescription = doc.RootElement();
        TiXmlNode *arenaDescription = doc.FirstChildElement("svg");

        TiXmlElement *element = arenaDescription->FirstChildElement();

        for (element; element; element = element->NextSiblingElement())
        {
            if (element->ValueTStr() == "circle")
            {
                readCircle(element);
            }
            else if (element->ValueTStr() == "line")
            {
                readLine(element);
            }
        }

        game.getPlayerAirplane().setSpeedMultiplier(speedMult);

        return true;
    }
    else
    {
        cout << "Failed to load file" << endl;

        return false;
    }
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        string filename = argv[1] + config_base_filename;
        arenaFilename = argv[1] + string("/");

        if (parametersInit(filename.c_str()))
        {
            if (readArenaFile())
            {
                glutInit(&argc, argv);
                glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
                glutInitWindowSize(window_size_x, window_size_y);
                glutInitWindowPosition(window_initial_x_position, window_initial_y_position);
                glutCreateWindow(window_title.c_str());
                init();
                glutDisplayFunc(display);

                glutKeyboardFunc(keyPress);
                glutKeyboardUpFunc(keyUp);

                glutIdleFunc(idle);
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