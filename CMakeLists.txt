cmake_minimum_required(VERSION 3.10)
project(escapist)

set(CMAKE_CXX_STANDARD 11)

add_library(escapist
        src/com.escapist/enum.h
        src/com.escapist/Direction.h
        src/com.escapist/piece/PieceType.h
        src/com.escapist/board/MoveResult.h

        src/com.escapist/board/Tile.cpp src/com.escapist/board/Tile.h
        src/com.escapist/board/Point.cpp src/com.escapist/board/Point.h
        src/com.escapist/board/MovablePoint.cpp src/com.escapist/board/MovablePoint.h
        src/com.escapist/Move.cpp src/com.escapist/Move.h
        src/com.escapist/piece/Piece.cpp src/com.escapist/piece/Piece.h
        src/com.escapist/board/Obstacle.cpp src/com.escapist/board/Obstacle.h
        src/com.escapist/board/GoalTile.cpp src/com.escapist/board/GoalTile.h
        src/com.escapist/board/Block.cpp src/com.escapist/board/Block.h
        src/com.escapist/board/Board.cpp src/com.escapist/board/Board.h
        src/com.escapist/ai/AIManager.cpp src/com.escapist/ai/AIManager.h
        src/com.escapist/Utils.h src/com.escapist/Utils.cpp
        src/com.escapist/piece/Dog.cpp src/com.escapist/piece/Dog.h
        src/com.escapist/input/UserInput.cpp src/com.escapist/input/UserInput.h
        )

add_executable(main src/com.escapist/Main.cpp)
target_link_libraries(main escapist)