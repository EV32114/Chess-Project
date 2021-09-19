#include "Rook.h"
class HandleGame;


Rook::Rook(char type) : Piece(type)
{
}

bool Rook::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
    int tempSrc[BOARD_INDEX] = { src[0], src[1] };
    int tempDest[BOARD_INDEX] = { dest[0], dest[1] };

    if (tempSrc[0] != tempDest[0] && tempSrc[1] != tempDest[1]) // If the rook is not going straight
    {
        return false;
    }

    if (tempSrc[0] == tempDest[0]) // If the rook is going right or left
    {
        if (tempDest[1] < tempSrc[1])
        {
            std::swap(tempSrc[1], tempDest[1]);
        }

        for (int i = tempSrc[1] + 1; i < tempDest[1]; i++)
        {
            if (board.getBoard()[tempSrc[0]][i]->getType() != EMPTY_SQUARE) // If the rook is trying to pass a piece
            {
                return false;
            }
        }
    }
    else // If the rook is going up or down
    {
        if (tempDest[0] < tempSrc[0])
        {
            std::swap(tempSrc[0], tempDest[0]);
        }

        for (int i = tempSrc[0] + 1; i < tempDest[0]; i++)
        {
            if (board.getBoard()[i][tempSrc[1]]->getType() != EMPTY_SQUARE) // If the rook is trying to pass a piece
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<string> Rook::getValidMoves(const int* src, const Board& board) const {
    std::vector<string> validMoves;
    bool breakFlag = false;
    for (size_t i = 0; i < 4; i++)
    {
        breakFlag = false;
        for (size_t j = 0; j < BOARD_SIDE && !breakFlag; j++)
        {
            switch (i)
            {
            case 0:
                if (src[1] + j < 8)
                {
                    if (board.getBoard()[src[0]][src[1] + j]->getType() == EMPTY_SQUARE || board.getBoard()[src[0]][src[1] + j]->getIsWhite() != this->getIsWhite())
                    {
                        validMoves.push_back(std::to_string(src[0]) + std::to_string(src[1] + j));
                    }
                    else {
                        breakFlag = true;
                        break;
                    }
                }
                else {
                    breakFlag = true;
                    break;
                }
                break;
            case 1:
                if (src[1] - j < 8)
                {
                    if (board.getBoard()[src[0]][src[1] - j]->getType() == EMPTY_SQUARE || board.getBoard()[src[0]][src[1] - j]->getIsWhite() != this->getIsWhite())
                    {
                        validMoves.push_back(std::to_string(src[0]) + std::to_string(src[1] - j));
                    }
                    else {
                        breakFlag = true;
                        break;
                    }
                }
                else {
                    breakFlag = true;
                    break;
                }
                break;
            case 2:
                if (src[0] + j < 8)
                {
                    if (board.getBoard()[src[0] + j][src[1]]->getType() == EMPTY_SQUARE || board.getBoard()[src[0] + j][src[1]]->getIsWhite() != this->getIsWhite())
                    {
                        validMoves.push_back(std::to_string(src[0] + j) + std::to_string(src[1]));
                    }
                    else {
                        breakFlag = true;
                        break;
                    }
                }
                else {
                    breakFlag = true;
                    break;
                }
                break;
            case 3:
                if (src[0] - j < 8)
                {
                    if (board.getBoard()[src[0] - j][src[1]]->getType() == EMPTY_SQUARE || board.getBoard()[src[0] - j][src[1]]->getIsWhite() != this->getIsWhite())
                    {
                        validMoves.push_back(std::to_string(src[0] - j) + std::to_string(src[1]));
                    }
                    else {
                        breakFlag = true;
                        break;
                    }
                }
                else {
                    breakFlag = true;
                    break;
                }
                break;
            default:
                break;
            }
        }
    }

    return validMoves;
}
