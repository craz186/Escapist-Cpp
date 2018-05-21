//
// Created by Sean on 12/05/2018.
//

#ifndef ESCAPIST_AIMANAGER_H
#define ESCAPIST_AIMANAGER_H

#include "../piece/Piece.h"
#include <list>
#include <cmath>
class Board;
class AIManager {
private:
    std::list<Piece> _aiPieces;
    const int MaxSearchDepth = 4;

    Move miniMax(Board &board, Piece &currentPiece, Piece &opponentPiece, int currentDepth);

    void printDepthTabs(int currentDepth);

    int scoreMove(Piece &currentPiece, Point beforePoint, Point afterPoint, Move move, Board board);

    static int calculateDistanceBetweenTwoPoints(Point first, Point second);

public:
    AIManager(list<Piece> aiPieces);

    void moveAllAiPieces(Board &board, Piece &opponent);

    list<Piece> getAiPieces();

    void removePiece(Piece &pieceToBeTaken);

};


#endif //ESCAPIST_AIMANAGER_H
