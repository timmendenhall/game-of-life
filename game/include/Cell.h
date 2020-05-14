//
// Created by Tim Mendenhall on 5/9/20.
//

#ifndef SFMLTEST_CELL_H
#define SFMLTEST_CELL_H

class Cell {
public:
    Cell();
    bool isAlive() const;
    void setIsAlive(bool alive);

private:
    bool _isAlive;
};

#endif //SFMLTEST_CELL_H
