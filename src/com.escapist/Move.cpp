//
// Created by Sean on 09/05/2018.
//

#include <sstream>
#include "Move.h"
#include "Direction.h"

Move::Move(Direction direction, int distance) {
    _direction = direction;
    _distance = distance;
}

int Move::getScore() {
    return _score;
}

void Move::setScore(int score) {
    _score = score;
}

Direction Move::getDirection() {
    return _direction;
}

int Move::getDistance() {
    return _distance;
}

Move Move::reverse() {
    int reverseDirectionInt = ((int) _direction + 2) % 4;
    Direction reverseDirection;
    switch (reverseDirectionInt) {
        case 0: {
            reverseDirection = Direction::Up;
            break;
        }
        case 1: {
            reverseDirection = Direction::Left;
            break;
        }
        case 2: {
            reverseDirection = Direction::Down;
            break;
        }
        case 3: {
            reverseDirection = Direction::Right;
            break;
        }
    }
    return *new Move(reverseDirection, _distance);;
}
