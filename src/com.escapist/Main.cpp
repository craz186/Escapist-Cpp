//
// Created by Sean on 12/05/2018.
//

#include "board/Board.h"
#include "input/UserInput.h"

int main()
{
    Board *board = Board::createBoardFromFile(R"(C:\Users\Sean\Documents\Chessmate v2\Assets\Levels\TestLevel.txt)");
    int i = 0;
    while (i < 10) {
        board->print();
        UserInput::makeUserMove(*board);
        board->print();
        board->makeAIMove();
        i++;
    }
}