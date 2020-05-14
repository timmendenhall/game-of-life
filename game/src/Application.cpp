//
// Created by Tim Mendenhall on 5/8/20.
//

#include "Application.h"

Application::Application() {}

Application::~Application() {}

void Application::initializeCells() {
    dream::log("Initializing cells...");

    std::mt19937 mt(_seed);
    std::uniform_int_distribution<unsigned int> dist(1, 100);

    for (int y = 0; y < Application::HEIGHT_IN_PIXELS; ++y) {
        for (int x = 0; x < Application::WIDTH_IN_PIXELS; ++x) {
            bool isAlive = dist(mt) % 2 == 0;

            // next gets moved to active, so we'll just default active as false and set the next
            _activeCells[y][x].setIsAlive(false);
            _nextCells[y][x].setIsAlive(isAlive);
        }
    }
}

void Application::initialize(unsigned int width, unsigned int height, const std::string& title, unsigned int seed) {
    _sleepTime = 30;

    // create the window
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
    _window->setVerticalSyncEnabled(true);

    // threading
    _renderThread = std::make_unique<sf::Thread>(&Application::draw, this);

    _isPaused = false;

    initializeSeed(seed);
    initializeCells();
}

void Application::start() {
    // deactivate its OpenGL context
    _window->setActive(false);

    _renderThread->launch();

    // run the program as long as the window is open
    while (_window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    _window->close();
                    break;
                case sf::Event::KeyPressed:
                    handleKeypressed(event);
                    break;
                default:
                    break;
            }
        }

        if (!_isPaused) {
            update();
        }
    }
    _renderThread->terminate();
}

void Application::update() {
    // Slow the updates
    sf::sleep(sf::milliseconds(_sleepTime));

    // move next cells into current
    for (int y = 0; y < Application::HEIGHT_IN_PIXELS; ++y) {
        for (int x = 0; x < Application::WIDTH_IN_PIXELS; ++x) {
            _activeCells[y][x].setIsAlive(_nextCells[y][x].isAlive());
        }
    }

    // Determine next generation
    unsigned int activeCellAliveNeighborCount = 0;
    bool activeCellIsAlive = false;

    // For each current cell
    for (int y = 0; y < Application::HEIGHT_IN_PIXELS; ++y) {
        for (int x = 0; x < Application::WIDTH_IN_PIXELS; ++x) {

            activeCellAliveNeighborCount = getAliveNeighborsCount(x, y);
            activeCellIsAlive = _activeCells[y][x].isAlive();

            // lonely -- dies
            if (activeCellIsAlive && activeCellAliveNeighborCount < 2) {

                _nextCells[y][x].setIsAlive(false);
            }
            // lives - survives this generation
            else if (activeCellIsAlive && (activeCellAliveNeighborCount == 2 || activeCellAliveNeighborCount == 3)) {
                _nextCells[y][x].setIsAlive(true);
            }
            // dies - over population
            else if (activeCellIsAlive && activeCellAliveNeighborCount > 3) {
                _nextCells[y][x].setIsAlive(false);
            }
            // new born -- reproduction
            else if (!activeCellIsAlive && activeCellAliveNeighborCount == 3) {
                _nextCells[y][x].setIsAlive(true);
            }
        }
    }
}

void Application::draw() {
    // activate the window's context
    _window->setActive(true);

    while (_window->isOpen()) {
        // clear the window with black color
        _window->clear(sf::Color::Black);

        // A "Pixel" for the game
        sf::RectangleShape rectangle(sf::Vector2f((float)Application::PIXEL_SIZE, (float)Application::PIXEL_SIZE));

        for (int y = 0; y < Application::HEIGHT_IN_PIXELS; ++y) {
            for (int x = 0; x < Application::WIDTH_IN_PIXELS; ++x) {

                if (_activeCells[y][x].isAlive()) {
                    rectangle.setPosition(
                            (float)(x * Application::PIXEL_SIZE),
                            (float)(y * Application::PIXEL_SIZE)
                    );

                    _window->draw(rectangle);
                }
            }
        }

        // end the current frame
        _window->display();
    }
}

unsigned int Application::getAliveNeighborsCount(unsigned int x, unsigned int y) {
    // finding number of neighbors that are alive
    int aliveNeighbors = 0;
    int checkingX, checkingY;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
           checkingX = x + j;
           checkingY = y + i;

           // Wrapping the X and Y planes (going too far left would put you furthest right for example)
           if (checkingX < 0) {
               checkingX = Application::WIDTH_IN_PIXELS - 1;
           } else if (checkingX >= Application::WIDTH_IN_PIXELS) {
               checkingX = 0;
           }

            if (checkingY < 0) {
                checkingY = Application::HEIGHT_IN_PIXELS - 1;
            } else if (checkingY >= Application::HEIGHT_IN_PIXELS) {
                checkingY = 0;
            }

           if (_activeCells[checkingY][checkingX].isAlive()) {
               aliveNeighbors++;
           }
        }
    }

    // Don't count the active cell we're checking the neighbors of
    if (_activeCells[y][x].isAlive()) {
        aliveNeighbors--;
    }

    return aliveNeighbors;
}

void Application::handleKeypressed(sf::Event &event) {
    switch (event.key.code) {
        case sf::Keyboard::Space:
            _isPaused = !_isPaused;
            break;
        case sf::Keyboard::R:
            restart(true);
            break;
        case sf::Keyboard::F:
            restart(false);
            break;
        case sf::Keyboard::W:
            if (_sleepTime >= 10) {
                _sleepTime -= 10;
            }
            break;
        case sf::Keyboard::S:
            if (_sleepTime <= 190) {
                _sleepTime += 10;
            }
            break;
        case sf::Keyboard::Escape:
            _window->close();
            break;
        default:
            break;
    }
}

void Application::initializeSeed(unsigned int seed) {
    // initialize random seed if it's not set
    if (seed == 0) {
        dream::log("Generating random seed");
        std::random_device rd;
        _seed = rd();
    } else {
        dream::log("Using set seed");
        _seed = seed;
    }

    dream::log("Seed: " + std::to_string(_seed));
}

void Application::restart(bool newSeed) {
    unsigned int seed = newSeed ? 0 : _seed;
    initializeSeed(seed);
    initializeCells();
}
