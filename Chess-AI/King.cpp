#include "King.h"

class Piece;

using std::string;

King::King(char type, int pos1, int pos2) : Piece(type)
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

bool King::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
    int subX = src[0] - dest[0];
    int subY = src[1] - dest[1];

    if (abs(subX) > 1 || abs(subY) > 1)
    {
        return false;
    }

    return true;
}

string* King::getValidMoves(const int* src, const Board& board) const {
    // A king only has 8 squares to move. We'll check which squares around him are free and return an array consisting of them.
    string* validMoves = new string[NUM_OF_MOVES]{ "" };
    int nIndex = 0;
    //while (true){
    //    if (board.getBoard()[src[0] - i][src[1] - j]->getType() == EMPTY_SQUARE) {
    //        validMoves[nIndex] = to_string(i) + to_string(j);
    //        nIndex++;
    //    }
    //    if (board.getBoard()[src[0] + i][src[1] + j]->getType() == EMPTY_SQUARE) {
    //        validMoves[nIndex] = to_string(i) + to_string(j);
    //        nIndex++;
    //    }
    //    if (i == 0) // ensuring we get j = 1 i = 0, j = -1 i = 0, i == 1 j == 1, i == -1 j == -1
    //        i += 1; 
    //    if (j == 1 && i == 1) // ensuring we also get i = 1 j = 0, i = -1 j = 0
    //        j -= 1;
    //    if (j == 0 && i == 1) // if we went over all the possibilities, we break.
    //        break;
    //}
   
    /*
        This for loop goes over each possible move for the king and checks whether it is a valid move. If so, it adds it to the valid move array.
    */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (!(i == 0 && j == 0)) {
                if (board.getBoard()[src[0] - i][src[1] - j]->getType() == EMPTY_SQUARE) {
                    validMoves[nIndex] = std::to_string(src[0] - i) + std::to_string(src[1] - j);
                    nIndex++;
                }
                if (board.getBoard()[src[0] + i][src[1] + j]->getType() == EMPTY_SQUARE) {
                    validMoves[nIndex] = std::to_string(src[0] + i) + std::to_string(src[1] + j);
                    nIndex++;
                }
            }
        }
    }
    return validMoves;
}
