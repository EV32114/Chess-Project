#include "Evaluate.h"

std::vector<std::string> blackMoves;
std::vector<std::string> whiteMoves;

int Evaluate::evalPos(string pos)
{
	int blackPieceCounter[6] = {0};
	int whitePieceCounter[6] = { 0 };
	int blackValid[MAX_VALID_MOVES] = { 0 };
	int whiteValid[MAX_VALID_MOVES] = { 0 };
	
	countPieces(pos, whitePieceCounter, blackPieceCounter);

	int evalWhite = evaluatePiecesMidGame(whitePieceCounter, blackPieceCounter, true);
	int evalBlack = evaluatePiecesMidGame(whitePieceCounter, blackPieceCounter, false);
	cout << "White's evaluation: \n" << evalWhite << endl;
	cout << "Black's evaluation: \n" << evalBlack << endl;

	evalWhite = evaluatePiecesEndGame(whitePieceCounter, blackPieceCounter, true);
	evalBlack = evaluatePiecesEndGame(whitePieceCounter, blackPieceCounter, false);
	cout << "White's evaluation: \n" << evalWhite << endl;
	cout << "Black's evaluation: \n" << evalBlack << endl;

	Board board(pos);
	board.printBoard();
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

void Evaluate::getValidMoves(Board& board) {
	for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
			std::vector<string> temp;
            if (std::tolower(board.getBoard()[i][j]->getType()) != '#' && !board.getBoard()[i][j]->getIsWhite()) {
				temp = board.getBoard()[i][j]->getValidMoves(new int[2]{ i, j }, board);
                blackMoves.insert(blackMoves.end(), temp.begin(), temp.end());
            }
			else if (std::tolower(board.getBoard()[i][j]->getType()) != '#' && board.getBoard()[i][j]->getIsWhite()) {
				temp = board.getBoard()[i][j]->getValidMoves(new int[2]{ i, j }, board);
				whiteMoves.insert(whiteMoves.end(), temp.begin(), temp.end());
			}
        }
    }
}

int Evaluate::evaluatePiecesMidGame(int *whitePieces, int *blackPieces, bool white) {
	int posEval = 0;

	for (int i = 0; i < 6; i++) {
		if (white) {
			switch (i) {
			case BISHOP:
				posEval += whitePieces[BISHOP] * MID_BISHOP;
				break;
			case ROOK:
				posEval += whitePieces[ROOK] * MID_ROOK;
				break;
			case PAWN:
				posEval += whitePieces[PAWN] * MID_PAWN;
				break;
			case QUEEN:
				posEval += whitePieces[QUEEN] * MID_QUEEN;
				break;
			case KNIGHT:
				posEval += whitePieces[KNIGHT] * MID_KNIGHT;
				break;
			}
		}
		else {
			switch (i) {
			case QUEEN:
				posEval += blackPieces[QUEEN] * MID_QUEEN;
				break;
			case KNIGHT:
				posEval += blackPieces[KNIGHT] * MID_KNIGHT;
				break;
			case PAWN:
				posEval += blackPieces[PAWN] * MID_PAWN;
				break;
			case ROOK:
				posEval += blackPieces[ROOK] * MID_ROOK;
				break;
			case BISHOP:
				posEval += blackPieces[BISHOP] * MID_BISHOP;
				break;
			}
		}
	}
	return posEval;
}

int Evaluate::evaluatePiecesEndGame(int* whitePieces, int* blackPieces, bool white) {
	int posEval = 0;

	for (int i = 0; i < 6; i++) {
		if (white) {
			switch (i) {
			case BISHOP:
				posEval += whitePieces[BISHOP] * END_BISHOP;
				break;
			case ROOK:
				posEval += whitePieces[ROOK] * END_ROOK;
				break;
			case PAWN:
				posEval += whitePieces[PAWN] * END_PAWN;
				break;
			case QUEEN:
				posEval += whitePieces[QUEEN] * END_QUEEN;
				break;
			case KNIGHT:
				posEval += whitePieces[KNIGHT] * END_KNIGHT;
				break;
			}
		}
		else {
			switch (i) {
			case QUEEN:
				posEval += blackPieces[QUEEN] * END_QUEEN;
				break;
			case KNIGHT:
				posEval += blackPieces[KNIGHT] * END_KNIGHT;
				break;
			case PAWN:
				posEval += blackPieces[PAWN] * END_PAWN;
				break;
			case ROOK:
				posEval += blackPieces[ROOK] * END_ROOK;
				break;
			case BISHOP:
				posEval += blackPieces[BISHOP] * END_BISHOP;
				break;
			}
		}
	}
	return posEval;
}