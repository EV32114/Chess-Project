cmake_minimum_required(VERSION 3.20)
project(chess_ai)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(chess_ai
        Bishop.cpp
        Bishop.h
        Board.cpp
        Board.h
        EmptySquare.cpp
        EmptySquare.h
        Evaluate.cpp
        Evaluate.h
        King.cpp
        King.h
        Knight.cpp
        Knight.h
        main.cpp
        Pawn.cpp
        Pawn.h
        Piece.cpp
        Piece.h
        Queen.cpp
        Queen.h
        Rook.cpp
        Rook.h)
