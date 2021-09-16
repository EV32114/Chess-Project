#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "Piece.h"

#define MID_PAWN 198
#define END_PAWN 258
#define MID_KNIGHT 817
#define END_KNIGHT 846
#define MID_BISHOP 836
#define END_BISHOP 857
#define MID_ROOK 1270
#define END_ROOK 1281
#define MID_QUEEN 2521
#define END_QUEEN 2558

#define B_KING 'k'
#define W_KING 'K'
#define B_ROOK 'r'
#define W_ROOK 'R'
#define B_BISHOP 'b'
#define W_BISHOP 'B'
#define B_QUEEN 'q'
#define W_QUEEN 'Q'
#define B_PAWN 'p'
#define W_PAWN 'P'
#define B_KNIGHT 'n'
#define W_KNIGHT 'N'

#define MAX_VALID_MOVES 321

enum { KING, QUEEN, KNIGHT, ROOK, BISHOP, PAWN };

using std::string;
using std::cout;
using std::endl;

class Evaluate
{
public:
	static int evalPos(string pos);

private:
	static void countPieces(string pos, int* whitePieces, int* blackPieces);
	static void getValidMoves(Board& board);
};
 