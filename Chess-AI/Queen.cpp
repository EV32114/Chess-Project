#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"


Queen::Queen(char type) : Piece(type)
{
}

bool Queen::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
    Rook rook('r');
    Bishop bishop('b');
    return rook.isValidPieceMove(src, dest, board) || bishop.isValidPieceMove(src, dest, board);
}

string* Queen::getValidMoves(const int* src, const int* dest, const Board& board) const {
    Rook rook('r');
    Bishop bishop('b');
    string rookArr[] = rook.getValidMoves(src, dest, board);
    string bishopArr[] = bishop.getValidMoves(src, dest, board);
    const int arrLength = sizeof(rookArr) + sizeof(bishopArr), nIndex = 0;
    bool goOverRook = true;
    string validMoves[arrLength];
    for (int i = 0; i < arrLength; i++, nIndex++) {
        if (goOverRook) {
            if (i == sizeOf(rookArr) || rookArr[nIndex] == "") {
                goOverRook = false;
                nIndex = 0;
            }
            else
                validMoves[i] = rookArr[nIndex];
        }
        else {
            if (bishopArr[nIndex] == "")
                break;
            validMoves[i] = bishopArr[nIndex];
        }
    }
}
