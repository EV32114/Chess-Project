#include "Evaluate.h"
#include <vector>
#include <iterator>

// static variables initialization
std::vector<std::string> Evaluate::blackMoves;
std::vector<std::string> Evaluate::whiteMoves;


int Evaluate::evalPos(string pos)
{
	int blackPieceCounter[6] = { 0 };
	int whitePieceCounter[6] = { 0 };
	int blackValid[MAX_VALID_MOVES] = { 0 };
	int whiteValid[MAX_VALID_MOVES] = { 0 };
	
	
	//countPieces(pos, whitePieceCounter, blackPieceCounter);

	Board board(pos);
	getValidMoves(board);
	for (std::vector<std::string>::iterator i = blackMoves.begin(); i != blackMoves.end(); i++) {
		cout << *i << endl;
	}
	for (std::vector<std::string>::iterator i = whiteMoves.begin(); i != whiteMoves.end(); i++) {
		cout << *i << endl;
	}
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
				blackMoves.push_back(std::string(1, board.getBoard()[i][j]->getType()) + ": ");
                blackMoves.insert(blackMoves.end(), temp.begin(), temp.end());
				blackMoves.push_back("\n");
            }
			else if (std::tolower(board.getBoard()[i][j]->getType()) != '#' && board.getBoard()[i][j]->getIsWhite()) {
				temp = board.getBoard()[i][j]->getValidMoves(new int[2]{ i, j }, board);
				whiteMoves.push_back(std::string(1, board.getBoard()[i][j]->getType()) + ": ");
				whiteMoves.insert(whiteMoves.end(), temp.begin(), temp.end());
				whiteMoves.push_back("\n");
			}
        }
    }
}

int Evaluate::evaluatePiecesBlack(int *blackPieces, bool midGame) {
	int posEval = 0;

	for (int i = 0; i < 6; i++) {
		switch (i) {
		case BISHOP:
			posEval += blackPieces[BISHOP] * midGame ? MID_BISHOP : END_BISHOP;
			break;
		case ROOK:
			posEval += blackPieces[ROOK] * midGame ? MID_ROOK : END_ROOK;
			break;
		case PAWN:
			posEval += blackPieces[PAWN] * midGame ? MID_PAWN : END_PAWN;
			break;
		case QUEEN:
			posEval += blackPieces[QUEEN] * midGame ? MID_QUEEN : END_QUEEN;
			break;
		case KNIGHT:
			posEval += blackPieces[KNIGHT] * midGame ? MID_KNIGHT : END_KNIGHT;
			break;
		}
	}
	return posEval;
}

int Evaluate::evaluateKingSafety(Board& board)
{

}

int Evaluate::evaluatePawnShield(int src[], Board& board)
{
	/*
		Firstly, we shall check whether the king is in a place that we need to evaluate.
		In our case, we will first check if the king is in either position 7,2 - 7,1 or 7,6.
		src[] is an array consisting of the row and column of the king respectively.
	*/
	King* tempK = (King*)(board.getBoard()[src[0]][src[1]]);
	bool _isWhite = board.getBoard()[src[0]][src[1]]->getIsWhite();
	int penalty = 0;

	if (_isWhite) {
		if (src[0] != 0) 
			return 0;
		if (src[1] != 1 && src[1] != 2 && src[1] != 6)
			return 0;
	}
	else {
		if (src[0] != 7)
			return 0;
		if (src[1] != 1 && src[1] != 2 && src[1] != 6)
			return 0;
	}

	// We check whether there's an open file
	bool openFile = true;
	for (int i = 1; i < 8; i++) {
		if (_isWhite) {
			if (board.getBoard()[src[0] - i][src[1]]->getType() == 'P' || board.getBoard()[src[0] - i][src[1]]->getType() == 'p') {
				openFile = false;
			}
		}
		else {
			if (board.getBoard()[src[0] + i][src[1]]->getType() == 'P' || board.getBoard()[src[0] + i][src[1]]->getType() == 'p') {
				openFile = false;
			}
		}
	}

	penalty += openFile ? OPEN_FILE_PENALTY : 0; 

	// We check whether there are pawns shielding the king



	return 0;
}

std::vector<Piece*> Evaluate::calcKingZone(Board& board, int src[], bool white) {
	std::vector<Piece*> vec;
	if(src[0] + 1 < 8)
		vec.push_back(board.getBoard()[src[0] + 1][src[1]]);
	if(src[1] + 1 < 8)
		vec.push_back(board.getBoard()[src[0]][src[1] + 1]);
	if(src[0] + 1 < 8 && src[1] + 1 < 8)
		vec.push_back(board.getBoard()[src[0] + 1][src[1] + 1]);
	if(src[0] - 1 >= 0)
		vec.push_back(board.getBoard()[src[0] - 1][src[1]]);
	if (src[1] - 1 >= 0)
		vec.push_back(board.getBoard()[src[0]][src[1] - 1]);
	if(src[0] - 1 >= 0 && src[1] - 1 >= 0)
		vec.push_back(board.getBoard()[src[0]][src[1] - 1]);
	if(src[0] - 1 >= 0 && src[1] + 1 < 8)
		vec.push_back(board.getBoard()[src[0] - 1][src[1] + 1]);
	if(src[0] + 1 < 8 && src[1] - 1 >= 0)
		vec.push_back(board.getBoard()[src[0] + 1][src[1] - 1]);
	if (white) {
		if (src[0] - 2 >= 0) {
			vec.push_back(board.getBoard()[src[0] - 2][src[1]]);
			if (src[1] + 1 < 8)
				vec.push_back(board.getBoard()[src[0] - 2][src[1] + 1]);
			if (src[1] - 1 >= 0)
				vec.push_back(board.getBoard()[src[0] - 2][src[1] - 1]);
		}
		if (src[0] - 3 >= 0) {
			vec.push_back(board.getBoard()[src[0] - 3][src[1]]);
			if (src[1] + 1 < 8)
				vec.push_back(board.getBoard()[src[0] - 3][src[1] + 1]);
			if (src[1] - 1 >= 0)
				vec.push_back(board.getBoard()[src[0] - 3][src[1] - 1]);
		}
		if (src[0] - 4 >= 0) {
			vec.push_back(board.getBoard()[src[0] - 4][src[1] - 1]);
			if (src[1] + 1 < 8)
				vec.push_back(board.getBoard()[src[0] - 4][src[1] + 1]);
			if (src[1] - 1 >= 0)
				vec.push_back(board.getBoard()[src[0] - 4][src[1] - 1]);
		}
	}
	else {
		if (src[0] + 2 < 8) {
			vec.push_back(board.getBoard()[src[0] + 2][src[1]]);
			if (src[1] + 1 < 8)
				vec.push_back(board.getBoard()[src[0] + 2][src[1] + 1]);
			if (src[1] - 1 >= 0)
				vec.push_back(board.getBoard()[src[0] + 2][src[1] - 1]);
		}
		if (src[0] + 3 < 8) {
			vec.push_back(board.getBoard()[src[0] + 3][src[1]]);
			if (src[1] + 1 < 8)
				vec.push_back(board.getBoard()[src[0] + 3][src[1] + 1]);
			if (src[1] - 1 >= 0)
				vec.push_back(board.getBoard()[src[0] + 3][src[1] - 1]);
		}
		if (src[0] + 4 < 8) {
			vec.push_back(board.getBoard()[src[0] + 4][src[1]]);
			if (src[1] + 1 < 8)
				vec.push_back(board.getBoard()[src[0] + 4][src[1] + 1]);
			if (src[1] - 1 >= 0)
				vec.push_back(board.getBoard()[src[0] + 4][src[1] - 1]);
		}
	}


	return vec;

}



int Evaluate::evaluatePiecesWhite(int* whitePieces, bool midGame) {
	int posEval = 0;

	for (int i = 0; i < 6; i++) {
		switch (i) {
			case BISHOP:
				posEval += whitePieces[BISHOP] * midGame ? MID_BISHOP : END_BISHOP;
				break;
			case ROOK:
				posEval += whitePieces[ROOK] * midGame ? MID_ROOK : END_ROOK;
				break;
			case PAWN:
				posEval += whitePieces[PAWN] * midGame ? MID_PAWN : END_PAWN;
				break;
			case QUEEN:
				posEval += whitePieces[QUEEN] * midGame ? MID_QUEEN : END_QUEEN;
				break;
			case KNIGHT:
				posEval += whitePieces[KNIGHT] * midGame ? MID_KNIGHT : END_KNIGHT;
				break;
		}
	}
	return posEval;
}
