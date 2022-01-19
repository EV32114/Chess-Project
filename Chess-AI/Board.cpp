#include "Board.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Knight.h"
#include "Piece.h"
#include "EmptySquare.h"
#include <string>

Board::Board(std::string strBoard)
{
    int segmentCounter = 0;
    int rowCounter = 0;
    int columnCounter = 0;

    this->_blackKing = 0;
    this->_whiteKing = 0;

  for (int i = 0; i < BOARD_SIDE; i++)
  {
    this->_board[i] = new Piece*[BOARD_SIDE];
  }

  for (size_t i = 0; i < strBoard.length(); i++)
  {
      if (strBoard[i] == ' ')
      {
          segmentCounter++;
      }
      else if (strBoard[i] == '/')
      {
          rowCounter++;
          columnCounter = 0;
      }
      else
      {
          switch (segmentCounter)
          {
          case 0:
          {
              switch (strBoard[i])
              {
              case B_KING:
              {
                  this->_blackKing = new King(strBoard[i], rowCounter, columnCounter);
                  this->_board[rowCounter][columnCounter] = new King(strBoard[i], rowCounter, columnCounter);
                  break;
              }
              case W_KING:
              {
                  this->_whiteKing = new King(strBoard[i], rowCounter, columnCounter);
                  this->_board[rowCounter][columnCounter] = new King(strBoard[i], rowCounter, columnCounter);
                  break;
              }
              case B_QUEEN:
              case W_QUEEN:
                  this->_board[rowCounter][columnCounter] = new Queen(strBoard[i], new int[2]{rowCounter, columnCounter});
                  break;
              case B_BISHOP:
              case W_BISHOP:
                  this->_board[rowCounter][columnCounter] = new Bishop(strBoard[i], new int[2]{ rowCounter, columnCounter });
                  break;
              case B_PAWN:
              case W_PAWN:
                  this->_board[rowCounter][columnCounter] = new Pawn(strBoard[i], new int[2]{ rowCounter, columnCounter });
                  break;
              case B_ROOK:
              case W_ROOK:
                  this->_board[rowCounter][columnCounter] = new Rook(strBoard[i], new int[2]{ rowCounter, columnCounter });
                  break;
              case B_KNIGHT:
              case W_KNIGHT:
                  this->_board[rowCounter][columnCounter] = new Knight(strBoard[i], new int[2]{ rowCounter, columnCounter });
                  break;
              default:
              {
                  if (std::isdigit(strBoard[i]))
                  {
					  for (short j = columnCounter; j < columnCounter + (strBoard[i] - '0'); j++)
					  {
						  this->_board[rowCounter][j] = new EmptySquare('#', new int[2]{ rowCounter, j });
					  }
                      columnCounter += (strBoard[i] - '0') - 1;
                  }
                  break;
              }
              }
              break;
          }
          case 1:
          {
              this->nextTurnWhite = (strBoard[i] == 'w');
              break;
          }
          case 2:
		  {
			  if (strBoard[i] == '-') {
				  this->castleBlackKing = false;
				  this->castleBlackQueen = false;
				  this->castleWhiteKing = false;
				  this->castleWhiteQueen = false;
			  }
			  else if (strBoard[i] == 'K')
				  this->castleWhiteKing = true;
			  else if (strBoard[i] == 'Q') {
				  this->castleWhiteQueen = true;
			  }
			  else if (strBoard[i] == 'k') {
				  this->castleBlackKing = true;
			  }
			  else if (strBoard[i] == 'q') {
				  this->castleBlackQueen = true;
			  }
              break;
          }
          case 3:
          {
			  if (strBoard[i] == '-') {
				  break;
			  }
			  else {
				  this->enPassantSquare = this->convertIndex(std::to_string(strBoard[i]) + std::to_string(strBoard[i + 1]));
			  }
              break;
          }
          case 4:
          {
              this->halfMove = (strBoard[i] - '0');
              break;
          }
          case 5:
          {
              this->fullMove = (strBoard[i] - '0');
              break;
          }
          default:
              break;
          }
          columnCounter++;
      }

  }
}

Board::~Board()
{
  for (int i = 0; i < BOARD_SIDE; i++)
  {
    for (int j = 0; j < BOARD_SIDE; j++)
    {
      delete this->_board[i][j];
    }
    delete[] this->_board[i];
  }
}

void Board::printBoard() const
{
  std::cout << "The board:" << std::endl;
  for (int i = 0; i < BOARD_SIDE; i++)
  {
    for (int j = 0; j < BOARD_SIDE; j++)
    {
      std::cout << this->_board[i][j]->getType() << " ";
    }
    std::cout << "\n";
  }
}

Piece*** Board::getBoard() const
{
  return (Piece***)this->_board;
}

King* Board::getBlackKing() const
{
  return this->_blackKing;
}

King* Board::getWhiteKing() const
{
  return this->_whiteKing;
}

void Board::undoMove(std::string move){
    int *src;
    int *dst;
    dst = Board::convertIndex(move.substr(0, 2));
	src = Board::convertIndex(move.substr(2, 2));

    this.movePiece(src, dst, board.getBoard()[dst[0]][dst[1]]->getType() != EMPTY_SQUARE);
}

void Board::movePiece(int* src, const int* dest, bool toDelete)
{
  char srcChar = this->_board[src[0]][src[1]]->getType();
  if (toDelete)
  {
    delete this->_board[dest[0]][dest[1]];
  }
  this->_board[dest[0]][dest[1]] = this->_board[src[0]][src[1]];
  this->_board[dest[0]][dest[1]]->setHasMoved(true);
  this->_board[dest[0]][dest[1]]->setPos(dest);
  this->_board[src[0]][src[1]] = new EmptySquare(EMPTY_SQUARE, src);

  if (srcChar == B_KING)
  {
    this->_blackKing->setPosition(dest);
  }
  else if (srcChar == W_KING)
  {
    this->_whiteKing->setPosition(dest);
  }
}

int* Board::convertIndex(std::string strIndex)
{
  int* index = new int[BOARD_INDEX];

  index[0] = (int)strIndex[1] - '0';
  index[0] = index[0] + (BOARD_SIDE - 2 * index[0]);
  index[1] = (int)strIndex[0] - FIRST_LETTER;

  return index;
}


int Board::isInCheck() const
{
  int i = 0, j = 0;
  bool blackInCheck = false, whiteInCheck = false;
  int currPos[BOARD_INDEX] = { 0 };
  int returnValue = 0;
  int* kingToCheck = nullptr;
  bool checkWhiteKing = false;
  Piece* piece;

  for (i = 0; i < BOARD_SIDE; i++)
  {
    for (j = 0; j < BOARD_SIDE; j++)
    {
      piece = this->_board[i][j];
      if (piece->getType() != EMPTY_SQUARE)
      {
        currPos[0] = i;
        currPos[1] = j;
        if (islower(piece->getType()))
        {
          checkWhiteKing = true;
          kingToCheck = this->_whiteKing->getPosition();
        }
        else
        {
          checkWhiteKing = false;
          kingToCheck = this->_blackKing->getPosition();
        }

        if (piece->isValidPieceMove(currPos, kingToCheck, *this))
        {
          if (checkWhiteKing)
          {
            whiteInCheck = true;
          }
          else
          {
            blackInCheck = true;
          }
        }
      }
    }
  }

  if (blackInCheck && whiteInCheck)
  {
    return 2;
  }
  else if (whiteInCheck)
  {
    return WHITE_IN_CHECK;
  }
  else if (blackInCheck)
  {
    return BLACK_IN_CHECK;
  }
  return -1;
}

int Board::isInMate(bool playerInCheck)
{   
    int i, j;
    int *src;
    int *dst;
    
    // Get the position of the king.
    for(i = 0; i < BOARD_SIDE; i++){
        for(j = 0; j < BOARD_SIDE; j++){
            char pieceType = this->_board[i][j]->getType();
            if(playerInCheck == isupper(pieceType) && std::tolower(pieceType) == 'k'){
                goto found;
            }
        }
    }

found:
    std::vector<std::string> enemyMoves = playerInCheck == BLACK ? Evaluate::whiteMoves : Evaluate::blackMoves;
    int moveCnt = 0;
    for(std::vector<std::string>::iterator iter = enemyMoves.begin(); iter != enemyMoves.end(); iter++){
        src = Board::convertIndex(*iter.substr(0, 2));
	    dst = Board::convertIndex(*iter.substr(2, 2));
        if(this->_board.getBoard()[i][j]->isValidPieceMove(src, dst, this))){
            moveCnt++;
        }
    }
    return moveCnt == 8 ? CHECKMATE : CHECK;
}

int Board::castle(const int* src, const int* dest)
{
  /*Piece* rook = this->_board[0][0];
  int rookSrc[BOARD_INDEX] = { 0 };
  int rookDest[BOARD_INDEX] = { 0 };
  bool srcColor = (isupper(this->_board[src[0]][src[1]]->getType())) ? WHITE : BLACK;

  if (HandleGame::getCurrentPlayer() != srcColor || this->_board[src[0]][src[1]]->getType() == EMPTY_SQUARE)
  {
    return INVALID_SRC;
  }


  if (dest[0] == 7 && dest[1] == 2) // white queen side
  {
    if (this->_board[7][0]->getType() == EMPTY_SQUARE || !checkBottomLeft())
    {
      return INVALID_MOVE;
    }

    rook = this->_board[7][0];
    rookSrc[0] = 7;
    rookSrc[1] = 0;
    rookDest[0] = 7;
    rookDest[1] = 3;
  }
  else if (dest[0] == 7 && dest[1] == 6) // white king side
  {
    if (this->_board[7][7]->getType() == EMPTY_SQUARE || !checkBottomRight())
    {
      return INVALID_MOVE;
    }

    rook = this->_board[7][7];
    rookSrc[0] = 7;
    rookSrc[1] = 7;
    rookDest[0] = 7;
    rookDest[1] = 5;
  }
  else if (dest[0] == 0 && dest[1] == 2) // black queen side
  {
    if (this->_board[0][0]->getType() == EMPTY_SQUARE || !checkTopLeft())
    {
      return INVALID_MOVE;
    }

    rook = this->_board[0][0];
    rookSrc[0] = 0;
    rookSrc[1] = 0;
    rookDest[0] = 0;
    rookDest[1] = 3;
  }
  else if (dest[0] == 0 && dest[1] == 6) // black king side
  {
    if (this->_board[0][7]->getType() == EMPTY_SQUARE || !checkTopRight())
    {
      return INVALID_MOVE;
    }

    rook = this->_board[0][7];
    rookSrc[0] = 0;
    rookSrc[1] = 7;
    rookDest[0] = 0;
    rookDest[1] = 5;
  }

  if (this->_board[src[0]][src[1]]->getHasMoved() || rook->getHasMoved() || this->isInCheck() != -1)
  {
    return INVALID_MOVE;
  }

  movePiece(rookSrc, rookDest, true);
  return CASTLE;*/
    return 0;
}

/*bool Board::checkBottomLeft()
{
  int square1[BOARD_INDEX] = { 7, 1 };
  int square2[BOARD_INDEX] = { 7, 2 };
  int square3[BOARD_INDEX] = { 7, 3 };

  if (this->_board[7][1]->getType() != EMPTY_SQUARE || this->_board[7][2]->getType() != EMPTY_SQUARE || this->_board[7][3]->getType() != EMPTY_SQUARE)
  {
    return false;
  }
  if (isUnderAttack(square1, false) || isUnderAttack(square2, false) || isUnderAttack(square3, false))
  {
    return false;
  }
  return true;
}

bool Board::checkBottomRight()
{
  int square1[BOARD_INDEX] = { 7, 5 };
  int square2[BOARD_INDEX] = { 7, 6 };

  if (this->_board[7][5]->getType() != EMPTY_SQUARE || this->_board[7][6]->getType() != EMPTY_SQUARE)
  {
    return false;
  }
  if (isUnderAttack(square1, false) || isUnderAttack(square2, false))
  {
    return false;
  }
  return true;
}

bool Board::checkTopLeft()
{
  int square1[BOARD_INDEX] = { 0, 1 };
  int square2[BOARD_INDEX] = { 0, 2 };
  int square3[BOARD_INDEX] = { 0, 3 };

  if (this->_board[0][1]->getType() != EMPTY_SQUARE || this->_board[0][2]->getType() != EMPTY_SQUARE || this->_board[0][3]->getType() != EMPTY_SQUARE)
  {
    return false;
  }
  if (isUnderAttack(square1, true) || isUnderAttack(square2, true) || isUnderAttack(square3, true))
  {
    return false;
  }
  return true;
}

bool Board::checkTopRight()
{
  int square1[BOARD_INDEX] = { 0, 5 };
  int square2[BOARD_INDEX] = { 0, 6 };

  if (this->_board[0][5]->getType() != EMPTY_SQUARE || this->_board[0][6]->getType() != EMPTY_SQUARE)
  {
    return false;
  }
  if (isUnderAttack(square1, true) || isUnderAttack(square2, true))
  {
    return false;
  }
  return true;
}

bool Board::isUnderAttack(const int* pos, bool isWhite)
{
  int i = 0, j = 0;
  int src[BOARD_INDEX] = { 0 };

  for (i = 0; i < BOARD_SIDE; i++)
  {
    for (j = 0; j < BOARD_SIDE; j++)
    {
      src[0] = i;
      src[1] = j;

      if (isWhite && isupper(this->getBoard()[i][j]->getType()))
      {
        if (this->_board[i][j]->isValidPieceMove(src, pos, *this))
        {
          return true;
        }
      }
      else if (!isWhite && islower(this->getBoard()[i][j]->getType()))
      {
        if (this->_board[i][j]->isValidPieceMove(src, pos, *this))
        {
          return true;
        }
      }
    }
  }
  return false;
}

bool Board::canMove(Piece& piece, int srcX, int srcY)
{
  int i = 0, j = 0;
  int src[BOARD_INDEX] = { srcX, srcY };
  int dest[BOARD_INDEX] = { 0 };

  for (i = 0; i < BOARD_SIDE; i++)
  {
    for (j = 0; j < BOARD_SIDE; j++)
    {
      dest[0] = i;
      dest[1] = j;

      if (piece.isValidMove(src, dest, *this) == VALID || piece.isValidMove(src, dest, *this) == CHECK)
      {
        return true;
      }
    }
  }

  return false;
}*/
