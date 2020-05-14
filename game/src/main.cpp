#include "Application.h"

int main()
{
    Application app;
    // Random seed
    app.initialize(800, 600, "Game of Life");

    // Pre-set seed
//    app.initialize(800, 600, "Game of Life", 810686421);

    app.start();

    return 0;
}