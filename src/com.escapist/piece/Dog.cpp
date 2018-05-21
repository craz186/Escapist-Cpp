//
// Created by Sean on 19/05/2018.
//

#include "Dog.h"

Dog::Dog(int x, int y) : Piece(x, y, PieceType::Dog){}

Dog::Dog(const Dog &another) : Piece((Piece &) another){}

list<Move> Dog::getMoves() {
    return _validMoves;
}

Dog* Dog::clone() {
    return new Dog(*this);
}
