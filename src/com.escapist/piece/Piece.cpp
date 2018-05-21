//
// Created by Sean on 10/05/2018.
//

#include <list>
#include <sstream>
#include <vector>
#include "Piece.h"

Piece::Piece(int x, int y, PieceType pieceType) : MovablePoint(x, y) {
    _pieceType = pieceType;
}
bool Piece::isUserPiece() {
    return _isUserPiece;
}

void Piece::setUserPiece(bool isUserPiece) {
    _isUserPiece = isUserPiece;
}

Piece::Piece(const Piece &another) : MovablePoint(another.getX(), another.getY()){
    _pieceType = another._pieceType;
    _isUserPiece = another._isUserPiece;
}


vector<Point> Piece::getAllMoveCoordinatesForMove(Move &move) {
    vector<Point> returnPoints;
    switch (move.getDirection()) {
        case Direction::Up:
            returnPoints = getAllPointsOnPath(move, 0, -1);
            break;
        case Direction::Down:
            returnPoints = getAllPointsOnPath(move, 0, 1);
            break;
        case Direction::Left:
            returnPoints = getAllPointsOnPath(move, -1, 0);
            break;
        case Direction::Right:
            returnPoints = getAllPointsOnPath(move, 1, 0);
            break;
}

return returnPoints;
}

vector<Point> Piece::getAllPointsOnPath(Move move, int xModifier, int yModifier) {
    vector<Point> returnPoints;
    int tempX = getX();
    int tempY = getY();
    for (int i = 0; i < move.getDistance(); i++) {
        tempX += xModifier;
        tempY += yModifier;
        returnPoints.emplace_back(tempX, tempY);
    }
    return returnPoints;
}

string Piece::toString() {
    ostringstream oss;
    oss << "(" << getX() << "," << getY() << ")";
    return oss.str();
}

PieceType Piece::getPieceType() {
    return _pieceType;
}

bool Piece::operator==(const Piece &another) {
    return (_pieceType == another._pieceType &&
        _isUserPiece == another._isUserPiece &&
        getX() == another.getX() &&
        getY() == another.getY());
}
