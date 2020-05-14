// Created by Tim Mendenhall on 5/8/20.
//

#ifndef SFMLTEST_APPLICATION_H
#define SFMLTEST_APPLICATION_H

#include <string>
#include <random>
#include <memory>
#include <dream/Log.h>
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Application {
public:
    Application();
    ~Application();
    void initialize(unsigned int width, unsigned int height, const std::string& title, unsigned int seed = 0);
    void start();

    static const unsigned int PIXEL_SIZE = 5;
    static const unsigned int WIDTH_IN_PIXELS = 160;
    static const unsigned int HEIGHT_IN_PIXELS = 120;

private:
    std::unique_ptr<sf::RenderWindow> _window;
    unsigned int _sleepTime;

    // Threading
    std::unique_ptr<sf::Thread> _renderThread;

    // app state
    unsigned int _seed;
    bool _isPaused;
    Cell _activeCells[Application::HEIGHT_IN_PIXELS][Application::WIDTH_IN_PIXELS];
    Cell _nextCells[Application::HEIGHT_IN_PIXELS][Application::WIDTH_IN_PIXELS];

    void restart(bool newSeed = false);
    void initializeSeed(unsigned int seed = 0);
    void initializeCells();
    void update();
    void draw();
    void handleKeypressed(sf::Event &event);

    unsigned int getAliveNeighborsCount(unsigned int x, unsigned int y);
};

#endif //SFMLTEST_APPLICATION_H
