//
// Created by Sean on 12/05/2018.
//

#ifndef ESCAPIST_BOARD_H
#define ESCAPIST_BOARD_H

#include <list>
#include "../piece/Dog.h"
#include "Tile.h"
#include "GoalTile.h"
#include "../piece/Piece.h"
#include "MoveResult.h"
#include "Block.h"
#include "../ai/AIManager.h"
#include "../Utils.h"
#include "Obstacle.h"
#include <fstream>

class Board {
    private:

        Tile *_tiles;
        GoalTile *_goal;
        list<Block> _blocks;
        Piece *_userPiece;
        AIManager *_aiManager;
        int _xLength = 0;
        int _yLength = 0;


    public:
        Board(Tile *tiles, list <Block> blocks, Piece &userPiece, GoalTile &goal, AIManager &aiManager, int xLength,
                             int yLength);

        Board(Board &another);

         void print();

        void makeAIMove();

        MoveResult movePiece(Piece &piece, Move &move);

        bool isValidPosition(int x, int y);

        Piece* checkPieceExists(int x, int y);

        Block* checkBlockExists(int x, int y);

        Piece* getUserPiece();

        list<Block> getBlocks();

        bool isCoordVacant(int x, int y);

        Board * clone();

        Point getGoal();

        Piece* getPiece(int x, int y);

        static Board * createBoardFromFile(string path);
};
#endif //ESCAPIST_BOARD_H
