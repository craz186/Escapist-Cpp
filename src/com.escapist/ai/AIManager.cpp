//
// Created by Sean on 12/05/2018.
//

#include "AIManager.h"
#include "../board/Board.h"

AIManager::AIManager(list<Piece> aiPieces) {
    _aiPieces = aiPieces;
};

void AIManager::moveAllAiPieces(Board &board, Piece &opponent) {
    for(Piece &aiPiece: _aiPieces) {
        // needs to recursively call the next part in a function
        cout << "Start Minimax\n";
        Move bestAvailableMove = miniMax(board, aiPiece, opponent, 1);
        board.movePiece(aiPiece, bestAvailableMove);
    }
};

Move AIManager::miniMax(Board &board, Piece &currentPiece, Piece &opponentPiece, int currentDepth) {
    Move* bestMove = nullptr;
    for (Move &move: currentPiece.getMoves()) {
        Board *copyBoard = board.clone();
        Piece *copyCurrentPiece = copyBoard->getPiece(currentPiece.getX(), currentPiece.getY());
        Point previousLocation = *new Point(copyCurrentPiece->getX(), copyCurrentPiece->getY());
        MoveResult moveResult = copyBoard->movePiece(*copyCurrentPiece, move);
        Point afterLocation = *new Point(copyCurrentPiece->getX(), copyCurrentPiece->getY());
        int currentScore = copyCurrentPiece->isUserPiece() ? 100000 : -100000;
        switch (moveResult) {
            case MoveResult::InvalidMove:
                continue;
                // This case can only be triggered by an AI
                //TODO A user piece seems to be choosing the highest score rather than lowest

            case MoveResult::UserPieceTaken:
                move.setScore(-currentScore);
                bestMove = &move;
                printDepthTabs(currentDepth);
                cout << "UserPieceTaken Depth: " << currentDepth << ", IsUser?" << copyCurrentPiece->isUserPiece() << ", "
                     << previousLocation.toString() << " -> " << afterLocation.toString() << ", Score:" << -currentScore << ", Opponent: " << opponentPiece.toString();
                continue;
                // This case could be triggered by an AI
            case MoveResult::AiPieceTaken:
                if (currentPiece.isUserPiece()) {
                    move.setScore(-currentScore / 10);
                    bestMove = &move;
                    printDepthTabs(currentDepth);
                    cout << "AIPieceTaken Depth: " << currentDepth << ", IsUser? true, " << previousLocation.toString() << " -> " << afterLocation.toString() << ", Score:" << -currentScore << ", Opponent: " << opponentPiece.toString();
                }
                continue;
            case MoveResult::BlockInteraction: {
                if (!currentPiece.isUserPiece()) {
                    continue;
                }
                break;
            }
            case MoveResult::ValidMove:
                break;
        }

        if (currentDepth < MaxSearchDepth) {
            // If we have not reached our MaxSearchDepth then keep branching
            Move currentMove= miniMax(*copyBoard, opponentPiece, *copyCurrentPiece, currentDepth + 1);
            if (&currentMove != nullptr) {
                currentScore = currentMove.getScore();
            }
        } else {
            // We only want to evaluate leaf nodes
            currentScore = scoreMove(*copyCurrentPiece, previousLocation, afterLocation, *currentPiece.getLastMove(), *copyBoard);
        }
        printDepthTabs(currentDepth);
        cout << "Depth: " << currentDepth << ", IsUser? " << copyCurrentPiece->isUserPiece() << ", " << previousLocation.toString() << " -> " << afterLocation.toString() << ", Score:" << currentScore << ", Opponent: " << opponentPiece.toString();

        if (bestMove == nullptr || (copyCurrentPiece->isUserPiece() ? currentScore < bestMove->getScore() : currentScore > bestMove->getScore())) {
            move.setScore(currentScore);
            bestMove = &move;
            printDepthTabs(currentDepth);
            cout << "New Best Move - Depth: " << currentDepth + ", IsUser? " << currentPiece.isUserPiece() << ", Destination:" <<
                 currentPiece.getAllMoveCoordinatesForMove(*bestMove)[bestMove->getDistance()-1].toString() + ", Score:" << bestMove->getScore() << ", Opponent: " << opponentPiece.toString();
        }
    }
    printDepthTabs(currentDepth);
    cout << "The Best Move - Depth: " << currentDepth << ", IsUser? " << currentPiece.isUserPiece() << ", " << currentPiece.toString()
           << " -> " << currentPiece.getAllMoveCoordinatesForMove(*bestMove)[bestMove->getDistance()-1].toString() << ", Score:" << bestMove->getScore() << ", Opponent: " << opponentPiece.toString();
    return *bestMove;
};

void AIManager::printDepthTabs(int currentDepth) {
    for (int i = 0; i < currentDepth; i++) {
        cout << "\t";
    }
};

int AIManager::scoreMove(Piece &currentPiece, Point beforePoint, Point afterPoint, Move move, Board board) {

    // calculate distance from before point to opponent
    // calculate distance from after point to opponent
    // score is negative for further away and positive for closer.
    // score is best if distance is 0.
    Point target = *board.getUserPiece();

    if (currentPiece.isUserPiece()) {
        target = board.getGoal();
    }

    int beforeDistance = calculateDistanceBetweenTwoPoints(beforePoint, target); // 8
    int afterDistance = calculateDistanceBetweenTwoPoints(afterPoint, target); // 2
    int score = beforeDistance - afterDistance;

    if (currentPiece.getLastMove() != nullptr &&
        currentPiece.getLastMove()->reverse().getDirection() == move.getDirection()) {
        score -= 50;
    }

    if (currentPiece.isUserPiece()) {
        return -score;
    }

    return score;
};

int AIManager::calculateDistanceBetweenTwoPoints(Point first, Point second) {
    return (int) (pow(second.getX() - first.getX(), 2) + pow(second.getY() - first.getY(), 2));
};

list<Piece> AIManager::getAiPieces() {
    return _aiPieces;
};

void AIManager::removePiece(Piece &pieceToBeTaken) {
    _aiPieces.remove(pieceToBeTaken);
};