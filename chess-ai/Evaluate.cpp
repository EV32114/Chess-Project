#include "Evaluate.h"

int Evaluate::evalPos(string pos)
{
	int blackPieceCounter[6] = {0};
	int whitePieceCounter[6] = { 0 };
	int blackValid[MAX_VALID_MOVES] = { 0 };
	int whiteValid[MAX_VALID_MOVES] = { 0 };
	/*
	countPieces(pos, whitePieceCounter, blackPieceCounter);*/
	Board board(pos);
	getValidMoves(board);
	return 0;
}

void Evaluate::countPieces(string pos, int* whitePieces, int* blackPieces){
	for(unsigned int i = 0; i < pos.length(); i++)
	{
		switch (pos[i])
		{
			case B_QUEEN: 
				++blackPieces[QUEEN];
				break;
			case B_KING:
				++blackPieces[KING];
				break; 
			case B_KNIGHT:
				++blackPieces[KNIGHT];
				break;
			case B_PAWN:
				++blackPieces[PAWN];
				break;
			case B_ROOK:
				++blackPieces[ROOK];
				break;
			case B_BISHOP:
				++blackPieces[BISHOP];
				break; 
			case W_BISHOP:
				++whitePieces[BISHOP];
				break;
			case W_ROOK:
				++whitePieces[ROOK];
				break;
			case W_PAWN:
				++whitePieces[PAWN];
				break;
			case W_KING:
				++whitePieces[KING];
				break;
			case W_QUEEN:
				++whitePieces[QUEEN];
				break;
			case W_KNIGHT:
				++whitePieces[KNIGHT];
				break;
			default:
				break;
		}
	}
}

void Evaluate::getValidMoves(const Board& board) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board.getBoard()[i, j]->getType() != KNIGHT) {

			}
		}
	}
}
