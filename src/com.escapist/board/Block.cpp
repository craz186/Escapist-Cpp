//
// Created by Sean on 12/05/2018.
//

#include "Block.h"

Block::Block(int x, int y) : MovablePoint(x, y) {}

Block::Block(const Block &another) : MovablePoint(another.getX(), another.getY()){}

string Block::toString() {
    ostringstream oss;
    oss << "B(" << getX() << "," << getY() << ")";
    return oss.str();
}
