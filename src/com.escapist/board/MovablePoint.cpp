//
// Created by Sean on 09/05/2018.
//

#include "MovablePoint.h"

MovablePoint::MovablePoint(int x, int y) : Point(x, y) {}

void MovablePoint::takeMove(Move &move) {
    Direction direction = move.getDirection();
    int distance = move.getDistance();

    switch (direction) {
        case Direction::Up:
            y -= distance;
            break;
        case Direction::Down:
            y += distance;
            break;
        case Direction::Right:
            x += distance;
            break;
        case Direction::Left:
            x -= distance;
            break;
    }

    _lastMove = &move;
}

Move* MovablePoint::getLastMove() {
    return _lastMove;
}