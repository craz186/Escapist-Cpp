#include "Board.h"

Board::Board(Tile *tiles, list<Block*> blocks, Piece &userPiece, GoalTile &goal, AIManager &aiManager, int xLength,
             int yLength) {
    _tiles = tiles;
    _blocks = blocks;
    _userPiece = &userPiece;
    _goal = &goal;
    _aiManager = &aiManager;
    _xLength = xLength;
    _yLength = yLength;

};

Board::Board(Board &another) {
    _tiles = another._tiles;
    for (Block *block : another._blocks) {
        _blocks.push_back(block);
    }
    _userPiece = another._userPiece->clone();
    auto aiPieces = *new list<Piece*>();
    another._aiManager->getAiPieces(aiPieces);
    auto cloneAIPieces = *new list<Piece*>();
    for (Piece *piece: aiPieces) {
        cloneAIPieces.push_back(piece->clone());
    }
    _goal = another._goal;
    _aiManager = new AIManager(cloneAIPieces);
    _xLength = another._xLength;
    _yLength = another._yLength;
};

Board* Board::createBoardFromFile(string path) {
    ifstream boardFile;
    Tile *tiles = nullptr;
    GoalTile *goal = nullptr;
    list<Block*> blocks;
    Piece *userPiece = nullptr;
    list<Piece*> aiPieces;
    int xLength = 1;
    int yLength = Utils::getNumberOfLinesInFile(path);
    // read in each lines and parse into Tiles and Pieces

    boardFile.open(path);

    for(int y = 0; !boardFile.eof(); y++) {

        string line;
        getline(boardFile, line);
        // 'D' is for Dog
        // A 'U' infront of a letter will indicate that this is a users piece
        vector<string> characters = Utils::split(line, ',');
        if (tiles == nullptr) {
            tiles = new Tile[characters.size() * yLength];
        }

        xLength = characters.size();
        for (int x = 0; x < xLength; x++) {
            string character = characters[x];
            Tile *tile = new Tile(x, y);
            if (character == "0") {
                tile = new Obstacle(x, y);
            } else if (character == "2") {
                goal = new GoalTile(x, y);
                tile = goal;
            } else if (character.rfind('U',0) == 0) {
                userPiece = new Dog(x, y);
                userPiece->setUserPiece(true);
            } else if (character == "D") {
                aiPieces.push_back(new Dog(x, y));
            }
//            } else if (character == "B") {
//                blocks.Add(new PushBlock(x, y));
//            }
            tiles[(x * xLength) + y] = *tile;
        }
    }
    return new Board(tiles, blocks, *userPiece, *goal, *new AIManager(aiPieces), xLength, yLength);
};

void Board::print() {
    cout << "XLength: " << _xLength << ", YLength: " << _yLength << "\n";
    cout << "UserPiece: " << _userPiece->toString() << "\n";
    list<Piece*> aiPieces;
    (*_aiManager).getAiPieces(aiPieces);
    cout << "Size is: " << aiPieces.size() << "\n";
    if (aiPieces.empty()) cout << "Size 0, uh oh";
    else {
        for (Piece *aiPiece: aiPieces) {
            cout << "AIPiece :" << aiPiece->toString() << "\n";
        }
    }
    for(Block *block : _blocks) {
       cout << "Block :" << block->toString() << "\n";
    }

    //TODO validate that this is okay -- y < XLength ??????
    for(int y = 0; y < _xLength; y++) {
        for(int x = 0; x < _yLength; x++) {
            Tile tile = _tiles[x * _xLength + y];
            cout << tile.toString() << " ";
        }
        cout << "\n";
    }
};

void Board::makeAIMove() {
    _aiManager->moveAllAiPieces(*this, *_userPiece);
}
//
//    // We will cycle through all coordinates of the move and stop the move early if a piece is found
MoveResult Board::movePiece(Piece &piece, Move &move) {
    Move filteredMove = move;
    MoveResult moveResult = MoveResult::ValidMove;
    vector<Point> moveCoordinates = piece.getAllMoveCoordinatesForMove(move);
    for(int i = 0; i < moveCoordinates.size(); i++) {
        Point point = moveCoordinates.at(i);
        // validate move here for obstacles and blocks
        // TODO SG Maybe this should be a valid move but filter it to stop the move early.
        if (!isValidPosition(point.getX(), point.getY())) {
            return MoveResult::InvalidMove;
        }

        Block* blockToBeActioned = checkBlockExists(point.getX(), point.getY());
        if (blockToBeActioned != nullptr) {
//            if (blockToBeActioned->takeAction(*this, move)) {
//                filteredMove = *new Move(move.getDirection(), i + 1);
//                moveResult = MoveResult::BlockInteraction;
//                break;
//            } else {
                return MoveResult::InvalidMove;
//            }
        } else {
            Piece* pieceToBeTaken = checkPieceExists(point.getX(), point.getY());
            if (pieceToBeTaken == nullptr || *pieceToBeTaken==piece) {
                continue;
            }

            if (pieceToBeTaken->isUserPiece()) {
                // Game over...
                _userPiece = new Dog(-20, -20);
                _userPiece->setUserPiece(true);

                filteredMove = *new Move(move.getDirection(), i + 1);
                moveResult = MoveResult::UserPieceTaken;
                break;
            } else {
                // TODO need to check that the piece not getting taken is actually the User piece
                _aiManager->removePiece(*pieceToBeTaken);

                filteredMove = *new Move(move.getDirection(), i + 1);
                moveResult = MoveResult::AiPieceTaken;
                break;
            }
        }
    }
    piece.takeMove(filteredMove);
    return moveResult;
};

Block* Board::checkBlockExists(int x, int y) {
//    return new Block(0, 0);
    if (_blocks.empty()) {
        return nullptr;
    }

    for (Block *block : _blocks) {
        if (block->getX() == x && block->getY() == y) {
            return block;
        }
    }
};

//
//    // TODO Can add Tile checks in here later
bool Board::isValidPosition(int x, int y) {
    // need to check for obstacles
    return x > -1 && x < _xLength && y > -1 && y < _yLength && _tiles[x, y].doesAllowPiece();
};

Piece* Board::checkPieceExists(int x, int y) {
    if (_userPiece->getX() == x && _userPiece->getY() == y) {
        return _userPiece;
    }
    list<Piece*> pieces;
    _aiManager->getAiPieces(pieces);
    for (Piece *aiPiece: pieces) {
        if (aiPiece->getX() == x && aiPiece->getY() == y) {
            return aiPiece;
        }
    }
    return nullptr;
};

Piece* Board::getUserPiece() {
    return _userPiece;
};

list<Block*> Board::getBlocks() {
    return _blocks;
};

bool Board::isCoordVacant(int x, int y) {
    if (_userPiece->getX() == x && _userPiece->getY() == y) {
        return false;
    }
    list<Piece*> pieces;
    _aiManager->getAiPieces(pieces);
    for(Piece *piece:pieces) {
        if (piece->getX() == x && piece->getY() == y) {
            return false;
        }
    }
    return isValidPosition(x, y);
};

Board * Board::clone() {
    return new Board(*this);
};

Point Board::getGoal() {
    return *_goal;
};

Piece* Board::getPiece(int x, int y) {
    if (_userPiece->getX() == x && _userPiece->getY() == y) {
        return _userPiece;
    }

    list<Piece*> pieces;
    _aiManager->getAiPieces(pieces);
    for(Piece *piece: pieces) {
        if (piece->getX() == x && piece->getY() == y) {
            return piece;
        }
    }
};
//
//
