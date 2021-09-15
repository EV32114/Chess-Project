#include "Piece.h"

Piece::Piece(const char type)
{
	this->_type = type;
    this->_hasMoved = false;
}

void Piece::setType(char type)
{
	this->_type = type;
}

char Piece::getType() const
{
	return this->_type;
}

int Piece::isValidMove(const int* src, const int* dest, Board& board)
{
    Piece* srcPiece = board.getBoard()[src[0]][src[1]];
    Piece* destPiece = board.getBoard()[dest[0]][dest[1]];
    bool srcColor = (isupper(srcPiece->getType())) ? WHITE : BLACK;
    bool destColor = (isupper(destPiece->getType())) ? WHITE : BLACK;

    if (srcColor != HandleGame::getCurrentPlayer() || srcPiece->getType() == EMPTY_SQUARE)
    {
        return INVALID_SRC;
    }

    if (destPiece->getType() != EMPTY_SQUARE && destColor == HandleGame::getCurrentPlayer())
    {
        return INVALID_DEST;
    }

    if (!srcPiece->isValidPieceMove(src, dest, board))
    {
        return INVALID_MOVE;
    }

    return Piece::HandleCheckCodes(board, src, dest);
}

int Piece::HandleCheckCodes(Board& board, const int* src, const int* dest)
{
    Piece* destPiece = board.getBoard()[dest[0]][dest[1]];
    int code = VALID;
    int checkValue = NO_CHECK;
    int currentPlayer = HandleGame::getCurrentPlayer();

    board.movePiece(src, dest, false);
    checkValue = board.isInCheck();

    if (currentPlayer != checkValue && checkValue != NO_CHECK)
    {
        code = CHECK;
    }
    if (currentPlayer == checkValue && checkValue != NO_CHECK)
    {
        code = SELF_CHECK;
    }
    if (checkValue == 2)
    {
        code = SELF_CHECK;
    }

    board.movePiece(dest, src, true);
    board.getBoard()[dest[0]][dest[1]] = destPiece;

    return code;
}

bool Piece::getHasMoved() const
{
    return this->_hasMoved;
}

void Piece::setHasMoved(const bool hasMoved)
{
    this->_hasMoved = hasMoved;
}
