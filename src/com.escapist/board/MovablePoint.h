//
// Created by Sean on 09/05/2018.
//

#ifndef ESCAPIST_MOVABLEPOINT_H
#define ESCAPIST_MOVABLEPOINT_H

#include "Point.h"
#include "../Move.h"
#include "../Direction.h"

class MovablePoint : public Point{
    private:
         Move *_lastMove = new Move(Direction::Up, 0);

public:
        MovablePoint(int x, int y);

        Move* getLastMove();

        void takeMove(Move&);

        using Point::getX;

        using Point::getY;

};


#endif //ESCAPIST_MOVABLEPOINT_H
