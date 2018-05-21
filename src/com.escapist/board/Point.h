//
// Created by Sean on 09/05/2018.
//
#ifndef ESCAPIST_POINT_H
#define ESCAPIST_POINT_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <list>
#include "../Move.h"
using namespace std;

//Class Point represents points in the Cartesian coordinate
class Point {
    protected:
        int x, y; // coordinates of the point

    public:
        Point(int, int);
        int getX() const;
        int getY() const;
        string toString();

};
#endif //ESCAPIST_POINT_H
