//
// Created by Sean on 09/05/2018.
//

#ifndef ESCAPIST_TILE_H
#define ESCAPIST_TILE_H

#include <cstdlib>
#include <iostream>
#include "Point.h"

using namespace std;

//Class Point represents points in the Cartesian coordinate
class Tile : public Point {
protected:
    bool _isGoal; // coordinates of the point
    int _tileType;
    bool _allowsPiece;

public:
    Tile(int x = 0, int y = 0, bool allowsPiece = true, int tileType = 1, bool isGoal = false);

    bool doesAllowPiece();

    bool isGoal();

    string toString();
};
#endif //ESCAPIST_TILE_H
