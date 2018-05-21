#include "Tile.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;


Tile::Tile(int x, int y, bool allowsPiece, int tileType, bool isGoal) : Point(x, y) {
    _allowsPiece = allowsPiece;
    _isGoal = isGoal;
    _tileType = tileType;
}

bool Tile::doesAllowPiece() {
    return _allowsPiece;
}

bool Tile::isGoal() {
    return _isGoal;
}

string Tile::toString() {
    ostringstream oss;
    oss << _tileType << "(" << x << "," << y << ")";
    return oss.str();
}