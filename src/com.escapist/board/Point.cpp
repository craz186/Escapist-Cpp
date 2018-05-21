#include "Point.h"


using namespace std;

Point::Point(int x_coord, int y_coord){
    x = x_coord;
    y = y_coord;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

string Point::toString() {
    ostringstream oss;
    oss << "(" << getX() << "," << getY() << ")";
    return oss.str();
}
