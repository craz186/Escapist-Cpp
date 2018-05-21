//
// Created by Sean on 19/05/2018.
//

#include "UserInput.h"

void UserInput::makeUserMove(Board &board) {

    string directionInput;
    string distance;
    cin >> directionInput >> distance;


    Direction direction;
    if (directionInput == "UP") {
        direction = Direction::Up;
    } else if (directionInput == "DOWN") {
        direction = Direction::Down;
    } else if (directionInput == "LEFT") {
        direction = Direction::Left;
    } else if (directionInput == "RIGHT") {
        direction = Direction::Right;
    }
    Move *move = new Move(direction, std::stoi(distance));
    board.movePiece(*board.getUserPiece(), *move);
}
