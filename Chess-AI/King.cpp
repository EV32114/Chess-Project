#include "King.h"

class Piece;

using std::string;

King::King(char type, int pos1, int pos2) : Piece(type, new int[2]{pos1, pos2})
{
    this->_position[0] = pos1;
    this->_position[1] = pos2;
}

int* King::getPosition() const
{
    return (int*)this->_position;
}

void King::setPosition(const int* position)
{
    this->_position[0] = position[0];
    this->_position[1] = position[1];
}

bool King::isValidPieceMove(int* src, const int* dest, const Board& board) const
{
    int subX = src[0] - dest[0];
    int subY = src[1] - dest[1];

    if (abs(subX) > 1 || abs(subY) > 1)
    {
        return false;
    }

    return true;
}

std::vector<std::string> King::getValidMoves(int* src, const Board& board) const {
    // A king only has 8 squares to move. We'll check which squares around him are free and return an array consisting of them.
    bool isWhite = isupper(this->_type);
    int sign = isWhite ? 1 : -1;
    std::vector<std::string> validMoves;
    int nIndex = 0;
   
    /*
        This for loop goes over each possible move for the king and checks whether it is a valid move. If so, it adds it to the valid move array.
    */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (!(i == 0 && j == 0)) {
                if (src[0] - i >= 0 && src[1] - j >= 0) {
                    if (board.getBoard()[src[0] - i][src[1] - j]->getType() == EMPTY_SQUARE ||
                        ((isupper(board.getBoard()[src[0] - i][src[1] - j]->getType()) && !isWhite) || (islower(board.getBoard()[src[0] - i][src[1] - j]->getType()) && isWhite))) {
                        validMoves.push_back(std::to_string(src[0] - i) + std::to_string(src[1] - j));
                        nIndex++;
                    }
                }
                
                if (src[0] + i < 8 && src[1] + j < 8) {
                    if (board.getBoard()[src[0] + i][src[1] + j]->getType() == EMPTY_SQUARE ||
                        ((isupper(board.getBoard()[src[0] + i][src[1] + j]->getType()) && !isWhite) || (islower(board.getBoard()[src[0] + i][src[1] + j]->getType()) && isWhite))) {
                        validMoves.push_back(std::to_string(src[0] + i) + std::to_string(src[1] + j));
                        nIndex++;
                    }
                }
            }
        }
    }
    return validMoves;
}
