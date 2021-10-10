#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "Piece.h"
#include <vector>

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
#define OPEN_FILE_PENALTY 50

enum { KING, QUEEN, KNIGHT, ROOK, BISHOP, PAWN };

using std::string;
using std::cout;
using std::endl;

class Evaluate
{
public:
	static int evalPos(string pos);

private:
	static constexpr short pawnTable[8][8] =  { 0,  0,  0,  0,  0,  0,  0,  0,
												50, 50, 50, 50, 50, 50, 50, 50,
												10, 10, 20, 30, 30, 20, 10, 10,
												 5,  5, 10, 27, 27, 10,  5,  5,
												 0,  0,  0, 25, 25,  0,  0,  0,
												 5, -5,-10,  0,  0,-10, -5,  5,
												 5, 10, 10,-25,-25, 10, 10,  5,
												 0,  0,  0,  0,  0,  0,  0,  0 };
	
	static constexpr short knightTable[8][8] = {-50,-40,-30,-30,-30,-30,-40,-50,
												-40,-20,  0,  0,  0,  0,-20,-40,
												-30,  0, 10, 15, 15, 10,  0,-30,
												-30,  5, 15, 20, 20, 15,  5,-30,
												-30,  0, 15, 20, 20, 15,  0,-30,
												-30,  5, 10, 15, 15, 10,  5,-30,
												-40,-20,  0,  5,  5,  0,-20,-40,
												-50,-40,-20,-30,-30,-20,-40,-50 };

	static constexpr short bishopTable[8][8] = {-20,-10,-10,-10,-10,-10,-10,-20,
												-10,  0,  0,  0,  0,  0,  0,-10,
												-10,  0,  5, 10, 10,  5,  0,-10,
												-10,  5,  5, 10, 10,  5,  5,-10,
												-10,  0, 10, 10, 10, 10,  0,-10,
												-10, 10, 10, 10, 10, 10, 10,-10,
												-10,  5,  0,  0,  0,  0,  5,-10,
												-20,-10,-40,-10,-10,-40,-10,-20 };

	static constexpr short kingTable[8][8] = {-30, -40, -40, -50, -50, -40, -40, -30,
											  -30, -40, -40, -50, -50, -40, -40, -30,
											  -30, -40, -40, -50, -50, -40, -40, -30,
											  -30, -40, -40, -50, -50, -40, -40, -30,
											  -20, -30, -30, -40, -40, -30, -30, -20,
											  -10, -20, -20, -20, -20, -20, -20, -10,
											   20,  20,   0,   0,   0,   0,  20,  20,
											   20,  30,  10,   0,   0,  10,  30,  20 };

	static constexpr short kingTableEndGame[8][8] = {-50,-40,-30,-20,-20,-30,-40,-50,
													-30,-20,-10,  0,  0,-10,-20,-30,
													-30,-10, 20, 30, 30, 20,-10,-30,
													-30,-10, 30, 40, 40, 30,-10,-30,
													-30,-10, 30, 40, 40, 30,-10,-30,
													-30,-10, 20, 30, 30, 20,-10,-30,
													-30,-30,  0,  0,  0,  0,-30,-30,
													-50,-30,-30,-30,-30,-30,-30,-50 };


	static std::vector<std::string> blackMoves;
	static std::vector<std::string> whiteMoves;
	static void countPieces(string pos, int* whitePieces, int* blackPieces);
	static void getValidMoves(Board& board);
	static int evaluatePiecesWhite(int* whitePieces, bool midGame);
	static int evaluatePiecesBlack(int* blackPieces, bool midGame);
	static int evaluateKingSafety(Board& board);
	static int evaluatePawnShield(int src[], Board& board);
	static std::vector<Piece*> calcKingZone(Board& board, int src[], bool white);
};
 