//
// Created by Tim Mendenhall on 5/9/20.
//

#include "Cell.h"

Cell::Cell() {
    _isAlive = false;
}

bool Cell::isAlive() const {
    return _isAlive;
}

void Cell::setIsAlive(bool alive) {
    _isAlive = alive;
}
