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

int Evaluate::evaluatePiecePositions(Board& board, bool white)
{
	int eval = 0;
	for (int i = 0; i < BOARD_SIDE; i++) {
		for (int j = 0; j < BOARD_SIDE; j++) {
			if (board.getBoard()[i][j]->getIsWhite()) {
				if (white) {
					switch (board.getBoard()[i][j]->getType()) {
					case 'P':
						eval += pawnTable[i][j];
					case 'B':
						eval += bishopTable[i][j];
					case 'N':
						eval += knightTable[i][j];
					case 'K':
						// TODO: SEPERATE END GAME 
						eval += kingTable[i][j];
					}
				}
			}
			else {
				if (!white) {
					int row = calculateBlackIndex(i);
					switch (board.getBoard()[i][j]->getType()) {
					case 'P':
						eval += pawnTable[row][j];
					case 'B':
						eval += bishopTable[row][j];
					case 'N':
						eval += knightTable[row][j];
					case 'K':
						// TODO: SEPERATE END GAME 
						eval += kingTable[row][j];
					}
				}
			}	
		}
	}
	return eval;
}

int Evaluate::evaluateKingSafety(Board& board)
{
	return 0;
}

bool Evaluate::isUnderAttack(Board& board, int src[])
{
	bool _isWhite = board.getBoard()[src[0]][src[1]]->getIsWhite();
	std::vector<std::string> enemyValidMoves = _isWhite ? blackMoves : whiteMoves;
	for (std::vector<std::string>::iterator i = enemyValidMoves.begin(); i != enemyValidMoves.end(); i++) {
		if ((std::to_string(src[0]) + std::to_string(src[1])) == *i) {
			return true;
		}
	}
	return false;
}

/*
	This function returns the adjusted index of the Piece-Square table for the black side.
	The tables are symmetrical, therefore we only need to change the row and adjust it to it's opposite row.
	From selected examples:
	7-0, 6-1, 5-2, etc.
	we can see a clear pattern of 7 (max row index) - the row number being the desired result.
	@params: src[], a sized array containing the position using the format row, col
	@returns: adjusted src[].
*/
int Evaluate::calculateBlackIndex(int row)
{
	return MAX_ROW_INDEX - row;
}

int Evaluate::evaluatePawnShield(int src[], Board& board)
{
	/*
		Firstly, we shall check whether the king is in a place that we need to evaluate.
		In our case, we will first check if the king is in either position 7,2 - 7,1 or 7,6.
		src[] is an array consisting of the row and column of the king respectively.
	*/
	bool _isWhite = board.getBoard()[src[0]][src[1]]->getIsWhite();
	char validPawn = _isWhite ? 'P' : 'p';
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
	int pawnCount = 0;
	std::vector<Piece*> kingZone = calcKingZone(board, src, _isWhite);
	for (std::vector<Piece*>::iterator i = kingZone.begin(); i != kingZone.end(); i++) {
		char currentPiece = (*i)->getType();
		if (currentPiece == validPawn)
			pawnCount += 1;
	}

	// Calculate using adjusted numbers.
	return pawnCount;
}

int Evaluate::attackKingZone(Board& board, bool white)
{
	getValidMoves(board); // TEMP
	int attackingPiecesCount = 0, valueOfAttack = 0;
	const int KNIGHT_VAL = 20, BISHOP_VAL = 20, ROOK_VAL = 40, QUEEN_VAL = 80;
	const int attackWeight[7] = { 0, 50, 75, 88, 94, 97, 99 };
	std::vector<std::string>::iterator attacker;
	std::vector<Piece*> kingZone = calcKingZone(board, white ? board.getWhiteKing()->getPosition() : board.getBlackKing()->getPosition(), white);
	for (std::vector<Piece*>::iterator it = kingZone.begin(); it != kingZone.end(); it++)
	{
		if (!white)
		{
			attacker = std::find_if(whiteMoves.begin(), whiteMoves.end(), [&](std::string s1) {return s1.find(std::to_string((*it)->getPos()[1])) != std::string::npos; });
		}
		else
		{
			attacker = std::find_if(blackMoves.begin(), blackMoves.end(), [&](std::string s1) {return s1.find(std::to_string((*it)->getPos()[1])) != std::string::npos; });
		}
		if ((!white && attacker != whiteMoves.end()) || (white && attacker != blackMoves.end()))
		{
			char type = board.getBoard()[std::stoi((*attacker).substr(0, 1))][std::stoi((*attacker).substr(1, 1))]->getType();
			attackingPiecesCount++;
			switch (type)
			{
			case B_QUEEN:
			case W_QUEEN:
				valueOfAttack += QUEEN_VAL;
				break;
			case B_BISHOP:
			case W_BISHOP:
				valueOfAttack += BISHOP_VAL;
				break;
			case B_ROOK:
			case W_ROOK:
				valueOfAttack += ROOK_VAL;
				break;
			case B_KNIGHT:
			case W_KNIGHT:
				valueOfAttack += KNIGHT_VAL;
			default:
				break;
			}
		}
	}

	return valueOfAttack * attackWeight[attackingPiecesCount] / 100;
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
