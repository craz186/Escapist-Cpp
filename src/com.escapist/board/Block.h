//
// Created by Sean on 12/05/2018.
//

#ifndef ESCAPIST_BLOCK_H
#define ESCAPIST_BLOCK_H

#include "MovablePoint.h"
#include <sstream>

class Block: public MovablePoint {
    public:
        Block(int x, int y);
        Block(const Block &another);

        virtual Block* clone() = 0;

//        virtual bool takeAction(Board &board, Move userMove);

        string toString();
};


#endif //ESCAPIST_BLOCK_H
