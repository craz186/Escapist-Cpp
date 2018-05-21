//
// Created by Sean on 09/05/2018.
//

#ifndef ESCAPIST_MOVE_H
#define ESCAPIST_MOVE_H

#include "Direction.h"

using namespace std;

class Move {
    private:
        int _distance;
        Direction _direction;
        int _score;

    public:
        Move(Direction direction, int distance);

        int getScore();

        void setScore(int score);

        Direction getDirection();

        int getDistance();

        Move reverse();
};


#endif //ESCAPIST_MOVE_H
