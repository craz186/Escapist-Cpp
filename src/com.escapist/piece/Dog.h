//
// Created by Sean on 19/05/2018.
//

#ifndef ESCAPIST_DOG_H
#define ESCAPIST_DOG_H


#include <list>
#include "../Move.h"
#include "Piece.h"

class Dog : public Piece{
private:
    list<Move> _validMoves {
        Move(Direction::Up, 3),
        Move(Direction::Down, 3),
        Move(Direction::Left, 3),
        Move(Direction::Right, 3),
        Move(Direction::Up, 2),
        Move(Direction::Down, 2),
        Move(Direction::Left, 2),
        Move(Direction::Right, 2),
        Move(Direction::Up, 1),
        Move(Direction::Down, 1),
        Move(Direction::Left, 1),
        Move(Direction::Right, 1)
    };

public:
    Dog(int x, int y);

    Dog(const Dog &another);

    list<Move> getMoves() override;

    Dog * clone() override;
};


#endif //ESCAPIST_DOG_H
