//
// Created by Sean on 10/05/2018.
//

#ifndef ESCAPIST_PIECE_H
#define ESCAPIST_PIECE_H


#include "../board/MovablePoint.h"
#include "PieceType.h"
#include <vector>

class Piece : public MovablePoint {
private:
    PieceType _pieceType;
    bool _isUserPiece;

public:
    Piece(int x, int y, PieceType pieceType);
    Piece(const Piece &another);
    bool isUserPiece();

    virtual list<Move> getMoves() = 0;
    virtual Piece* clone() = 0;
    std::vector<Point> getAllMoveCoordinatesForMove(Move &move);


    std::vector<Point> getAllPointsOnPath(Move move, int xModifier, int yModifier);

    string toString();

    PieceType getPieceType();

    bool operator==(const Piece &another);

    void setUserPiece(bool isUserPiece);
};

#endif //ESCAPIST_PIECE_H


